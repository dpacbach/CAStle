/*
 * CharString.h
 *
 *  Created on: Feb 8, 2013
 *      Author: davidsicilia
 */

#ifndef CHARSTRING_H_
#define CHARSTRING_H_

#include <string>
#include "../Scanner.h"

using namespace std;

namespace DS {
namespace Tokens {
namespace Scanners {

class CharString: public DS::Tokens::Scanner
{
public:
    CharString(const string& aString) : scanString(aString) {}
    CharString(const char aChar) : scanString(1, aChar) {}
    virtual ~CharString() {}

    virtual Scanner::bounds scan(Scanner::bounds);

    const string& getString(void) const { return scanString; }

protected:
    string scanString;
};

} /* namespace Scanners */
} /* namespace Token */
} /* namespace DS */
#endif /* CHARSTRING_H_ */
