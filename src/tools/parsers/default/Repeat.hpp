/*
 * Repeat.h
 *
 *  Created on: Feb 8, 2013
 *      Author: davidsicilia
 */

#ifndef REPEAT_H_
#define REPEAT_H_

namespace DS {
namespace Tokens {
namespace Scanners {

class Repeat: public DS::Tokens::Scanner
{
public:
    Repeat(Scanner::Ptr _repeated) : repeated(_repeated) {}
    virtual ~Repeat() {}

    virtual Scanner::bounds scan(Scanner::bounds);

protected:
    Scanner::Ptr repeated;
};

} /* namespace Scanners */
} /* namespace Tokens */
} /* namespace DS */
#endif /* REPEAT_H_ */
