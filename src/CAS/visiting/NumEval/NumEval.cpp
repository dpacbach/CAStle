/*
 * NumEval.cpp
 *
 *  Created on: Feb 17, 2013
 *      Author: davidsicilia
 */

#include <stdexcept>
#include "NumEval.h"

namespace DS {
namespace CAS {
namespace Expressions {
namespace Visitors {

NumEval::NumEval() {
    // TODO Auto-generated constructor stub

}

NumEval::~NumEval() {
    // TODO Auto-generated destructor stub
}

bool NumEval::visitAdd(const Add& exp)
{
    NumberP sum = getPop(childResults);
    unsigned int nc = exp.numberOfChildren();
    if (exp.getSignForChild(nc-1) == Expressions::n)
        sum.negate();
    for (int i = static_cast<int>(nc)-2; i >= 0; i--)
    {
        NumberP term = getPop(childResults);
        if (exp.getSignForChild(static_cast<unsigned int>(i)) == Expressions::n)
            term.negate();
        sum += term;
    }
    childResults.push(sum);
    return true;
}
bool NumEval::visitDivide(const Divide& exp)
{
    NumberP right = getPop(childResults);
    NumberP left  = getPop(childResults);
    left /= right;
    childResults.push(left);
    return true;
}
bool NumEval::visitFactorial(const Factorial& exp)
{
    throw invalid_argument("NumEval::visitFactorial not implemented");
    return true;
}
bool NumEval::visitLiteral(const Literal& exp)
{
    childResults.push(exp.getNumber());
    return true;
}
bool NumEval::visitModulus(const Modulus& exp)
{
    throw invalid_argument("NumEval::visitModulus not implemented");
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
bool NumEval::visitNegate(const Negate& exp)
{
    NumberP result = getPop(childResults);
    result.negate();
    childResults.push(result);
    return true;
}
bool NumEval::visitPower(const Power& exp)
{
    NumberP exponent = getPop(childResults);
    NumberP base = getPop(childResults);
    base.raiseToPower(exponent);
    childResults.push(base);
    return true;
}
bool NumEval::visitSymbol(const Symbol& exp)
{
    return false;
}


} /* namespace Visitors */
} /* namespace Expressions */
} /* namespace CAS */
} /* namespace DS */
