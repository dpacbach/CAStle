/*
 * Substitution.cpp
 *
 *  Created on: Mar 3, 2013
 *      Author: davidsicilia
 */

#include "Substitution.h"

namespace DS {
namespace CAS {
namespace Expressions {
namespace Visitors {
namespace Restructurers {

Expression::Ptr Substitution::symbol(const Symbol& exp, const vector<Expression::Ptr>& children)
{
    if (exp.numberOfChildren())
        return Visitors::Restructurer::symbol(exp, children);

    map<string, Expression::Ptr>::const_iterator it = dictionary.find(exp.getName());

    if (it == dictionary.end())
        return Visitors::Restructurer::symbol(exp, children);

    return it->second;
}


} /* namespace Restructurers */
} /* namespace Visitors */
} /* namespace Expressions */
} /* namespace CAS */
} /* namespace DS */
