#include <string>
#include <stdexcept>
#include <cstdlib>
#include <memory>
#include <vector>
#include <string.h>

#include "Float.hpp"
#include "Expression.hpp"
#include "Visitor.hpp"
#include "Restructurer.hpp"
#include "Substitution.hpp"
#include "Composite.hpp"
#include "Renderer.hpp"
#include "ASCIITree.hpp"
#include "Basic.hpp"
#include "String.hpp"
#include "CharMap.hpp"
#include "ScannerBuilder.hpp"
#include "Simple.hpp"
#include "Tokenizer.hpp"
#include "Token.hpp"
#include "NumberFactory.hpp"
#include "NumberFactoryPrototype.hpp"
#include "NumberFormatter.hpp"
#include "NumberFormatterStandard.hpp"
#include "NumberProxy.hpp"
#include "NumberDouble.hpp"
#include "Standard.hpp"
#include "Parser.hpp"
#include "parsers/Infix.hpp"
#include "rendering/Infix.hpp"
#include "NumEval.hpp"

#include "icalcterm/icalcterm.h"

using namespace DS;
using namespace DS::CAS;
using namespace DS::CAS::Numbers;
using namespace DS::CAS::Expressions;
using namespace DS::CAS::Expressions::Visitors;
using namespace DS::CAS::Expressions::Visitors::Restructurers::Reduction;

/*
template<typename T>
void reduce(Expression::Ptr&);
ostream& operator<< (ostream& out, Expression::Ptr);
*/

// ===============================================================
// Configuration
// ===============================================================

const int sigFigs = 100;
typedef DS::Numbers::Float                        FloatType;
typedef CAS::Numbers::NumberDouble<FloatType>     NumberImp;

std::shared_ptr<Tokens::ScannerBuilder> scannerBuilder_ptr  (new Tokens::ScannerBuilders::Simple);
std::shared_ptr<Tokens::Tokenizer>      tokenizer_ptr       (new Tokens::Tokenizer);
std::shared_ptr<NumberFactory>          nFactory_ptr        (new NumberFactoryPrototype(Proxy::NumberP(new NumberImp())));
std::shared_ptr<NumberFormatter>        nFormatter_ptr      (new NumberFormatterStandard(nFactory_ptr, scannerBuilder_ptr, sigFigs));
std::shared_ptr<Builder>                eBuilder_ptr        (new Builders::Standard);
std::shared_ptr<Parser>                 parser_ptr          (new Parsers::Infix(scannerBuilder_ptr, eBuilder_ptr, nFormatter_ptr, tokenizer_ptr));

// ===============================================================
// Reduction
// ===============================================================

template<typename T>
auto reduce( Expression::Ptr& exp ) -> Expression::Ptr
{
    auto visitor = std::make_unique<T>( nFactory_ptr, eBuilder_ptr );
    auto success = visitor->visitExpression(exp);
    if ( !success )
        throw std::logic_error("success == false in reduce()");
    return visitor->result();
}

auto simplify( Expression::Ptr exp ) -> Expression::Ptr
{
    Expression::Ptr res;
    res = reduce<BasicSymbols>(exp);
    res = reduce<ComplexSplitter>(res);
    res = reduce<Rationalizer>(res);

    for (int k = 0; k < 20; k++)
    {
        res = reduce<ComplexNormalizer>(res);
        res = reduce<GCDLiteral>(res);
        res = reduce<SizeOneArray>(res);
        res = reduce<SelfNesting>(res);
        res = reduce<Negatives>(res);
        res = reduce<FirstOrderBasic>(res);
        res = reduce<NumberReducerBasic>(res);
    }

    res = reduce<ComplexExpander>(res);
    res = reduce<ComplexSplitter>(res);
    res = reduce<ComplexNormalizer>(res);
    res = reduce<GCDLiteral>(res);
    res = reduce<SizeOneArray>(res);
    res = reduce<SelfNesting>(res);
    res = reduce<Negatives>(res);

    return res;
}

// ===============================================================
// Rendering
// ===============================================================

struct Rendered {
    Rendered() { }
    Rendered( std::string const& s )
        : one_line( s )
        , grid( {s} )
    { }
    std::string one_line;
    std::vector<std::string> grid;
    Rendered(Rendered const& rendered) {
        throw std::logic_error("Inside Rendered copy constructor!");
    }
    Rendered const& operator=( Rendered const& rendered ) {
        throw std::logic_error("Inside Rendered assignment operator!");
    }
};

