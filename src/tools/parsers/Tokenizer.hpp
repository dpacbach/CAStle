/*
 * Tokenizer.h
 *
 *  Created on: Feb 8, 2013
 *      Author: davidsicilia
 */

#ifndef TOKENIZER_H_
#define TOKENIZER_H_

#include <string>
#include <vector>
#include <boost/noncopyable.hpp>
#include "Token.h"
#include "Scanner.h"

using namespace std;

namespace DS {
namespace Tokens {

class Tokenizer : private boost::noncopyable
{
public:
    Tokenizer();
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
#endif /* TOKENIZER_H_ */
