#pragma once

#include <vector>
#include "Expression.hpp"

namespace DS          {
namespace CAS         {
namespace Expressions {

class Add: public DS::CAS::Expressions::Expression
{
public:
    Add(const vector<pair<Sign, Expression::Ptr> >& _childPairs);
    virtual ~Add() {}

    virtual ID id(void) const { return add; }

    virtual bool acceptVisitor(Visitor&) const;

    virtual unsigned int  numberOfChildren(void) const;

    virtual Ptr getChild(unsigned int) const;
    virtual const vector<pair<Sign, Ptr> >& getPairVector(void) const;

    Sign getSignForChild(unsigned int) const;
    vector<Sign> getSignVector(void) const;

    pair<Sign, Expression::Ptr> getChildPair(unsigned int) const;

protected:
    vector<pair<Sign, Expression::Ptr> > childPairs;
};

} /* namespace Expression */
} /* namespace CAS */
} /* namespace DS */
