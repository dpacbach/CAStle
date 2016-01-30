/*
 * Not.h
 *
 *  Created on: Feb 10, 2013
 *      Author: davidsicilia
 */

#ifndef SCANNERNOT_H_
#define SCANNERNOT_H_

#include "../Scanner.h"

namespace DS {
namespace Tokens {
namespace Scanners {

class Not: public DS::Tokens::Scanner
{
public:
    Not(Scanner::Ptr _repeated) : repeated(_repeated) {}
    virtual ~Not() {}

    virtual Scanner::bounds scan(Scanner::bounds);

protected:
    Scanner::Ptr repeated;
};

} /* namespace Scanners */
} /* namespace Tokens */
} /* namespace DS */
#endif /* NOT_H_ */
