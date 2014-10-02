/*
 * ExpressionNegate.h
 *
 *  Created on: Jan 11, 2013
 *      Author: davidsicilia
 */

#ifndef EXPRESSIONNEGATE_H_
#define EXPRESSIONNEGATE_H_

#include "../Expression.h"

namespace DS {
namespace CAS {
namespace Expressions {

class Negate: public DS::CAS::Expressions::Expression
{
public:
    Negate(const Expression::Ptr ptr) : child(ptr) {}
    virtual ~Negate() {}

    virtual ID id(void) const { return negate; }

    virtual bool acceptVisitor(Visitor&) const;

    virtual unsigned int numberOfChildren(void) const
    {
        return 1;
    }
    virtual Ptr getChild(unsigned int) const;

protected:
    Expression::Ptr child;
};

} /* namespace Expression */
} /* namespace CAS */
} /* namespace DS */
#endif /* EXPRESSIONNEGATE_H_ */
