#include "Add.hpp"
#include "visiting/Visitor.hpp"
#include <stdexcept>

namespace DS          {
namespace CAS         {
namespace Expressions {

Add::Add(const vector<pair<Sign, Expression::Ptr> >& _childPairs)
{
    if (_childPairs.size() == 0)
        throw invalid_argument("_childPairs == 0 in Add::Add(vector)");
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
    throw out_of_range("i out of range in Add::getChild");
}
Sign Add::getSignForChild(unsigned int i) const
{
    if (i < childPairs.size())
        return childPairs[i].first;
    throw out_of_range("i out of range in Add::getSignForChild");
}
vector<Sign> Add::getSignVector(void) const
{
    vector<Sign> result(numberOfChildren());
    for (unsigned int i = 0; i < numberOfChildren(); i++)
        result[i] = getSignForChild(i);
    return result;
}
const vector<pair<Sign, Expression::Ptr> >& Add::getPairVector(void) const
{
    return childPairs;
}

pair<Sign, Expression::Ptr> Add::getChildPair(unsigned int i) const
{
    if (i < childPairs.size())
        return childPairs[i];
    throw out_of_range("i out of range in Add::getChildPair");
}

} /* namespace Expression */
} /* namespace CAS */
} /* namespace DS */
