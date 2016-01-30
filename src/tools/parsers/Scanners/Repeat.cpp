/*
 * Repeat.cpp
 *
 *  Created on: Feb 8, 2013
 *      Author: davidsicilia
 */

#include "Repeat.hpp"

namespace DS {
namespace Tokens {
namespace Scanners {

Scanner::bounds Repeat::scan(Scanner::bounds bounds)
{
    if (bounds.first == bounds.second)
        return bounds;

    typeof(bounds.first) index = bounds.first;
    Scanner::bounds currentBounds = Scanner::make_bounds(index, bounds.second);

    bool found = false;
    while (currentBounds.first != currentBounds.second)
    {
        Scanner::bounds result = repeated->scan(currentBounds);
        if (result.first == result.second)
            break;
        found = true;
        currentBounds.first = result.second;
    }
    if (!found)
    {
        bounds.second = bounds.first;
        return bounds;
    }
    bounds.second = currentBounds.first;
    return bounds;
}

} /* namespace Scanners */
} /* namespace Tokens */
} /* namespace DS */
