/*
 * ExpressionFactorial.cpp
 *
 *  Created on: Jan 11, 2013
 *      Author: davidsicilia
 */

#include "Factorial.h"
#include "../../ExpressionVisiting/Visitor.h"
#include <stdexcept>

namespace DS {
namespace CAS {
namespace Expressions {

bool Factorial::acceptVisitor(Visitor& visitor) const
{
    return visitor.visitFactorial(*this);
}
unsigned int  Factorial::numberOfChildren(void)    const
{
    return 1;
}
Expression::Ptr Factorial::getChild(unsigned int i) const
{
    if (i == 0)
        return child;
    throw out_of_range("i != 0 in Factorial::getChild");
}

} /* namespace Expression */
} /* namespace CAS */
} /* namespace DS */
