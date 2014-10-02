/*
 * OptionalList.h
 *
 *  Created on: Feb 8, 2013
 *      Author: davidsicilia
 */

#ifndef OPTIONALLIST_H_
#define OPTIONALLIST_H_

#include <vector>
#include "../Scanner.h"

namespace DS {
namespace Tokens {
namespace Scanners {

class OptionalList: public DS::Tokens::Scanner
{
public:
    OptionalList(const vector<Scanner::Ptr>&);
    OptionalList(const vector<Scanner::Ptr>&, const vector<bool>&);
    virtual ~OptionalList() {}

    virtual Scanner::bounds scan(Scanner::bounds);

protected:
    vector<Scanner::Ptr> theList;
    vector<bool> optionalFlags;
};

} /* namespace Scanners */
} /* namespace Tokens */
} /* namespace DS */
#endif /* OPTIONALLIST_H_ */
