#include <stdexcept>
#include "Builder.hpp"

namespace DS {
namespace CAS {
namespace Expressions {

Expression::Ptr Builder::operator()(const std::string& name, const std::vector<Expression::Ptr>& children) const
{
    if (name == "+")
    {
        if (children.size() == 0)
            throw std::invalid_argument("children.size() invalid in DS::CAS::Expressions::Builders::Builder::operator()");
        return add(children);
    }
    if (name == "-")
    {
        if (children.size() != 2)
            throw std::invalid_argument("children.size() invalid in DS::CAS::Expressions::Builders::Builder::operator()");
        return subtract(children[0], children[1]);
    }
    if (name == "*")
    {
        if (children.size() == 0)
            throw std::invalid_argument("children.size() invalid in DS::CAS::Expressions::Builders::Builder::operator()");
        return multiply(children);
    }
    if (name == "/")
    {
        if (children.size() != 2)
            throw std::invalid_argument("children.size() invalid in DS::CAS::Expressions::Builders::Builder::operator()");
        return divide(children[0], children[1]);
    }
    if (name == "%")
    {
        if (children.size() != 2)
            throw std::invalid_argument("children.size() invalid in DS::CAS::Expressions::Builders::Builder::operator()");
        return modulus(children[0], children[1]);
    }
    if (name == "ng")
    {
        if (children.size() != 1)
            throw std::invalid_argument("children.size() invalid in DS::CAS::Expressions::Builders::Builder::operator()");
        return negate(children[0]);
    }
    if (name == "^")
    {
        if (children.size() != 2)
            throw std::invalid_argument("children.size() invalid in DS::CAS::Expressions::Builders::Builder::operator()");
        return power(children[0], children[1]);
    }
    if (name == "!")
    {
        if (children.size() != 1)
            throw std::invalid_argument("children.size() invalid in DS::CAS::Expressions::Builders::Builder::operator()");
        return factorial(children[0]);
    }
    if (name == "")
        throw std::invalid_argument("name == empty in DS::CAS::Expressions::Builders::Builder::operator()");
    return symbol(name, children);
}
Expression::Ptr Builder::operator()(const std::string& name) const
{
    if (name == "")
        throw std::invalid_argument("name == empty in Builder::operator()");
    return this->symbol(name);
}
Expression::Ptr Builder::operator()(const std::string& name, Expression::Ptr ptr) const
{
    std::vector<Expression::Ptr> children(1);
    children[0] = ptr;
    return (*this)(name, children);
}
Expression::Ptr Builder::operator()(const std::string& name, Expression::Ptr ptr1, Expression::Ptr ptr2) const
{
    std::vector<Expression::Ptr> children(2);
    children[0] = ptr1;
    children[1] = ptr2;
    return (*this)(name, children);
}


} /* namespace Expressions */
} /* namespace CAS */
} /* namespace DS */
