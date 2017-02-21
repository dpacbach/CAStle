#pragma once

#include "Number.hpp"
#include "NumberProxy.hpp"
#include "Expression.hpp"

#include <string>
#include <vector>
#include <exception>
#include <stdexcept>
#include <utility>

namespace DS          {
namespace CAS         {
namespace Expressions {

/**********************************************************
 *                           Add 
 **********************************************************/
class Add: public Expr
{
public:
    using SignedExpr    = std::pair<Sign, ExprConstSP>;
    using SignedExprVec = std::vector<SignedExpr>;

    Add( std::vector<ExprConstSP> const& exprs,
         std::vector<Sign>        const& signs );

    virtual ID id( void ) const { return ID::add; }

    virtual bool acceptVisitor( Visitor& ) const;

    virtual SignedExprVec const& getPairVector() const;

    Sign getSignForChild( size_t ) const;
    std::vector<Sign> const& getSignVector() const;

protected:
    std::vector<Sign> signs;
};

/**********************************************************
 *                         Divide
 **********************************************************/
class Divide: public Expr
{
public:
    Divide( ExprConstSP numerator, ExprConstSP denominator)
        : Expr( { numerator, denominator } ) {}

    virtual ID id(void) const { return ID::divide; }

    virtual bool acceptVisitor(Visitor&) const;
};

/**********************************************************
 *                        Factorial
 **********************************************************/
class Factorial: public DS::CAS::Expressions::Expr
{
public:
    Factorial(ExprConstSP ptr) : Expr( { ptr } ) {}

    virtual ~Factorial() {}

    virtual ID id(void) const { return ID::factorial; }

    virtual bool acceptVisitor(Visitor&) const;
};

/**********************************************************
 *                         Literal
 **********************************************************/
class Literal : public DS::CAS::Expressions::Expr
{
public:
    Literal(Numbers::Number* _number) : number(_number) {} // number will take ownership of this
    Literal(const Numbers::Number& _number) : number(_number) {} // number will copy this

    virtual ~Literal() {}

    virtual ID id(void) const { return ID::literal; }

    virtual bool acceptVisitor(Visitor&) const;

    const Numbers::Number& getNumber(void) const
    {
        return number;
    }

protected:
    Numbers::Proxy::NumberP number;
};

/**********************************************************
 *                         Modulus
 **********************************************************/
class Modulus: public DS::CAS::Expressions::Expr {
public:
    Modulus(ExprConstSP n, ExprConstSP d) : Expr( { n, d } ) {}

    virtual ~Modulus() {}

    virtual ID id(void) const { return ID::modulus; }

    virtual bool acceptVisitor(Visitor& visitor) const;
};

/**********************************************************
 *                        Multiply
 **********************************************************/
class Multiply: public DS::CAS::Expressions::Expr {
public:
    Multiply(const std::vector<ExprConstSP>&);

    virtual ~Multiply() {}

    virtual ID id(void) const { return ID::multiply; }

    virtual bool acceptVisitor(Visitor&) const;
};

/**********************************************************
 *                         Negate
 **********************************************************/
class Negate: public DS::CAS::Expressions::Expr
{
public:
    Negate(const ExprConstSP ptr) : Expr( { ptr } ) {}
    virtual ~Negate() {}

    virtual ID id(void) const { return ID::negate; }

    virtual bool acceptVisitor(Visitor&) const;
};

/**********************************************************
 *                          Power
 **********************************************************/
class Power: public DS::CAS::Expressions::Expr {
public:
    Power(const ExprConstSP base, const ExprConstSP exponent)
        : Expr( { base, exponent } ) {}
    virtual ~Power() {}

    virtual ID id(void) const { return ID::power; }

    virtual bool acceptVisitor(Visitor&) const;
};

/**********************************************************
 *                         Symbol
 **********************************************************/
class Symbol: public DS::CAS::Expressions::Expr
{
public:
    Symbol(const std::string& _name) : name(_name) {}
    Symbol(const std::string& _name, const std::vector<ExprConstSP>& _children)
        : Expr( children ), name(_name) {}

    virtual ~Symbol() {}

    virtual ID id(void) const { return ID::symbol; }

    virtual bool acceptVisitor(Visitor&) const;

    const std::string& getName(void) const;

protected:
    std::string name;
};

} /* namespace Expressions */
} /* namespace CAS */
} /* namespace DS */
