/*
 * Standard.h
 *
 *  Created on: Jan 22, 2013
 *      Author: davidsicilia
 */

#ifndef EXPBUILDSTANDARD_H_
#define EXPBUILDSTANDARD_H_

#include "../Builder.h"

namespace DS {
namespace CAS {
namespace Expressions {
namespace Builders {

class Standard: public DS::CAS::Expressions::Builder
{
public:
    Standard();
    virtual ~Standard();

    virtual Expression::Ptr symbol(const string&) const;
    virtual Expression::Ptr symbol(const string&, Expression::Ptr) const;
    virtual Expression::Ptr symbol(const string&, Expression::Ptr, Expression::Ptr) const;
    virtual Expression::Ptr symbol(const string&, const vector<Expression::Ptr>&) const;
    virtual Expression::Ptr literal(Numbers::Number*) const;
    virtual Expression::Ptr literal(const Numbers::Number&) const;
    virtual Expression::Ptr add(Expression::Ptr, Expression::Ptr) const;
    virtual Expression::Ptr add(const vector<Expression::Ptr>&) const;
    virtual Expression::Ptr add(const vector<Expression::Ptr>&, const vector<Sign>&) const;
    virtual Expression::Ptr subtract(Expression::Ptr, Expression::Ptr) const;
    virtual Expression::Ptr negate(Expression::Ptr) const;
    virtual Expression::Ptr multiply(Expression::Ptr, Expression::Ptr) const;
    virtual Expression::Ptr multiply(const vector<Expression::Ptr>&) const;
    virtual Expression::Ptr divide(Expression::Ptr top, Expression::Ptr bottom) const;
    virtual Expression::Ptr modulus(Expression::Ptr top, Expression::Ptr bottom) const;
    virtual Expression::Ptr power(Expression::Ptr base, Expression::Ptr power) const;
    virtual Expression::Ptr factorial(Expression::Ptr) const;
};

} /* namespace Builders */
} /* namespace Expressions */
} /* namespace CAS */
} /* namespace DS */
#endif /* STANDARD_H_ */
