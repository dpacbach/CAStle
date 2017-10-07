#pragma once

#include "Builder.hpp"

namespace DS          {
namespace CAS         {
namespace Expressions {
namespace Builders    {

class Standard: public DS::CAS::Expressions::Builder
{
public:
    Standard();
    virtual ~Standard();

    virtual ExprConstSP symbol(const std::string&) const;
    virtual ExprConstSP symbol(const std::string&, ExprConstSP) const;
    virtual ExprConstSP symbol(const std::string&, ExprConstSP, ExprConstSP) const;
    virtual ExprConstSP symbol(const std::string&, const std::vector<ExprConstSP>&) const;
    virtual ExprConstSP literal(Numbers::Number*) const;
    virtual ExprConstSP literal(const Numbers::Number&) const;
    virtual ExprConstSP add(ExprConstSP, ExprConstSP) const;
    virtual ExprConstSP add(const std::vector<ExprConstSP>&) const;
    virtual ExprConstSP add(const std::vector<ExprConstSP>&, const std::vector<Sign>&) const;
    virtual ExprConstSP subtract(ExprConstSP, ExprConstSP) const;
    virtual ExprConstSP negate(ExprConstSP) const;
    virtual ExprConstSP multiply(ExprConstSP, ExprConstSP) const;
    virtual ExprConstSP multiply(const std::vector<ExprConstSP>&) const;
    virtual ExprConstSP divide(ExprConstSP top, ExprConstSP bottom) const;
    virtual ExprConstSP modulus(ExprConstSP top, ExprConstSP bottom) const;
    virtual ExprConstSP power(ExprConstSP base, ExprConstSP power) const;
    virtual ExprConstSP factorial(ExprConstSP) const;
};

} /* namespace Builders */
} /* namespace Expressions */
} /* namespace CAS */
} /* namespace DS */
