/*
 * Composite.h
 *
 *  Created on: Mar 16, 2013
 *      Author: davidsicilia
 */

#ifndef RS_COMPOSITE_H_
#define RS_COMPOSITE_H_

#include <vector>
#include <boost/shared_ptr.hpp>
#include "../Restructurer.h"

using namespace std;

namespace DS {
namespace CAS {
namespace Expressions {
namespace Visitors {
namespace Restructurers {

class Composite : public DS::CAS::Expressions::Visitors::Restructurer
{
    Composite(boost::shared_ptr<Numbers::NumberFactory> _nFactory,
              boost::shared_ptr<Expressions::Builder> _eBuilder) : Restructurer(_nFactory, _eBuilder) {}

    virtual bool visitExpression(const Expression::Ptr exp);

    void addChildToEnd(boost::shared_ptr<Restructurer> child)
    {
        children.push_back(child);
    }

protected:
    vector<boost::shared_ptr<Restructurer> > children;
};

} /* namespace Restructurers */
} /* namespace Visitors */
} /* namespace Expressions */
} /* namespace CAS */
} /* namespace DS */
#endif /* COMPOSITE_H_ */
