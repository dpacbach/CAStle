#pragma once

#include <string>
#include "Infix.hpp"

namespace DS          {
namespace CAS         {
namespace Expressions {
namespace Visitors    {
namespace Render      {
namespace Infixs      {

class String: public DS::CAS::Expressions::Visitors::Render::Infix<string>
{
public:
    String(std::shared_ptr<Numbers::NumberFormatter> formatter) : Infix<string>(formatter) {}
    virtual ~String() {}

protected:
    bool noParenthesisInDivision(void) const { return false; }
    bool noParenthesisInExponent(void) const { return false; }
    bool parenthesisInNegateDivision(void) const { return false; }

    virtual string renderParenthesis(const string& arg);
    virtual string renderComma(const string& leftArg, const string& rightArg);
    virtual string renderAdjacent(const string& leftArg, const string& rightArg);
    virtual string renderString(const string& arg);
    virtual string renderBinaryOp(const string& op, const string& leftArg, const string& rightArg, bool spaces);
    virtual string renderUnaryOp(const string& op, const string& arg, bool leftRight);
    virtual string renderSuperscript(const string& base, const string& super);
    virtual string renderFraction(const string& top, const string& bottom);

};

} /* namespace Infixs */
} /* namespace Render */
} /* namespace Visitors */
} /* namespace Expressions */
} /* namespace CAS */
} /* namespace DS */
