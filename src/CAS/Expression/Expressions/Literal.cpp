/*
 * ExpressionLiteral.cpp
 *
 *  Created on: Jan 11, 2013
 *      Author: davidsicilia
 */

#include "Literal.h"
#include "../../ExpressionVisiting/Visitor.h"

using namespace DS::CAS::Numbers;
using namespace DS::CAS::Numbers::Proxy;

namespace DS {
namespace CAS {
namespace Expressions {

bool Literal::acceptVisitor(Visitor& visitor) const
{
    return visitor.visitLiteral(*this);
}

} /* namespace Expression */
} /* namespace CAS */
} /* namespace DS */
