#pragma once

#include "Expression.hpp"
#include "exprfwd.hpp"

namespace DS          {
namespace CAS         {
namespace Expressions {

class Visitor
{
public:
    virtual ~Visitor() {}

    Visitor(Visitor const&) = delete;
    Visitor const& operator= (Visitor const&) = delete;

    virtual void reset(void) {}

    virtual bool visitExpression(ExprConstSP); // default visits children then node

    virtual bool visitAdd(const Add&)                = 0;
    virtual bool visitDivide(const Divide&)          = 0;
    virtual bool visitFactorial(const Factorial&)    = 0;
    virtual bool visitLiteral(const Literal&)        = 0;
    virtual bool visitModulus(const Modulus&)        = 0;
    virtual bool visitMultiply(const Multiply&)      = 0;
    virtual bool visitNegate(const Negate&)          = 0;
    virtual bool visitPower(const Power&)            = 0;
    virtual bool visitSymbol(const Symbol&)          = 0;

protected:
    Visitor() {}
};

} } }
