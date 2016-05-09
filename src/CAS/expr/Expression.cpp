#include "Expression.hpp"

namespace DS          { 
namespace CAS         {
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

std::vector<Expression::Ptr> Expression::getChildVector(void)    const
{
    std::vector<Expression::Ptr> result(numberOfChildren());
    for (unsigned int i = 0; i < numberOfChildren(); i++)
        result[i] = getChild(i);
    return result;
}

} } }
