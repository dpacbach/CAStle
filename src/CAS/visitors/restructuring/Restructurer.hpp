#pragma once

#include <stack>
#include <stdexcept>
#include "Visitor.hpp"
#include "Builder.hpp"
#include "Templates.hpp"
#include "exprs.hpp"

namespace DS { namespace CAS { namespace Numbers {
    class NumberFactory;
} } }

namespace DS          {
namespace CAS         {
namespace Expressions {
namespace Visitors    {

class Restructurer : public DS::CAS::Expressions::Visitor
{
protected:
    std::vector<ExprConstSP> getChildren(const Expr& exp)
    {
        unsigned int nc = exp.numberOfChildren();
        std::vector<ExprConstSP> children(nc);
        for (unsigned int i = 0; i < nc; i++)
            children[nc-i-1] = getPop(childResults);
        return children;
    }

public:
    Restructurer(std::shared_ptr<Numbers::NumberFactory> _nFactory,
                 std::shared_ptr<Expressions::Builder> _eBuilder)
                : nFactory(_nFactory), eBuilder(_eBuilder), nF(*_nFactory), eB(*_eBuilder) {}
    virtual ~Restructurer() {}

    virtual bool visitAdd(const Add& exp)
    {
        childResults.push(add(exp, getChildren(exp)));
        return true;
    }
    virtual bool visitDivide(const Divide& exp)
    {
        childResults.push(divide(exp, getChildren(exp)));
        return true;
    }
    virtual bool visitFactorial(const Factorial& exp)
    {
        childResults.push(factorial(exp, getChildren(exp)));
        return true;
    }
    virtual bool visitLiteral(const Literal& exp)
    {
        childResults.push(literal(exp, getChildren(exp)));
        return true;
    }
    virtual bool visitModulus(const Modulus& exp)
    {
        childResults.push(modulus(exp, getChildren(exp)));
        return true;
    }
    virtual bool visitMultiply(const Multiply& exp)
    {
        childResults.push(multiply(exp, getChildren(exp)));
        return true;
    }
    virtual bool visitNegate(const Negate& exp)
    {
        childResults.push(negate(exp, getChildren(exp)));
        return true;
    }
    virtual bool visitPower(const Power& exp)
    {
        childResults.push(power(exp, getChildren(exp)));
        return true;
    }
    virtual bool visitSymbol(const Symbol& exp)
    {
        childResults.push(symbol(exp, getChildren(exp)));
        return true;
    }

    virtual void reset(void)
    {
        clearStack(childResults);
    }

    virtual ExprConstSP result(void)
    {
        if (childResults.size() != 1)
            throw std::logic_error("childResults.size() != 1 in Expressions::Visitors::Restructurer::result");
        return getPop(childResults);
    }

protected:
    virtual ExprConstSP add(const Add& exp, const std::vector<ExprConstSP>& children)
    {
        return eBuilder->add(children, exp.getSignVector());
    }
    virtual ExprConstSP divide(const Divide& exp, const std::vector<ExprConstSP>& children)
    {
        return eBuilder->operator()("/",children);
    }
    virtual ExprConstSP factorial(const Factorial& exp, const std::vector<ExprConstSP>& children)
    {
        return eBuilder->operator()("!",children);
    }
    virtual ExprConstSP literal(const Literal& exp, const std::vector<ExprConstSP>& children)
    {
        return eBuilder->literal(exp.getNumber());
    }
    virtual ExprConstSP modulus(const Modulus& exp, const std::vector<ExprConstSP>& children)
    {
        return eBuilder->operator()("%",children);
    }
    virtual ExprConstSP multiply(const Multiply& exp, const std::vector<ExprConstSP>& children)
    {
        return eBuilder->operator()("*",children);
    }
    virtual ExprConstSP negate(const Negate& exp, const std::vector<ExprConstSP>& children)
    {
        return eBuilder->operator()("ng",children);
    }
    virtual ExprConstSP power(const Power& exp, const std::vector<ExprConstSP>& children)
    {
        return eBuilder->operator()("^",children);
    }
    virtual ExprConstSP symbol(const Symbol& exp, const std::vector<ExprConstSP>& children)
    {
        return eBuilder->operator()(exp.getName(),children);
    }

private:
    std::shared_ptr<Numbers::NumberFactory> nFactory;
    std::shared_ptr<Expressions::Builder> eBuilder;
protected:
    Numbers::NumberFactory& nF;
    Expressions::Builder& eB;

    std::stack<ExprConstSP> childResults;
};

} /* namespace Visitors */
} /* namespace Expressions */
} /* namespace CAS */
} /* namespace DS */
