#include "macros.hpp"
#include "exprs.hpp"
#include "Visitor.hpp"

#include <stdexcept>

namespace DS          {
namespace CAS         {
namespace Expressions {

Add::Add( std::vector<ExprConstSP> const& exprs,
          std::vector<Sign>        const& _signs ) {
    ASSERT( exprs.size() == _signs.size() );
    ASSERT( exprs.size() > 0 );
    children = exprs;
    signs    = _signs;
}

bool Add::acceptVisitor(Visitor& visitor) const
{
    return visitor.visitAdd(*this);
}

Sign Add::getSignForChild(size_t i) const
{
    ASSERT( i < signs.size() );
    return signs[i];
}

std::vector<Sign> const& Add::getSignVector(void) const
{
    return signs;
}

Expressions::Add::SignedExprVec const& Add::getPairVector(void) const
{
    SignedExprVec res; // reserve?
    for( size_t i = 0; i < children.size(); ++i )
        res.push_back( make_pair( signs[i], children[i] ) );
    return res;
}

bool Divide::acceptVisitor(Visitor& visitor) const
{
    return visitor.visitDivide(*this);
}

bool Factorial::acceptVisitor(Visitor& visitor) const
{
    return visitor.visitFactorial(*this);
}

using namespace DS::CAS::Numbers;
using namespace DS::CAS::Numbers::Proxy;

bool Literal::acceptVisitor(Visitor& visitor) const
{
    return visitor.visitLiteral(*this);
}

bool Modulus::acceptVisitor(Visitor& visitor) const
{
    return visitor.visitModulus(*this);
}

Multiply::Multiply(const std::vector<ExprConstSP>& _children)
{
    if (_children.size() == 0)
        throw std::invalid_argument("_children == 0 in Multiply::Multiply(vector)");
    children = _children;
}

bool Multiply::acceptVisitor(Visitor& visitor) const
{
    return visitor.visitMultiply(*this);
}

bool Negate::acceptVisitor(Visitor& visitor) const
{
    return visitor.visitNegate(*this);
}

bool Power::acceptVisitor(Visitor& visitor) const
{
    return visitor.visitPower(*this);
}

bool Symbol::acceptVisitor(Visitor& visitor) const
{
    return visitor.visitSymbol(*this);
}

const std::string& Symbol::getName(void) const
{
    return name;
}

} /* namespace Expressions */
} /* namespace CAS */
} /* namespace DS */
