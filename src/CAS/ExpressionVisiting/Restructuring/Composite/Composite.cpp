/*
 * Composite.cpp
 *
 *  Created on: Mar 16, 2013
 *      Author: davidsicilia
 */

#include "Composite.h"

namespace DS {
namespace CAS {
namespace Expressions {
namespace Visitors {
namespace Restructurers {

bool Composite::visitExpression(const Expression::Ptr exp)
{
    if (children.size() == 0)
        return false;
    Expression::Ptr result;
    if (!children[0]->visitExpression(exp))
        return false;
    result = children[0]->result();
    for (unsigned int i = 1; i < children.size(); i++)
    {
        if (!children[i]->visitExpression(result))
            return false;
        result = children[i]->result();
    }
    childResults.push(result);
    return true;
}

} /* namespace Restructurers */
} /* namespace Visitors */
} /* namespace Expressions */
} /* namespace CAS */
} /* namespace DS */
