/*
 * Substitution.h
 *
 *  Created on: Mar 3, 2013
 *      Author: davidsicilia
 */

#ifndef SUBSTITUTION_H_
#define SUBSTITUTION_H_

#include <string>
#include <map>
#include "../Restructurer.h"

namespace DS {
namespace CAS {
namespace Expressions {
namespace Visitors {
namespace Restructurers {

class Substitution: public DS::CAS::Expressions::Visitors::Restructurer
{
public:
    Substitution(boost::shared_ptr<Numbers::NumberFactory> _nFactory, boost::shared_ptr<Expressions::Builder> _eBuilder,
                 const map<string,Expression::Ptr>& _dictionary) : Restructurer(_nFactory, _eBuilder), dictionary(_dictionary) {}
    virtual ~Substitution() {}

    map<string, Expression::Ptr>& getDictionary(void) { return dictionary; }

protected:
    virtual Expression::Ptr symbol(const Symbol& exp, const vector<Expression::Ptr>& children);
    map<string, Expression::Ptr> dictionary;
};

} /* namespace Restructurers */
} /* namespace Visitors */
} /* namespace Expressions */
} /* namespace CAS */
} /* namespace DS */
#endif /* SUBSTITUTION_H_ */
