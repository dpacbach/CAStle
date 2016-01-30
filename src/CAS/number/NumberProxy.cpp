/*
 * NumberProxy.cpp
 *
 *  Created on: Dec 27, 2012
 *      Author: davidsicilia
 */

#include "NumberProxy.h"

namespace DS {
namespace CAS {
namespace Numbers {
namespace Proxy {

NumberProxy operator- (const NumberProxy& number)
{
    NumberProxy result = number;
    result.negate();
    return result;
}

NumberProxy operator+ (const NumberProxy& lhs, const NumberProxy& rhs)
{
    NumberProxy result = lhs;
    result += rhs;
    return result;
}
NumberProxy operator- (const NumberProxy& lhs, const NumberProxy& rhs)
{
    NumberProxy result = lhs;
    result -= rhs;
    return result;
}
NumberProxy operator* (const NumberProxy& lhs, const NumberProxy& rhs)
{
    NumberProxy result = lhs;
    result *= rhs;
    return result;
}
NumberProxy operator/ (const NumberProxy& lhs, const NumberProxy& rhs)
{
    NumberProxy result = lhs;
    result /= rhs;
    return result;
}

NumberProxy sqrt(const NumberProxy& number)
{
    NumberProxy result = number;
    result.squareRoot();
    return result;
}
NumberProxy exp(const NumberProxy& number)
{
    NumberProxy result = number;
    result.raiseEToSelf();
    return result;
}
NumberProxy ln(const NumberProxy& number)
{
    NumberProxy result = number;
    result.naturalLog();
    return result;
}
NumberProxy pow(const NumberProxy& base, const NumberProxy& power)
{
    NumberProxy result = base;
    result.raiseToPower(power);
    return result;
}
}
}
}
}
