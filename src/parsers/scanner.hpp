#pragma once

#include <iterator>
#include <string>
#include <utility>
#include <memory>

namespace castle {

class scanner {

public:

    using ptr        = std::shared_ptr<scanner>;
    using iterator_t = std::string::const_iterator;
    using bounds     = std::pair<iterator_t, iterator_t>;

    static bounds make_bounds( iterator_t first,
                               iterator_t second ) {
        return make_pair( first, second );
    }

    virtual ~scanner() {}

    virtual bounds scan( bounds abound ) = 0;

    scanner( scanner const& )            = delete;
    scanner& operator=( scanner const& ) = delete;

protected:

    scanner() {}

};

} // namespace castle
