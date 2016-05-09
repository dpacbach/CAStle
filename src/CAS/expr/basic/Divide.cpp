/*
 * ExpressionDivide.cpp
 *
 *  Created on: Jan 11, 2013
 *      Author: davidsicilia
 */

#include "Divide.h"
#include "../../ExpressionVisiting/Visitor.h"
#include <stdexcept>

namespace DS {
namespace CAS {
namespace Expressions {

bool Divide::acceptVisitor(Visitor& visitor) const
{
    return visitor.visitDivide(*this);
}

unsigned int Divide::numberOfChildren(void)    const
{
    return 2;
}
Expression::Ptr Divide::getChild(unsigned int i) const
{
    if (i == 0)
        return numerator;
    if (i == 1)
        return denominator;
    throw out_of_range("i out of range in Divide::getChild");
}

} /* namespace Expression */
} /* namespace CAS */
} /* namespace DS */
