/*
 * OrList.h
 *
 *  Created on: Feb 8, 2013
 *      Author: davidsicilia
 */

#ifndef ORLIST_H_
#define ORLIST_H_

#include <vector>

namespace DS {
namespace Tokens {
namespace Scanners {

class OrList: public DS::Tokens::Scanner
{
public:
    OrList(const vector<Scanner::Ptr>&);
    virtual ~OrList() {}

    virtual Scanner::bounds scan(Scanner::bounds);

protected:
    vector<Scanner::Ptr> theList;
};

} /* namespace Scanners */
} /* namespace Tokens */
} /* namespace DS */
#endif /* ORLIST_H_ */
