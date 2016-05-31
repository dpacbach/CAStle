#pragma once

#include <memory>
#include <vector>

namespace DS          {
namespace CAS         {
namespace Expressions {

enum Sign
{
    p = true, n = false
};

class Visitor;

class Expression
{
public:
    typedef enum { add, divide, factorial, literal, modulus, multiply, negate, power, symbol } ID;
    typedef std::shared_ptr<const Expression> Ptr; // use only this to reference Expression objects

    Expression();
    virtual ~Expression();

    Expression(Expression const&) = delete;
    Expression const& operator= (Expression const&) = delete;

    virtual ID id(void) const = 0;

    virtual unsigned int numberOfChildren(void) const = 0;
    virtual Ptr getChild(unsigned int i)        const = 0;
    virtual std::vector<Ptr> getChildVector(void)    const;

    virtual bool acceptVisitor(Visitor&) const = 0;

    static int numberOfExpressions;
};

} } }
