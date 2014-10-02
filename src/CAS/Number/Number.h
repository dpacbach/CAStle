/*
 * Number.h
 *
 *  Created on: Dec 23, 2012
 *      Author: David Sicilia
 *
 *  Interface for Complex Number Class
 */

#ifndef NUMBER_H_
#define NUMBER_H_

#include <boost/noncopyable.hpp>

namespace DS {
namespace CAS {
namespace Numbers {

class Number : private boost::noncopyable
{
public:
    virtual Number* create(double realPart = 0, double imaginaryPart = 0) const = 0;
    virtual void     copyFrom(const Number&) = 0;

    virtual bool isReal(void)                    const = 0;
    virtual bool isImaginary(void)                const = 0;
    virtual bool isPositiveReal(void)            const = 0;
    virtual bool isNegativeReal(void)            const = 0;
    virtual bool isPositiveImaginary(void)        const = 0;
    virtual bool isNegativeImaginary(void)        const = 0;
    virtual bool isOne(void)                    const = 0;
    virtual bool isImaginaryUnit(void)            const = 0;
    virtual bool isZero(void)                    const = 0;
    virtual bool isNegativeOne(void)            const = 0;
    virtual bool isRealPartInteger(void)        const = 0;
    virtual bool isImaginaryPartInteger(void)    const = 0;
    virtual bool isInfinity(void)                 const = 0;
    virtual bool isPositiveInfinity(void)        const = 0;
    virtual bool isNegativeInfinity(void)        const = 0;
    virtual bool isNotANumber(void)                const = 0;

    virtual bool isEqualReals(const Number&)     const = 0;
    virtual bool isEqualImaginary(const Number&) const = 0;
    virtual bool isLessReals(const Number&)         const = 0;
    virtual bool isLessImaginaries(const Number&)const = 0;

    virtual void negate(void)                     = 0;
    virtual void conjugate(void)                 = 0;
    virtual void makeRealPart(void)             = 0;
    virtual void exchangeRealAndImaginary(void) = 0;
    virtual void modulusSquared(void)             = 0;
    virtual void modulus(void)                     = 0;
    virtual void argument(void)                 = 0;

    virtual void add(const Number&)              = 0;
    virtual void multiply(const Number&)          = 0;
    virtual void divideBy(const Number&)          = 0;
    virtual void naturalLog(void)                  = 0;
    virtual void raiseEToSelf(void)              = 0;
    virtual void raiseToPower(const Number&)     = 0;
    virtual void GCD(const Number&)                = 0;

    virtual void makePi(void)                    = 0;

    enum RoundingMode {RoundDown, RoundUp, RoundClosest};
    virtual void roundUsingMode(enum RoundingMode roundingMode) = 0;

    // Optional to override
    virtual operator bool() const
    {
        return !isZero();
    }

    virtual bool operator<  (const Number& rhs) const
    {
        return isLessReals(rhs);
    }
    virtual bool operator<= (const Number& rhs) const
    {
        return (isLessReals(rhs) || isEqualReals(rhs));
    }
    virtual bool operator>  (const Number& rhs) const
    {
        return !(isLessReals(rhs) || isEqualReals(rhs));
    }
    virtual bool operator>= (const Number& rhs) const
    {
        return !isLessReals(rhs);
    }
    virtual bool operator<  (double rhs) const
    {
        Number* temp = this->create(rhs);
        bool result = isLessReals(*temp);
        delete temp;
        return result;
    }
    virtual bool operator<= (double rhs) const
    {
        Number* temp = this->create(rhs);
        bool result = (isLessReals(*temp) || isEqualReals(*temp));
        delete temp;
        return result;
    }
    virtual bool operator>  (double rhs) const
    {
        Number* temp = this->create(rhs);
        bool result = !(isLessReals(*temp) || isEqualReals(*temp));
        delete temp;
        return result;
    }
    virtual bool operator>= (double rhs) const
    {
        Number* temp = this->create(rhs);
        bool result = !isLessReals(*temp);
        delete temp;
        return result;
    }

    virtual Number& operator+= (const Number& rhs)
    {
        add(rhs);
        return *this;
    }
    virtual Number& operator-= (const Number& rhs)
    {
        subtract(rhs);
        return *this;
    }
    virtual Number& operator*= (const Number& rhs)
    {
        multiply(rhs);
        return *this;
    }
    virtual Number& operator/= (const Number& rhs)
    {
        divideBy(rhs);
        return *this;
    }
    virtual Number& operator++ (void)
    {
        incRealPart();
        return *this;
    }
    virtual Number& operator-- (void)
    {
        decRealPart();
        return *this;
    }

