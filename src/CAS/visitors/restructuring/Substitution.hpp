#pragma once

#include <string>
#include <map>
#include "Restructurer.hpp"

namespace DS { namespace CAS { namespace Numbers {
    class NumberFactory;
} } }

namespace DS            {
namespace CAS           {
namespace Expressions   {
namespace Visitors      {
namespace Restructurers {

class Substitution: public DS::CAS::Expressions::Visitors::Restructurer
{
public:
    Substitution(std::shared_ptr<Numbers::NumberFactory> _nFactory, std::shared_ptr<Expressions::Builder> _eBuilder,
                 const std::map<std::string,ExprConstSP>& _dictionary) : Restructurer(_nFactory, _eBuilder), dictionary(_dictionary) {}
    virtual ~Substitution() {}

    std::map<std::string, ExprConstSP>& getDictionary(void) { return dictionary; }

protected:
    virtual ExprConstSP symbol(const Symbol& exp, const std::vector<ExprConstSP>& children);
    std::map<std::string, ExprConstSP> dictionary;
};

} /* namespace Restructurers */
} /* namespace Visitors */
} /* namespace Expressions */
} /* namespace CAS */
} /* namespace DS */
