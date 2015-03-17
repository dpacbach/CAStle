#include <stdexcept>
#include <iostream>
#include "Float.h"
#include <cmath>

namespace DS {
namespace Numbers {

// The guesses based on the standard floating point library
//   aren't going to cut it
// Try the algorithm for exp(x) based on exp(x)-1 = (exp(x/2)-1)*(exp(x/2)+1)

const int Float::maxMantissaDigits(7);
//const int Float::maxMantissaDigits(13);    // 26 --> 200
                                        // 13 --> 100 decimal digits
                                        //  7 -->  50

// This will do an inefficient calculation of (double)(1 << size)
// which can be calculated at compile time
constexpr double one_shift_left(size_t size)
{
    return (size == 0) ? 1.0 : (2.0 * one_shift_left(size-1));
}

double Float::toDouble(void) const
{
    BaseArray::unit_t mostSignificant = mantissa.getMostSigUnit();
    BaseArray::unit_t secondMostSignificant = mantissa.getSecondMostSigUnit();
    double result = secondMostSignificant;
    constexpr double dividend = one_shift_left(UNIT_T_BITS);
    result /= dividend;
    result += mostSignificant;
    int resultExp = (mantissa.numberOfDigits()+exponent-1)*UNIT_T_BITS;
    result = ldexp(result, resultExp);
    if (isNegative())
        result = -result;
    return result;
}

void Float::copyFrom(const Float& number)
{
    mantissa = number.mantissa;
    exponent = number.exponent;
}
void Float::copyFrom(double number)
{
    int intExp = 0;
    double doubleMantissa = frexp(number, &intExp);

    // TODO: make sure this doesn't have to be changed for
    // 64 bit words
    doubleMantissa *= 2147483648; // 2^31
    BaseArray::unit_t intMantissa = static_cast<BaseArray::unit_t>(doubleMantissa);

    intExp -= 31;

    mantissa = intMantissa;
    exponent = intExp/(int)UNIT_T_BITS;

    intExp %= (int)UNIT_T_BITS;

    static const Float two(Integer(2));
    if (intExp > 0)
    {
        for (; intExp > 0; intExp--)
            *this *= two;
    }
    else if (intExp < 0)
    {
        int shifts = (int)UNIT_T_BITS+intExp;
        for (; shifts > 0; shifts--)
            *this *= two;
        exponent--;
    }
    removeExcessMantissa();
}

Float::~Float()
{

}

void Float::floor(void)
{
    if (exponent >= 0)
        return;
    mantissa.shiftRightByUnits(-exponent);
    exponent = 0;
    removeExcessMantissa();
}

void Float::operator+= (const Float& number)
{
    const Float *_smaller, *_larger;
    _smaller = this;
    _larger  = &number;

    if (abs(number).isLessThan(abs(*this)))
    {
        _smaller = &number;
        _larger = this;
    }

    const Float& smaller = *_smaller;
    const Float& larger = *_larger;
    int smallerIndex = smaller.numberOfMantissaUnits() + smaller.exponent;
    int largerIndex = larger.numberOfMantissaUnits() + larger.exponent;

    if (largerIndex - smallerIndex >= Float::maxMantissaDigits)
    {
        *this = larger;
        return;
    }

    intType tempLargerMantissa = larger.mantissa;
    intType tempSmallerMantissa = smaller.mantissa;
    int tempLargerExponent = larger.exponent;
    int tempSmallerExponent = smaller.exponent;

    int largerRightSide = largerIndex - larger.numberOfMantissaUnits();
    int largerRightSideTarget = smallerIndex - smaller.numberOfMantissaUnits();
    int numberToAdd = largerRightSide-largerRightSideTarget;
    if (numberToAdd < 0)
        numberToAdd = 0;
    if (numberToAdd+larger.numberOfMantissaUnits() > Float::maxMantissaDigits)
        numberToAdd = Float::maxMantissaDigits - larger.numberOfMantissaUnits();

    if (numberToAdd > 0)
    {
        tempLargerMantissa.shiftLeftByUnits((unsigned int)numberToAdd);
        tempLargerExponent -= numberToAdd;
    }

    int smallerRightSide = smallerIndex - smaller.numberOfMantissaUnits();
    int smallerRightSideTarget = largerIndex - larger.numberOfMantissaUnits() - numberToAdd;
    numberToAdd = smallerRightSide - smallerRightSideTarget;

    tempSmallerMantissa.shiftLeftByUnits((unsigned int)numberToAdd);
    tempSmallerExponent -= numberToAdd;
    mantissa = tempLargerMantissa;
    mantissa += tempSmallerMantissa;
    exponent = tempLargerExponent;
    removeExcessMantissa();
}

void Float::operator*= (const Float& number)
{
    mantissa *= number.mantissa;
    exponent += number.exponent;
    removeExcessMantissa();
}

void Float::operator/= (const Float& number)
{
    Float temp = number;
    temp.inverse();
    (*this) *= temp;
}

void Float::operator%= (const Float& number)
{
    if (this->isLessThan(number))
        return;
    Float intPart = *this / number;
    Float floatPart = intPart;
    intPart.floor();
    floatPart -= intPart;
    *this = floatPart*number;
}

void Float::inverse(void)
{
    const Float two(Integer(2));
    Float x = Float(1.0/toDouble());

    unsigned int maxIterations = 1 + (unsigned int)(.5 + log(double(Float::maxMantissaDigits*UNIT_T_BITS))/log(2));
    ((void)maxIterations);
    unsigned int count = 0;
    ((void)count);
    Float temp;
    while (1)
    {
        x = x*(two - (*this)*x);
        if (x.isEqualTo(temp))
            break;
        temp = x;
#ifndef NO_FLOAT_EXCEPTIONS
        if (++count >= maxIterations)
            throw logic_error("count >= maxIterations in Float::inverse()");
#endif
    }
    *this = x;
}

void Float::sqrt(void)
{
#ifndef NO_FLOAT_EXCEPTIONS
    if (isNegative())
        throw invalid_argument("sqrt of a negative number in Float::sqrt");
#endif

    static Float one(Integer(1)), two(Integer(2)), six(Integer(6)), ten(Integer(10));
    static Float oneHalf, guessCache[2][10];

    if (oneHalf.isZero())
    {
        oneHalf = one/two;
#ifndef NO_FLOAT_EXCEPTIONS
        if (oneHalf.numberOfMantissaUnits() != 1)
            throw logic_error("oneHalf.numberOfMantissaDecimalDigits() != 1 in Float::sqrt");
#endif
    }

    Float x = Float(std::sqrt(toDouble()));

    unsigned int maxIterations = 2 + (unsigned int)(.5 + log(double(Float::maxMantissaDigits*UNIT_T_BITS))/log(2));
    ((void)maxIterations);
    unsigned int count = 0;
    ((void)count);
    Float temp;
    while (1)
    {
        x = (x + (*this)/x)*oneHalf;

        if (x.isEqualTo(temp))
            break;
        temp = x;
#ifndef NO_FLOAT_EXCEPTIONS
        if (++count >= maxIterations)
            throw logic_error("count >= maxIterations in Float::sqrt()");
#endif
    }
    *this = x;
}

const Float& Float::pi(void)
{
    static Float Pi;

    if (Pi.isZero())
    {
        Float a, g, t, p, aTemp;
        Float one(Integer(1)), two(Integer(2)), four(Integer(4));
        Float oneHalf(one/two), oneFourth(one/four);

        a = one;
        g = one/two;
        g.sqrt();
        t = one/four;
        p = one;
        aTemp = a;

        unsigned int maxIterations = 1 + (unsigned int)(.5 + log(double(Float::maxMantissaDigits*UNIT_T_BITS))/log(2));
        unsigned int i;
        for (i = 0; i < maxIterations; i++)
        {
            a += g;
            a /= two;
            g *= aTemp;
            g.sqrt();
            Float temp(aTemp);
            temp -= a;
            temp *= temp;
            t -= p*temp;
            p *= two;
            aTemp = a;
            if (a.isEqualTo(g))
                break;
        }
#ifndef NO_FLOAT_EXCEPTIONS
        if (i == maxIterations)
            throw logic_error("i == maxIterations in Float::pi()");
#endif
        Pi = (a+g)*(a+g)/(four*t);
    }
    return Pi;
}

void Float::AG_mean(const Float& _g) // make sure this doesn't go into an infinite loop
{
    Float a(*this), g(_g);
    static Float oneHalf;
    if (oneHalf.isZero())
        oneHalf = Float(Integer(1))/Float(Integer(2));

    unsigned int maxIterations = 20 + (unsigned int)(.5 + log(double(Float::maxMantissaDigits*UNIT_T_BITS))/log(2));
                                // unneeded + (base + scaling)
    ((void)maxIterations);
    unsigned int count = 0;
    while (1)
    {
        *this += g;
        *this *= oneHalf;
        g *= a;
        g.sqrt();
        a = *this;
        count++;
#ifndef NO_FLOAT_EXCEPTIONS
        if (count >= maxIterations)
            throw logic_error("count >= maxIterations in Float::AG_mean()");
#endif
        if ((*this).isEqualTo(g))
            break;
    }
}

const Float& Float::lnTwo(void)
{
    static Float lnTwoVar;

    if (lnTwoVar.isZero())
    {
        unsigned int m = 2 + (unsigned int)(double(Float::maxMantissaDigits)*13 + .5);

        Float two(Integer(2)), four(Integer(4));
        Float AGM(Integer(1)), x(two);

        Float s(Integer(1));
        for (unsigned int i = 0; i < m; i++)
            s *= two;

        AGM.AG_mean(four/s);
        lnTwoVar = Float::pi() / (AGM*two*Float(Integer((BaseArray::unit_t)m)));
    }
    return lnTwoVar;
}

void Float::ln(void)
{
    static Float one(Integer(1)), two(Integer(2)), four(Integer(4));

    if (this->mantissa.isNegative() || !bool(this->mantissa))
    {
#ifndef NO_FLOAT_EXCEPTIONS
        throw invalid_argument("log of a non-positive number in Float::ln");
#endif
        return;
    }
    if (*this == one)
    {
        setToZero();
        return;
    }

    int reduction = 0;

    int adjustment = this->mantissa.numberOfDigits()+this->exponent - 1;
    exponent -= adjustment;
    reduction = sizeof(BaseArray::unit_t)*8*adjustment;
    BaseArray::unit_t unit = this->mantissa.getMostSigUnit();
    while (unit > 1)
    {
        unit >>= 1;
        reduction++;
        this->divideByTwo();
    }

    const unsigned int m = 2 + (unsigned int)(double(Float::maxMantissaDigits)*13 + .5);
    static Integer mInt((BaseArray::unit_t)m);
    static Float s, fourOverS, piOverTwo, mFloat(mInt), mFloatLnTwo;
    if (s.isZero())
    {
        s = one;
        for (unsigned int i = 0; i < m; i++)
            s *= two;
        fourOverS = four/s;
        piOverTwo = Float::pi()/two;
        mFloatLnTwo = mFloat*Float::lnTwo();
    }

    Float AGM(one);
    AGM.AG_mean(fourOverS/(*this));

    *this = piOverTwo / AGM - mFloatLnTwo + Float(Integer(reduction))*Float::lnTwo();
}

void Float::exp(void) // make reductions faster
{
     // x'=x*(1+(a+1-Ln(x))^2)/2

    bool negativeFlag = false;
    if (isNegative())
    {
        negativeFlag = true;
        negate();
    }
    unsigned int maxIterations = 20 + (unsigned int)(.5 + log(double(Float::maxMantissaDigits*UNIT_T_BITS))/log(3));

    static Float one(Integer(1)), two(Integer(2));
    static Float oneHalf(one/two);
    Float temp, x;
    unsigned int i;

    unsigned int reductions = 0;

    while (one.isLessThan(*this))
    {
        reductions++;
        this->divideByTwo();
    }

    x = std::exp(this->toDouble());
    for (i = 0; i < maxIterations; i++)
    {
        temp = x;
        x.ln();
        x.negate();
        x += one;
        x += *this;
        x *= x;
        x += one;
        x *= oneHalf;
        x *= temp;
        if (x.isEqualTo(temp))
            break;
    }
#ifndef NO_FLOAT_EXCEPTIONS
    if (i == maxIterations)
        throw logic_error("i == maxIterations in Float::exp()");
#endif

    for (unsigned int j = 0; j < reductions; j++)
        x *= x;

    if (negativeFlag)
        x.inverse();
    *this = x;
}

void Float::sin(void)
{
    static const Float pi(Float::pi());
    static const Float piOverTwo(pi/2.0);
    static const Float twoPi(2.0*pi);
    static const Float one(Integer(1)), reductionInt(Integer(10000));
    static const Float three(Integer(3)), four(Integer(4));
    static const Float reductionFloat(one/reductionInt), oneThird(one/three);
    bool negateFlag = false;
    if (this->isNegative())
    {
        this->negate();
        negateFlag = !negateFlag;
    }
    if (twoPi.isLessThan(*this))
        *this %= twoPi;
    if (pi.isLessThan(*this))
    {
        *this -= pi;
        negateFlag = !negateFlag;
    }
    if (piOverTwo.isLessThan(*this))
        *this = pi-*this;

    unsigned int reductions = 0;
    while (reductionFloat.isLessThan(*this))
    {
        reductions++;
        *this *= oneThird;
    }

    Float result, power(*this), fact(Integer(1)), temp;
    bool sign = true;
    double numberOfDigits = Float::maxMantissaDigits*double(UNIT_T_BITS)/3.32;
    // .25 for reductions
    int maxTerms = .25 * 2.0*std::pow(numberOfDigits, .7), i;
    for (i = 1; i < 1+2*maxTerms; i += 2)
    {
        temp = result;
        if (sign)
            result += power/fact;
        else
            result -= power/fact;
        power *= *this;
        power *= *this;
        fact *= Float(Integer(i+1));
        fact *= Float(Integer(i+2));
        sign = !sign;
        if (temp.isEqualTo(result))
            break;
    }
#ifndef NO_FLOAT_EXCEPTIONS
    if (i == maxTerms*2+1)
        throw logic_error("i == maxTerms in Float::sin()");
#endif
    //cout << endl << "terms = " << (i-1)/2 << ", maxTerms = " << maxTerms;

    // sin(3x) = 3*sin(x) - 4*sin(x)^3
    for (unsigned int i = 0; i < reductions; i++)
        result = three*result-four*result*result*result;

    if (negateFlag)
        result.negate();
    *this = result;
}

void Float::atan(void)
{
    static const Float one(Integer(1)), two(Integer(2));
    static const Float piOverTwo(Float::pi()/two);
    static const Float reductionInt(Integer(10000));
    static const Float reductionFloat(one/reductionInt);
    if (isNegative())
    {
        negate();
        atan();
        negate();
        return;
    }
    if (one.isLessThan(*this))
    {
        // arctan(x) = (pi/2)*Sign(x) - arctan(1/x)
        inverse();
        atan();
        if (isNegative())
            operator+=(piOverTwo);
        else
            operator-=(piOverTwo);
        negate();
        return;
    }

    // *this <= 1, so perform reduction using
    // atan(x) = 2atan(x/(1+sqrt(1+x^2)))

    int reductions = 0;
    while (reductionFloat.isLessThan(*this))
    {
        reductions++;
        Float temp = (*this)*(*this)+one;
        temp.sqrt();
        temp = (*this)/(one+temp);
        *this = temp;
    }

    // now *this is a very small positive number, so use
    // taylor series

    Float result, power(*this), denominator(one), temp;
    bool sign = true;

    double numberOfDigits = Float::maxMantissaDigits*double(UNIT_T_BITS)/3.32;
    int maxTerms = .4 * 2.0*std::pow(numberOfDigits, .7), i;
    for (i = 1; i < 1+2*maxTerms; i += 2)
    {
        temp = result;
        if (sign)
            result += power/denominator;
        else
            result -= power/denominator;
        power *= *this;
        power *= *this;
        denominator += two;
        sign = !sign;
        if (temp.isEqualTo(result))
            break;
    }
#ifndef NO_FLOAT_EXCEPTIONS
    if (i == maxTerms*2+1)
        throw logic_error("i == maxTerms in Float::atan()");
#endif
    //cout << endl << "terms = " << (i-1)/2 << ", maxTerms = " << maxTerms;

    for (int i = 0; i < reductions; i++)
        result *= two;

    *this = result;
}

bool Float::isLessThan(const Float& number) const // may have to be optimized
{
    if (mantissa < 0 && number.mantissa >= 0)
        return true;
    if (mantissa >=0 && number.mantissa < 0)
        return false;
    if (mantissa == 0 && number.mantissa == 0)
        return false;
    else if (mantissa == 0)
    {
        if (number.mantissa > 0)
            return true;
        return false;
    }
    else if (number.mantissa == 0)
    {
        if (mantissa > 0)
            return false;
        return true;
    }
    // at this point neither are zero and the both have the same sign
    bool invertSign = false;
    if (mantissa < 0)
        invertSign = true;

    int thisMDD = numberOfMantissaUnits();
    int numberMDD = number.numberOfMantissaUnits();
    int thisIndex = thisMDD + exponent;
    int numberIndex = numberMDD + number.exponent;

    if (thisIndex != numberIndex)
        return (thisIndex < numberIndex)^invertSign;

    // the indices are equal

    intType targetIndex = (thisMDD > numberMDD) ? thisMDD : numberMDD;

    intType mantissaCopy = mantissa;
    intType numberMantissaCopy = number.mantissa;
    if (targetIndex > thisMDD)
        for (int i = 0; i < (targetIndex-intType(thisMDD)); i++)
            mantissaCopy.shiftLeftByUnits(1);
    if (targetIndex > numberMDD)
        for (int i = 0; i < (targetIndex-intType(numberMDD)); i++)
            numberMantissaCopy.shiftLeftByUnits(1);

    return (mantissaCopy < numberMantissaCopy);
}

bool Float::isEqualTo(const Float& number) const // this needs to be redone based on a difference
{
    int nodl = (*this).mantissa.numberOfDigits();
    int nodr = number.mantissa.numberOfDigits();
    Integer templ, tempr;
    Float diff, tolerance;
    if (nodl == Float::maxMantissaDigits || nodr == Float::maxMantissaDigits)
    {
        tolerance = Float(Integer(1));
        if (nodl == nodr)    // do they both have max digits?
        {
            if (this->exponent != number.exponent)  // if so they must have equal exponents
                return false;
            tolerance.exponent = this->exponent + 1;
        }
        else
        {
            if (nodl == Float::maxMantissaDigits)
            {
                if (this->exponent != number.exponent-(nodl-nodr))
                    return false;
                tolerance.exponent = this->exponent + 1;
            }
            else // number is max digits
            {
                if (this->exponent-(nodr-nodl) != number.exponent)
                    return false;
                tolerance.exponent = number.exponent + 1;
            }
        }
        tolerance.removeExcessMantissa(); // good practice

        diff = *this - number;
        diff.makeAbs();

        if (diff.isLessThan(tolerance))
            return true;
        return false;
    }
    else
        return (this->mantissa == number.mantissa) && (this->exponent == number.exponent);
}

int Float::numberOfMantissaUnits(void) const
{
    return mantissa.numberOfDigits();
}

void Float::multiplyByBase(int number)
{
    exponent += number;
}

void Float::divideByBase(int number)
{
    exponent -= number;
}

void Float::divideByTwo(void)
{
    BaseArray::unit_t lsu = mantissa.getModByOneUnit();
    if (lsu & 1) // is the least sig bit == 1?
    {
        mantissa.shiftLeftByUnits(1);
        exponent--;
    }
    mantissa.shiftRightOneBit();
    removeExcessMantissa();
}

void Float::setToZero(void)
{
    mantissa = 0;
    exponent = 0;
}

void Float::removeExcessMantissa(void)
{
    if (!bool(mantissa))
    {
        exponent = 0;
        return;
    }
    int digits = mantissa.numberOfDigits();
    int excess = digits - Float::maxMantissaDigits;
    if (excess > 0)
    {
        static Integer one(1);
        mantissa.shiftRightByUnits(excess-1);
        exponent += (excess-1);
        bool carry = false;
        BaseArray::unit_t digit = mantissa.getModByOneUnit();
        if (digit >= ((BaseArray::unit_t)1 << (UNIT_T_BITS-1))) //0x80000000)
            carry = true;
        mantissa.shiftRightByUnits(1);
        exponent += 1;
        if (carry)
        {
            mantissa += one;
            removeExcessMantissa();
            return;
        }
    }

    int zeros = mantissa.numberOfTrailingZeros();
    if (zeros)
    {
        mantissa.shiftRightByUnits(zeros);
        exponent += zeros;
    }
}

Float::Float()
{
    setToZero();
}
Float::Float(double number)
{
    copyFrom(number);
}
Float::Float(const Float& number)
{
    copyFrom(number);
}
Float::Float(const intType& _mantissa, int _exponent)
{
    mantissa = _mantissa;
    exponent = _exponent;
    removeExcessMantissa();
}
Float::Float(int _mantissa, int _exponent)
{
    mantissa = _mantissa;
    exponent = _exponent;
    removeExcessMantissa();
}
Float& Float::operator= (const Float& number)
{
    copyFrom(number);
    return *this;
}
Float& Float::operator= (double number)
{
    copyFrom(number);
    return *this;
}

void Float::negate(void)
{
    mantissa.negate();
}
void Float::makeAbs(void)
{
    if (mantissa.isNegative())
        mantissa.negate();
}
bool Float::isNegative(void) const
{
    return mantissa.isNegative();
}
bool Float::isZero(void) const
{
    return !mantissa;
}

void Float::pow(const Float& number)
{
    bool negativeFlag = false;
    if (!mantissa)
    {
        if (!number.mantissa)
        {
            mantissa = 1;
            exponent = 0;
            return;
        }
        setToZero();
        return;
    }
    if (mantissa < 0)
    {
        if (number.exponent >= 0) // integer
        {
            this->negate();
            if (number.mantissa.getModByOneUnit() % 2)
                negativeFlag = true;
        }
        else
        {
            // error, raising a negative number to a non integer power
#ifndef NO_FLOAT_EXCEPTIONS
            throw logic_error("error, raising a negative number to a non integer power in Float::pow");
#endif
            return;
        }
    }
    ln();
    *this *= number;
    exp();
    if (negativeFlag)
        this->negate();
}

void Float::operator-= (const Float& number)
{
    Float temp = number;
    temp.negate();
    *this += temp;
}

Float gcd(const Float& a, const Float& b)
{
    const static Float zero(Integer(0)), one(Integer(1)), two(Integer(2));

#ifndef NO_FLOAT_EXCEPTIONS
    if (a.exponent < 0 || b.exponent < 0)
        throw invalid_argument("a or b is not a whole number in Float gcd(Float,Float)");
    if (a.mantissa < 0 || b.mantissa < 0)
        throw invalid_argument("a or b is not a positive number in Float gcd(Float,Float)");
#endif

    if (a.isZero()) return b;
    if (b.isZero()) return a;
    if (a.isEqualTo(b))    return a;
    if (a.isEqualTo(one) || b.isEqualTo(one))
        return one;

    bool aOdd = false, bOdd = false;
    if (a.exponent == 0)
        aOdd = a.mantissa.getModByOneUnit() & 1;
    if (b.exponent == 0)
        bOdd = b.mantissa.getModByOneUnit() & 1;

    if (aOdd)
    {
        if (!bOdd)
            return gcd(b, a);
        // a and b are odd
        if (a >= b)
            return gcd(a-b, b);
        return gcd(b, a);
    }

    // a is even

    if (bOdd)
    {
        Float aNew = a;
        aNew.divideByTwo();
        return gcd(aNew, b);
    }

    // a and b are even

    Float aNew = a, bNew = b;
    aNew.divideByTwo();
    bNew.divideByTwo();
    return two*gcd(aNew, bNew);
}

} /* namespace Numbers */
} /* namespace DS */
