/*
 * ScannerBuilder.h
 *
 *  Created on: Feb 8, 2013
 *      Author: davidsicilia
 */

#ifndef SCANNERBUILDER_H_
#define SCANNERBUILDER_H_

#include <string>
#include <stack>
#include "Scanner.h"
#include <boost/noncopyable.hpp>

namespace DS {
namespace Tokens {

class ScannerBuilder : private boost::noncopyable
{
public:
    ScannerBuilder() {}
    virtual ~ScannerBuilder() {}

    virtual void clearStack(void);
    virtual unsigned int stackSize(void);
    virtual void push(Scanner::Ptr);
    virtual Scanner::Ptr pop(void);

    virtual void clearFlagStack(void);
    virtual unsigned int flagStackSize(void);
    virtual void pushFlag(bool);
    virtual bool popFlag(void);

    virtual void charString(const string&)  = 0;
    virtual void notted(void)                = 0;
    virtual void repeat(void)                 = 0;
    virtual void orList(unsigned int)         = 0;
    virtual void optionalList(unsigned int) = 0;

    virtual void space(bool includeNewLine = true);
    virtual void digit(void);
    virtual void alpha(void);
    virtual void alphas(void);
    virtual void digits(void);

    virtual void nonSpace(void);
    virtual void spaces(bool includeNewLine = true);
    virtual void nonSpaces(void);
    virtual void alphaNumString(void);
    virtual void nonAlphaNumSpace(void);
    virtual void orCharString(const string&);

    virtual void list(unsigned int);
    virtual void listSpaces(unsigned int, bool includeNewLine = true);
    virtual void optionalListSpaces(unsigned int, bool includeNewLine = true);

    virtual void variable(void);

    virtual void integer(void);
    virtual void posInteger(void);
    virtual void floatNumber(void);
    virtual void posFloatNumber(void);
    virtual void floatScientific(void);
    virtual void posFloatScientific(void);
    virtual void imgFloat(void);
    virtual void imgScientific(void);

    virtual void duplicate(void);

protected:
    stack<Scanner::Ptr> scannerStack;
    stack<bool> flagStack;
};

} /* namespace Token */
} /* namespace DS */
#endif /* SCANNERBUILDER_H_ */
