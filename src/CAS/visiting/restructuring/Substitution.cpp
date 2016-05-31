#include "Substitution.hpp"
#include "AllBasic.hpp"

namespace DS            {
namespace CAS           {
namespace Expressions   {
namespace Visitors      {
namespace Restructurers {

Expression::Ptr Substitution::symbol(const Symbol& exp, const std::vector<Expression::Ptr>& children)
{
    if (exp.numberOfChildren())
        return Visitors::Restructurer::symbol(exp, children);

    std::map<std::string, Expression::Ptr>::const_iterator it = dictionary.find(exp.getName());

    if (it == dictionary.end())
        return Visitors::Restructurer::symbol(exp, children);

    return it->second;
}

} /* namespace Restructurers */
} /* namespace Visitors */
} /* namespace Expressions */
} /* namespace CAS */
} /* namespace DS */
