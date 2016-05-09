/*
 * Renderer.h
 *
 *  Created on: Jan 22, 2013
 *      Author: davidsicilia
 */

#ifndef RENDERER_H_
#define RENDERER_H_

#include <stack>
#include <boost/shared_ptr.hpp>
#include "../Visitor.h"
#include "../../Number/Numbers.h"
#include "../../../Utilities/Templates.h"

namespace DS {
namespace CAS {
namespace Expressions {
namespace Visitors {

template <typename T>
class Renderer : public DS::CAS::Expressions::Visitor
{
public:
    Renderer(boost::shared_ptr<Numbers::NumberFormatter>);
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
    boost::shared_ptr<Numbers::NumberFormatter> formatter;
};

template<typename T>
Renderer<T>::Renderer(boost::shared_ptr<Numbers::NumberFormatter> _formatter)
{
    if (!_formatter)
        throw invalid_argument("aFormatter == 0 in DS::CAS::Expressions::Visitors::Render::Renderer::Renderer()");
    formatter = _formatter;
}

} /* namespace Visitors */
} /* namespace Expressions */
} /* namespace CAS */
} /* namespace DS */
#endif /* RENDERER_H_ */
