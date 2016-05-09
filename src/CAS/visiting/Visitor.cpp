/*
 * Visitor.cpp
 *
 *  Created on: Jan 11, 2013
 *      Author: davidsicilia
 */

#include <stdexcept>
#include "Visitor.h"

namespace DS {
namespace CAS {
namespace Expressions {

bool Visitor::visitExpression(const Expression::Ptr ptr)
{
    unsigned int numberOfChildren = ptr->numberOfChildren();
    for (unsigned int index = 0; index < numberOfChildren; index++)
    {
        if (!visitExpression(ptr->getChild(index)))
        {
            reset();
            return false;
        }
    }
    if (!(ptr->acceptVisitor(*this)))
    {
        reset();
        return false;
    }
    return true;
}

} /* namespace Expression */
} /* namespace CAS */
} /* namespace DS */
