#include <stdexcept>
#include "Builder.hpp"

namespace DS {
namespace CAS {
namespace Expressions {

ExprConstSP Builder::operator()(const std::string& name, const std::vector<ExprConstSP>& children) const
{
    if (name == "+")
    {
        if (children.size() == 0)
            throw std::invalid_argument(name + ": children.size() invalid in DS::CAS::Expressions::Builders::Builder::operator()");
        return add(children);
    }
    if (name == "-")
    {
        if (children.size() != 2)
            throw std::invalid_argument(name + ": children.size() invalid in DS::CAS::Expressions::Builders::Builder::operator()");
        return subtract(children[0], children[1]);
    }
    if (name == "*")
    {
        if (children.size() == 0)
            throw std::invalid_argument(name + ": children.size() invalid in DS::CAS::Expressions::Builders::Builder::operator()");
        return multiply(children);
    }
    if (name == "/")
    {
        if (children.size() != 2)
            throw std::invalid_argument(name + ": children.size() invalid in DS::CAS::Expressions::Builders::Builder::operator()");
        return divide(children[0], children[1]);
    }
    if (name == "%")
    {
        if (children.size() != 2)
            throw std::invalid_argument(name + ": children.size() invalid in DS::CAS::Expressions::Builders::Builder::operator()");
        return modulus(children[0], children[1]);
    }
    if (name == "ng")
    {
        if (children.size() != 1)
            throw std::invalid_argument(name + ": children.size() invalid in DS::CAS::Expressions::Builders::Builder::operator()");
        return negate(children[0]);
    }
    if (name == "^")
    {
        if (children.size() != 2)
            throw std::invalid_argument(name + ": children.size() invalid in DS::CAS::Expressions::Builders::Builder::operator()");
        return power(children[0], children[1]);
    }
    if (name == "!")
    {
        if (children.size() != 1)
            throw std::invalid_argument(name + ": children.size() invalid in DS::CAS::Expressions::Builders::Builder::operator()");
        return factorial(children[0]);
    }
    if (name == "")
        throw std::invalid_argument("name == empty in DS::CAS::Expressions::Builders::Builder::operator()");
    return symbol(name, children);
}
ExprConstSP Builder::operator()(const std::string& name) const
{
    if (name == "")
        throw std::invalid_argument("name == empty in Builder::operator()");
    return this->symbol(name);
}
ExprConstSP Builder::operator()(const std::string& name, ExprConstSP ptr) const
{
    std::vector<ExprConstSP> children(1);
    children[0] = ptr;
    return (*this)(name, children);
}
ExprConstSP Builder::operator()(const std::string& name, ExprConstSP ptr1, ExprConstSP ptr2) const
{
    std::vector<ExprConstSP> children(2);
    children[0] = ptr1;
    children[1] = ptr2;
    return (*this)(name, children);
}


} /* namespace Expressions */
} /* namespace CAS */
} /* namespace DS */
