#pragma once

#include <stdexcept>
#include <stack>
#include <vector>
#include <string>
#include <memory>
#include "Renderer.hpp"
#include "Templates.hpp"

namespace DS          {
namespace CAS         {
namespace Expressions {
namespace Visitors    {
namespace Render      {

class ASCIITree : public Renderer<vector<string> >
{
public:
    ASCIITree(std::shared_ptr<Numbers::NumberFormatter> _formatter) : Renderer<vector<string> >(_formatter) {}
    virtual ~ASCIITree() {}

    virtual Visitor* create(void) const;
    virtual Visitor* clone(void)  const;
    virtual void      reset(void);

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
    bool handleNode(const string&, const Expression&);
};

} /* namespace Render */
} /* namespace Visitors */
} /* namespace Expressions */
} /* namespace CAS */
} /* namespace DS */
