#pragma once

#include "Expression.hpp"

namespace DS          {
namespace CAS         {
namespace Expressions {

class Factorial: public DS::CAS::Expressions::Expression
{
public:
    Factorial(const Expression::Ptr ptr) : child(ptr) {}

    virtual ~Factorial() {}

    virtual ID id(void) const { return factorial; }

    virtual bool acceptVisitor(Visitor&) const;
    virtual unsigned int  numberOfChildren(void) const;
    virtual Expression::Ptr  getChild(unsigned int)   const;

protected:
    Expression::Ptr child;
};

} /* namespace Expression */
} /* namespace CAS */
} /* namespace DS */
