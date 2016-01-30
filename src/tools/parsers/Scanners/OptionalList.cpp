/*
 * OptionalList.cpp
 *
 *  Created on: Feb 8, 2013
 *      Author: davidsicilia
 */

#include <stdexcept>
#include "OptionalList.hpp"

namespace DS {
namespace Tokens {
namespace Scanners {

OptionalList::OptionalList(const vector<Scanner::Ptr>& aList) : optionalFlags(aList.size(), false)
{
    if (aList.size() == 0)
        throw invalid_argument("aList is empty in DS::Tokens::Scanners::OptionalList::OptionalList(vector)");
    theList = aList;
}
OptionalList::OptionalList(const vector<Scanner::Ptr>& aList, const vector<bool>& aFlagList)
{
    if (aList.size() == 0)
        throw invalid_argument("aList is empty in DS::Tokens::Scanners::OptionalList::OptionalList(vector, vector)");
    if (aFlagList.size() != aList.size())
        throw invalid_argument("aList.size != aFlagList.size in DS::Tokens::Scanners::OptionalList::OptionalList(vector, vector)");
    bool allOptional = true;
    for (vector<bool>::const_iterator it = aFlagList.begin(); it != aFlagList.end(); ++it)
        allOptional &= *it;
    if (allOptional)
        throw invalid_argument("aFlagList all optional in DS::Tokens::Scanners::OptionalList::OptionalList(vector, vector)");
    theList = aList;
    optionalFlags = aFlagList;
}

Scanner::bounds OptionalList::scan(Scanner::bounds bounds)
{
    if (bounds.first == bounds.second)
        return bounds;

    vector<Scanner::Ptr>::iterator itS = theList.begin();
    vector<bool>::iterator itB = optionalFlags.begin();

    Scanner::bounds currentBounds = bounds;

    for (unsigned int i = 0; i < theList.size(); i++)
    {
        Scanner::Ptr currentScanner = *itS;
        bool optionalFlag = *itB;

        Scanner::bounds resultBounds = currentScanner->scan(currentBounds);
        if (resultBounds.first != resultBounds.second)
        {
            currentBounds.first = resultBounds.second;
        }
        else if (!optionalFlag)
        {
            bounds.second = bounds.first;
            return bounds;
        }
        ++itS;
        ++itB;
    }
    bounds.second = currentBounds.first;
    return bounds;
}

} /* namespace Scanners */
} /* namespace Tokens */
} /* namespace DS */
