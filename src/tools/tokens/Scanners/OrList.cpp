/*
 * OrList.cpp
 *
 *  Created on: Feb 8, 2013
 *      Author: davidsicilia
 */

#include <stdexcept>
#include "OrList.h"

namespace DS {
namespace Tokens {
namespace Scanners {

OrList::OrList(const vector<Scanner::Ptr>& aList)
{
    if (aList.size() == 0)
        throw invalid_argument("aList.size == 0 in DS::Tokens::Scanners::OrList::OrList(vector)");
    theList = aList;
}

Scanner::bounds OrList::scan(Scanner::bounds bounds)
{
    if (bounds.first == bounds.second)
        return bounds;

    vector<Scanner::Ptr>::iterator itS = theList.begin();
    Scanner::bounds currentBounds = bounds;

    for (unsigned int i = 0; i < theList.size(); i++)
    {
        Scanner::Ptr currentScanner = *itS;

        Scanner::bounds resultBounds = currentScanner->scan(currentBounds);
        if (resultBounds.first != resultBounds.second)
        {
            currentBounds.first = resultBounds.second;
            break;
        }
        ++itS;
    }
    bounds.second = currentBounds.first;
    return bounds;
}

} /* namespace Scanners */
} /* namespace Tokens */
} /* namespace DS */
