#pragma once

#include <stack>
#include <memory>
#include "Visitor.hpp"
#include "NumberFormatter.hpp"
#include "Templates.hpp"

namespace DS          {
namespace CAS         {
namespace Expressions {
namespace Visitors    {

template <typename T>
class Renderer : public DS::CAS::Expressions::Visitor
{
public:
    Renderer(std::shared_ptr<Numbers::NumberFormatter>);
    virtual ~Renderer() {}

    virtual void reset(void)
    {
        clearStack(childResults);
    }
    virtual T result(void)
    {
        if (childResults.size() != 1)
            throw logic_error("childResults.size() != 1 in Expressions::Visitors::Renderer::result");
        return getPop(childResults);
    }

protected:
    std::stack<T> childResults;
    std::shared_ptr<Numbers::NumberFormatter> formatter;
};

template<typename T>
Renderer<T>::Renderer(std::shared_ptr<Numbers::NumberFormatter> _formatter)
{
    if (!_formatter)
        throw invalid_argument("aFormatter == 0 in DS::CAS::Expressions::Visitors::Render::Renderer::Renderer()");
    formatter = _formatter;
}

} /* namespace Visitors */
} /* namespace Expressions */
} /* namespace CAS */
} /* namespace DS */
