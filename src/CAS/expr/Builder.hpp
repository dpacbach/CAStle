#pragma once

#include <string>
#include <vector>
#include "Expression.hpp"

namespace DS {
namespace CAS {

namespace Numbers {
    class Number;
}

namespace Expressions {

class Builder
{
public:
    Builder() {}
    virtual ~Builder() {}

    Builder(Builder const&) = delete;
    Builder const& operator= (Builder const&) = delete;

    virtual ExprConstSP operator()(const std::string& name) const;
    virtual ExprConstSP operator()(const std::string& name, const std::vector<ExprConstSP>& children) const;
    virtual ExprConstSP operator()(const std::string& name, ExprConstSP ptr) const;
    virtual ExprConstSP operator()(const std::string& name, ExprConstSP ptr1, ExprConstSP ptr2) const;

    virtual ExprConstSP symbol(const std::string&) const = 0;
    virtual ExprConstSP symbol(const std::string&, ExprConstSP) const = 0;
    virtual ExprConstSP symbol(const std::string&, ExprConstSP, ExprConstSP) const = 0;
    virtual ExprConstSP symbol(const std::string&, const std::vector<ExprConstSP>&) const = 0;
    virtual ExprConstSP literal(Numbers::Number*) const = 0;
    virtual ExprConstSP literal(const Numbers::Number&) const = 0;
    virtual ExprConstSP add(ExprConstSP, ExprConstSP) const = 0;
    virtual ExprConstSP add(const std::vector<ExprConstSP>&) const = 0;
    virtual ExprConstSP add(const std::vector<ExprConstSP>&, const std::vector<Sign>&) const = 0;
    virtual ExprConstSP subtract(ExprConstSP, ExprConstSP) const = 0;
    virtual ExprConstSP negate(ExprConstSP) const = 0;
    virtual ExprConstSP multiply(ExprConstSP, ExprConstSP) const = 0;
    virtual ExprConstSP multiply(const std::vector<ExprConstSP>&) const = 0;
    virtual ExprConstSP divide(ExprConstSP top, ExprConstSP bottom) const = 0;
    virtual ExprConstSP modulus(ExprConstSP top, ExprConstSP bottom) const = 0;
    virtual ExprConstSP power(ExprConstSP base, ExprConstSP power) const = 0;
    virtual ExprConstSP factorial(ExprConstSP) const = 0;
};

} /* namespace Expressions */
} /* namespace CAS */
} /* namespace DS */
