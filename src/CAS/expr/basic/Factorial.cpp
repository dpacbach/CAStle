#include "Factorial.hpp"
#include "../../visiting/Visitor.hpp"
#include <stdexcept>

namespace DS          {
namespace CAS         {
namespace Expressions {

bool Factorial::acceptVisitor(Visitor& visitor) const
{
    return visitor.visitFactorial(*this);
}
unsigned int  Factorial::numberOfChildren(void)    const
{
    return 1;
}
Expression::Ptr Factorial::getChild(unsigned int i) const
{
    if (i == 0)
        return child;
    throw std::out_of_range("i != 0 in Factorial::getChild");
}

} /* namespace Expression */
} /* namespace CAS */
} /* namespace DS */
