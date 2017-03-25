#include <stdexcept>
#include "NumEval.hpp"
#include "NumberProxy.hpp"
#include "exprs.hpp"

using namespace DS::CAS::Numbers::Proxy;

namespace DS          {
namespace CAS         {
namespace Expressions {
namespace Visitors    {

NumEval::NumEval() { }

NumEval::~NumEval() { }

NumberP NumEval::result(void)
{
    if (childResults.size() != 1)
        throw std::logic_error("childResults.size() != 1 in Expressions::Visitors::Renderer::result");
    return getPop(childResults);
}

bool NumEval::visitAdd(const Add& exp)
{
    NumberP sum = getPop(childResults);
    unsigned int nc = exp.numberOfChildren();
    if (exp.getSignForChild(nc-1) == Expressions::Sign::n)
        sum.negate();
    for (int i = static_cast<int>(nc)-2; i >= 0; i--)
    {
        NumberP term = getPop(childResults);
        if (exp.getSignForChild(static_cast<unsigned int>(i)) == Expressions::Sign::n)
            term.negate();
        sum += term;
    }
    childResults.push(sum);
    return true;
}
bool NumEval::visitDivide(const Divide&)
{
    NumberP right = getPop(childResults);
    NumberP left  = getPop(childResults);
    left /= right;
    childResults.push(left);
    return true;
}
bool NumEval::visitFactorial(const Factorial&)
{
    throw std::invalid_argument("NumEval::visitFactorial not implemented");
    return true;
}
bool NumEval::visitLiteral(const Literal& exp)
{
    childResults.push(exp.getNumber());
    return true;
}
bool NumEval::visitModulus(const Modulus&)
{
    throw std::invalid_argument("NumEval::visitModulus not implemented");
    return true;
}
bool NumEval::visitMultiply(const Multiply& exp)
{
    NumberP product = getPop(childResults);
    unsigned int nc = exp.numberOfChildren();
    for (int i = static_cast<int>(nc)-2; i >= 0; i--)
    {
        NumberP factor = getPop(childResults);
        product *= factor;
    }
    childResults.push(product);
    return true;
}
bool NumEval::visitNegate(const Negate&)
{
    NumberP result = getPop(childResults);
    result.negate();
    childResults.push(result);
    return true;
}
bool NumEval::visitPower(const Power&)
{
    NumberP exponent = getPop(childResults);
    NumberP base = getPop(childResults);
    base.raiseToPower(exponent);
    childResults.push(base);
    return true;
}
bool NumEval::visitSymbol(const Symbol&)
{
    return false;
}


} /* namespace Visitors */
} /* namespace Expressions */
} /* namespace CAS */
} /* namespace DS */
