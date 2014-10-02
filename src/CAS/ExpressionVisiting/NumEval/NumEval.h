/*
 * NumEval.h
 *
 *  Created on: Feb 17, 2013
 *      Author: davidsicilia
 */

#ifndef NUMEVAL_H_
#define NUMEVAL_H_

#include <stack>
#include <stdexcept>
#include "../../Number/Numbers.h"
#include "../Visitor.h"
#include "../../../Utilities/Templates.h"

using namespace std;
using namespace DS::CAS::Numbers;
using namespace DS::CAS::Numbers::Proxy;

namespace DS {
namespace CAS {
namespace Expressions {
namespace Visitors {

class NumEval: public DS::CAS::Expressions::Visitor
{
public:
    NumEval();
    virtual ~NumEval();

    virtual void reset(void)
    {
        clearStack(childResults);
    }

    virtual bool visitAdd(const Add&);
    virtual bool visitDivide(const Divide&);
    virtual bool visitFactorial(const Factorial&);
    virtual bool visitLiteral(const Literal&);
    virtual bool visitModulus(const Modulus&);
    virtual bool visitMultiply(const Multiply&);
    virtual bool visitNegate(const Negate&);
    virtual bool visitPower(const Power&);
    virtual bool visitSymbol(const Symbol&);

    virtual NumberP result(void)
    {
        if (childResults.size() != 1)
            throw logic_error("childResults.size() != 1 in Expressions::Visitors::Renderer::result");
        return getPop(childResults);
    }

protected:
    stack<NumberP> childResults;
};

} /* namespace Visitors */
} /* namespace Expressions */
} /* namespace CAS */
} /* namespace DS */
#endif /* NUMEVAL_H_ */
