// ╔═════════════════════════════════════════════════════════════╗
// ║                           Parsers                           ║
// ╚═════════════════════════════════════════════════════════════╝
#pragma once

#include <string>
#include <vector>
#include "Scanner.hpp"
#include "ScannerBuilder.hpp"

using namespace std;

namespace DS {
namespace Tokens {
namespace Scanners {

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//                           CharString
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
class CharString: public DS::Tokens::Scanner
{
public:
    CharString(const string& aString) : scanString(aString) {}
    CharString(const char aChar) : scanString(1, aChar) {}
    virtual ~CharString() {}

    virtual Scanner::bounds scan(Scanner::bounds);

    const string& getString(void) const { return scanString; }

protected:
    string scanString;
};

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//                               Not
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
class Not: public DS::Tokens::Scanner
{
public:
    Not(Scanner::Ptr _repeated) : repeated(_repeated) {}
    virtual ~Not() {}

    virtual Scanner::bounds scan(Scanner::bounds);

protected:
    Scanner::Ptr repeated;
};

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//                          OptionalList
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
class OptionalList: public DS::Tokens::Scanner
{
public:
    OptionalList(const vector<Scanner::Ptr>&);
    OptionalList(const vector<Scanner::Ptr>&, const vector<bool>&);
    virtual ~OptionalList() {}

    virtual Scanner::bounds scan(Scanner::bounds);

protected:
    vector<Scanner::Ptr> theList;
    vector<bool> optionalFlags;
};

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//                             OrList
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
class OrList: public DS::Tokens::Scanner
{
public:
    OrList(const vector<Scanner::Ptr>&);
    virtual ~OrList() {}

    virtual Scanner::bounds scan(Scanner::bounds);

protected:
    vector<Scanner::Ptr> theList;
};

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//                             Repeat
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
class Repeat: public DS::Tokens::Scanner
{
public:
    Repeat(Scanner::Ptr _repeated) : repeated(_repeated) {}
    virtual ~Repeat() {}

    virtual Scanner::bounds scan(Scanner::bounds);

protected:
    Scanner::Ptr repeated;
};

} /* namespace Scanners */

namespace ScannerBuilders {

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//                             Simple
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
class Simple: public DS::Tokens::ScannerBuilder
{
public:
    Simple();
    virtual ~Simple();

    virtual void charString(const string&);
    virtual void notted(void);
    virtual void repeat(void);
    virtual void orList(unsigned int);
    virtual void optionalList(unsigned int);
};

} /* namespace ScannerBuilders */
} /* namespace Tokens */
} /* namespace DS */
