#include "Expression.hpp"

namespace DS          { 
namespace CAS         {
namespace Expressions {

int Expr::numberOfExpressions(0);

Expr::Expr()  { numberOfExpressions++; }
Expr::~Expr() { numberOfExpressions--; }

} } }
