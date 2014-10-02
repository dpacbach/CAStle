/*
 * NumberDouble.h
 *
 *  Created on: Dec 27, 2012
 *      Author: davidsicilia
 */

#ifndef NumberDouble_H_
#define NumberDouble_H_

#include <iostream>
#include <stdexcept>
#include <cmath>
#include "../../../Number.h"

using namespace std;

namespace DS {
namespace CAS {
namespace Numbers {

template<typename T>
class NumberDouble : public Number
{
public:
    NumberDouble() {}
    NumberDouble(const T& _real, const T& _imaginary = 0) : realPart(_real), imaginaryPart(_imaginary) { }
    NumberDouble(const NumberDouble<T>& number) : realPart(number.realPart), imaginaryPart(number.imaginaryPart) { }

    virtual ~NumberDouble() { }

    T getRealPart(void) const         { return realPart;         }
    T getImaginaryPart(void) const { return imaginaryPart; }

    virtual Number* create(double _realPart = 0, double _imaginaryPart = 0) const { return new NumberDouble<T>(_realPart, _imaginaryPart); }

    virtual void copyFrom(const Number& rhs);

    virtual bool isReal(void)                    const;
    virtual bool isImaginary(void)                const;
    virtual bool isPositiveReal(void)            const;
    virtual bool isNegativeReal(void)            const;
    virtual bool isPositiveImaginary(void)        const;
    virtual bool isNegativeImaginary(void)        const;
    virtual bool isOne(void)                    const;
    virtual bool isImaginaryUnit(void)            const;
    virtual bool isZero(void)                    const;
    virtual bool isNegativeOne(void)             const;
    virtual bool isRealPartInteger(void)        const;
    virtual bool isImaginaryPartInteger(void)    const;
    virtual bool isInfinity(void)                 const;
    virtual bool isPositiveInfinity(void)        const;
    virtual bool isNegativeInfinity(void)        const;
    virtual bool isNotANumber(void)             const;

    virtual bool isEqualReals(const Number&)     const;
    virtual bool isEqualImaginary(const Number&) const;
    virtual bool isLessReals(const Number&)         const;
    virtual bool isLessImaginaries(const Number&)const;

    virtual void negate(void);
    virtual void conjugate(void);
    virtual void makeRealPart(void);
    virtual void exchangeRealAndImaginary(void);
    virtual void modulusSquared(void);
    virtual void modulus(void);
    virtual void argument(void);

    virtual void add(const Number&);
    virtual void multiply(const Number&);
    virtual void divideBy(const Number&);
    virtual void naturalLog(void);
    virtual void raiseEToSelf(void);
    virtual void raiseToPower(const Number&);
    virtual void GCD(const Number&);

    virtual void makePi(void);

