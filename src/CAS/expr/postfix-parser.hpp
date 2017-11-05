#pragma once

#include "parser.hpp"

namespace DS          {
namespace CAS         {
namespace Expressions {
namespace Parsers     {

class Postfix : public DS::CAS::Expressions::Parser
{
public:
    Postfix(std::shared_ptr<castle::scanner_builder> _sBuilder, std::shared_ptr<Expressions::Builder> _eBuilder,
            std::shared_ptr<Numbers::NumberFormatter> _nFormatter, std::shared_ptr<castle::tokenizer> _tokenizer);
    virtual ~Postfix() {}

    virtual void buildScanners(std::vector<castle::scanner::ptr>&, std::shared_ptr<castle::scanner_builder>);
    virtual bool parseTokens(const std::vector<castle::token>&, std::vector<Command>&);

protected:
    unsigned int extractNumberOfChildren(std::string&);
    unsigned int defaultChildrenForSymbol(const std::string&);
    std::vector<castle::scanner::ptr> childNumberScanners;
};

} /* namespace Parsers */
} /* namespace Expressions */
} /* namespace CAS */
} /* namespace DS */
