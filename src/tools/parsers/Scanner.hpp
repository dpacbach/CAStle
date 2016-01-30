#pragma once

#include <iterator>
#include <string>
#include <utility>
#include <memory>

using namespace std;

namespace DS {
namespace Tokens {

class Scanner
{
public:
    typedef shared_ptr<Scanner> Ptr;
    typedef string::const_iterator iterator_t;
    typedef pair<iterator_t, iterator_t> bounds;
    static bounds make_bounds(iterator_t _first, iterator_t _second)
    {
        return make_pair(_first, _second);
    }

    virtual ~Scanner() {}

    virtual bounds scan(bounds abound) = 0;

    Scanner(const Scanner&)            = delete;
    Scanner& operator=(const Scanner&) = delete;

protected:
    Scanner() {}
};

} /* namespace Token */
} /* namespace DS */
