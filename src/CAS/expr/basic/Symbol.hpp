#pragma once

#include <vector>
#include <string>
#include "Expression.hpp"

namespace DS          {
namespace CAS         {
namespace Expressions {

class Symbol: public DS::CAS::Expressions::Expression
{
public:
    Symbol(const std::string& _name) : name(_name) {}
    Symbol(const std::string& _name, const std::vector<Expression::Ptr>& _children) : name(_name), children(_children) {}

    virtual ~Symbol() {}

    virtual ID id(void) const { return symbol; }

    virtual bool acceptVisitor(Visitor&) const;
    virtual unsigned int  numberOfChildren(void) const;
    virtual Ptr  getChild(unsigned int) const;

    const std::string& getName(void) const;

protected:
    std::string name;
    std::vector<Expression::Ptr> children;
};

} /* namespace Expression */
} /* namespace CAS */
} /* namespace DS */
