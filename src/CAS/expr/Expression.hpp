#pragma once

#include "macros.hpp"

#include <memory>
#include <vector>

namespace DS          {
namespace CAS         {
namespace Expressions {

enum class Sign { p = true, n = false };

enum class ID {
    add,      divide, factorial, literal, modulus,
    multiply, negate, power,     symbol
};

class Visitor;

DECLARE_SHARED( Expr )

class Expr {

public:
    Expr();
    Expr(std::vector<ExprConstSP> children) : children( children ) {}
    virtual ~Expr();

    Expr(Expr const&)                   = delete;
    Expr const& operator= (Expr const&) = delete;

    virtual ID id(void) const = 0;

    size_t numberOfChildren(void) const { return children.size(); }

    ExprConstSP getChild(size_t i) const {
        ASSERT( i < children.size() );
        return children[i];
    }

    virtual bool acceptVisitor(Visitor&) const = 0;

    std::vector<ExprConstSP> const& getChildVector() const {
        return children;
    }

    static int numberOfExpressions;

protected:
    std::vector<ExprConstSP> children;
};

} } }
