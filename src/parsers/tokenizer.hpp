#pragma once

#include "token.hpp"
#include "scanner.hpp"

#include <string>
#include <vector>

using namespace std;

namespace castle {

class tokenizer {

public:

    tokenizer()                              = default;
    tokenizer( tokenizer const& )            = delete;
    tokenizer& operator=( tokenizer const& ) = delete;

    bool tokenize_priority( string const& source,
                            vector<scanner::ptr> const& scanners,
                            vector<token>& destination );

    bool tokenize_ordered( string const&               source,
                           vector<scanner::ptr> const& scanners,
                           vector<bool> const&         optionalFlags,
                           vector<token>&              destination,
                           bool                        dummies = false );

    string::const_iterator stop_location() const {
        return m_stop_loc;
    }

protected:

    std::string::const_iterator m_stop_loc;

};

} // namespace castle
