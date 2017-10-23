#pragma once

#include <vector>
#include "Restructurer.hpp"

namespace DS { namespace CAS { namespace Numbers {
    class NumberFactory;
} } }

namespace DS            {
namespace CAS           {
namespace Expressions   {
namespace Visitors      {
namespace Restructurers {

class Composite : public DS::CAS::Expressions::Visitors::Restructurer
{
    Composite(std::shared_ptr<Numbers::NumberFactory> _nFactory,
              std::shared_ptr<Expressions::Builder> _eBuilder) : Restructurer(_nFactory, _eBuilder) {}

    virtual bool visitExpression(ExprConstSP exp);

    void addChildToEnd(std::shared_ptr<Restructurer> child)
    {
        children.push_back(child);
    }

protected:
    std::vector<std::shared_ptr<Restructurer> > children;
};

} /* namespace Restructurers */
} /* namespace Visitors */
} /* namespace Expressions */
} /* namespace CAS */
} /* namespace DS */
