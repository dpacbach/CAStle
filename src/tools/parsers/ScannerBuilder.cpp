#include "ScannerBuilder.hpp"
#include "Templates.hpp"

namespace DS {
namespace Tokens {

void ScannerBuilder::clearStack(void)
{
    while (!scannerStack.empty())
        scannerStack.pop();
}
unsigned int ScannerBuilder::stackSize(void)
{
    return scannerStack.size();
}
void ScannerBuilder::push(Scanner::Ptr ptr)
{
    scannerStack.push(ptr);
}
Scanner::Ptr ScannerBuilder::pop(void)
{
    return getPop(scannerStack);
}

void ScannerBuilder::clearFlagStack(void)
{
    while (!flagStack.empty())
        flagStack.pop();
}
unsigned int ScannerBuilder::flagStackSize(void)
{
    return flagStack.size();
}
void ScannerBuilder::pushFlag(bool flag)
{
    flagStack.push(flag);
}
bool ScannerBuilder::popFlag(void)
{
    return getPop(flagStack);
}

void ScannerBuilder::space(bool includeNewLine)
{
    if (includeNewLine)
        orCharString(" \t\n");
    else
        orCharString(" \t");
}
void ScannerBuilder::digit(void)
{
    orCharString("0123456789");
}
void ScannerBuilder::alpha(void)
{
    orCharString("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
}

void ScannerBuilder::nonSpace(void)
{
    space();
    notted();
}
void ScannerBuilder::spaces(bool includeNewLine)
{
    space(includeNewLine);
    repeat();
}
void ScannerBuilder::nonSpaces(void)
{
    nonSpace();
    repeat();
}
void ScannerBuilder::alphas(void)
{
    alpha();
    repeat();
}
void ScannerBuilder::digits(void)
{
    digit();
    repeat();
}
void ScannerBuilder::alphaNumString(void)
{
    alpha();
    digit();
    orList(2);
    repeat();
}
void ScannerBuilder::nonAlphaNumSpace(void)
{
    alpha();
    digit();
    space();
    orList(3);
    notted();
}
void ScannerBuilder::orCharString(const string& aString)
{
    string temp = " ";
    for (unsigned int i = 0; i < aString.length(); i++)
    {
        temp[0] = aString[i];
        charString(temp);
    }
    orList(aString.length());
}

void ScannerBuilder::list(unsigned int count)
{
    for (unsigned int i = 0; i < count; i++)
        flagStack.push(false);
    optionalList(count);
}
void ScannerBuilder::listSpaces(unsigned int count, bool includeNewLine)
{
    for (unsigned int i = 0; i < count; i++)
        flagStack.push(false);
    optionalListSpaces(count, includeNewLine);
}
void ScannerBuilder::optionalListSpaces(unsigned int count, bool includeNewLine)
{
    stack<Scanner::Ptr> tempScanners;
    stack<bool> tempFlags;

    for (unsigned int i = 0; i < count; i++)
    {
        tempScanners.push(pop());
        tempFlags.push(popFlag());
    }
    for (unsigned int i = 0; i < count; i++)
    {
        push(getPop(tempScanners));
        pushFlag(getPop(tempFlags));
        if (i < count-1)
        {
            spaces(includeNewLine);
            pushFlag(true);
        }
    }
    optionalList(2*count-1);
}

void ScannerBuilder::variable(void)
{
    alpha();
    pushFlag(false);
    alphaNumString();
    pushFlag(true);
    optionalList(2);
}
void ScannerBuilder::integer(void)
{
    charString("-");
    pushFlag(true);
    digits();
    pushFlag(false);
    optionalList(2);
}
void ScannerBuilder::posInteger(void)
{
    digits();
}
void ScannerBuilder::posFloatNumber(void)
{
    digits();
    pushFlag(true);
    charString(".");
    pushFlag(true);
    digits();
    pushFlag(false);
    optionalList(3);

    digits();
    pushFlag(false);
    charString(".");
    pushFlag(true);
    optionalList(2);

    orList(2);
}
void ScannerBuilder::floatNumber(void)
{
    charString("-");
    pushFlag(true);
    posFloatNumber();
    pushFlag(false);
    optionalList(2);
}
void ScannerBuilder::floatScientific(void)
{
    floatNumber();
    charString("e");
    integer();
    list(3);
}
void ScannerBuilder::posFloatScientific(void)
{
    posFloatNumber();
    charString("e");
    integer();
    list(3);
}

void ScannerBuilder::imgFloat(void)
{
    floatNumber();
    charString("i");
    list(2);
}
void ScannerBuilder::imgScientific(void)
{
    floatScientific();
    charString("i");
    list(2);
}

void ScannerBuilder::duplicate(void)
{
    Scanner::Ptr temp = pop();
    push(temp);
    push(temp);
}

}
}


