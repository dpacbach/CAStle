/*
 * Scanner.h
 *
 *  Created on: Feb 8, 2013
 *      Author: davidsicilia
 */

#ifndef TOKENSCANNER_H_
#define TOKENSCANNER_H_

#include <iterator>
#include <string>
#include <utility>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

using namespace std;

namespace DS {
namespace Tokens {

class Scanner : private boost::noncopyable
{
public:
    typedef boost::shared_ptr<Scanner> Ptr;
    typedef string::const_iterator iterator_t;
    typedef pair<iterator_t, iterator_t> bounds;
    static bounds make_bounds(iterator_t _first, iterator_t _second)
    {
        return make_pair(_first, _second);
    }

    virtual ~Scanner() {}

    virtual bounds scan(bounds abound) = 0;

protected:
    Scanner() {}
};

} /* namespace Token */
} /* namespace DS */
#endif /* SCANNER_H_ */
