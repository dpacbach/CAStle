#include "Divide.hpp"
#include "../../visiting/Visitor.hpp"
#include <stdexcept>

namespace DS          {
namespace CAS         {
namespace Expressions {

bool Divide::acceptVisitor(Visitor& visitor) const
{
    return visitor.visitDivide(*this);
}

unsigned int Divide::numberOfChildren(void)    const
{
    return 2;
}
Expression::Ptr Divide::getChild(unsigned int i) const
{
    if (i == 0)
        return numerator;
    if (i == 1)
        return denominator;
    throw std::out_of_range("i out of range in Divide::getChild");
}

} /* namespace Expression */
} /* namespace CAS */
} /* namespace DS */
