#include <stdexcept>
#include "Visitor.hpp"

namespace DS          {
namespace CAS         {
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
