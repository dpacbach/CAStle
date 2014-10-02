/*
 * ExpressionNegate.cpp
 *
 *  Created on: Jan 11, 2013
 *      Author: davidsicilia
 */

#include <stdexcept>
#include "Negate.h"
#include "../../ExpressionVisiting/Visitor.h"

namespace DS {
namespace CAS {
namespace Expressions {

bool Negate::acceptVisitor(Visitor& visitor) const
{
    return visitor.visitNegate(*this);
}

Expression::Ptr Negate::getChild(unsigned int i) const
{
    if (i == 0)
        return child;
    throw out_of_range("i != 0 in Expressions::Negate.getChild");
}

} /* namespace Expression */
} /* namespace CAS */
} /* namespace DS */
