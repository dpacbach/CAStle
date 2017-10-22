//============================================================================
// Name        : CAS.cpp
//============================================================================

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <map>
#include <stdexcept>
#include <cstdlib>

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
#include "DefaultParsers.hpp"
#include "Tokenizer.hpp"
#include "Token.hpp"
#include "NumberFactory.hpp"
#include "NumberFactoryPrototype.hpp"
#include "NumberFormatter.hpp"
#include "NumberFormatterStandard.hpp"
#include "NumberProxy.hpp"
#include "NumberDouble.hpp"
#include "Standard.hpp"
#include "parser.hpp"
#include "infix-parser.hpp"
#include "InfixRender.hpp"
#include "NumEval.hpp"

using namespace std;
using namespace DS;
using namespace DS::CAS;
using namespace DS::CAS::Numbers;
using namespace DS::CAS::Expressions;
using namespace DS::CAS::Expressions::Visitors;
using namespace DS::CAS::Expressions::Visitors::Restructurers::Reduction;

template<typename T>
void reduce(ExprConstSP&);
ostream& operator<< (ostream& out, ExprConstSP);

//== CAS Machinery =====================================================

int const columns = 65;
const int sigFigs = 100;
typedef DS::Numbers::Float                        FloatType;
typedef CAS::Numbers::NumberDouble<FloatType>     NumberImp;

std::shared_ptr<Tokens::ScannerBuilder> scannerBuilder_ptr  (new Tokens::ScannerBuilders::Simple);
std::shared_ptr<Tokens::Tokenizer>      tokenizer_ptr       (new Tokens::Tokenizer);
std::shared_ptr<NumberFactory>          nFactory_ptr        (new NumberFactoryPrototype(Proxy::NumberP(new NumberImp())));
std::shared_ptr<NumberFormatter>        nFormatter_ptr      (new NumberFormatterStandard(nFactory_ptr, scannerBuilder_ptr, sigFigs));
std::shared_ptr<Builder>                eBuilder_ptr        (new Builders::Standard);
std::shared_ptr<Parser>                 parser_ptr          (new Parsers::Infix(scannerBuilder_ptr, eBuilder_ptr, nFormatter_ptr, tokenizer_ptr));

