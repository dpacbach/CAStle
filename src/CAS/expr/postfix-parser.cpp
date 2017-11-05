#include <stdlib.h>
#include <stdexcept>

#include "postfix-parser.hpp"
#include "scanner-builder.hpp"

using namespace castle;

namespace DS          {
namespace CAS         {
namespace Expressions {
namespace Parsers     {

Postfix::Postfix(std::shared_ptr<scanner_builder> _sBuilder, std::shared_ptr<Expressions::Builder> _eBuilder,
        std::shared_ptr<Numbers::NumberFormatter> _nFormatter, std::shared_ptr<tokenizer> _tokenizer)
     : Parser(_sBuilder, _eBuilder, _nFormatter, _tokenizer)
{
    sBuilder->alpha_num_string();
    sBuilder->or_char_string("+-/*!^%");
    sBuilder->or_list(2);
    sBuilder->repeat();
    scanner::ptr symbol = sBuilder->pop();
    scanner::ptr scnr;

    childNumberScanners.push_back(symbol);
    sBuilder->char_string("(");
    scnr = sBuilder->pop();
    childNumberScanners.push_back(scnr);
    sBuilder->pos_integer();
    scnr = sBuilder->pop();
    childNumberScanners.push_back(scnr);
    sBuilder->char_string(")");
    scnr = sBuilder->pop();
    childNumberScanners.push_back(scnr);
}

void Postfix::buildScanners(std::vector<scanner::ptr>& scanners, std::shared_ptr<scanner_builder> sBuilder)
{
    sBuilder->spaces();
    scanners.push_back(sBuilder->pop());

    sBuilder->img_scientific();
    sBuilder->img_float();
    sBuilder->float_scientific();
    sBuilder->float_number();
    sBuilder->or_list(4);
    scanners.push_back(sBuilder->pop());

    sBuilder->alpha_num_string();
    sBuilder->or_char_string("+-/*!^%");
    sBuilder->or_list(2);
    sBuilder->repeat();
    scanner::ptr symbol = sBuilder->pop();

    sBuilder->push(symbol);
    sBuilder->push_flag(false);
    sBuilder->char_string("(");
    sBuilder->push_flag(false);
    sBuilder->spaces();
    sBuilder->push_flag(true);
    sBuilder->pos_integer();
    sBuilder->push_flag(false);
    sBuilder->spaces();
    sBuilder->push_flag(true);
    sBuilder->char_string(")");
    sBuilder->push_flag(false);
    sBuilder->optional_list(6);
    scanners.push_back(sBuilder->pop());

    scanners.push_back(symbol);
}

unsigned int Postfix::extractNumberOfChildren(std::string& token) // token = abc123def(123)
{
    std::vector<castle::token> tokens;
    bool success = m_tokenizer->tokenize_ordered(token, childNumberScanners, std::vector<bool>(childNumberScanners.size(), false), tokens);
    if (!success)
    {
        throw std::logic_error("failure of tokenizer in Postfix::extractNumberOfChildren");
    }
    token = (tokens[0]).string();
    std::string intString = (tokens[2]).string();

    unsigned int children = atoi(intString.c_str());

    return children;
}

unsigned int Postfix::defaultChildrenForSymbol(const std::string& symbol)
{
    if (symbol == "+" || symbol == "-" || symbol == "*" ||
        symbol == "/" || symbol == "^" || symbol == "%")
        return 2;
    if (symbol == "!" || symbol == "ng")
        return 1;
    return 0;
}

bool Postfix::parseTokens(const std::vector<token>& tokens, std::vector<Command>& commands)
{
    if (tokens.empty())
        return false;

    enum { spaces, number, symbolChildren, symbolNoChildren };
    std::string newToken;
    unsigned int numberOfChildren;
    std::vector<token>::const_iterator it = tokens.begin();

    if (it != tokens.end())
    {
        if ((*it).id() == spaces)
        {
            stopLocation += (*it).string().length();
            ++it;
        }
    }

    while (it != tokens.end())
    {
        switch ((*it).id())
        {
        case number:
            commands.push_back(Command(Command::literal, (*it).string(), 0));
            break;
        case symbolNoChildren:
            numberOfChildren = defaultChildrenForSymbol((*it).string());
            commands.push_back(Command(Command::symbol, (*it).string(), numberOfChildren));
            break;
        case symbolChildren:
            newToken = (*it).string();
            numberOfChildren = extractNumberOfChildren(newToken);
            commands.push_back(Command(Command::symbol, newToken, numberOfChildren));
            break;
        default:
            commands.clear();
            throw std::invalid_argument("invalid token type in Postfix::parseTokens()");
        }

        stopLocation += (*it).string().length();
        ++it;
        if (it != tokens.end())
        {
            if ((*it).id() != spaces)
            {
                commands.clear();
                return false;
            }
            stopLocation += (*it).string().length();
            ++it;
        }
    }
    return true;
}

} /* namespace Parsers */
} /* namespace Expressions */
} /* namespace CAS */
} /* namespace DS */
