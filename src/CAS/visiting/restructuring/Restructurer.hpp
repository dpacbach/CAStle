#pragma once

#include <stack>
#include <stdexcept>
#include "Visitor.hpp"
#include "Builder.hpp"
#include "Templates.hpp"
#include "AllBasic.hpp"

namespace DS { namespace CAS { namespace Numbers {
    class NumberFactory;
} } }

namespace DS          {
namespace CAS         {
namespace Expressions {
namespace Visitors    {

class Restructurer : public DS::CAS::Expressions::Visitor
{
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

    virtual Expression::Ptr result(void)
    {
        if (childResults.size() != 1)
            throw std::logic_error("childResults.size() != 1 in Expressions::Visitors::Restructurer::result");
        return getPop(childResults);
    }

protected:
    virtual Expression::Ptr add(const Add& exp, const std::vector<Expression::Ptr>& children)
    {
        return eBuilder->add(children, exp.getSignVector());
    }
    virtual Expression::Ptr divide(const Divide& exp, const std::vector<Expression::Ptr>& children)
    {
        return eBuilder->operator()("/",children);
    }
    virtual Expression::Ptr factorial(const Factorial& exp, const std::vector<Expression::Ptr>& children)
    {
        return eBuilder->operator()("!",children);
    }
    virtual Expression::Ptr literal(const Literal& exp, const std::vector<Expression::Ptr>& children)
    {
        return eBuilder->literal(exp.getNumber());
    }
    virtual Expression::Ptr modulus(const Modulus& exp, const std::vector<Expression::Ptr>& children)
    {
        return eBuilder->operator()("%",children);
    }
    virtual Expression::Ptr multiply(const Multiply& exp, const std::vector<Expression::Ptr>& children)
    {
        return eBuilder->operator()("*",children);
    }
    virtual Expression::Ptr negate(const Negate& exp, const std::vector<Expression::Ptr>& children)
    {
        return eBuilder->operator()("ng",children);
    }
    virtual Expression::Ptr power(const Power& exp, const std::vector<Expression::Ptr>& children)
    {
        return eBuilder->operator()("^",children);
    }
    virtual Expression::Ptr symbol(const Symbol& exp, const std::vector<Expression::Ptr>& children)
    {
        return eBuilder->operator()(exp.getName(),children);
    }

private:
    std::shared_ptr<Numbers::NumberFactory> nFactory;
    std::shared_ptr<Expressions::Builder> eBuilder;
protected:
    Numbers::NumberFactory& nF;
    Expressions::Builder& eB;

    std::stack<Expression::Ptr> childResults;
    std::vector<Expression::Ptr> getChildren(const Expression& exp)
    {
        unsigned int nc = exp.numberOfChildren();
        std::vector<Expression::Ptr> children(nc);
        for (unsigned int i = 0; i < nc; i++)
            children[nc-i-1] = getPop(childResults);
        return children;
    }
};

} /* namespace Visitors */
} /* namespace Expressions */
} /* namespace CAS */
} /* namespace DS */
