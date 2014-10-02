/*
 * Parser.cpp
 *
 *  Created on: Feb 11, 2013
 *      Author: davidsicilia
 */

#include <stdexcept>
#include <stack>
#include "Parser.h"
#include "../../Utilities/Templates.h"

namespace DS {
namespace CAS {
namespace Expressions {

Parser::Parser(boost::shared_ptr<Tokens::ScannerBuilder> _sBuilder, boost::shared_ptr<Expressions::Builder> _eBuilder,
               boost::shared_ptr<Numbers::NumberFormatter> _nFormatter, boost::shared_ptr<Tokens::Tokenizer> _tokenizer)
{
    eBuilder     = _eBuilder;
    nFormatter     = _nFormatter;
    sBuilder     = _sBuilder;
    tokenizer     = _tokenizer;
}

Expression::Ptr Parser::parse(const string& source)
{
    if (scanners.empty())
        buildScanners(scanners, sBuilder);
    vector<Token> tokens;
    stopLocation = source.begin();
    bool success = tokenizer->tokenizePriority(source, scanners, tokens);
    if (!success)
    {
        stopLocation = tokenizer->getStopLocation();
        return Expression::Ptr();
    }
    vector<Command> commands;
    if (!parseTokens(tokens, commands))
        return Expression::Ptr();
    for (vector<Command>::const_iterator it = commands.begin(); it != commands.end(); ++it)
    {
        //cout << endl << (*it).getNodeName() << ",  " << (*it).getNodeType() << ",  " << (*it).getNumberOfChildren();
    }
    return buildExpression(commands);
}

Expression::Ptr Parser::buildExpression(const vector<Command>& commands)
{
    stack<Expression::Ptr> expStack;
    Expression::Ptr node, nullShared;
    Numbers::Number* number;
    vector<Expression::Ptr> children;

    for (vector<Command>::const_iterator it = commands.begin(); it != commands.end(); ++it)
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
                    return Expression::Ptr();
                children.insert(children.begin(), getPop(expStack));
            }
            node = eBuilder->operator()((*it).getNodeName(), children);
            if (!node)
                return nullShared;
            expStack.push(node);
            children.resize(0);
            break;
        default:
            throw invalid_argument("invalid node type in Expressions::Parser::buildExpressions(vector<Command>)");
        }
    }
    if (expStack.size() != 1)
        return nullShared;

    return expStack.top();
}

} /* namespace Expressions */
} /* namespace CAS */
} /* namespace DS */
