#include <stdexcept>
#include "Visitor.hpp"

namespace DS          {
namespace CAS         {
namespace Expressions {

bool Visitor::visitExpression(ExprConstSP ptr)
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

} /* namespace Expressions */
} /* namespace CAS */
} /* namespace DS */
