/*
 * Postfix.h
 *
 *  Created on: Feb 11, 2013
 *      Author: davidsicilia
 */

#ifndef POSTFIX_H_
#define POSTFIX_H_

#include "../Parser.h"

using namespace std;

namespace DS {
namespace CAS {
namespace Expressions {
namespace Parsers {

class Postfix: public DS::CAS::Expressions::Parser
{
public:
    Postfix(boost::shared_ptr<Tokens::ScannerBuilder> _sBuilder, boost::shared_ptr<Expressions::Builder> _eBuilder,
            boost::shared_ptr<Numbers::NumberFormatter> _nFormatter, boost::shared_ptr<Tokens::Tokenizer> _tokenizer);
    virtual ~Postfix() {}

    virtual void buildScanners(vector<Tokens::Scanner::Ptr>&, boost::shared_ptr<Tokens::ScannerBuilder>);
    virtual bool parseTokens(const vector<Token>&, vector<Command>&);

protected:
    unsigned int extractNumberOfChildren(string&);
    unsigned int defaultChildrenForSymbol(const string&);
    vector<Tokens::Scanner::Ptr> childNumberScanners;
};

} /* namespace Parsers */
} /* namespace Expressions */
} /* namespace CAS */
} /* namespace DS */
#endif /* POSTFIX_H_ */
