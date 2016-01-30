/*
 * NumberFactory.h
 *
 *  Created on: Dec 30, 2012
 *      Author: davidsicilia
 */

#ifndef NUMBERFACTORY_H_
#define NUMBERFACTORY_H_

#include <boost/noncopyable.hpp>
#include <math.h>
#include "Number.h"
#include "NumberProxy.h"

namespace DS {
namespace CAS {
namespace Numbers {

class NumberFactory : private boost::noncopyable
{
public:
    virtual ~NumberFactory() {}

    virtual Number* number(double realPart = 0, double imaginaryPart = 0) const = 0;

    // Optional methods
    virtual Number* number(const Number& number) const
    {
        return number.clone();
    }
    virtual Number* number(const Number* number) const
    {
        return number->clone();
    }

    virtual Number* operator() (double realPart = 0, double imaginaryPart = 0) const
    {
        return number(realPart, imaginaryPart);
    }
    virtual Number* operator() (const Number& number) const
    {
        return this->number(number);
    }
    virtual Number* operator() (const Number* number) const
    {
        return this->number(number);
    }

    virtual Number* zero(void)      const
    {
        return number();
    }
    virtual Number* one(void)      const
    {
        return number(1.0);
    }
    virtual Number* i(void)      const
    {
        return number(0,1.0);
    }
    virtual Number* negOne(void) const
    {
        return number(-1);
    }
    virtual Number* two(void)      const
    {
        return number(2);
    }
    virtual Number* ten(void)      const
    {
        return number(10);
    }

    virtual Number* numberFromRealParts(const Number* realPart, const Number* imaginaryPart) const
    {
        Number* newRealPart = realPart->clone();
        newRealPart->makeRealPart();
        Number* newImaginaryPart = imaginaryPart->clone();
        newImaginaryPart->makeRealPart();
        newImaginaryPart->exchangeRealAndImaginary();
        newRealPart->add(*newImaginaryPart);
        delete newImaginaryPart;
        return newRealPart;
    }
    virtual Number* numberModulusArgument(const Number* modulus, const Number* argument) const
    {
        Number *result = number(argument);
        result->multiplyByImaginaryUnit();
        result->raiseEToSelf();
        result->multiply(*modulus);
        return result;
    }
    virtual Number* numberModulusArgument(double modulus, double argument) const
    {
        double realPart = modulus*sin(argument);
        double imaginaryPart = modulus*cos(argument);
        return number(realPart, imaginaryPart);
    }

    virtual Number* PI(void) const = 0;
    virtual Number* e(void) const
    {
        Number* result = number(1.0);
        result->raiseEToSelf();
        return result;
    }
};

} } }

#endif /* NUMBERFACTORY_H_ */