    virtual void roundUsingMode(enum RoundingMode roundingMode);

protected:
    T realPart;
    T imaginaryPart;
};

template<typename T>
void NumberDouble<T>::copyFrom(const Number& _rhs)
{
    const NumberDouble<T>& rhs = number_cast<const NumberDouble<T>&>(_rhs);

    realPart = rhs.realPart;
    imaginaryPart = rhs.imaginaryPart;
}
template<typename T>
bool NumberDouble<T>::isReal(void)              const
{
    return (imaginaryPart == 0);
}
template<typename T>
bool NumberDouble<T>::isImaginary(void)          const
{
    return ((realPart == 0) && (imaginaryPart != 0));
}
template<typename T>
bool NumberDouble<T>::isPositiveReal(void)      const
{
    return (isReal() && realPart > 0);
}
template<typename T>
bool NumberDouble<T>::isNegativeReal(void)      const
{
    return (isReal() && realPart < 0);
}
template<typename T>
bool NumberDouble<T>::isPositiveImaginary(void)      const
{
    return (isImaginary() && imaginaryPart > 0);
}
template<typename T>
bool NumberDouble<T>::isNegativeImaginary(void)      const
{
    return (isImaginary() && imaginaryPart < 0);
}
template<typename T>
bool NumberDouble<T>::isOne(void)              const
{
    return ((realPart == 1) && (imaginaryPart == 0));
}
template<typename T>
bool NumberDouble<T>::isImaginaryUnit(void)      const
{
    return ((realPart == 0) && (imaginaryPart == 1));
}
template<typename T>
bool NumberDouble<T>::isZero(void)              const
{
    return ((realPart == 0) && (imaginaryPart == 0));
}
template<typename T>
bool NumberDouble<T>::isNegativeOne(void)       const
{
    return ((realPart == -1) && (imaginaryPart == 0));
}
template<typename T>
bool NumberDouble<T>::isRealPartInteger(void)  const
{
    // add/sub .5 in the floor to round to nearest integer
    // This is eliminate problems with minute trucation errors
    T push(.5);
    if (realPart < 0)
        push = -push;
    return (realPart == floor(realPart+push));
}
template<typename T>
bool NumberDouble<T>::isImaginaryPartInteger(void)  const
{
    // add/sub .5 in the floor to round to nearest integer
    // This is eliminate problems with minute trucation errors
    T push(.5);
    if (imaginaryPart < 0)
        push = -push;
    return (imaginaryPart == floor(imaginaryPart+push));
}
template<typename T>
bool NumberDouble<T>::isInfinity(void)           const
{
    return false;//(isinf(realPart) || isinf(imaginaryPart));
}
template<typename T>
bool NumberDouble<T>::isPositiveInfinity(void) const
{
    return false;//(isinf(realPart) && realPart > 0);
}
template<typename T>
bool NumberDouble<T>::isNegativeInfinity(void) const
{
    return false;//(isinf(realPart) && realPart < 0);
}
template<typename T>
bool NumberDouble<T>::isNotANumber(void)       const
{
    return false;//(isnan(realPart) || isnan(imaginaryPart));
}

template<typename T>
bool NumberDouble<T>::isEqualReals(const Number& _rhs)     const
{
    const NumberDouble<T>& rhs = number_cast<const NumberDouble<T>&>(_rhs);
    return realPart == rhs.realPart;
}
template<typename T>
bool NumberDouble<T>::isEqualImaginary(const Number& _rhs) const
{
    const NumberDouble<T>& rhs = number_cast<const NumberDouble<T>&>(_rhs);
    return imaginaryPart == rhs.imaginaryPart;
}
template<typename T>
bool NumberDouble<T>::isLessReals(const Number& _rhs)         const
{
    const NumberDouble<T>& rhs = number_cast<const NumberDouble<T>&>(_rhs);
    return realPart < rhs.realPart;
}
template<typename T>
bool NumberDouble<T>::isLessImaginaries(const Number& _rhs)         const
{
    const NumberDouble<T>& rhs = number_cast<const NumberDouble<T>&>(_rhs);
    return imaginaryPart < rhs.imaginaryPart;
}

template<typename T>
void NumberDouble<T>::negate(void)
{
    realPart = -realPart;
    imaginaryPart = -imaginaryPart;
}
template<typename T>
void NumberDouble<T>::conjugate(void)
{
    imaginaryPart = -imaginaryPart;
}
template<typename T>
void NumberDouble<T>::makeRealPart(void)
{
    imaginaryPart = 0;
}
template<typename T>
void NumberDouble<T>::exchangeRealAndImaginary(void)
{
    T temp = realPart;
    realPart = imaginaryPart;
    imaginaryPart = temp;
}
template<typename T>
void NumberDouble<T>::modulusSquared(void)
{
    realPart = realPart*realPart + imaginaryPart*imaginaryPart;
    imaginaryPart = 0;
}
template<typename T>
void NumberDouble<T>::modulus(void)
{
    if (imaginaryPart == 0)
    {
        realPart = abs(realPart);
        return;
    }
    realPart = sqrt(realPart*realPart + imaginaryPart*imaginaryPart);
    imaginaryPart = 0;
}
inline void createPi(double& number)
{
    number = 3.141592653589793238462643383279;
}
template<typename T>
void NumberDouble<T>::argument(void)
{
    T pi;
    createPi(pi);
    T argument;
    if (realPart == 0 && imaginaryPart == 0)
        realPart = imaginaryPart = 0;
    if (realPart == 0)
    {
        if (imaginaryPart >= 0)
            argument =  pi*T(1)/T(2);
        else
            argument = -pi*T(1)/T(2);
    }
    else if (imaginaryPart == 0)
    {
        if (realPart > 0)
            argument = 0;
        else
            argument = pi;
    }
    else
    {
        if (realPart > 0)
            argument = atan(imaginaryPart/realPart);
        else if (imaginaryPart >= 0)
            argument =  pi + atan(imaginaryPart/realPart);
        else
            argument = -pi + atan(imaginaryPart/realPart);
    }
    realPart = argument;
    imaginaryPart = 0;
}

template<typename T>
void NumberDouble<T>::add(const Number& _rhs)
{
    const NumberDouble<T>& rhs = number_cast<const NumberDouble<T>&>(_rhs);
    realPart += rhs.realPart;
    imaginaryPart += rhs.imaginaryPart;
}
template<typename T>
void NumberDouble<T>::multiply(const Number& _rhs)
{
    const NumberDouble<T>& rhs = number_cast<const NumberDouble<T>&>(_rhs);
    T _realPart       = realPart*rhs.realPart - imaginaryPart*rhs.imaginaryPart;
    T _imaginaryPart = realPart*rhs.imaginaryPart + imaginaryPart*rhs.realPart;
    realPart = _realPart;
    imaginaryPart = _imaginaryPart;
}
template<typename T>
void NumberDouble<T>::divideBy(const Number& _rhs)
{
    const NumberDouble<T>& rhs = number_cast<const NumberDouble<T>&>(_rhs);
    T _realPart      = rhs.realPart;
    T _imaginaryPart = rhs.imaginaryPart;
    T modSquared = _realPart*_realPart + _imaginaryPart*_imaginaryPart;
    if (modSquared == 0)
    {
        throw invalid_argument("divide by zero in NumberDouble<T>::divideBy()");
    }
    _imaginaryPart = -_imaginaryPart;
    T realPartResult      = (realPart*_realPart - imaginaryPart*_imaginaryPart)/modSquared;
    T imaginaryPartResult = (realPart*_imaginaryPart + _realPart*imaginaryPart)/modSquared;
    realPart = realPartResult;
    imaginaryPart = imaginaryPartResult;
}
inline double ln(double arg)
{
    return log(arg);
}
template<typename T>
void NumberDouble<T>::naturalLog(void)
{
    T realResult = ln(sqrt(realPart*realPart + imaginaryPart*imaginaryPart));
    argument();
    exchangeRealAndImaginary();
    realPart = realResult;
}
template<typename T>
void NumberDouble<T>::raiseEToSelf(void)
{
    T _realPart      = exp(realPart)*cos(imaginaryPart);
    T _imaginaryPart = exp(realPart)*sin(imaginaryPart);
    realPart = _realPart;
    imaginaryPart = _imaginaryPart;
}
template<typename T>
void NumberDouble<T>::raiseToPower(const Number& _rhs)
{
    const NumberDouble<T>& rhs = number_cast<const NumberDouble<T>&>(_rhs);

    if (isZero() && !rhs.isZero())
        return;
    if (rhs.isZero())
    {
        realPart = 1.0;
        imaginaryPart = 0;
        return;
    }
    naturalLog();
    multiply(rhs);
    raiseEToSelf();
}

inline double gcd(const double& _a, const double& _b)
{
    unsigned long a = (unsigned long)_a;
    unsigned long b = (unsigned long)_b;

    if (a == 0)    return b;
    if (b == 0)    return a;
    if (a == b)    return a;
    if (a == 1 || b == 1)
        return 1;

    if (a % 2 == 1)
    {
        if (b % 1 == 0)
            return gcd(b, a);
        // a and b are odd
        if (a >= b)
            return gcd(a-b, b);
        return gcd(b, a);
    }

    // a is even

    if (b % 2 == 1)
        return gcd(a/2, b);

    // a and b are even

    return 2*gcd(a/2, b/2);
}
template<typename T>
void NumberDouble<T>::GCD(const Number& _second)
{
    const NumberDouble<T>& second = number_cast<const NumberDouble<T>&>(_second);

    if (!this->isReal() || !second.isReal())
        throw invalid_argument("arguments not real in NumberDouble<T>::GCD()");
    if (!this->isRealPartInteger() || !second.isRealPartInteger())
        throw invalid_argument("arguments not whole numbers in NumberDouble<T>::GCD()");

    this->roundUsingMode(RoundClosest);
    NumberDouble<T> temp = second;
    temp.roundUsingMode(RoundClosest);

    if (this->isNegativeReal() || temp.isNegativeReal())
        throw invalid_argument("arguments not positive in NumberDouble<T>::GCD()");

    realPart = gcd(realPart, temp.realPart);
}

template<typename T>
void NumberDouble<T>::makePi(void)
{
    imaginaryPart = 0;
    createPi(realPart);
}

template<typename T>
void NumberDouble<T>::roundUsingMode(enum RoundingMode roundingMode)
{
    static T one(1.0), oneHalf(T(1.0)/T(2.0));
    T push;
    switch (roundingMode)
    {
        case RoundDown:
            realPart = floor(realPart);
            imaginaryPart = floor(imaginaryPart);
            break;
        case RoundUp:
            push = one;
            if (realPart < 0)
                push = -push;
            realPart = (T)(floor(realPart+push));
            push = one;
            if (imaginaryPart < 0)
                push = -push;
            imaginaryPart = (T)(floor(imaginaryPart+push));
            break;
        case RoundClosest:
            push = oneHalf;
            if (realPart < 0)
                push = -push;
            realPart = (T)(floor(realPart+push));
            push = oneHalf;
            if (imaginaryPart < 0)
                push = -push;
            imaginaryPart = (T)(floor(imaginaryPart+push));
            break;
        default:
            throw invalid_argument("unrecognized rounding mode in NumberDouble<T>::roundUsingMode()");
    }

}

} } }
#endif /* NumberDouble_H_ */
