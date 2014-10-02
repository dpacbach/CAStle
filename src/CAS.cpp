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
#include <boost/shared_ptr.hpp>

#include "Utilities/Utilities.h"
#include "CAS/CAS.h"

using namespace std;
using namespace DS;
using namespace DS::CAS;
using namespace DS::CAS::Expressions;
using namespace DS::CAS::Expressions::Visitors;
using namespace DS::CAS::Expressions::Visitors::Restructurers::Reduction;

template<typename T>
void reduce(Expression::Ptr&);
ostream& operator<< (ostream& out, Expression::Ptr);

//== CAS Machinery =====================================================

const int sigFigs = 100;
typedef DS::Numbers::Float                        FloatType;
typedef CAS::Numbers::NumberDouble<FloatType>     NumberImp;

boost::shared_ptr<Tokens::ScannerBuilder> scannerBuilder_ptr  (new Tokens::ScannerBuilders::Simple);
boost::shared_ptr<Tokens::Tokenizer>      tokenizer_ptr       (new Tokens::Tokenizer);
boost::shared_ptr<NumberFactory>          nFactory_ptr        (new NumberFactoryPrototype(NumberP(new NumberImp())));
boost::shared_ptr<NumberFormatter>        nFormatter_ptr      (new NumberFormatterStandard(nFactory_ptr, scannerBuilder_ptr, sigFigs));
boost::shared_ptr<Builder>                eBuilder_ptr        (new Builders::Standard);
boost::shared_ptr<Parser>                 parser_ptr          (new Parsers::Infix(scannerBuilder_ptr, eBuilder_ptr, nFormatter_ptr, tokenizer_ptr));

int main()
{
    cout << endl;

    typedef DS::Numbers::Integer intType;

    intType x(798675);
    intType y = x*x*x;
    cout << endl;
    y.output(cout);
    y.intRoot(intType(2));
    cout << endl;
    y.output(cout);
    cout << endl;

    //return 0;


    try {

    //=======================================================================

    string expString = "";

    Expression::Ptr exp, previous;
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
            for (string::const_iterator it = expString.begin(); it != parser_ptr->getStopLocation(); ++it)
                cout << " ";
            cout << "^---Syntax Error!" << endl;
            continue;
        }

        //== Pre-Processing =====================================================

        if (previous)
        {
            map<string, Expression::Ptr> dictionary;
            dictionary["r"] = previous;
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
        vector<string> strings = map.result().vectorOfStrings();
        for (vector<string>::const_iterator it = strings.begin(); it != strings.end(); ++it)
            cout << endl << setw(176) << *it;
        /*
        cout << endl;
        strings = logger.result();
        unsigned int maxLength = 0;
        for (vector<string>::iterator it = strings.begin(); it != strings.end(); ++it)
            if (it->length() > maxLength)
                maxLength = it->length();
        for (vector<string>::iterator it = strings.begin(); it != strings.end(); ++it)
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
        //Expression::Ptr constantsExp = constantsSub.result();

        NumEval eval;
        if (eval.visitExpression(exp))
        {
            NumberP result = eval.result();
            if (!(result.isRealPartInteger() && result.isImaginaryPartInteger()))
            {
                cout << endl << endl;
                string realPart, imaginaryPart;
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
                    string value = "~ " + realPart;
                    cout << setw(176) << value;
                }
                else if (realPart == "0")
                {
                    string value = "~ " + imaginaryPart;
                    cout << setw(176) << value;
                }
                else
                {
                    if (realPart.length() + imaginaryPart.length() + 10 > 176)
                    {
                        string signString = "";
                        result.exchangeRealAndImaginary();
                        result.makeRealPart();
                        if (result.isPositiveReal())
                            signString = "+";
                        string value = "~ " + realPart;
                        cout << setw(176) << value;
                        value = signString + imaginaryPart;
                        cout << endl << setw(176) << value;
                    }
                    else
                    {
                        result.exchangeRealAndImaginary();
                        string signString = "";
                        result.makeRealPart();
                        if (result.isPositiveReal())
                            signString = "+";
                        string value = "~ " + realPart + signString + imaginaryPart;
                        cout << setw(176) << value;
                    }
                }
            }
        }
        //else
        //    cout << setw(120) << "(Can't Evaluate)";

        cout << endl;
        for (unsigned int i = 0; i < 176; i++)
            cout << "_";
        cout << endl;

    } while(loop);
    } catch (const exception& e) { cout << endl << "EXCEPTION: " << e.what(); }
    //=======================================================================

    cout << endl << endl;
    return 0;
}

ostream& operator<< (ostream& out, Expression::Ptr exp)
{
    //out << endl;
    Render::Infixs::CharMap map(nFormatter_ptr);
    map.visitExpression(exp);
    Render::Infixs::CenteredCharMatrix matResult = map.result();
    if (matResult.xSize() <= 98)
    {
        vector<string> strings = matResult.vectorOfStrings();
        for (vector<string>::const_iterator it = strings.begin(); it != strings.end(); ++it)
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
void reduce(Expression::Ptr& exp)
{
    T* visitor = new T(nFactory_ptr, eBuilder_ptr);
    bool success = visitor->visitExpression(exp);
    if (!success)
        throw logic_error("success == false in reduce()");
    exp = visitor->result();
    delete visitor;
}
