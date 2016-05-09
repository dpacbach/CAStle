/*
 * ExpressionModulus.h
 *
 *  Created on: Jan 11, 2013
 *      Author: davidsicilia
 */

#ifndef EXPRESSIONMODULUS_H_
#define EXPRESSIONMODULUS_H_

#include "../Expression.h"

namespace DS {
namespace CAS {
namespace Expressions {

class Modulus: public DS::CAS::Expressions::Expression {
public:
    Modulus(const Expression::Ptr n, const Expression::Ptr d) : numerator(n), denominator(d) {}
    virtual ~Modulus() {}

    virtual ID id(void) const { return modulus; }

    virtual bool acceptVisitor(Visitor& visitor) const;
    virtual unsigned int  numberOfChildren(void) const;
    virtual Ptr  getChild(unsigned int) const;

protected:
    Expression::Ptr numerator;
    Expression::Ptr denominator;
};

} /* namespace Expression */
} /* namespace CAS */
} /* namespace DS */
#endif /* EXPRESSIONMODULUS_H_ */
