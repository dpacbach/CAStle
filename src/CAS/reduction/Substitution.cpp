#include "Substitution.hpp"
#include "exprs.hpp"

namespace DS            {
namespace CAS           {
namespace Expressions   {
namespace Visitors      {
namespace Restructurers {

ExprConstSP Substitution::symbol(const Symbol& exp, const std::vector<ExprConstSP>& children)
{
    if (exp.numberOfChildren())
        return Visitors::Restructurer::symbol(exp, children);

    std::map<std::string, ExprConstSP>::const_iterator it = dictionary.find(exp.getName());

    if (it == dictionary.end())
        return Visitors::Restructurer::symbol(exp, children);

    return it->second;
}

} /* namespace Restructurers */
} /* namespace Visitors */
} /* namespace Expressions */
} /* namespace CAS */
} /* namespace DS */
