/*
 * Expression.h
 *
 *  Created on: Jan 11, 2013
 *      Author: davidsicilia
 */

#ifndef EXPRESSION_H_
#define EXPRESSION_H_

#include <vector>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

using namespace std;

namespace DS           {
namespace CAS           {
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
    virtual vector<Ptr> getChildVector(void)    const;

    virtual bool acceptVisitor(Visitor&) const = 0;

    static int numberOfExpressions;
};

} } }

#endif /* EXPRESSION_H_ */
