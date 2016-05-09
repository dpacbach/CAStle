#include "Symbol.hpp"
#include "../../visiting/Visitor.hpp"
#include <stdexcept>

namespace DS          {
namespace CAS         {
namespace Expressions {

bool Symbol::acceptVisitor(Visitor& visitor) const
{
    return visitor.visitSymbol(*this);
}
unsigned int  Symbol::numberOfChildren(void) const
{
    return children.size();
}
Expression::Ptr Symbol::getChild(unsigned int i) const
{
    if (i < children.size())
        return children[i];
    throw std::out_of_range("i out of range in Symbol::getChild");
}

const std::string& Symbol::getName(void) const
{
    return name;
}

} /* namespace Expression */
} /* namespace CAS */
} /* namespace DS */
