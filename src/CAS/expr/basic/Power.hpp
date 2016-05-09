#pragma once

#include "Expression.hpp"

namespace DS          {
namespace CAS         {
namespace Expressions {

class Power: public DS::CAS::Expressions::Expression {
public:
    Power(const Expression::Ptr _base, const Expression::Ptr _exponent) : base(_base), exponent(_exponent) {}
    virtual ~Power() {}

    virtual ID id(void) const { return power; }

    virtual bool acceptVisitor(Visitor&) const;
    virtual unsigned int  numberOfChildren(void)    const;
    virtual Expression::Ptr  getChild(unsigned int i) const;

protected:
    Expression::Ptr base;
    Expression::Ptr exponent;
};

} /* namespace Expression */
} /* namespace CAS */
} /* namespace DS */
