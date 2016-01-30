/*
 * NumberFormatterStandard.cpp
 *
 *  Created on: Dec 31, 2012
 *      Author: davidsicilia
 */

#include "../../../NumberProxy.h"
#include "NumberFormatterStandard.h"
#include "../../NumberImp/Complex/NumberDouble.h"
#include <stdexcept>
#include <sstream>
#include <string>
#include <iostream>

namespace DS {
namespace CAS {
namespace Numbers {

using namespace DS::CAS::Numbers::Proxy;

string NumberFormatterStandard::formatRealPart(const Number& _number)
{
    static NumberP intSizeLimit = format("-1");
    if (intSizeLimit.isNegativeReal())
        intSizeLimit = format("1e20");

    if (_number.isRealPartInteger())
        if (_number.isLessReals(intSizeLimit))
            return formatRealDecimal(_number, 21);
    return formatRealScientific(_number, maximumSigFigs);
}

string NumberFormatterStandard::formatRealDecimal(const Number& _number, unsigned int maxSigDigits)
{
    NumberP ten = factory->ten();
    NumberP one = factory->one();
    NumberP buffer = factory->number(.1);

    string result, integerPart, fractionalPart;

    NumberP number = _number;
    number.makeRealPart();

    if (number.isNotANumber())
        return "NaN";
    if (number.isNegativeReal())
    {
        result += "-";
        number.negate();
    }
    if (number.isInfinity())
    {
        result += "inf";
        return result;
    }

    NumberP order = factory->number(-1), nextOrder = factory->one();
    unsigned int sigFigs = 0;

    while (number >= nextOrder)
    {
        order = nextOrder;
        nextOrder *= ten;
        if (!nextOrder.isFiniteAndExists())
            throw logic_error("!nextOrder.isFiniteAndExists() in NumberFormatter::formatRealPart()");
    }
    if (order.isPositiveReal())
    {
        while (order > one+buffer)
        {
            int digit = 0;
            while (number >= order)
            {
                digit++;
                number -= order;
            }
            integerPart += (static_cast<char>(digit) + '0');
            sigFigs++;
            order /= ten;
        }
        // order should be == 1
        int digit = 0;
        while (number >= order)
        {
            digit++;
            number -= order;
        }
        integerPart += (static_cast<char>(digit) + '0');
        sigFigs++;
        order /= ten;
        // order should == 1/10
    }
    else
    {
        order = one;
        order /= ten; // do this in two steps to avoid rounding errors with .1 which will mess up code below
        integerPart += "0";
    }

    int remainingDigits = int(maxSigDigits)-int(sigFigs);

    if (remainingDigits <= 0)
        throw logic_error("remainingDigits <= 0 in NumberFormatterStandard::formatRealDecimal()");

    // order == 1/10
    // number should contain only fractional part

    unsigned int decimalDigits = 0, maxDecimalDigits = (unsigned int)remainingDigits+1; // plus one for rounding algorithm, must be >= 2
    bool roundDecimal = true;

    while (!number.isZero() && decimalDigits < maxDecimalDigits && order.isFiniteAndExists() && !order.isZero())
    {
        int digit = 0;
        while (number >= order)
        {
            digit++;
            number -= order;
        }
        fractionalPart += (static_cast<char>(digit) + '0');
        order.divideByTen();
        decimalDigits++;
    }

    if (decimalDigits > 0 && roundDecimal && fractionalPart.length() == maxDecimalDigits)
    {
        int roundLocation = maxDecimalDigits-2;
        if (fractionalPart[roundLocation+1] >= '5')
        {
            if (fractionalPart[roundLocation] == '9')
            {
                int currentRoundLocation = roundLocation;
                while (fractionalPart[currentRoundLocation] == '9')
                {
                    fractionalPart[currentRoundLocation] = '0';
                    currentRoundLocation--;
                    if (currentRoundLocation < 0)
                        break;
                }
                if (currentRoundLocation >= 0)
                    fractionalPart[currentRoundLocation]++;
                else
                {
                    currentRoundLocation = integerPart.length() - 1;
                    if (currentRoundLocation < 0)
                    {
                        integerPart = "0";
                        currentRoundLocation = 0;
                    }
                    while (integerPart[currentRoundLocation] == '9')
                    {
                        integerPart[currentRoundLocation] = '0';
                        currentRoundLocation--;
                        if (currentRoundLocation < 0)
                            break;
                    }
                    if (currentRoundLocation >= 0)
                        integerPart[currentRoundLocation]++;
                    else
                        integerPart = "1" + integerPart;
                }
            }
            else
                fractionalPart[roundLocation]++;

        }
        fractionalPart[roundLocation+1] = '0';

    }
    // remove trailing zeros from fractional part

    while (fractionalPart.length() > 0)
    {
        if (fractionalPart[fractionalPart.length()-1] == '0')
            fractionalPart.resize(fractionalPart.length()-1);
        else
            break;
    }

    result += integerPart;
    if (fractionalPart.length() > 0)
        result += (string(".") + fractionalPart);
    if (result == "-0")
        result = "0";

    return result;
}
string NumberFormatterStandard::formatRealScientific(const Number& _number, unsigned int maxSigDigits)
{
    // Formats in scientific notation if the number is outside of high and low bounds [10000-ep, .0001]

    NumberP number = _number;
    number.makeRealPart();
    bool negativeFlag = false;
    if (number.isNegativeReal())
    {
        number.negate();
        negativeFlag = true;
    }

    NumberP tenThousand = factory->number(10000.0), one = factory->one(), ten = factory->ten();
    NumberP oneTenThousanth = one/tenThousand, oneTenth = one/ten;

    if (number.isLessReals(oneTenThousanth))
    {
        if (number.isZero())
            return "0";
        int exp = 0;
        while (number.isLessReals(ten))
        {
            number.multiply(ten);
            exp--;
        }
        number.multiply(oneTenth);
        exp++;
        if (negativeFlag)
            number.negate();
        string result = formatRealDecimal(number, maxSigDigits);
        while (result[result.size()-1] == '0')
        {
            result.resize(result.size()-1);
            exp++;
        }
        ostringstream out;
        out << result << "e" << exp;
        return out.str();
    }
    else if (number.isLessReals(tenThousand))
    {
        if (negativeFlag)
            number.negate();
        string result = formatRealDecimal(number, maxSigDigits);
        return result;
    }
    else // number is >= 10,000
    {
        int exp = 0;
        while (!(number.isLessReals(ten)))
        {
            number.multiply(oneTenth);
            exp++;
        }
        if (negativeFlag)
            number.negate();
        string result = formatRealDecimal(number, maxSigDigits);
        while (result[result.size()-1] == '0')
        {
            result.resize(result.size()-1);
            exp++;
        }
        ostringstream out;
        out << result << "e" << exp;
        return out.str();
    }
}

void NumberFormatterStandard::buildScanners(void)
{
    //enum {spaces1, scientific, img, spaces2}; real/img scientific
    //enum {number, exp}; real scientific
    //enum {neg, whole, point, fraction}; real float

    sBuilder->spaces();
    optionalFlags.push_back(true);
    scanners.push_back(sBuilder->pop());
    sBuilder->floatScientific();
    sBuilder->floatNumber();
    sBuilder->orList(2);
    optionalFlags.push_back(false);
    scanners.push_back(sBuilder->pop());
    sBuilder->charString("i");
    optionalFlags.push_back(true);
    scanners.push_back(sBuilder->pop());
    sBuilder->spaces();
    optionalFlags.push_back(true);
    scanners.push_back(sBuilder->pop());

    sBuilder->floatNumber();
    realScientificOptionalFlags.push_back(false);
    realScientificScanners.push_back(sBuilder->pop());
    sBuilder->charString("e");
    sBuilder->pushFlag(false);
    sBuilder->integer();
    sBuilder->pushFlag(false);
    sBuilder->optionalList(2);
    realScientificOptionalFlags.push_back(true);
    realScientificScanners.push_back(sBuilder->pop());

    sBuilder->charString("-");
    realFloatOptionalFlags.push_back(true);
    realFloatScanners.push_back(sBuilder->pop());
    sBuilder->posInteger();
    realFloatOptionalFlags.push_back(true);
    realFloatScanners.push_back(sBuilder->pop());
    sBuilder->charString(".");
    realFloatOptionalFlags.push_back(true);
    realFloatScanners.push_back(sBuilder->pop());
    sBuilder->posInteger();
    realFloatOptionalFlags.push_back(true);
    realFloatScanners.push_back(sBuilder->pop());
}

Number* NumberFormatterStandard::format(const string& _number)
{
    enum {spaces1, scientific, img, spaces2};

    if (scanners.size() == 0)
        buildScanners();

    DS::Tokens::Tokenizer tokenizer;
    vector<DS::Token> tokens;
    if (!tokenizer.tokenizeOrdered(_number, scanners, optionalFlags, tokens, true))
        return NULL;

    NumberP result = formatRealScientific(tokens[scientific].getString());
    if (tokens[img].getString() != "")
        result.multiplyByImaginaryUnit();

    return result.clone();
}
Numbers::Proxy::NumberP NumberFormatterStandard::formatRealScientific(const string& _number)
{
    enum {number, exp};

    if (realScientificScanners.size() == 0)
        buildScanners();

    DS::Tokens::Tokenizer tokenizer;
    vector<DS::Token> tokens;
    if (!tokenizer.tokenizeOrdered(_number, realScientificScanners, realScientificOptionalFlags, tokens, true))
        throw invalid_argument("Tokenizer failed in NumberFormatterStandard::formatRealScientific()");

    string numberString = tokens[number].getString();

    NumberP result = formatRealFloat(numberString);

    if (tokens[exp].getString() != "")
    {
        NumberP zero = factory->zero(), one = factory->one(), ten = factory->ten();
        string exponentString(tokens[exp].getString().begin()+1, tokens[exp].getString().end());
        NumberP exponent = formatRealInteger(exponentString);
        bool negateFlag = false;
        if (exponent.isLessReals(zero))
        {
            negateFlag = true;
            exponent.negate();
        }
        NumberP multiplier = one;
        for (NumberP i = zero; i < exponent; ++i)
            multiplier.multiply(ten);
        if (negateFlag)
            multiplier.invert();
        result.multiply(multiplier);
    }
    return result;
}
Numbers::Proxy::NumberP NumberFormatterStandard::formatRealFloat(const string& _number)
{
    // Assumes a valid real float format -1234.4321, .456, 876, etc.

    enum {neg, whole, point, fraction};

    if (realFloatScanners.size() == 0)
        buildScanners();

    DS::Tokens::Tokenizer tokenizer;
    vector<DS::Token> tokens;
    if (!tokenizer.tokenizeOrdered(_number, realFloatScanners, realFloatOptionalFlags, tokens, true))
        throw invalid_argument("Tokenizer failed in NumberFormatterStandard::formatRealFloat()");

    NumberP wholePart = factory->zero(), fracPart = factory->zero();
    if (tokens[whole].getString() != "")
        wholePart = formatRealInteger(tokens[whole].getString());
    if (tokens[fraction].getString() != "")
    {
        fracPart = formatRealInteger(tokens[fraction].getString());
        NumberP one = factory->one(), ten = factory->ten();
        NumberP powerOfTen = one, oneTenth = one/ten;
        unsigned int numberOfDigits = tokens[fraction].getString().length();
        for (unsigned int i = 0; i < numberOfDigits; i++)
            powerOfTen *= oneTenth;
        fracPart.multiply(powerOfTen);
    }
    NumberP result = wholePart + fracPart;
    if (tokens[neg].getString() != "")
        result.negate();
    return result;
}
NumberP NumberFormatterStandard::formatRealInteger(const string& _number)
{
    // Assumes _number is valid

    NumberP result = factory->zero(), ten = factory->ten();
    string::const_iterator it = _number.begin();
    if (*it == '-')
        ++it;
    while (1)
    {
        result += NumberP(factory->number(double(*it++ - '0')));
        if (it == _number.end())
            break;
        result *= ten;
    }
    if (_number[0] == '-')
        result.negate();
    return result;
}

} } }