auto render( Expression::Ptr exp ) -> Rendered
{
    Rendered res;

    Render::Infixs::CharMap map(nFormatter_ptr);
    map.visitExpression(exp);
    res.grid = map.result().vectorOfStrings();

    Render::Infixs::String s(nFormatter_ptr);
    s.visitExpression(exp);
    res.one_line = s.result();

    return res;
}

auto render( Proxy::NumberP const& _n ) -> Rendered
{
    Proxy::NumberP n = _n;
    //if ( result.isRealPartInteger() && result.isImaginaryPartInteger() )
    //    return MaybeNumber();

    auto realPart      = nFormatter_ptr->formatRealPart(n);
    auto imaginaryPart = nFormatter_ptr->formatImaginaryPart(n);

    if (imaginaryPart ==  "1") imaginaryPart =   "i";
    if (imaginaryPart == "-1") imaginaryPart =  "-i";
    if (imaginaryPart !=  "0") imaginaryPart +=  "i";

    if (imaginaryPart == "0") return Rendered( realPart );
    if (realPart      == "0") return Rendered( imaginaryPart );

    n.exchangeRealAndImaginary();
    n.makeRealPart();
    return Rendered( realPart + ( n.isPositiveReal() ? "+" : "" ) + imaginaryPart );
}

// ===============================================================
// Parsing
// ===============================================================

auto parse( std::string const& expString ) -> Expression::Ptr
{
    Expression::Ptr exp = parser_ptr->parse(expString);
    if (!exp)
    {
        return Expression::Ptr();
        /*cout << "  ";
        for (std::string::const_iterator it = expString.begin(); it != parser_ptr->getStopLocation(); ++it)
            cout << " ";
        cout << "^---Syntax Error!" << endl;
        continue;*/
    }
    return exp;
}

// ===============================================================
// Numerical Evaluation
// ===============================================================

struct MaybeNumber {
    typedef Proxy::NumberP JustType;
    MaybeNumber() : nothing( true )
                  , data( nFactory_ptr->zero() )
    { }
    MaybeNumber( JustType just ) : nothing( false )
                                 , data( just )
    { }
    operator bool() { return !nothing; }
    bool nothing;
    JustType data;
};

auto evaluate( Expression::Ptr exp ) -> MaybeNumber
{
    NumEval eval;
    if ( !eval.visitExpression( exp ) )
        return MaybeNumber();

    return MaybeNumber( eval.result() );
}

// ===============================================================
// icalcterm interface
// ===============================================================

extern "C" {

void CI_init( CI_Config* ) { }

void CI_config( CI_Config* ) { }

static CI_ResultComponent component( Rendered const& r )
{
    CI_ResultComponent res;
    res.one_line = strdup( r.one_line.c_str() );
    res.grid_rows = r.grid.size();
    res.grid = new char*[r.grid.size()];
    for( size_t i = 0; i < r.grid.size(); ++i )
        res.grid[i] = strdup( r.grid[i].c_str() );
    return res;
}

CI_Result* CI_submit( char const* _input )
{
    CI_Result* res = new CI_Result;

    Expression::Ptr input = parse( std::string( _input ) );
    if( !input )
        return NULL;
    Expression::Ptr output = simplify( input );
    MaybeNumber n_may = evaluate( output );

    Rendered r_input  = render( input );
    Rendered r_output = render( output );
    Rendered r_num    = n_may ? render( n_may.data )
                              : Rendered();

    res->input       = component( r_input );

    res->num_outputs = n_may ? 2 : 1;
    res->outputs     = new CI_ResultComponent[res->num_outputs];
    res->outputs[0]  = component( r_output );

    if( n_may )
        res->outputs[1] = component( r_num );

    return res;
}

static void component_free( CI_ResultComponent& comp )
{
    free( comp.one_line );

    for( int i = 0; i < comp.grid_rows; ++i )
        free( comp.grid[i] );

    delete[] comp.grid;
}

void CI_result_free( CI_Result* result )
{
    if( !result )
        return;

    component_free( result->input );

    for( int i = 0; i < result->num_outputs; ++i )
        component_free( result->outputs[i] );

    delete[] result->outputs;

    delete result;
}

} // extern "C"
