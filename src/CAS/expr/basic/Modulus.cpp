/*
 * ExpressionModulus.cpp
 *
 *  Created on: Jan 11, 2013
 *      Author: davidsicilia
 */

#include "Modulus.h"
#include "../../ExpressionVisiting/Visitor.h"
#include <stdexcept>

namespace DS {
namespace CAS {
namespace Expressions {

bool Modulus::acceptVisitor(Visitor& visitor) const
{
    return visitor.visitModulus(*this);
}

unsigned int  Modulus::numberOfChildren(void)    const
{
    return 2;
}
Expression::Ptr Modulus::getChild(unsigned int i) const
{
    if (i == 0)
        return numerator;
    if (i == 1)
        return denominator;
    throw out_of_range("i out of range in Modulus::getChild");
}

} /* namespace Expression */
} /* namespace CAS */
} /* namespace DS */
