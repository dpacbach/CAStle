/*
 * Visitor.h
 *
 *  Created on: Jan 11, 2013
 *      Author: davidsicilia
 */

#ifndef EXPVISITOR_H_
#define EXPVISITOR_H_

#include <boost/noncopyable.hpp>
#include "../Expression/Expressions/ExpressionTypes.h"

namespace DS           {
namespace CAS           {
namespace Expressions {

class Visitor : private boost::noncopyable
{
public:
    virtual ~Visitor() {}

    virtual void reset(void) {}

    virtual bool visitExpression(const Expression::Ptr); // default visits children then node

    virtual bool visitAdd(const Add&)                = 0;
    virtual bool visitDivide(const Divide&)            = 0;
    virtual bool visitFactorial(const Factorial&)    = 0;
    virtual bool visitLiteral(const Literal&)        = 0;
    virtual bool visitModulus(const Modulus&)        = 0;
    virtual bool visitMultiply(const Multiply&)        = 0;
    virtual bool visitNegate(const Negate&)            = 0;
    virtual bool visitPower(const Power&)            = 0;
    virtual bool visitSymbol(const Symbol&)            = 0;

protected:
    Visitor() {}
};

} } }

#endif /* VISITOR_H_ */
