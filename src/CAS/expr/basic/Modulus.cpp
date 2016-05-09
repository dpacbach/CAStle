#include "Modulus.hpp"
#include "../../visiting/Visitor.hpp"
#include <stdexcept>

namespace DS          {
namespace CAS         {
namespace Expressions {

bool Modulus::acceptVisitor(Visitor& visitor) const
{
    return visitor.visitModulus(*this);
}

unsigned int  Modulus::numberOfChildren(void)    const
{
    return 2;
}
Expression::Ptr Modulus::getChild(unsigned int i) const
{
    if (i == 0)
        return numerator;
    if (i == 1)
        return denominator;
    throw std::out_of_range("i out of range in Modulus::getChild");
}

} /* namespace Expression */
} /* namespace CAS */
} /* namespace DS */
