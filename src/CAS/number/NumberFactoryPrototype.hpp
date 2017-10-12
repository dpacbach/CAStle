#pragma once

#include "NumberFactory.hpp"

namespace DS {
namespace CAS {
namespace Numbers {

class NumberFactoryPrototype: public NumberFactory
{
public:
    NumberFactoryPrototype(const Number*);
    NumberFactoryPrototype(const Number&);
    NumberFactoryPrototype(const NumberFactoryPrototype&);
    virtual ~NumberFactoryPrototype();

    //NumberFactoryPrototype& operator=(const NumberFactoryPrototype&);

    virtual Number* number(double realPart, double imaginaryPart) const;
    virtual Number* PI(void) const;

protected:
    const Number* prototype;
};

} } }
