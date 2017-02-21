#pragma once

#include "Renderer.hpp"
#include "exprs.hpp"

namespace DS          {
namespace CAS         {
namespace Expressions {
namespace Visitors    {
namespace Render      {

template<typename T>
class Infix : public DS::CAS::Expressions::Visitors::Renderer<T>
{
public:
    Infix(std::shared_ptr<Numbers::NumberFormatter> formatter) : Renderer<T>(formatter) {}
    virtual ~Infix() {}

    virtual bool visitAdd(const Add&);
    virtual bool visitDivide(const Divide&);
    virtual bool visitFactorial(const Factorial&);
    virtual bool visitLiteral(const Literal&);
    virtual bool visitModulus(const Modulus&);
    virtual bool visitMultiply(const Multiply&);
    virtual bool visitNegate(const Negate&);
    virtual bool visitPower(const Power&);
    virtual bool visitSymbol(const Symbol&);

protected:
    virtual bool noParenthesisInDivision(void) const = 0;
    virtual bool noParenthesisInExponent(void) const = 0;
    virtual bool parenthesisInNegateDivision(void) const = 0;

    virtual T renderParenthesis(const T& arg) = 0;
    virtual T renderComma(const T& leftArg, const T& rightArg) = 0;
    virtual T renderAdjacent(const T& leftArg, const T& rightArg) = 0;
    virtual T renderString(const string& arg) = 0;
    virtual T renderBinaryOp(const string& op, const T& leftArg, const T& rightArg, bool spaces) = 0;
    virtual T renderUnaryOp(const string& op, const T& arg, bool leftRight) = 0;
    virtual T renderSuperscript(const T& base, const T& super) = 0;
    virtual T renderFraction(const T& top, const T& bottom) = 0;
};

template<typename T>
bool Infix<T>::visitAdd(const Add& exp)
{
    unsigned int nc = exp.numberOfChildren();
    T resultLeft, resultRight;
    for (unsigned int currentChild = nc-1; (currentChild+1) >= 1; currentChild--)
    {
        resultLeft = getPop(this->childResults);
        if (exp.getSignForChild(currentChild) == Expressions::Sign::n &&
            exp.getChild(currentChild)->id()  == ID::add)
            resultLeft = renderParenthesis(resultLeft);
        if (currentChild != nc-1)
        {
            if (exp.getSignForChild(currentChild+1) == Expressions::Sign::p)
                resultRight = renderBinaryOp("+", resultLeft, resultRight, true);
            else
                resultRight = renderBinaryOp("-", resultLeft, resultRight, true);
        }
        else
            resultRight = resultLeft;
    }
    if (exp.getSignForChild(0) == Expressions::Sign::n)
        resultRight = renderUnaryOp("-", resultRight, false);

    this->childResults.push(resultRight);
    return true;
}
template<typename T>
bool Infix<T>::visitDivide(const Divide& exp)
{
    T denominator = getPop(this->childResults);
    T numerator = getPop(this->childResults);
    if (!noParenthesisInDivision())
    {
        Expressions::ID numID = exp.getChild(0)->id();
        Expressions::ID denID = exp.getChild(1)->id();
        if (numID == Expressions::ID::add)
            numerator = renderParenthesis(numerator);
        if (denID == Expressions::ID::add || denID == Expressions::ID::divide ||
            denID == Expressions::ID::modulus || denID == Expressions::ID::multiply)
            denominator = renderParenthesis(denominator);
    }
    this->childResults.push(renderFraction(numerator, denominator));
    return true;
}
template<typename T>
bool Infix<T>::visitFactorial(const Factorial& exp)
{
    T arg = getPop(this->childResults);
    Expressions::ID id = exp.getChild(0)->id();
    if (id == Expressions::ID::add || id == Expressions::ID::divide || id == Expressions::ID::modulus ||
        id == Expressions::ID::multiply || id == Expressions::ID::negate || id == Expressions::ID::power)
        arg = renderParenthesis(arg);
    this->childResults.push(renderUnaryOp("!", arg, true));
    return true;
}
template<typename T>
bool Infix<T>::visitLiteral(const Literal& exp)
{
    const CAS::Numbers::Number& number = exp.getNumber();
    if (number.isReal())
        this->childResults.push(renderString(this->formatter->formatRealPart(number)));
    else if (number.isImaginary())
    {
        string iNumber = this->formatter->formatImaginaryPart(number);
        if (iNumber == "1")
            iNumber = "";
        if (iNumber == "-1")
            iNumber = "-";
        this->childResults.push(renderString(iNumber + "i"));
    }
    else
        throw logic_error("Attempting to render a number with non-zero real and imaginary parts in Visitors::Render::Infix::visitLiteral()");
    return true;
}
template<typename T>
bool Infix<T>::visitModulus(const Modulus& exp)
{
    T denominator = getPop(this->childResults);
    T numerator = getPop(this->childResults);

    Expressions::ID numID = exp.getChild(0)->id();
    Expressions::ID denID = exp.getChild(1)->id();
    if (numID == Expressions::ID::add || numID == Expressions::ID::negate)
        numerator = renderParenthesis(numerator);
    if (denID == Expressions::ID::add || denID == Expressions::ID::divide ||
        denID == Expressions::ID::modulus || denID == Expressions::ID::multiply)
        denominator = renderParenthesis(denominator);

    this->childResults.push(renderBinaryOp("%", numerator, denominator, false));
    return true;
}
template<typename T>
bool Infix<T>::visitMultiply(const Multiply& exp)
{
    unsigned int nc = exp.numberOfChildren();
    T resultLeft, resultRight;
    for (unsigned int currentChild = nc-1; (currentChild+1) >= 1; currentChild--)
    {
        resultLeft = getPop(this->childResults);
        Expressions::ID id = exp.getChild(currentChild)->id();
        if (id == Expressions::ID::add || id == Expressions::ID::modulus)
            resultLeft = renderParenthesis(resultLeft);
        if (currentChild != nc-1)
            resultRight = renderBinaryOp("*", resultLeft, resultRight, false);
        else
            resultRight = resultLeft;
    }
    this->childResults.push(resultRight);
    return true;
}
template<typename T>
bool Infix<T>::visitNegate(const Negate& exp)
{
    T arg = getPop(this->childResults);
    Expressions::ID id = exp.getChild(0)->id();
    if (id == Expressions::ID::add || (id == Expressions::ID::divide && parenthesisInNegateDivision()))
        arg = renderParenthesis(arg);
    this->childResults.push(renderUnaryOp("-", arg, false));
    return true;
}
template<typename T>
bool Infix<T>::visitPower(const Power& exp)
{
    T exponent = getPop(this->childResults);
    T base = getPop(this->childResults);

    Expressions::ID id = exp.getChild(0)->id(); // base
    if (id == Expressions::ID::add || id == Expressions::ID::divide || id == Expressions::ID::modulus ||
        id == Expressions::ID::multiply || id == Expressions::ID::negate || id == Expressions::ID::power)
        base = renderParenthesis(base);
    if (!noParenthesisInExponent())
    {
        id = exp.getChild(1)->id();
        if (id == Expressions::ID::add || id == Expressions::ID::divide ||
            id == Expressions::ID::modulus || id == Expressions::ID::multiply)
            exponent = renderParenthesis(exponent);
    }
    this->childResults.push(renderSuperscript(base, exponent));
    return true;
}
template<typename T>
bool Infix<T>::visitSymbol(const Symbol& exp)
{
    unsigned int nc = exp.numberOfChildren();
    if (!nc)
    {
        this->childResults.push(renderString(exp.getName()));
        return true;
    }
    T resultLeft, resultRight;
    for (unsigned int currentChild = nc-1; (currentChild+1) >= 1; currentChild--)
    {
        resultLeft = getPop(this->childResults);
        if (currentChild != nc-1)
            resultRight = renderComma(resultLeft, resultRight);
        else
            resultRight = resultLeft;
    }
    resultRight = renderParenthesis(resultRight);
    T name = renderString(exp.getName());
    this->childResults.push(renderAdjacent(name, resultRight));
    return true;
}

} /* namespace Render */
} /* namespace Visitors */
} /* namespace Expressions */
} /* namespace CAS */
} /* namespace DS */
