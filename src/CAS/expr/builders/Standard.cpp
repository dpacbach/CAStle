#include <stdexcept>
#include "Standard.hpp"
#include "Number.hpp"
#include "AllBasic.hpp"

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

Expression::Ptr Standard::symbol(const std::string& name) const
{
    return Expression::Ptr(new Symbol(name));
}
Expression::Ptr Standard::symbol(const std::string& name, Expression::Ptr child) const
{
    std::vector<Expression::Ptr> children(1);
    children[0] = child;
    return Expression::Ptr(new Symbol(name, children));
}
Expression::Ptr Standard::symbol(const std::string& name, Expression::Ptr ptr1, Expression::Ptr ptr2) const
{
    std::vector<Expression::Ptr> children(2);
    children[0] = ptr1;
    children[1] = ptr2;
    return Expression::Ptr(new Symbol(name, children));
}
Expression::Ptr Standard::symbol(const std::string& name, const std::vector<Expression::Ptr>& children) const
{
    return Expression::Ptr(new Symbol(name, children));
}
Expression::Ptr Standard::literal(Numbers::Number* number) const
{
    return Expression::Ptr(new Literal(number));
}
Expression::Ptr Standard::literal(const Numbers::Number& number) const
{
    return Expression::Ptr(new Literal(number));
}
Expression::Ptr Standard::add(Expression::Ptr ptr1, Expression::Ptr ptr2) const
{
    std::vector<std::pair<Sign, Expression::Ptr> > childPairs(2);
    childPairs[0] = std::make_pair(p, ptr1);
    childPairs[1] = std::make_pair(p, ptr2);
    return Expression::Ptr(new Add(childPairs));
}
Expression::Ptr Standard::subtract(Expression::Ptr ptr1, Expression::Ptr ptr2) const
{
    std::vector<std::pair<Sign, Expression::Ptr> > childPairs(2);
    childPairs[0] = std::make_pair(p, ptr1);
    childPairs[1] = std::make_pair(n, ptr2);
    return Expression::Ptr(new Add(childPairs));
}
Expression::Ptr Standard::add(const std::vector<Expression::Ptr>& children) const
{
    std::vector<std::pair<Sign, Expression::Ptr> > childPairs(children.size());
    for (unsigned int i = 0; i < children.size(); i++)
        childPairs[i] = std::make_pair(p, children[i]);
    return Expression::Ptr(new Add(childPairs));
}
Expression::Ptr Standard::add(const std::vector<Expression::Ptr>& children, const std::vector<Sign>& signs) const
{
    if (children.size() != signs.size())
        throw std::invalid_argument("children.size() != signs.size() in Builders::Standard::addArray");
    std::vector<std::pair<Sign, Expression::Ptr> > childPairs(children.size());
    for (unsigned int i = 0; i < children.size(); i++)
        childPairs[i] = std::make_pair(signs[i], children[i]);
    return Expression::Ptr(new Add(childPairs));
}
Expression::Ptr Standard::negate(Expression::Ptr child) const
{
    return Expression::Ptr(new Negate(child));
}
Expression::Ptr Standard::multiply(Expression::Ptr ptr1, Expression::Ptr ptr2) const
{
    std::vector<Expression::Ptr> children(2);
    children[0] = ptr1;
    children[1] = ptr2;
    return Expression::Ptr(new Multiply(children));
}
Expression::Ptr Standard::multiply(const std::vector<Expression::Ptr>& children) const
{
    return Expression::Ptr(new Multiply(children));
}
Expression::Ptr Standard::divide(Expression::Ptr top, Expression::Ptr bottom) const
{
    return Expression::Ptr(new Divide(top, bottom));
}
Expression::Ptr Standard::modulus(Expression::Ptr top, Expression::Ptr bottom) const
{
    return Expression::Ptr(new Modulus(top, bottom));
}
Expression::Ptr Standard::power(Expression::Ptr base, Expression::Ptr power) const
{
    return Expression::Ptr(new Power(base, power));
}
Expression::Ptr Standard::factorial(Expression::Ptr child) const
{
    return Expression::Ptr(new Factorial(child));
}

} /* namespace Builders */
} /* namespace Expressions */
} /* namespace CAS */
} /* namespace DS */
