#include <stdlib.h>
#include <stdexcept>
#include "Postfix.hpp"
#include "ScannerBuilder.hpp"

namespace DS          {
namespace CAS         {
namespace Expressions {
namespace Parsers     {

Postfix::Postfix(std::shared_ptr<Tokens::ScannerBuilder> _sBuilder, std::shared_ptr<Expressions::Builder> _eBuilder,
        std::shared_ptr<Numbers::NumberFormatter> _nFormatter, std::shared_ptr<Tokens::Tokenizer> _tokenizer)
     : Parser(_sBuilder, _eBuilder, _nFormatter, _tokenizer)
{
    sBuilder->alphaNumString();
    sBuilder->orCharString("+-/*!^%");
    sBuilder->orList(2);
    sBuilder->repeat();
    Tokens::Scanner::Ptr symbol = sBuilder->pop();
    Tokens::Scanner::Ptr scnr;

    childNumberScanners.push_back(symbol);
    sBuilder->charString("(");
    scnr = sBuilder->pop();
    childNumberScanners.push_back(scnr);
    sBuilder->posInteger();
    scnr = sBuilder->pop();
    childNumberScanners.push_back(scnr);
    sBuilder->charString(")");
    scnr = sBuilder->pop();
    childNumberScanners.push_back(scnr);
}

void Postfix::buildScanners(std::vector<Tokens::Scanner::Ptr>& scanners, std::shared_ptr<Tokens::ScannerBuilder> sBuilder)
{
    sBuilder->spaces();
    scanners.push_back(sBuilder->pop());

    sBuilder->imgScientific();
    sBuilder->imgFloat();
    sBuilder->floatScientific();
    sBuilder->floatNumber();
    sBuilder->orList(4);
    scanners.push_back(sBuilder->pop());

    sBuilder->alphaNumString();
    sBuilder->orCharString("+-/*!^%");
    sBuilder->orList(2);
    sBuilder->repeat();
    Tokens::Scanner::Ptr symbol = sBuilder->pop();

    sBuilder->push(symbol);
    sBuilder->pushFlag(false);
    sBuilder->charString("(");
    sBuilder->pushFlag(false);
    sBuilder->spaces();
    sBuilder->pushFlag(true);
    sBuilder->posInteger();
    sBuilder->pushFlag(false);
    sBuilder->spaces();
    sBuilder->pushFlag(true);
    sBuilder->charString(")");
    sBuilder->pushFlag(false);
    sBuilder->optionalList(6);
    scanners.push_back(sBuilder->pop());

    scanners.push_back(symbol);
}

unsigned int Postfix::extractNumberOfChildren(std::string& token) // token = abc123def(123)
{
    std::vector<Token> tokens;
    bool success = tokenizer->tokenizeOrdered(token, childNumberScanners, std::vector<bool>(childNumberScanners.size(), false), tokens);
    if (!success)
    {
        throw std::logic_error("failure of tokenizer in Postfix::extractNumberOfChildren");
    }
    token = (tokens[0]).getString();
    std::string intString = (tokens[2]).getString();

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

bool Postfix::parseTokens(const std::vector<Token>& tokens, std::vector<Command>& commands)
{
    if (tokens.empty())
        return false;

    enum { spaces, number, symbolChildren, symbolNoChildren };
    std::string newToken;
    unsigned int numberOfChildren;
    std::vector<Token>::const_iterator it = tokens.begin();

    if (it != tokens.end())
    {
        if ((*it).getId() == spaces)
        {
            stopLocation += (*it).getString().length();
            ++it;
        }
    }

    while (it != tokens.end())
    {
        switch ((*it).getId())
        {
        case number:
            commands.push_back(Command(Command::literal, (*it).getString(), 0));
            break;
        case symbolNoChildren:
            numberOfChildren = defaultChildrenForSymbol((*it).getString());
            commands.push_back(Command(Command::symbol, (*it).getString(), numberOfChildren));
            break;
        case symbolChildren:
            newToken = (*it).getString();
            numberOfChildren = extractNumberOfChildren(newToken);
            commands.push_back(Command(Command::symbol, newToken, numberOfChildren));
            break;
        default:
            commands.clear();
            throw std::invalid_argument("invalid token type in Postfix::parseTokens()");
        }

        stopLocation += (*it).getString().length();
        ++it;
        if (it != tokens.end())
        {
            if ((*it).getId() != spaces)
            {
                commands.clear();
                return false;
            }
            stopLocation += (*it).getString().length();
            ++it;
        }
    }
    return true;
}

} /* namespace Parsers */
} /* namespace Expressions */
} /* namespace CAS */
} /* namespace DS */
