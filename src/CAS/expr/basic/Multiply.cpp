#include "Multiply.hpp"
#include "../../visiting/Visitor.hpp"
#include <stdexcept>

namespace DS          {
namespace CAS         {
namespace Expressions {

Multiply::Multiply(const std::vector<Expression::Ptr>& _children)
{
    if (_children.size() == 0)
        throw std::invalid_argument("_children == 0 in Multiply::Multiply(vector)");
    children = _children;
}

bool Multiply::acceptVisitor(Visitor& visitor) const
{
    return visitor.visitMultiply(*this);
}
unsigned int Multiply::numberOfChildren(void)    const
{
    return children.size();
}
Expression::Ptr Multiply::getChild(unsigned int i) const
{
    if (i < children.size())
        return children[i];
    throw std::out_of_range("i out of range in Multiply::getChild");
}

} /* namespace Expression */
} /* namespace CAS */
} /* namespace DS */
