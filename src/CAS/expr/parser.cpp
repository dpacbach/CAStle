#include <stdexcept>
#include <stack>
#include "parser.hpp"
#include "Templates.hpp"

using namespace castle;

namespace DS          {
namespace CAS         {
namespace Expressions {

Parser::Parser(std::shared_ptr<scanner_builder> _sBuilder, std::shared_ptr<Expressions::Builder> _eBuilder,
               std::shared_ptr<Numbers::NumberFormatter> _nFormatter, std::shared_ptr<tokenizer> _tokenizer)
{
    eBuilder     = _eBuilder;
    nFormatter     = _nFormatter;
    sBuilder     = _sBuilder;
    m_tokenizer  = _tokenizer;
}

ExprConstSP Parser::parse(const std::string& source)
{
    if (scanners.empty())
        buildScanners(scanners, sBuilder);
    std::vector<token> tokens;
    stopLocation = source.begin();
    bool success = m_tokenizer->tokenize_priority(source, scanners, tokens);
    if (!success)
    {
        stopLocation = m_tokenizer->stop_location();
        return ExprConstSP();
    }
    std::vector<Command> commands;
    if (!parseTokens(tokens, commands))
        return ExprConstSP();
    for (std::vector<Command>::const_iterator it = commands.begin(); it != commands.end(); ++it)
    {
        //cout << endl << (*it).getNodeName() << ",  " << (*it).getNodeType() << ",  " << (*it).getNumberOfChildren();
    }
    return buildExpression(commands);
}

ExprConstSP Parser::buildExpression(const std::vector<Command>& commands)
{
    stack<ExprConstSP> expStack;
    ExprConstSP node, nullShared;
    Numbers::Number* number;
    std::vector<ExprConstSP> children;

    for (std::vector<Command>::const_iterator it = commands.begin(); it != commands.end(); ++it)
    {
        switch ((*it).getNodeType())
        {
        case Command::literal:
            number = nFormatter->format((*it).getNodeName());
            if (!number)
                return nullShared;
            node = eBuilder->literal(number);
            expStack.push(node);
            break;
        case Command::symbol:
            for (unsigned int i = 0; i < (*it).getNumberOfChildren(); i++)
            {
                if (expStack.size() == 0)
                    return ExprConstSP();
                children.insert(children.begin(), getPop(expStack));
            }
            node = eBuilder->operator()((*it).getNodeName(), children);
            if (!node)
                return nullShared;
            expStack.push(node);
            children.resize(0);
            break;
        default:
            throw std::invalid_argument("invalid node type in Expressions::Parser::buildExpressions(std::vector<Command>)");
        }
    }
    if (expStack.size() != 1)
        return nullShared;

    return expStack.top();
}

} /* namespace Expressions */
} /* namespace CAS */
} /* namespace DS */
