#pragma once

#include <stack>
#include <stdexcept>
#include "NumberProxy.hpp"
#include "Visitor.hpp"
#include "Templates.hpp"

//using namespace std;
//using namespace DS::CAS::Numbers;
//using namespace DS::CAS::Numbers::Proxy;

namespace DS          {
namespace CAS         {
namespace Expressions {
namespace Visitors    {

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

    virtual Numbers::Proxy::NumberP result(void);

protected:
    std::stack<Numbers::Proxy::NumberP> childResults;
};

} /* namespace Visitors */
} /* namespace Expressions */
} /* namespace CAS */
} /* namespace DS */
