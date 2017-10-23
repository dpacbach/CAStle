#include "DefaultParsers.hpp"

#include <stdexcept>

namespace DS {
namespace Tokens {
namespace Scanners {

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//                           CharString
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
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

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//                               Not
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
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

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//                          OptionalList
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
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

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//                             OrList
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
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

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//                             Repeat
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Scanner::bounds Repeat::scan(Scanner::bounds bounds)
{
    if (bounds.first == bounds.second)
        return bounds;

    decltype(bounds.first) index = bounds.first;
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

} /* namespace Scanner */

namespace ScannerBuilders {

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//                             Simple
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Simple::Simple()  { }
Simple::~Simple() { }

void Simple::charString(const string& aString)
{
    push(Scanner::Ptr(new Scanners::CharString(aString)));
}

void Simple::notted(void)
{
    push(Scanner::Ptr(new Scanners::Not(pop())));
}

void Simple::repeat(void)
{
    push(Scanner::Ptr(new Scanners::Repeat(pop())));
}

void Simple::orList(unsigned int count)
{
    vector<Scanner::Ptr> theList(count);
    for (unsigned int i = 0; i < count; i++)
        theList[count-i-1] = pop();
    push(Scanner::Ptr(new Scanners::OrList(theList)));
}

void Simple::optionalList(unsigned int count)
{
    vector<Scanner::Ptr> theList(count);
    vector<bool> optionalFlags(count);
    for (unsigned int i = 0; i < count; i++)
    {
        theList[count-i-1] = pop();
        optionalFlags[count-i-1] = popFlag();
    }
    push(Scanner::Ptr(new Scanners::OptionalList(theList, optionalFlags)));
}

} /* namespace ScannerBuilders */
} /* namespace Tokens */
} /* namespace DS */
