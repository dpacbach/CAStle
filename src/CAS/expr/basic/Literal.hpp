#pragma once

#include <exception>
#include <stdexcept>
#include "Expression.hpp"
#include "Number.hpp"
#include "NumberProxy.hpp"

namespace DS          {
namespace CAS         {
namespace Expressions {

class Literal : public DS::CAS::Expressions::Expression
{
public:
    Literal(Numbers::Number* _number) : number(_number) {} // number will take ownership of this
    Literal(const Numbers::Number& _number) : number(_number) {} // number will copy this

    virtual ~Literal() {}

    virtual ID id(void) const { return literal; }

    virtual bool acceptVisitor(Visitor&) const;
    virtual unsigned int numberOfChildren(void) const
    {
        return 0;
    }
    virtual Expression::Ptr getChild(unsigned int i) const
    {
        throw std::out_of_range("getChild called in class Expressions::Literal");
    }

    const Numbers::Number& getNumber(void) const
    {
        return number;
    }

protected:
    Numbers::Proxy::NumberP number;
};

} } }
