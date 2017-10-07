#include <stdexcept>
#include "Standard.hpp"
#include "Number.hpp"
#include "exprs.hpp"

namespace DS          {
namespace CAS         {
namespace Expressions {
namespace Builders    {

Standard::Standard() {
    // TODO Auto-generated constructor stub

}

Standard::~Standard() {
    // TODO Auto-generated destructor stub
}

ExprConstSP Standard::symbol(const std::string& name) const
{
    return ExprConstSP(new Symbol(name));
}
ExprConstSP Standard::symbol(const std::string& name, ExprConstSP child) const
{
    std::vector<ExprConstSP> children(1);
    children[0] = child;
    return ExprConstSP(new Symbol(name, children));
}
ExprConstSP Standard::symbol(const std::string& name, ExprConstSP ptr1, ExprConstSP ptr2) const
{
    std::vector<ExprConstSP> children(2);
    children[0] = ptr1;
    children[1] = ptr2;
    return ExprConstSP(new Symbol(name, children));
}
ExprConstSP Standard::symbol(const std::string& name, const std::vector<ExprConstSP>& children) const
{
    return ExprConstSP(new Symbol(name, children));
}
ExprConstSP Standard::literal(Numbers::Number* number) const
{
    return ExprConstSP(new Literal(number));
}
ExprConstSP Standard::literal(const Numbers::Number& number) const
{
    return ExprConstSP(new Literal(number));
}
ExprConstSP Standard::add(ExprConstSP ptr1, ExprConstSP ptr2) const
{
    std::vector<Sign> signs(2);
    signs[0] = Sign::p;
    signs[1] = Sign::p;
    return ExprConstSP(new Add({ ptr1, ptr2 }, signs));
}
ExprConstSP Standard::subtract(ExprConstSP ptr1, ExprConstSP ptr2) const
{
    std::vector<Sign> signs(2);
    signs[0] = Sign::p;
    signs[1] = Sign::n;
    return ExprConstSP(new Add( { ptr1, ptr2 }, signs));
}
ExprConstSP Standard::add(const std::vector<ExprConstSP>& children) const
{
    std::vector<Sign> signs(children.size());
    for (unsigned int i = 0; i < children.size(); i++)
        signs[i] = Sign::p;
    return ExprConstSP(new Add(children, signs));
}
ExprConstSP Standard::add(const std::vector<ExprConstSP>& children, const std::vector<Sign>& signs) const
{
    if (children.size() != signs.size())
        throw std::invalid_argument("children.size() != signs.size() in Builders::Standard::addArray");
    return ExprConstSP(new Add(children, signs));
}
ExprConstSP Standard::negate(ExprConstSP child) const
{
    return ExprConstSP(new Negate(child));
}
ExprConstSP Standard::multiply(ExprConstSP ptr1, ExprConstSP ptr2) const
{
    std::vector<ExprConstSP> children(2);
    children[0] = ptr1;
    children[1] = ptr2;
    return ExprConstSP(new Multiply(children));
}
ExprConstSP Standard::multiply(const std::vector<ExprConstSP>& children) const
{
    return ExprConstSP(new Multiply(children));
}
ExprConstSP Standard::divide(ExprConstSP top, ExprConstSP bottom) const
{
    return ExprConstSP(new Divide(top, bottom));
}
ExprConstSP Standard::modulus(ExprConstSP top, ExprConstSP bottom) const
{
    return ExprConstSP(new Modulus(top, bottom));
}
ExprConstSP Standard::power(ExprConstSP base, ExprConstSP power) const
{
    return ExprConstSP(new Power(base, power));
}
ExprConstSP Standard::factorial(ExprConstSP child) const
{
    return ExprConstSP(new Factorial(child));
}

} /* namespace Builders */
} /* namespace Expressions */
} /* namespace CAS */
} /* namespace DS */
