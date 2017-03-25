#include "NumberFactory.hpp"
#include "NumberProxy.hpp"
#include "Basic.hpp"
#include "Templates.hpp"

using namespace DS::CAS::Numbers;

namespace DS            {
namespace CAS           {
namespace Expressions   {
namespace Visitors      {
namespace Restructurers {
namespace Reduction     {

// == Support Functions =========================================================================================

const Number& getLiteralNumber(EP exp)
{
    return (dynamic_cast<const Literal&>(*exp)).getNumber();
}

Expressions::ID eID(EP exp)
{
    return exp->id();
}

void GCDReduce(Proxy::NumberP& litNum, Proxy::NumberP& litDen)
{
    if (litDen.isZero())
    {
        if (!litNum.isZero())
            litNum = litNum.create(1.0);
        return;
    }
    if (!litNum.isRealPartInteger() || !litNum.isImaginaryPartInteger() ||
        !litDen.isRealPartInteger() || !litDen.isImaginaryPartInteger())
        throw std::logic_error("parameters not integer in CAS::Expressions::Visitors::Restructurers::Reduction::GCDReduce()");
    Proxy::NumberP gcd = litDen;
    if (gcd.isComplex())
        throw std::logic_error("gcd is complex in CAS::Expressions::Visitors::Restructurers::Reduction::GCDReduce()");
    if (gcd.isImaginary())
        gcd.exchangeRealAndImaginary();
    if (gcd.isNegativeReal())
        gcd.negate();
    Proxy::NumberP litNumReal = litNum;
    Proxy::NumberP litNumImg  = litNum;
    litNumReal.makeRealPart();
    litNumImg.imaginaryPart();
    if (litNumReal.isNegativeReal())
        litNumReal.negate();
    if (litNumImg.isNegativeReal())
        litNumImg.negate();

    if (!litNumReal.isZero())
        gcd.GCD(litNumReal);
    if (!litNumImg.isZero())
        gcd.GCD(litNumImg);

    litNum.divideBy(gcd);
    litDen.divideBy(gcd);

    litNum.roundUsingMode(CAS::Numbers::Number::RoundClosest);
    litDen.roundUsingMode(CAS::Numbers::Number::RoundClosest);
}

Sign flipSign(Sign sign)
{
    if (sign == Sign::p)
        return Sign::n;
    return Sign::p;
}

std::vector<Sign> flipSigns(const std::vector<Sign>& signs)
{
    std::vector<Sign> result = signs;
    for (std::vector<Sign>::iterator it = result.begin(); it != result.end(); ++it)
        *it = flipSign(*it);
    return result;
}

bool isRealPartEvenInteger(const Numbers::Number& number)
{
    Proxy::NumberP temp = number;
    temp.divideByTwo();
    return (temp.isRealPartInteger());
}

// == Basic Symbols =============================================================================================

EP BasicSymbols::symbol(const Symbol& exp, const std::vector<EP>& children)
{
    if (exp.getName() == "i" && children.size() == 0)
        return eB.literal(nF.i());
    return Restructurer::symbol(exp, children);
}

// == Complex Splitter ==========================================================================================

EP ComplexSplitter::literal(const Literal& exp, const std::vector<EP>& children)
{
    Proxy::NumberP number = exp.getNumber();
    if (number.isComplex())
    {
        Proxy::NumberP realPart = number, imgPart = number;
        realPart.makeRealPart();
        imgPart.makeImaginaryPart();
        return eB.add(eB.literal(realPart), eB.literal(imgPart));
    }
    return Restructurer::literal(exp,children);
}

// == Rationalizer ==============================================================================================

EP Rationalizer::literal(const Literal& exp, const std::vector<EP>& children)
{
    Proxy::NumberP number = exp.getNumber();
    if (number.isComplex())
        return Restructurer::literal(exp,children);

    bool imaginary = false;
    if (number.isImaginary())
    {
        imaginary = true;
        number.exchangeRealAndImaginary();
    }
    Proxy::NumberP ten           = nF.ten();
    Proxy::NumberP denominator = nF.one();
    Proxy::NumberP numerator   = number;
    while (!numerator.isRealPartInteger())
    {
        numerator.multiply(ten);
        denominator.multiply(ten);
    }
    if (imaginary)
        numerator.exchangeRealAndImaginary();
    EP result = eB.literal(numerator);
    if (!denominator.isOne())
        result = eB.divide(result, eB.literal(denominator));
    return result;
}

// == Complex Normalizer ========================================================================================

EP ComplexNormalizer::divide(const Divide& exp, const std::vector<EP>& children)
{
    if (eID(children[1]) == Expressions::ID::literal)
    {
        Proxy::NumberP number = getLiteralNumber(children[1]);
        if (!number.isReal())
        {
            Proxy::NumberP conjugate = number, modSquared = number;
            conjugate.conjugate();
            modSquared.modulusSquared();
            return eB.divide(eB.multiply(children[0], eB.literal(conjugate)), eB.literal(modSquared));
        }
    }
    return Restructurer::divide(exp,children);
}

// == Complex Expander ==========================================================================================

EP ComplexExpander::divide(const Divide& exp, const std::vector<EP>& children)
{
    if (eID(children[0]) == Expressions::ID::literal)
    {
        Proxy::NumberP number = getLiteralNumber(children[0]);
        if (number.isComplex())
        {
            Proxy::NumberP real = number, img = number;
            real.makeRealPart();
            img.makeImaginaryPart();
            return eB.add(eB.divide(eB.literal(real), children[1]), eB.divide(eB.literal(img), children[1]));
        }
    }
    return Restructurer::divide(exp,children);
}

// == GCD Literal ===============================================================================================

EP GCDLiteral::divide(const Divide& exp, const std::vector<EP>& children)
{
    if (eID(children[0]) != Expressions::ID::literal || eID(children[1]) != Expressions::ID::literal)
        return Restructurer::divide(exp,children);
    Proxy::NumberP litNum = getLiteralNumber(children[0]);
    Proxy::NumberP litDen = getLiteralNumber(children[1]);

    if (litDen.isComplex())
        return Restructurer::divide(exp,children);
    if (!litNum.isRealPartInteger() || !litNum.isImaginaryPartInteger() ||
        !litDen.isRealPartInteger() || !litDen.isImaginaryPartInteger())
        return Restructurer::divide(exp,children);

    GCDReduce(litNum, litDen);

    return eB.divide(eB.literal(litNum), eB.literal(litDen));
}

// == Size One Array ============================================================================================

EP SizeOneArray::add(const Add& exp, const std::vector<EP>& children)
{
    if (children.size() == 1)
        return (exp.getSignForChild(0) == Sign::p) ? children[0] : eB.negate(children[0]);
    return Restructurer::add(exp,children);
}
EP SizeOneArray::multiply(const Multiply& exp, const std::vector<EP>& children)
{
    if (children.size() == 1)
        return children[0];
    return Restructurer::multiply(exp,children);
}

// == Self Nesting ==============================================================================================

EP SelfNesting::add(const Add& exp, const std::vector<EP>& children)
{
    std::vector<EP> newExps;
    std::vector<Sign> newSigns;
    for (unsigned int i = 0; i < exp.numberOfChildren(); i++)
    {
        if (eID(children[i]) == Expressions::ID::add)
        {
            const Add& childRef = dynamic_cast<const Add&>(*children[i]);
            bool flipSign = (exp.getSignForChild(i) == Sign::n) ? true : false;
            for (unsigned int j = 0; j < childRef.numberOfChildren(); j++)
            {
                newExps.push_back(childRef.getChild(j));
                newSigns.push_back((Sign)(bool(childRef.getSignForChild(j)) ^ flipSign));
            }
            continue;
        }
        newExps.push_back(children[i]);
        newSigns.push_back(exp.getSignForChild(i));
    }
    return eB.add(newExps, newSigns);
}
EP SelfNesting::divide(const Divide& exp, const std::vector<EP>& children)
{
    Expressions::ID idN = children[0]->id();
    Expressions::ID idD = children[1]->id();
    EP newN, newD;
    if (idN == Expressions::ID::divide && idD == Expressions::ID::divide)
    {
        newN = eB.multiply(children[0]->getChild(0), children[1]->getChild(1));
        newD = eB.multiply(children[0]->getChild(1), children[1]->getChild(0));
        return eB.divide(newN, newD);
    }
    else if (idN == Expressions::ID::divide)
    {
        newN = children[0]->getChild(0);
        newD = eB.multiply(children[0]->getChild(1), children[1]);
        return eB.divide(newN, newD);
    }
    else if (idD == Expressions::ID::divide)
    {
        newD = children[1]->getChild(0);
        newN = eB.multiply(children[0], children[1]->getChild(1));
        return eB.divide(newN, newD);
    }
    else
        return Restructurer::divide(exp,children);
}
EP SelfNesting::multiply(const Multiply& exp, const std::vector<EP>& children)
{
    std::vector<EP> newExps;
    for (unsigned int i = 0; i < exp.numberOfChildren(); i++)
    {
        if (eID(children[i]) == Expressions::ID::multiply)
            for (unsigned int j = 0; j < children[i]->numberOfChildren(); j++)
                newExps.push_back(children[i]->getChild(j));
        else
            newExps.push_back(children[i]);
    }
    return eB.multiply(newExps);
}
EP SelfNesting::negate(const Negate& exp, const std::vector<EP>& children)
{
    if (eID(children[0]) == Expressions::ID::negate)
        return children[0]->getChild(0);
    return Restructurer::negate(exp,children);
}
EP SelfNesting::power(const Power& exp, const std::vector<EP>& children)
{
    // tests for (a^b)^c and will turn it into a^(b*c) if a is positive real and
    //   either (b is real) || (c is a real integer)
    if (eID(children[0]) != Expressions::ID::power)
        return Restructurer::power(exp,children);

    if (eID(children[0]->getChild(0)) != Expressions::ID::literal)
        return Restructurer::power(exp,children);

    const Proxy::NumberP& base = getLiteralNumber(children[0]->getChild(0));

    if (!base.isPositiveReal())
        return Restructurer::power(exp,children);

    EP firstExp  = children[0]->getChild(1);
    EP secondExp = children[1];

    if (eID(firstExp) == Expressions::ID::negate)
        firstExp = firstExp->getChild(0);
    if (eID(secondExp) == Expressions::ID::negate)
        secondExp = secondExp->getChild(0);

    if (eID(firstExp) == Expressions::ID::literal)
        if (getLiteralNumber(firstExp).isReal())
            return eB.power(children[0]->getChild(0), eB.multiply(children[0]->getChild(1), children[1]));

    if (eID(secondExp) == Expressions::ID::literal)
        if (getLiteralNumber(secondExp).isReal() && getLiteralNumber(secondExp).isIntegral())
            return eB.power(children[0]->getChild(0), eB.multiply(children[0]->getChild(1), children[1]));

    return Restructurer::power(exp,children);
}

// == Negatives =================================================================================================

EP Negatives::add(const Add& exp, const std::vector<EP>& children)
{
    std::vector<EP> newTerms;
    std::vector<Sign> newSigns;
    int firstPositiveIndex = -1;
    for (unsigned int i = 0; i < children.size(); i++)
    {
        bool isNegate = (eID(children[i]) == Expressions::ID::negate);
        Sign sign     = exp.getSignForChild(i);

        newTerms.push_back(isNegate ? children[i]->getChild(0) : children[i]);
        newSigns.push_back(isNegate ? flipSign(sign)           : sign);

        if (newSigns[i] == Sign::p && firstPositiveIndex < 0)
            firstPositiveIndex = int(i);
    }
    if (newSigns[0] == Sign::p)
        return eB.add(newTerms, newSigns);

    if (firstPositiveIndex >= 0)
    {
        std::swap(newTerms[firstPositiveIndex], newTerms[0]);
        std::swap(newSigns[firstPositiveIndex], newSigns[0]);
        return eB.add(newTerms, newSigns);
    }
    return eB.negate(eB.add(newTerms, std::vector<Sign>(newSigns.size(), Sign::p)));
}
EP Negatives::divide(const Divide&, const std::vector<EP>& children)
{
    bool negate = false;
    EP newNum = children[0];
    EP newDen = children[1];
    if (eID(children[0]) == Expressions::ID::negate)
    {
        negate ^= true;
        newNum = children[0]->getChild(0);
    }
    if (eID(children[1]) == Expressions::ID::negate)
    {
        negate ^= true;
        newDen = children[1]->getChild(0);
    }
    EP result = eB.divide(newNum, newDen);
    if (negate)
        result = eB.negate(result);
    return result;
}
EP Negatives::multiply(const Multiply&, const std::vector<EP>& children)
{
    bool negativeSign = false;
    std::vector<EP> newChildren;
    for (std::vector<EP>::const_iterator it = children.begin(); it != children.end(); ++it)
    {
        if (eID(*it) == Expressions::ID::negate)
        {
            negativeSign ^= true;
            newChildren.push_back((*it)->getChild(0));
            continue;
        }
        newChildren.push_back(*it);
    }
    if (negativeSign)
        return eB.negate(eB.multiply(newChildren));
    return eB.multiply(newChildren);
}
EP Negatives::power(const Power&, const std::vector<EP>& children)
{
    // if the base has a negate in front of it and the exponent is a real integer then
    // the negative will be factored out
    EP newBase = children[0];
    EP absExpo = children[1];
    if (eID(absExpo) == Expressions::ID::negate)
        absExpo = absExpo->getChild(0);
    if (eID(newBase) == Expressions::ID::negate && eID(absExpo) == Expressions::ID::literal)
    {
        Proxy::NumberP expo = getLiteralNumber(absExpo);
        if (expo.isReal() && expo.isRealPartInteger())
        {
            newBase = newBase->getChild(0);
            if (!isRealPartEvenInteger(expo))
                return eB.negate(eB.power(newBase, children[1]));
        }
    }
    return eB.power(newBase, children[1]);
}
EP Negatives::literal(const Literal& exp, const std::vector<EP>& children)
{
    Proxy::NumberP number = exp.getNumber(), zero(nF.zero());
    if (number.isLessReals(Proxy::NumberP(zero)) || (number.isImaginary() && number.isLessImaginaries(zero)))
        return eB.negate(eB.literal(-number));
    return Restructurer::literal(exp,children);
}

// == First Order Basic =========================================================================================

EP FirstOrderBasic::divide(const Divide& exp, const std::vector<EP>& children)
{
    if (eID(children[1]) == Expressions::ID::power)
        return eB.multiply(children[0], eB.power(children[1]->getChild(0), eB.negate(children[1]->getChild(1))));
    return Restructurer::divide(exp,children);
}
EP FirstOrderBasic::multiply(const Multiply& exp, const std::vector<EP>& children)
{
    std::vector<EP> numerator, denominator;
    for (unsigned int i = 0; i < children.size(); i++)
    {
        if (eID(children[i]) == Expressions::ID::divide)
        {
            numerator.push_back(children[i]->getChild(0));
            denominator.push_back(children[i]->getChild(1));
            continue;
        }
        numerator.push_back(children[i]);
    }
    if (denominator.empty())
        return Restructurer::multiply(exp,children);
    return eB.divide(eB.multiply(numerator), eB.multiply(denominator));
}
EP FirstOrderBasic::negate(const Negate& exp, const std::vector<EP>& children)
{
    // Distributes a negative into an Add if there are minus signs in it
    if (eID(children[0]) == Expressions::ID::add)
    {
        const Add& add = dynamic_cast<const Add&>(*(children[0]));
        for (unsigned int i = 0; i < add.numberOfChildren(); i++)
            if (add.getSignForChild(i) == Sign::n)
                return eB.add(add.getChildVector(), flipSigns(add.getSignVector()));
    }
    return Restructurer::negate(exp,children);
}
EP FirstOrderBasic::power(const Power& exp, const std::vector<EP>& children)
{
    if (eID(children[0]) == Expressions::ID::divide)
    {
        EP div = children[0];
        if (eID(div->getChild(0)) == Expressions::ID::literal || eID(div->getChild(1)) == Expressions::ID::literal)
            return eB.divide(eB.power(children[0]->getChild(0), children[1]), eB.power(children[0]->getChild(1), children[1]));
    }
    return Restructurer::power(exp,children);
}

// == Number Reducer Basic ======================================================================================

EP NumberReducerBasic::add(const Add& exp, const std::vector<EP>& children)
{
    std::vector<EP> newTerms, fractions;
    std::vector<Sign> newSigns, fractionSigns;
    Proxy::NumberP sum = nF.zero(), one = nF.one();

    for (unsigned int i = 0; i < children.size(); i++)
    {
        if (eID(children[i]) == Expressions::ID::literal)
        {
            fractions.push_back(eB.divide(children[i], eB.literal(one)));
            fractionSigns.push_back(exp.getSignForChild(i));
            continue;
        }
        else if (eID(children[i]) == Expressions::ID::divide)
        {
            if (eID(children[i]->getChild(0)) == Expressions::ID::literal &&
                eID(children[i]->getChild(1)) == Expressions::ID::literal)
            {
                fractions.push_back(children[i]);
                fractionSigns.push_back(exp.getSignForChild(i));
                continue;
            }
        }
        newTerms.push_back(children[i]);
        newSigns.push_back(exp.getSignForChild(i));
    }

    Proxy::NumberP num = sum, den = nF.one();
    for (unsigned int i = 0; i < fractions.size(); i++)
    {
        Proxy::NumberP num2 = getLiteralNumber(fractions[i]->getChild(0));
        Proxy::NumberP den2 = getLiteralNumber(fractions[i]->getChild(1));
        if (fractionSigns[i] == Sign::n)
            num2.negate();
        num = num*den2 + num2*den;
        den *= den2;
    }
    if (!num.isZero())
    {
        if (!den.isOne())
            newTerms.push_back(eB.divide(eB.literal(num), eB.literal(den)));
        else
            newTerms.push_back(eB.literal(num));
        newSigns.push_back(Sign::p);
    }
    if (newTerms.size() == 0)
        return eB.literal(nF.zero());
    return eB.add(newTerms, newSigns);
}
EP NumberReducerBasic::divide(const Divide& exp, const std::vector<EP>& children)
{
    if (eID(children[0]) == Expressions::ID::literal)
        if (getLiteralNumber(children[0]).isZero())
            return children[0];

    if (eID(children[1]) == Expressions::ID::literal)
        if (getLiteralNumber(children[1]).isOne())
            return children[0];

    return Restructurer::divide(exp,children);
}
EP NumberReducerBasic::multiply(const Multiply&, const std::vector<EP>& children)
{
    std::vector<EP> newFactors;
    Proxy::NumberP product = nF.one();
    for (unsigned int i = 0; i < children.size(); i++)
    {
        if (eID(children[i]) == Expressions::ID::literal)
        {
            if (getLiteralNumber(children[i]).isZero())
                return children[i];
            product.multiply(getLiteralNumber(children[i]));
            continue;
        }
        newFactors.push_back(children[i]);
    }
    if (!product.isOne() || newFactors.size() == 0)
        newFactors.push_back(eB.literal(product));
    return eB.multiply(newFactors);
}
EP NumberReducerBasic::negate(const Negate& exp, const std::vector<EP>& children)
{
    if (eID(children[0]) == Expressions::ID::literal)
        if (getLiteralNumber(children[0]).isZero())
            return children[0];
    return Restructurer::negate(exp,children);
}
EP NumberReducerBasic::power(const Power& exp, const std::vector<EP>& children)
{
    if (eID(children[1]) == Expressions::ID::literal)
    {
        if (getLiteralNumber(children[1]).isZero())
            return eB.literal(nF.one());
        if (getLiteralNumber(children[1]).isOne())
            return children[0];
    }
    if (eID(children[0]) == Expressions::ID::literal)
        if (getLiteralNumber(children[0]).isZero() || getLiteralNumber(children[0]).isOne())
            return children[0];

    EP exponent = children[1];
    if (eID(exponent) == Expressions::ID::negate)
        exponent = exponent->getChild(0);

    if (eID(children[0]) == Expressions::ID::literal && eID(exponent) == Expressions::ID::literal)
    {
        Proxy::NumberP baseNum = getLiteralNumber(children[0]);
        Proxy::NumberP expNum  = getLiteralNumber(exponent);
        Proxy::NumberP realExpNum = expNum, imgExpNum = expNum;
        realExpNum.makeRealPart();
        imgExpNum.makeImaginaryPart();
        if (realExpNum.isNegativeReal())
            return Restructurer::power(exp,children);

        baseNum.raiseToPower(realExpNum);
        baseNum.roundUsingMode(Number::RoundClosest);

        EP result = eB.literal(baseNum);
        if (eID(children[1]) == Expressions::ID::negate)
        {
            result = eB.divide(eB.literal(nF.one()), result);
            imgExpNum.negate();
        }
        if (!imgExpNum.isZero())
        {
            if (!baseNum.isOne())
                result = eB.multiply(result, eB.power(children[0], eB.literal(imgExpNum)));
            else
                result = eB.power(children[0], eB.literal(imgExpNum));
        }
        return result;
    }
    return Restructurer::power(exp,children);
}

// == Templates =================================================================================================

/*
EP X::add(const Add& exp, const std::vector<EP>& children) { return Restructurer::add(exp,children); }
EP X::divide(const Divide& exp, const std::vector<EP>& children) { return Restructurer::divide(exp,children); }
EP X::factorial(const Factorial& exp, const std::vector<EP>& children) { return Restructurer::factorial(exp,children); }
EP X::literal(const Literal& exp, const std::vector<EP>& children) { return Restructurer::literal(exp,children); }
EP X::modulus(const Modulus& exp, const std::vector<EP>& children) { return Restructurer::modulus(exp,children); }
EP X::multiply(const Multiply& exp, const std::vector<EP>& children) { return Restructurer::multiply(exp,children); }
EP X::negate(const Negate& exp, const std::vector<EP>& children) { return Restructurer::negate(exp,children); }
EP X::power(const Power& exp, const std::vector<EP>& children) { return Restructurer::power(exp,children); }
EP X::symbol(const Symbol& exp, const std::vector<EP>& children) { return Restructurer::symbol(exp,children); }
*/

}}}}}}
