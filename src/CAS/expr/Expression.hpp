#pragma once

#include <vector>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

namespace DS          {
namespace CAS         {
namespace Expressions {

enum Sign
{
    p = true, n = false
};

class Visitor;

class Expression : private boost::noncopyable
{
public:
    typedef enum { add, divide, factorial, literal, modulus, multiply, negate, power, symbol } ID;
    typedef boost::shared_ptr<const Expression> Ptr; // use only this to reference Expression objects

    Expression();
    virtual ~Expression();

    virtual ID id(void) const = 0;

    virtual unsigned int numberOfChildren(void) const = 0;
    virtual Ptr getChild(unsigned int i)        const = 0;
    virtual std::vector<Ptr> getChildVector(void)    const;

    virtual bool acceptVisitor(Visitor&) const = 0;

    static int numberOfExpressions;
};

} } }
