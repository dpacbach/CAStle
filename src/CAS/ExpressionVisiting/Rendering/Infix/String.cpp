/*
 * String.cpp
 *
 *  Created on: Feb 14, 2013
 *      Author: davidsicilia
 */

#include "String.h"

namespace DS {
namespace CAS {
namespace Expressions {
namespace Visitors {
namespace Render {
namespace Infixs {

string String::renderParenthesis(const string& arg)
{
    return "(" + arg + ")";
}
string String::renderComma(const string& leftArg, const string& rightArg)
{
    return leftArg + ", " + rightArg;
}
string String::renderAdjacent(const string& leftArg, const string& rightArg)
{
    return leftArg + rightArg;
}
string String::renderString(const string& arg)
{
    return arg;
}
string String::renderBinaryOp(const string& op, const string& leftArg, const string& rightArg, bool spaces)
{
    string space = spaces ? " " : "";
    return leftArg + space + op + space + rightArg;
}
string String::renderUnaryOp(const string& op, const string& arg, bool leftRight)
{
    if (leftRight)
        return arg + op;
    return op + arg;
}
string String::renderSuperscript(const string& base, const string& super)
{
    return base + "^" + super;
}
string String::renderFraction(const string& top, const string& bottom)
{
    return top + "/" + bottom;
}


} /* namespace Infixs */
} /* namespace Render */
} /* namespace Visitors */
} /* namespace Expressions */
} /* namespace CAS */
} /* namespace DS */
