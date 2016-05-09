#pragma once

#include "Expression.hpp"

namespace DS          {
namespace CAS         {
namespace Expressions {

class Divide: public DS::CAS::Expressions::Expression
{
public:
    Divide(const Expression::Ptr _numerator, const Expression::Ptr _denominator) : numerator(_numerator),
                                                                                   denominator(_denominator) {}
    virtual ~Divide() {}

    virtual ID id(void) const { return divide; }

    virtual bool acceptVisitor(Visitor&) const;
    virtual unsigned int  numberOfChildren(void) const;
    virtual Ptr  getChild(unsigned int i)   const;

protected:
    Expression::Ptr numerator;
    Expression::Ptr denominator;
};

} /* namespace Expression */
} /* namespace CAS */
} /* namespace DS */
