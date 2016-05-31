#pragma once

#include "Parser.hpp"

namespace DS          {
namespace CAS         {
namespace Expressions {
namespace Parsers     {

class Postfix : public DS::CAS::Expressions::Parser
{
public:
    Postfix(std::shared_ptr<Tokens::ScannerBuilder> _sBuilder, std::shared_ptr<Expressions::Builder> _eBuilder,
            std::shared_ptr<Numbers::NumberFormatter> _nFormatter, std::shared_ptr<Tokens::Tokenizer> _tokenizer);
    virtual ~Postfix() {}

    virtual void buildScanners(std::vector<Tokens::Scanner::Ptr>&, std::shared_ptr<Tokens::ScannerBuilder>);
    virtual bool parseTokens(const std::vector<Token>&, std::vector<Command>&);

protected:
    unsigned int extractNumberOfChildren(std::string&);
    unsigned int defaultChildrenForSymbol(const std::string&);
    std::vector<Tokens::Scanner::Ptr> childNumberScanners;
};

} /* namespace Parsers */
} /* namespace Expressions */
} /* namespace CAS */
} /* namespace DS */
