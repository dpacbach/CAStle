/*
 * ExpressionSymbol.cpp
 *
 *  Created on: Jan 11, 2013
 *      Author: davidsicilia
 */

#include "Symbol.h"
#include "../../ExpressionVisiting/Visitor.h"
#include <stdexcept>

namespace DS {
namespace CAS {
namespace Expressions {

bool Symbol::acceptVisitor(Visitor& visitor) const
{
    return visitor.visitSymbol(*this);
}
unsigned int  Symbol::numberOfChildren(void) const
{
    return children.size();
}
Expression::Ptr Symbol::getChild(unsigned int i) const
{
    if (i < children.size())
        return children[i];
    throw out_of_range("i out of range in Symbol::getChild");
}

const string& Symbol::getName(void) const
{
    return name;
}

} /* namespace Expression */
} /* namespace CAS */
} /* namespace DS */
