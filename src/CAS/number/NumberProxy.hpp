/*
 * NumberProxy.h
 *
 *  Created on: Dec 27, 2012
 *      Author: David Sicilia
 */

#ifndef NUMBERPROXY_H_
#define NUMBERPROXY_H_

#include <iostream>
#include "Number.h"

namespace DS {
namespace CAS {
namespace Numbers {
namespace Proxy { // to prevent strange compiler errors

class NumberProxy : public Number {
public:
    // NumberProxy owns the number that you give it and will free on destruction
    NumberProxy(const NumberProxy& aNumberProxy) // need this otherwise compiler generates a default version
    {
        number = aNumberProxy.clone();
    }
    NumberProxy(const Number& aNumber)
    {
        number = aNumber.clone();
    }
    NumberProxy(Number* aNumber)
    {
        number = aNumber;
    }
    NumberProxy& operator= (Number* aNumber)
    {
        delete number;
        number = aNumber;
        return *this;
    }
    Number& operator= (const NumberProxy& aNumber) // need this otherwise compiler generates a default version
    {
        return operator=(static_cast<const Number&>(aNumber));
    }

    virtual ~NumberProxy()
    {
        delete number;
    }
    virtual bool isValid(void) const
    {
        return (number != NULL);
    }
    // Fowarded methods
    virtual Number* create(double realPart = 0, double imaginaryPart = 0) const { return number->create(realPart, imaginaryPart); }

    virtual void copyFrom(const Number& rhs) { number->copyFrom(rhs); }

    virtual bool isReal(void)                    const { return number->isReal();                 }
    virtual bool isImaginary(void)                const { return number->isImaginary();             }
    virtual bool isPositiveReal(void)            const { return number->isPositiveReal();         }
    virtual bool isNegativeReal(void)            const { return number->isNegativeReal();         }
    virtual bool isPositiveImaginary(void)        const { return number->isPositiveImaginary();    }
    virtual bool isNegativeImaginary(void)        const { return number->isNegativeImaginary();    }
    virtual bool isOne(void)                    const { return number->isOne();                 }
    virtual bool isImaginaryUnit(void)            const { return number->isImaginaryUnit();        }
    virtual bool isZero(void)                    const { return number->isZero();                 }
    virtual bool isNegativeOne(void)             const { return number->isNegativeOne();         }
    virtual bool isRealPartInteger(void)        const { return number->isRealPartInteger();        }
    virtual bool isImaginaryPartInteger(void)    const { return number->isImaginaryPartInteger();}
    virtual bool isInfinity(void)                 const { return number->isInfinity();             }
    virtual bool isPositiveInfinity(void)        const { return number->isPositiveInfinity();    }
    virtual bool isNegativeInfinity(void)        const { return number->isNegativeInfinity();    }
    virtual bool isNotANumber(void)             const { return number->isNotANumber();            }
    virtual operator bool(void)                    const { return number->operator bool();            }

    virtual bool isEqualReals(const Number& rhs)     const { return number->isEqualReals(rhs);        }
    virtual bool isEqualImaginary(const Number& rhs) const { return number->isEqualImaginary(rhs); }
    virtual bool isLessReals(const Number& rhs)         const { return number->isLessReals(rhs);        }
    virtual bool isLessImaginaries(const Number& rhs)const { return number->isLessImaginaries(rhs);}
    virtual bool operator< (const Number& rhs)          const { return number->operator< (rhs);       }
    virtual bool operator<= (const Number& rhs)         const { return number->operator<= (rhs);       }
    virtual bool operator> (const Number& rhs)         const { return number->operator> (rhs);       }
    virtual bool operator>= (const Number& rhs)         const { return number->operator>= (rhs);       }
    virtual bool operator< (double rhs)          const { return number->operator< (rhs);       }
    virtual bool operator<= (double rhs)         const { return number->operator<= (rhs);       }
    virtual bool operator> (double rhs)             const { return number->operator> (rhs);       }
    virtual bool operator>= (double rhs)         const { return number->operator>= (rhs);       }

    virtual void negate(void)                     { number->negate();                   }
    virtual void conjugate(void)                 { number->conjugate();                   }
    virtual void makeRealPart(void)             { number->makeRealPart();               }
    virtual void exchangeRealAndImaginary(void) { number->exchangeRealAndImaginary(); }
    virtual void modulusSquared(void)             { number->modulusSquared();           }
    virtual void modulus(void)                     { number->modulus();                   }
    virtual void argument(void)                 { number->argument();                   }

    virtual void add(const Number& rhs)          { number->add(rhs);               }
    virtual void multiply(const Number& rhs)      { number->multiply(rhs);           }
    virtual void divideBy(const Number& rhs)      { number->divideBy(rhs);           }
    virtual void naturalLog(void)                   { number->naturalLog();           }
    virtual void raiseEToSelf(void)               { number->raiseEToSelf();           }
    virtual void raiseToPower(const Number& rhs) { number->raiseToPower(rhs);       }
    virtual void GCD(const Number& second)         { number->GCD(second);              }
    virtual void makePi(void) { number->makePi(); }