int main()
{
//    cout << endl;

//    typedef DS::Numbers::Integer intType;
/*
    intType x(798675);
    intType y = x*x*x;
    cout << endl;
    y.output(cout);
    y.intRoot(intType(2));
    cout << endl;
    y.output(cout);
    cout << endl;
*/
    //return 0;


    try {

    //=======================================================================

    std::string expString = "";

    ExprConstSP exp, previous;
    bool loop = false;
    do
    {
        //== Input ==============================================================

        if (1)
        {
        if (expString == "" || loop)
        {
            cout << "> ";
            loop = true;
            getline(cin, expString);
        }
        else
            cout << "> " << expString << endl;

        if (expString == "")
            continue;
        if (expString == "quit" || expString == "exit")
            break;
        if (expString == "clear" || expString == "clr")
        {
            std::system("clear");
            continue;
        }
        }

        //== Parsing ============================================================

        exp = parser_ptr->parse(expString);
        if (!exp)
        {
            cout << "  ";
            for (std::string::const_iterator it = expString.begin(); it != parser_ptr->getStopLocation(); ++it)
                cout << " ";
            cout << "^---Syntax Error!" << endl;
            continue;
        }

        //== Pre-Processing =====================================================

        if (previous)
        {
            std::map<std::string, ExprConstSP> dictionary;
            dictionary["_"] = previous;
            Restructurers::Substitution prevSub(nFactory_ptr, eBuilder_ptr, dictionary);
            prevSub.visitExpression(exp);
            exp = prevSub.result();
        }

        //== Pre-Rendering ======================================================

        cout << exp;

        //== Reduction ==========================================================

        reduce<BasicSymbols>(exp);
        reduce<ComplexSplitter>(exp);
        reduce<Rationalizer>(exp);

        for (int k = 0; k < 20; k++)
        {
            //cout << endl;
            reduce<ComplexNormalizer>(exp);
            //cout << exp << endl << "____________________________________________________________________1";
            reduce<GCDLiteral>(exp);
            //cout << exp << endl << "____________________________________________________________________2";
            reduce<SizeOneArray>(exp);
            reduce<SelfNesting>(exp);
            reduce<Negatives>(exp);
            //cout << exp << endl << "____________________________________________________________________3";
            reduce<FirstOrderBasic>(exp);
            //cout << exp << endl << "____________________________________________________________________4";
            reduce<NumberReducerBasic>(exp);
            //cout << exp << endl << "____________________________________________________________________5";
        }

        reduce<ComplexExpander>(exp);
        reduce<ComplexSplitter>(exp);
        reduce<ComplexNormalizer>(exp);
        reduce<GCDLiteral>(exp);
        reduce<SizeOneArray>(exp);
        reduce<SelfNesting>(exp);
        reduce<Negatives>(exp);

        //== Post Processing ====================================================

        previous = exp;

        //== Post Rendering =====================================================

        if (1) {
        cout << endl;
        Render::Infixs::CharMap map(nFormatter_ptr);
        Render::ASCIITree logger(nFormatter_ptr);
        map.visitExpression(exp);
        logger.visitExpression(exp);
        std::vector<std::string> strings = map.result().vectorOfStrings();
        for (std::vector<std::string>::const_iterator it = strings.begin(); it != strings.end(); ++it)
            cout << endl << setw(columns) << *it;
        /*
        cout << endl;
        strings = logger.result();
        unsigned int maxLength = 0;
        for (std::vector<std::string>::iterator it = strings.begin(); it != strings.end(); ++it)
            if (it->length() > maxLength)
                maxLength = it->length();
        for (std::vector<std::string>::iterator it = strings.begin(); it != strings.end(); ++it)
        {
            ostringstream o;
            o << *it;
            for (unsigned int i = 0; i < maxLength-it->length(); i++)
                o << " ";
            cout << endl << setw(120) << o.str();
        }
        */
        //cout << endl << endl;
        //Render::Infixs::String infixString(nFormatter_ptr);
        //infixString.visitExpression(exp);
        //cout << setw(100) << infixString.result();
        }

        // Num Eval
        //if (!constantsSub.visitExpression(exp))
        //{
        //    cout << endl << "Error in substitution of constants dictionary!";
        //    continue;
        //}
        //ExprConstSP constantsExp = constantsSub.result();

        NumEval eval;
        if (eval.visitExpression(exp))
        {
            Proxy::NumberP result = eval.result();
            if (!(result.isRealPartInteger() && result.isImaginaryPartInteger()))
            {
                cout << endl << endl;
                std::string realPart, imaginaryPart;
                realPart = nFormatter_ptr->formatRealPart(result);
                imaginaryPart = nFormatter_ptr->formatImaginaryPart(result);
                if (imaginaryPart == "1")
                    imaginaryPart = "i";
                else if (imaginaryPart == "-1")
                    imaginaryPart = "-i";
                else if (imaginaryPart != "0")
                    imaginaryPart += "i";

                if (imaginaryPart == "0")
                {
                    std::string value = "~ " + realPart;
                    cout << setw(columns) << value;
                }
                else if (realPart == "0")
                {
                    std::string value = "~ " + imaginaryPart;
                    cout << setw(columns) << value;
                }
                else
                {
                    if (realPart.length() + imaginaryPart.length() + 10 > columns)
                    {
                        std::string signString = "";
                        result.exchangeRealAndImaginary();
                        result.makeRealPart();
                        if (result.isPositiveReal())
                            signString = "+";
                        std::string value = "~ " + realPart;
                        cout << setw(columns) << value;
                        value = signString + imaginaryPart;
                        cout << endl << setw(columns) << value;
                    }
                    else
                    {
                        result.exchangeRealAndImaginary();
                        std::string signString = "";
                        result.makeRealPart();
                        if (result.isPositiveReal())
                            signString = "+";
                        std::string value = "~ " + realPart + signString + imaginaryPart;
                        cout << setw(columns) << value;
                    }
                }
            }
        }
        //else
        //    cout << setw(120) << "(Can't Evaluate)";

        cout << endl;
        for (unsigned int i = 0; i < columns; i++)
            cout << "_";
        cout << endl;

    } while(loop);
    } catch (const exception& e) { cout << endl << "EXCEPTION: " << e.what(); }
    //=======================================================================

    cout << endl << endl;
    return 0;
}

ostream& operator<< (ostream& out, ExprConstSP exp)
{
    //out << endl;
    Render::Infixs::CharMap map(nFormatter_ptr);
    map.visitExpression(exp);
    Render::Infixs::CenteredCharMatrix matResult = map.result();
    if (matResult.xSize() <= 98)
    {
        std::vector<std::string> strings = matResult.vectorOfStrings();
        for (std::vector<std::string>::const_iterator it = strings.begin(); it != strings.end(); ++it)
            cout << endl << "  " << *it;
    }
    else
    {
        Render::Infixs::String s(nFormatter_ptr);
        s.visitExpression(exp);
        cout << endl << "  " << s.result();
    }
    return out;
}

template<typename T>
void reduce(ExprConstSP& exp)
{
    T* visitor = new T(nFactory_ptr, eBuilder_ptr);
    bool success = visitor->visitExpression(exp);
    if (!success)
        throw std::logic_error("success == false in reduce()");
    exp = visitor->result();
    delete visitor;
}
