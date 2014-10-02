/*
 * NumberFactoryPrototype.cpp
 *
 *  Created on: Dec 30, 2012
 *      Author: davidsicilia
 */

#include "NumberFactoryPrototype.h"
#include <iostream>

using namespace std;

namespace DS {
namespace CAS {
namespace Numbers {

NumberFactoryPrototype::NumberFactoryPrototype(const NumberFactoryPrototype& factory)
{
    prototype = factory.prototype->create();
}

NumberFactoryPrototype::NumberFactoryPrototype(const Number* number)
{
    prototype = number;
}

NumberFactoryPrototype::NumberFactoryPrototype(const Number& number)
{
    prototype = number.create();
}

NumberFactoryPrototype::~NumberFactoryPrototype()
{
    delete prototype;
}

Number* NumberFactoryPrototype::number(double realPart = 0, double imaginaryPart = 0) const
{
    return prototype->create(realPart, imaginaryPart);
}

Number* NumberFactoryPrototype::PI(void) const
{
    Number* result = prototype->create();
    result->makePi();
    return result;
}
/*
NumberFactoryPrototype& NumberFactoryPrototype::operator=(const NumberFactoryPrototype& factory)
{
    delete prototype;
    prototype = factory.prototype->create();
    return *this;
}
*/
} } }
