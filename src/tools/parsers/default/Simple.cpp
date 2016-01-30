/*
 * Simple.cpp
 *
 *  Created on: Feb 10, 2013
 *      Author: davidsicilia
 */

#include "Simple.hpp"
#include "Scanner.hpp"

#include "CharString.hpp"
#include "Not.hpp"
#include "Repeat.hpp"
#include "OrList.hpp"
#include "OptionalList.hpp"

namespace DS {
namespace Tokens {
namespace ScannerBuilders {

Simple::Simple() {
    // TODO Auto-generated constructor stub

}

Simple::~Simple() {
    // TODO Auto-generated destructor stub
}

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
