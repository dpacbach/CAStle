/*
 * CharString.cpp
 *
 *  Created on: Feb 8, 2013
 *      Author: davidsicilia
 */

#include "CharString.h"

namespace DS {
namespace Tokens {
namespace Scanners {

Scanner::bounds CharString::scan(Scanner::bounds bounds)
{
    if (bounds.first == bounds.second)
        return bounds;

    string::const_iterator searchIndex = bounds.first;
    string::const_iterator sourceIndex = scanString.begin();

    while (sourceIndex != scanString.end() && searchIndex != bounds.second)
    {
        if (*searchIndex != *sourceIndex)
            break;
        ++searchIndex;
        ++sourceIndex;
    }
    if (sourceIndex == scanString.end())
    {
        bounds.second = searchIndex;
        return bounds;
    }
    bounds.second = bounds.first;
    return bounds;
}

} /* namespace Scanners */
} /* namespace Token */
} /* namespace DS */
