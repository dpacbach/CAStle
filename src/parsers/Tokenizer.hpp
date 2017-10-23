#pragma once

#include <string>
#include <vector>
#include "Token.hpp"
#include "Scanner.hpp"

using namespace std;

namespace DS {
namespace Tokens {

class Tokenizer
{
public:
    Tokenizer();
    Tokenizer(const Tokenizer&)            = delete;
    Tokenizer& operator=(const Tokenizer&) = delete;

    virtual ~Tokenizer();

    virtual bool tokenizePriority(const string& source, const vector<Scanner::Ptr>& scanners, vector<Token>& destination);
    virtual bool tokenizeOrdered(const string& source, const vector<Scanner::Ptr>& scanners,
                                 const vector<bool>& optionalFlags, vector<Token>& destination, bool dummies = false);
    string::const_iterator getStopLocation(void) const { return stopLocation; }

protected:
    string::const_iterator stopLocation;
};

} /* namespace Token */
} /* namespace DS */
