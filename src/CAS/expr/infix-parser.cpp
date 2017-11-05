#include <stdexcept>
#include <stack>

#include "infix-parser.hpp"
#include "scanner-builder.hpp"

using namespace castle;

namespace DS          {
namespace CAS         {
namespace Expressions {
namespace Parsers     {

void Infix::buildScanners(std::vector<scanner::ptr>& scanners, std::shared_ptr<scanner_builder> sBuilder)
{
    sBuilder->spaces();
    scanners.push_back(sBuilder->pop());

    sBuilder->or_char_string("-");
    scanners.push_back(sBuilder->pop());

    sBuilder->or_char_string("+*/%^");
    scanners.push_back(sBuilder->pop());

    sBuilder->or_char_string("!");
    scanners.push_back(sBuilder->pop());

    sBuilder->img_scientific();
    sBuilder->img_float();
    sBuilder->float_scientific();
    sBuilder->float_number();
    sBuilder->or_list(4);
    scanners.push_back(sBuilder->pop());

    sBuilder->char_string("(");
    scanners.push_back(sBuilder->pop());
    sBuilder->char_string(")");
    scanners.push_back(sBuilder->pop());
    sBuilder->char_string(",");
    scanners.push_back(sBuilder->pop());

    sBuilder->alpha_num_string();
    sBuilder->or_char_string("_");
    sBuilder->or_list(2);
    scanners.push_back(sBuilder->pop());
}

int getOperatorPrecedence(const std::string& str)
{
    if (str == "!")
        return 5;
    if (str == "^")
        return 4;
    if (str == "*" || str == "/" || str == "%")
        return 3;
    if (str == "ng")
          return 4;
    if (str == "+" || str == "-")
        return 2;
    throw std::invalid_argument("invalid operator in getOperatorPrecedence()");
}

int getOperatorChildren(const std::string& str)
{
    if (str == "!" || str == "ng")
        return 1;
    if (str == "^" || str == "*" || str == "/" || str == "+" || str == "-" || str == "%")
        return 2;
    throw std::invalid_argument("invalid operator in getOperatorChildren()");
}

bool isLeftAssociative(const std::string& str)
{
    if (str == "!")
        return true;
    if (str == "^")
        return false;
    if (str == "ng")
        return false;
    if (str == "*" || str == "/" || str == "%")
        return true;
    if (str == "+" || str == "-")
        return true;
    throw std::invalid_argument("invalid operator in isLeftAssociative()");
}

bool Infix::parseTokens(const std::vector<token>& tokens, std::vector<Command>& commands)
{
    enum { spaces, minus, binaryOp, factorial, number, leftP, rightP, comma, var };
    std::stack<token> operatorStack;
    std::stack<int> functionArgStack;
    std::vector<token>::const_iterator it = tokens.begin();
    bool lookingForValue = true;

      //While there are tokens to be read:
    //    Read a token.

    while (1)
    {
        while (it != tokens.end())
        {
            if ((*it).id() == spaces)
            {
                stopLocation += (*it).string().length();
                ++it;
            }
            else
                break;
        }
        if (it == tokens.end())
            break;
        int id = (*it).id();
        std::string str = (*it).string();

        if (lookingForValue)
        {
            //    If the token is a number, then add it to the output queue.
            if (id == number)
            {
                commands.push_back(Command(Command::literal, str, 0));
                stopLocation += (*it).string().length();
                ++it;
                lookingForValue = false;
            }
            //  If the token is a variable or function
            else if (id == var)
            {
                // if we're at the end then it's a variable, add it to output
                if ((it+1) == tokens.end())
                {
                    commands.push_back(Command(Command::symbol, str, 0));
                    stopLocation += (*it).string().length();
                    ++it;
                    lookingForValue = false;
                }
                // could be a variable or function
                else
                {
                    // if next token is not '(' then it's a variable, add it to output
                    if ((*(it+1)).id() != leftP)
                    {
                        commands.push_back(Command(Command::symbol, str, 0));
                        stopLocation += (*it).string().length();
                        ++it;
                        lookingForValue = false;
                    }
                    // it's a function, add it and '(' to stack
                    else
                    {
                        operatorStack.push(*it);
                        operatorStack.push(*(it+1));
                        stopLocation += (*it).string().length();
                        ++it;
                        stopLocation += (*it).string().length();
                        ++it;
                        functionArgStack.push(1);
                        lookingForValue = true;
                    }
                }
            }
            //    If the token is a minus sign
            else if (id == minus)
            {
                // remove operators from stack with higher precedence
                while (!operatorStack.empty())
                {
                    token o2 = operatorStack.top();
                    int o2Id = o2.id();
                    std::string o2Str = o2.string();
                    if (o2Id != minus && o2Id != binaryOp && o2Id != factorial)
                        break;
                    int ngPrecedence = getOperatorPrecedence("ng");
                    int o2Precedence = getOperatorPrecedence(o2Str);
                    if ((ngPrecedence < o2Precedence) || ((ngPrecedence <= o2Precedence) && isLeftAssociative("ng")))
                    {
                        commands.push_back(Command(Command::symbol, o2Str, getOperatorChildren(o2Str)));
                        operatorStack.pop();
                    }
                    else
                        break;
                }
                // add it to stack
                token newToken("ng", minus);
                operatorStack.push(newToken);
                stopLocation += (*it).string().length();
                ++it;
                lookingForValue = true;
            }
            //    If the token is a left parenthesis then add it to stack
            else if (id == leftP)
            {
                operatorStack.push(*it);
                stopLocation += (*it).string().length();
                ++it;
                lookingForValue = true;
            }
            // looking for a value and haven't found one, problem
            else
            {
                commands.clear();
                return false;
            }
        }
        // Looking for an operator
        else
        {
            //    If the token is an operator, o1, then:
            //        while there is an operator token, o2, at the top of the stack, and either o1 is left-associative and its precedence is less than or equal to that of o2, or o1 has precedence less than that of o2,
            //            pop o2 off the stack, onto the output queue;
            //        push o1 onto the stack.
            if (id == minus || id == binaryOp || id == factorial)
            {
                while (!operatorStack.empty())
                {
                    token o2 = operatorStack.top();
                    int o2Id = o2.id();
                    std::string o2Str = o2.string();
                    if (o2Id != minus && o2Id != binaryOp && o2Id != factorial)
                        break;
                    int o1Precedence = getOperatorPrecedence(str);
                    int o2Precedence = getOperatorPrecedence(o2Str);
                    if ((o1Precedence < o2Precedence) || ((o1Precedence <= o2Precedence) && isLeftAssociative(str)))
                    {
                        commands.push_back(Command(Command::symbol, o2Str, getOperatorChildren(o2Str)));
                        operatorStack.pop();
                    }
                    else
                        break;
                }
                // add it to stack
                operatorStack.push(*it);
                stopLocation += (*it).string().length();
                ++it;
                if (id == minus || id == binaryOp)
                    lookingForValue = true;
                else
                    lookingForValue = false;
            }
            //    If the token is a function argument separator (e.g., a comma):
            //        Until the token at the top of the stack is a left parenthesis, pop operators off the stack onto the output queue.
            //        If no left parentheses are encountered, either the separator was misplaced or parentheses were mismatched.
            else if (id == comma)
            {
                // misplaced comma?
                if (functionArgStack.empty())
                {
                    commands.clear();
                    return false;
                }
                ++(functionArgStack.top());
                stopLocation += (*it).string().length();
                ++it;
                while (1)
                {
                    if (operatorStack.empty())
                    {
                        commands.clear();
                        return false;
                    }
                    token token = operatorStack.top();
                    if (token.string() == "(")
                        break;
                    commands.push_back(Command(Command::symbol, token.string(), getOperatorChildren(token.string())));
                    operatorStack.pop();
                }
                lookingForValue = true;
            }
            //    If the token is a right parenthesis:
            //        Until the token at the top of the stack is a left parenthesis
            //            pop operators off the stack onto the output queue.
            //        Pop the left parenthesis from the stack, but not onto the output queue.
            //        If the token at the top of the stack is a function token, pop it onto the output queue.
            //        If the stack runs out without finding a left parenthesis, then there are mismatched parentheses.
            else if (id == rightP)
            {
                while (1)
                {
                    if (operatorStack.empty())
                    {
                        commands.clear();
                        return false;
                    }
                    token token = operatorStack.top();
                    if (token.string() == "(")
                        break;
                    commands.push_back(Command(Command::symbol, token.string(), getOperatorChildren(token.string())));
                    operatorStack.pop();
                }
                operatorStack.pop();
                if (!operatorStack.empty())
                {
                    token token = operatorStack.top();
                    if (token.id() == var)
                    {
                        if (functionArgStack.empty())
                        {
                            commands.clear();
                            return false;
                        }
                        int children = functionArgStack.top();
                        functionArgStack.pop();
                        commands.push_back(Command(Command::symbol, token.string(), children));
                        operatorStack.pop();
                    }
                }
                stopLocation += (*it).string().length();
                ++it;
                lookingForValue = false;
            }
            else
            {
                commands.clear();
                return false;
            }
        }
    }

    if (lookingForValue || !functionArgStack.empty())
    {
        commands.clear();
        return false;
    }

    //When there are no more tokens to read:
    //    While there are still operator tokens in the stack:
    //        If the operator token on the top of the stack is a parenthesis, then there are mismatched parentheses.
    //        Pop the operator onto the output queue.
    while (!operatorStack.empty())
    {
        token token = operatorStack.top();
        operatorStack.pop();
        int id = token.id();
        std::string str = token.string();

        if (id != minus && id != binaryOp && id != factorial)
        {
            commands.clear();
            return false;
        }
        commands.push_back(Command(Command::symbol, str, getOperatorChildren(str)));
    }

    return true;
}

} /* namespace Parsers */
} /* namespace Expressions */
} /* namespace CAS */
} /* namespace DS */
