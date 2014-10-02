/*
 * ExpressionPower.cpp
 *
 *  Created on: Jan 11, 2013
 *      Author: davidsicilia
 */

#include "Power.h"
#include "../../ExpressionVisiting/Visitor.h"
#include <stdexcept>

namespace DS {
namespace CAS {
namespace Expressions {

bool Power::acceptVisitor(Visitor& visitor) const
{
    return visitor.visitPower(*this);
}

unsigned int  Power::numberOfChildren(void)    const
{
    return 2;
}
Expression::Ptr Power::getChild(unsigned int i) const
{
    if (i == 0)
        return base;
    if (i == 1)
        return exponent;
    throw out_of_range("i out of range in Power::getChild");
}

} /* namespace Expression */
} /* namespace CAS */
} /* namespace DS */
