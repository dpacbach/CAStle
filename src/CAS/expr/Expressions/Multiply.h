/*
 * ExpressionMultiply.h
 *
 *  Created on: Jan 11, 2013
 *      Author: davidsicilia
 */

#ifndef EXPRESSIONMULTIPLY_H_
#define EXPRESSIONMULTIPLY_H_

#include <vector>
#include "../Expression.h"

namespace DS {
namespace CAS {
namespace Expressions {

class Multiply: public DS::CAS::Expressions::Expression {
public:
    Multiply(const vector<Expression::Ptr>&);

    virtual ~Multiply() {}

    virtual ID id(void) const { return multiply; }

    virtual bool acceptVisitor(Visitor&) const;
    virtual unsigned int  numberOfChildren(void)    const;
    virtual Ptr  getChild(unsigned int) const;

protected:
    vector<Expression::Ptr> children;
};

} /* namespace Expression */
} /* namespace CAS */
} /* namespace DS */
#endif /* EXPRESSIONMULTIPLY_H_ */
