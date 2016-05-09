#pragma once

#include <vector>
#include "Expression.hpp"

namespace DS          {
namespace CAS         {
namespace Expressions {

class Multiply: public DS::CAS::Expressions::Expression {
public:
    Multiply(const std::vector<Expression::Ptr>&);

    virtual ~Multiply() {}

    virtual ID id(void) const { return multiply; }

    virtual bool acceptVisitor(Visitor&) const;
    virtual unsigned int  numberOfChildren(void)    const;
    virtual Ptr  getChild(unsigned int) const;

protected:
    std::vector<Expression::Ptr> children;
};

} /* namespace Expression */
} /* namespace CAS */
} /* namespace DS */
