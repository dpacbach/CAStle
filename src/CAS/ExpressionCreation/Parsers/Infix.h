/*
 * Infix.h
 *
 *  Created on: Feb 11, 2013
 *      Author: davidsicilia
 */

#ifndef INFIX_H_
#define INFIX_H_

#include "../Parser.h"

namespace DS {
namespace CAS {
namespace Expressions {
namespace Parsers {

class Infix: public DS::CAS::Expressions::Parser
{
public:
    Infix(boost::shared_ptr<Tokens::ScannerBuilder> _sBuilder, boost::shared_ptr<Expressions::Builder> _eBuilder,
          boost::shared_ptr<Numbers::NumberFormatter> _nFormatter, boost::shared_ptr<Tokens::Tokenizer> _tokenizer)
         : Parser(_sBuilder, _eBuilder, _nFormatter, _tokenizer) {}
    virtual ~Infix() {}

    virtual void buildScanners(vector<Tokens::Scanner::Ptr>&, boost::shared_ptr<Tokens::ScannerBuilder>);
    virtual bool parseTokens(const vector<Token>&, vector<Command>&);
};

} /* namespace Parsers */
} /* namespace Expressions */
} /* namespace CAS */
} /* namespace DS */
#endif /* INFIX_H_ */
