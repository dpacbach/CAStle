/*
 * Space.cpp
 *
 *  Created on: Feb 8, 2013
 *      Author: davidsicilia
 */

#include "Space.h"

namespace DS {
namespace Tokens {
namespace Scanners {

Scanner::bounds Space::scan(Scanner::bounds bounds)
{
    if (bounds.first == bounds.second)
        return bounds;

    char firstChar = *bounds.first;
    if (firstChar == ' ' || firstChar == '\t')
    {
        bounds.second = bounds.first;
        ++bounds.second;
        return bounds;
    }
    if (includeNewLine)
    {
        if (firstChar == '\n')
        {
            bounds.second = bounds.first;
            ++bounds.second;
            return bounds;
        }
    }
    bounds.second = bounds.first;
    return bounds;
}

} /* namespace Scanners */
} /* namespace Token */
} /* namespace DS */