    virtual Number& operator+= (double rhs)
    {
        Number* temp = this->create(rhs);
        add(*temp);
        delete temp;
        return *this;
    }
    virtual Number& operator-= (double rhs)
    {
        Number* temp = this->create(rhs);
        subtract(*temp);
        delete temp;
        return *this;
    }
    virtual Number& operator*= (double rhs)
    {
        Number* temp = this->create(rhs);
        multiply(*temp);
        delete temp;
        return *this;
    }
    virtual Number& operator/= (double rhs)
    {
        Number* temp = this->create(rhs);
        divideBy(*temp);
        delete temp;
        return *this;
    }

    virtual const Number& implementation(void) const
    {
        return *this;
    }
    virtual Number& operator= (const Number& rhs)
    {
        copyFrom(rhs);
        return *this;
    }
    virtual Number& operator= (double rhs)
    {
        Number* temp = create(rhs);
        copyFrom(*temp);
        delete temp;
        return *this;
    }

    virtual Number* clone(void) const
    {
        Number* copy = create(0);
        copy->copyFrom(*this);
        return copy;
    }

    virtual ~Number() {};

    virtual bool isIntegral(void) const
    {
        return isRealPartInteger() && isImaginaryPartInteger();
    }
    virtual bool isComplex(void) const
    {
        return !(isReal() || isImaginary());
    }
    virtual bool isFiniteAndExists(void)  const
    {
        return (!isNotANumber() && !isInfinity());
    }
    virtual void imaginaryPart(void)
    {
        exchangeRealAndImaginary();
        makeRealPart();
    }
    virtual void fractionalPart(void)
    {
        Number* wholePart = clone();
        wholePart->roundUsingMode(RoundDown);
        this->subtract(*wholePart);
        delete wholePart;
    }
    virtual void makeImaginaryPart(void)
    {
        exchangeRealAndImaginary();
        makeRealPart();
        exchangeRealAndImaginary();
    }
    virtual bool operator== (const Number& rhs) const
    {
        return (isEqualReals(rhs) && isEqualImaginary(rhs));
    }
    virtual bool operator== (double rhs) const
    {
        Number* temp = create(rhs);
        bool result = (*this == *temp);
        delete temp;
        return result;
    }
    virtual bool isLessOrEqualReals(const Number& rhs)
    {
        return (isLessReals(rhs) || (*this == rhs));
    }
    virtual bool isGreaterReals(const Number& rhs)
    {
        return (!isLessReals(rhs) && !(*this == rhs));
    }
    virtual bool isGreaterOrEqualReals(const Number& rhs)
    {
        return !isLessReals(rhs);
    }

    virtual void subtract(const Number& aNumber)
    {
        Number *i = aNumber.clone();
        i->negate();
        add(*i);
        delete i;
    }
    virtual void logWithBase(const Number& base)
    {
        Number* logBase = base.clone();
        logBase->naturalLog();
        naturalLog();
        divideBy(*logBase);
        delete logBase;
    }
    virtual void logWithBaseTwo(void)
    {
        Number* i = create(2);
        logWithBase(*i);
        delete i;
    }
    virtual void logWithBaseTen(void)
    {
        Number* i = create(10);
        logWithBase(*i);
        delete i;
    }
    virtual void raiseBaseToSelf(const Number& base)
    {
        Number* i = base.clone();
        i->naturalLog();
        multiply(*i);
        raiseEToSelf();
        delete i;
    }
    virtual void incRealPart(void)
    {
        Number* one = create(1);
        add(*one);
        delete one;
    }
    virtual void decRealPart(void)
    {
        Number* negativeOne = create(-1);
        add(*negativeOne);
        delete negativeOne;
    }
    virtual void multiplyByImaginaryUnit(void)
    {
        Number* i = create(0,1);
        multiply(*i);
        delete i;
    }
    virtual void multiplyByTwo(void)
    {
        Number* i = create(2);
        multiply(*i);
        delete i;
    }
    virtual void multiplyByTen(void)
    {
        Number* i = create(10);
        multiply(*i);
        delete i;
    }
    virtual void divideByTwo(void)
    {
        Number* i = create(2);
        divideBy(*i);
        delete i;
    }
    virtual void divideByTen(void)
    {
        Number* i = create(10);
        divideBy(*i);
        delete i;
    }
    virtual void squareRoot(void)
    {
        Number* i = create(0.5, 0);
        raiseToPower(*i);
        delete i;
    }
    virtual void square(void)
    {
        multiply(*this);
    }
    virtual void invert(void)
    {
        Number* i = create(1);
        i->divideBy(*this);
        *this = *i;
        delete i;
    }
    virtual void rotateByRealPartOfNumber(const Number& angle)
    {
        Number* i = angle.clone();
        i->multiplyByImaginaryUnit();
        i->raiseEToSelf();
        multiply(*i);
        delete i;
    }
};

// use these instead of dynamic_cast to cast downcast in the Number hierarchy
template<typename TO>
inline TO number_cast(const Number* from)
{
    return dynamic_cast<TO>(from->implementation());
}
template<typename TO>
inline TO number_cast(const Number& from)
{
    return dynamic_cast<TO>(from.implementation());
}

} } }

#endif
