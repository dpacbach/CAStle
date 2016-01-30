/*
 * Space.h
 *
 *  Created on: Feb 8, 2013
 *      Author: davidsicilia
 */

#ifndef SPACE_H_
#define SPACE_H_

#include "../Scanner.h"

namespace DS {
namespace Tokens {
namespace Scanners {

class Space: public DS::Tokens::Scanner
{
public:
    Space(bool _includeNewLine = true): includeNewLine(_includeNewLine) {}
    virtual ~Space() {}

    bool includesNewLine(void) const { return includeNewLine; }

    virtual Scanner::bounds scan(Scanner::bounds);

protected:
    bool includeNewLine;
};

} /* namespace Scanners */
} /* namespace Token */
} /* namespace DS */
#endif /* SPACE_H_ */
