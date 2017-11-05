#pragma once

#include "parser.hpp"

namespace DS          {
namespace CAS         {
namespace Expressions {
namespace Parsers     {

class Infix : public DS::CAS::Expressions::Parser
{
public:
    Infix(std::shared_ptr<castle::scanner_builder> _sBuilder, std::shared_ptr<Expressions::Builder> _eBuilder,
          std::shared_ptr<Numbers::NumberFormatter> _nFormatter, std::shared_ptr<castle::tokenizer> _tokenizer)
         : Parser(_sBuilder, _eBuilder, _nFormatter, _tokenizer) {}
    virtual ~Infix() {}

    virtual void buildScanners(std::vector<castle::scanner::ptr>&, std::shared_ptr<castle::scanner_builder>);
    virtual bool parseTokens(const std::vector<castle::token>&, std::vector<Command>&);
};

} /* namespace Parsers */
} /* namespace Expressions */
} /* namespace CAS */
} /* namespace DS */
