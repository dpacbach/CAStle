/*
 * ExpressionMultiply.cpp
 *
 *  Created on: Jan 11, 2013
 *      Author: davidsicilia
 */

#include "Multiply.h"
#include "../../ExpressionVisiting/Visitor.h"
#include <stdexcept>

namespace DS {
namespace CAS {
namespace Expressions {

Multiply::Multiply(const vector<Expression::Ptr>& _children)
{
    if (_children.size() == 0)
        throw invalid_argument("_children == 0 in Multiply::Multiply(vector)");
    children = _children;
}

bool Multiply::acceptVisitor(Visitor& visitor) const
{
    return visitor.visitMultiply(*this);
}
unsigned int Multiply::numberOfChildren(void)    const
{
    return children.size();
}
Expression::Ptr Multiply::getChild(unsigned int i) const
{
    if (i < children.size())
        return children[i];
    throw out_of_range("i out of range in Multiply::getChild");
}

} /* namespace Expression */
} /* namespace CAS */
} /* namespace DS */
