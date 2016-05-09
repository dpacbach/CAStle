#include "Add.hpp"
#include "../../visiting/Visitor.hpp"
#include <stdexcept>

namespace DS          {
namespace CAS         {
namespace Expressions {

Add::Add(const std::vector<std::pair<Sign, Expression::Ptr> >& _childPairs)
{
    if (_childPairs.size() == 0)
        throw std::invalid_argument("_childPairs == 0 in Add::Add(std::vector)");
    childPairs = _childPairs;
}


bool Add::acceptVisitor(Visitor& visitor) const
{
    return visitor.visitAdd(*this);
}
unsigned int Add::numberOfChildren(void)    const
{
    return childPairs.size();
}
Expression::Ptr Add::getChild(unsigned int i) const
{
    if (i < childPairs.size())
        return childPairs[i].second;
    throw std::out_of_range("i out of range in Add::getChild");
}
Sign Add::getSignForChild(unsigned int i) const
{
    if (i < childPairs.size())
        return childPairs[i].first;
    throw std::out_of_range("i out of range in Add::getSignForChild");
}
std::vector<Sign> Add::getSignVector(void) const
{
    std::vector<Sign> result(numberOfChildren());
    for (unsigned int i = 0; i < numberOfChildren(); i++)
        result[i] = getSignForChild(i);
    return result;
}
const std::vector<std::pair<Sign, Expression::Ptr> >& Add::getPairVector(void) const
{
    return childPairs;
}

std::pair<Sign, Expression::Ptr> Add::getChildPair(unsigned int i) const
{
    if (i < childPairs.size())
        return childPairs[i];
    throw std::out_of_range("i out of range in Add::getChildPair");
}

} /* namespace Expression */
} /* namespace CAS */
} /* namespace DS */
