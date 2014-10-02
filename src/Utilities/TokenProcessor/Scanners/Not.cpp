/*
 * Not.cpp
 *
 *  Created on: Feb 10, 2013
 *      Author: davidsicilia
 */

#include "Not.h"

namespace DS {
namespace Tokens {
namespace Scanners {

Scanner::bounds Not::scan(Scanner::bounds bounds)
{
    if (bounds.first == bounds.second)
        return bounds;

    Scanner::bounds currentBounds = bounds;

    while (currentBounds.first != currentBounds.second)
    {
        Scanner::bounds result = repeated->scan(currentBounds);
        if (result.first != result.second)
            break;
        ++currentBounds.first;
    }
    bounds.second = currentBounds.first;
    return bounds;
}

} /* namespace Scanners */
} /* namespace Tokens */
} /* namespace DS */
