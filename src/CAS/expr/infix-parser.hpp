#pragma once

#include "Parser.hpp"

namespace DS          {
namespace CAS         {
namespace Expressions {
namespace Parsers     {

class Infix : public DS::CAS::Expressions::Parser
{
public:
    Infix(std::shared_ptr<Tokens::ScannerBuilder> _sBuilder, std::shared_ptr<Expressions::Builder> _eBuilder,
          std::shared_ptr<Numbers::NumberFormatter> _nFormatter, std::shared_ptr<Tokens::Tokenizer> _tokenizer)
         : Parser(_sBuilder, _eBuilder, _nFormatter, _tokenizer) {}
    virtual ~Infix() {}

    virtual void buildScanners(std::vector<Tokens::Scanner::Ptr>&, std::shared_ptr<Tokens::ScannerBuilder>);
    virtual bool parseTokens(const std::vector<Token>&, std::vector<Command>&);
};

} /* namespace Parsers */
} /* namespace Expressions */
} /* namespace CAS */
} /* namespace DS */
