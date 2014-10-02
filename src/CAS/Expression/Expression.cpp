/*
 * Expression.cpp
 *
 *  Created on: Jan 11, 2013
 *      Author: davidsicilia
 */

#include "Expression.h"
#include "../ExpressionVisiting/Visitor.h"

namespace DS {
namespace CAS {
namespace Expressions {

int Expression::numberOfExpressions(0);

Expression::Expression()
{
    numberOfExpressions++;
}

Expression::~Expression()
{
    numberOfExpressions--;
}

vector<Expression::Ptr> Expression::getChildVector(void)    const
{
    vector<Expression::Ptr> result(numberOfChildren());
    for (unsigned int i = 0; i < numberOfChildren(); i++)
        result[i] = getChild(i);
    return result;
}

} } }