    virtual Number& operator+= (const Number& rhs) { return number->operator+= (rhs); }
    virtual Number& operator-= (const Number& rhs) { return number->operator-= (rhs); }
    virtual Number& operator*= (const Number& rhs) { return number->operator*= (rhs); }
    virtual Number& operator/= (const Number& rhs) { return number->operator/= (rhs); }
    virtual Number& operator+= (double rhs) { return number->operator+= (rhs); }
    virtual Number& operator-= (double rhs) { return number->operator-= (rhs); }
    virtual Number& operator*= (double rhs) { return number->operator*= (rhs); }
    virtual Number& operator/= (double rhs) { return number->operator/= (rhs); }

    virtual Number& operator++ (void) { return number->operator++(); }
    virtual Number& operator-- (void) { return number->operator--(); }

    virtual void roundUsingMode(enum RoundingMode roundingMode) { number->roundUsingMode(roundingMode); }

    virtual const Number& implementation(void) const { return number->implementation();  }
    virtual Number& operator= (const Number& rhs)
    {
        *number = rhs;
        return *this;
    }
    virtual Number& operator= (double rhs) { return number->operator= (rhs); }

    virtual Number* clone(void) const { return number->clone();    }

    virtual bool isIntegral(void) const            { return number->isIntegral();          }
    virtual bool isComplex(void) const            { return number->isComplex();          }
    virtual bool isFiniteAndExists(void)  const { return number->isFiniteAndExists(); }

    virtual void imaginaryPart(void)     { number->imaginaryPart();        }
    virtual void fractionalPart(void)     { number->fractionalPart();    }
    virtual void makeImaginaryPart(void) { number->makeImaginaryPart();    }

    virtual bool operator== (const Number& rhs) const      { return number->operator==(rhs);            }
    virtual bool operator== (double rhs)         const      { return number->operator==(rhs);            }
    virtual bool isLessOrEqualReals(const Number& rhs)      { return number->isLessOrEqualReals(rhs);    }
    virtual bool isGreaterReals(const Number& rhs)          { return number->isGreaterReals(rhs);        }
    virtual bool isGreaterOrEqualReals(const Number& rhs) { return number->isGreaterOrEqualReals(rhs); }

    virtual void subtract(const Number& rhs)         { number->subtract(rhs);                 }
    virtual void logWithBase(const Number& base)     { number->logWithBase(base);             }
    virtual void logWithBaseTwo(void)                 { number->logWithBaseTwo();             }
    virtual void logWithBaseTen(void)                 { number->logWithBaseTen();             }
    virtual void raiseBaseToSelf(const Number& base) { number->raiseBaseToSelf(base);         }
    virtual void incRealPart(void)                     { number->incRealPart();                 }
    virtual void decRealPart(void)                     { number->decRealPart();                 }
    virtual void multiplyByImaginaryUnit(void)         { number->multiplyByImaginaryUnit();     }
    virtual void multiplyByTwo(void)                 { number->multiplyByTwo();             }
    virtual void multiplyByTen(void)                 { number->multiplyByTen();             }
    virtual void divideByTwo(void)                     { number->divideByTwo();                 }
    virtual void divideByTen(void)                     { number->divideByTen();                 }
    virtual void squareRoot(void)                     { number->squareRoot();                 }
    virtual void square(void)                         { number->square();                     }
    virtual void invert(void)                         { number->invert();                     }

    virtual void rotateByRealPartOfNumber(const Number& angle) { number->rotateByRealPartOfNumber(angle); }

protected:
    NumberProxy();
    Number* number;
};

typedef NumberProxy NumberP;

NumberProxy operator+ (const NumberProxy& lhs, const NumberProxy& rhs);
template<typename T>
NumberProxy operator+ (const NumberProxy& lhs, const T& rhs)
{
    NumberProxy result = lhs;
    result += rhs;
    return result;
}
template<typename T>
NumberProxy operator+ (const T& lhs, const NumberProxy& rhs)
{
    return rhs+lhs;
}

NumberProxy operator* (const NumberProxy& lhs, const NumberProxy& rhs);
template<typename T>
NumberProxy operator* (const NumberProxy& lhs, const T& rhs)
{
    NumberProxy result = lhs;
    result *= rhs;
    return result;
}
template<typename T>
NumberProxy operator* (const T& lhs, const NumberProxy& rhs)
{
    return rhs*lhs;
}

NumberProxy operator- (const NumberProxy& lhs, const NumberProxy& rhs);
template<typename T>
NumberProxy operator- (const NumberProxy& lhs, const T& rhs)
{
    NumberProxy result = lhs;
    result -= rhs;
    return result;
}
template<typename T>
NumberProxy operator- (const T& lhs, const NumberProxy& rhs)
{
    NumberProxy temp = rhs.create();
    temp = lhs;
    temp -= rhs;
    return temp;
}

NumberProxy operator/ (const NumberProxy& lhs, const NumberProxy& rhs);
template<typename T>
NumberProxy operator/ (const NumberProxy& lhs, const T& rhs)
{
    NumberProxy result = lhs;
    result /= rhs;
    return result;
}
template<typename T>
NumberProxy operator/ (const T& lhs, const NumberProxy& rhs)
{
    NumberProxy temp = rhs.create();
    temp = lhs;
    temp /= rhs;
    return temp;
}

NumberProxy operator- (const NumberProxy& number);
NumberProxy sqrt(const NumberProxy& number);
NumberProxy exp(const NumberProxy& number);
NumberProxy ln(const NumberProxy& number);
NumberProxy pow(const NumberProxy& base, const NumberProxy& power);



} } } }

#endif
