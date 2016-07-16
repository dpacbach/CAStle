#include <string>
#include <stdexcept>
#include <cstdlib>
#include <memory>
#include <vector>

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

//== CAS Machinery =====================================================

const int sigFigs = 100;
typedef DS::Numbers::Float                        FloatType;
typedef CAS::Numbers::NumberDouble<FloatType>     NumberImp;

std::shared_ptr<Tokens::ScannerBuilder> scannerBuilder_ptr  (new Tokens::ScannerBuilders::Simple);
std::shared_ptr<Tokens::Tokenizer>      tokenizer_ptr       (new Tokens::Tokenizer);
std::shared_ptr<NumberFactory>          nFactory_ptr        (new NumberFactoryPrototype(Proxy::NumberP(new NumberImp())));
std::shared_ptr<NumberFormatter>        nFormatter_ptr      (new NumberFormatterStandard(nFactory_ptr, scannerBuilder_ptr, sigFigs));
std::shared_ptr<Builder>                eBuilder_ptr        (new Builders::Standard);
std::shared_ptr<Parser>                 parser_ptr          (new Parsers::Infix(scannerBuilder_ptr, eBuilder_ptr, nFormatter_ptr, tokenizer_ptr));

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

auto input( std::string const& expString ) -> std::string
{
    Expression::Ptr exp = parser_ptr->parse(expString);
    if (!exp)
    {
        return std::string();
        /*cout << "  ";
        for (std::string::const_iterator it = expString.begin(); it != parser_ptr->getStopLocation(); ++it)
            cout << " ";
        cout << "^---Syntax Error!" << endl;
        continue;*/
    }

    auto exp_simp = simplify( exp );

    Render::Infixs::CharMap map(nFormatter_ptr);
    map.visitExpression(exp);
    std::vector<std::string> grid = map.result().vectorOfStrings();

    Render::Infixs::String s(nFormatter_ptr);
    s.visitExpression(exp);
    std::string infix = s.result();

    return std::string();
}

auto evalutate( Expression::Ptr exp ) -> std::string
{
    NumEval eval;
    if ( !eval.visitExpression( exp ) )
        return std::string();

    Proxy::NumberP result = eval.result();
    if ( result.isRealPartInteger() && result.isImaginaryPartInteger() )
        return std::string();

    auto realPart      = nFormatter_ptr->formatRealPart(result);
    auto imaginaryPart = nFormatter_ptr->formatImaginaryPart(result);

    if (imaginaryPart ==  "1") imaginaryPart =   "i";
    if (imaginaryPart == "-1") imaginaryPart =  "-i";
    if (imaginaryPart !=  "0") imaginaryPart +=  "i";

    if (imaginaryPart == "0") return realPart;
    if (realPart      == "0") return imaginaryPart;

    result.exchangeRealAndImaginary();
    result.makeRealPart();
    return realPart + ( result.isPositiveReal() ? "+" : "" ) + imaginaryPart;
}
