#pragma once

#include <string>

namespace castle {

class token {

public:

    token( std::string const& token_str, int const id )
        : m_token_str( token_str ), m_id( id ) { }

    token( token const& token )
        : m_token_str( token.m_token_str ), m_id( token.m_id ) { }

    token& operator=( token const& token ) {
        m_token_str = token.m_token_str;
        m_id        = token.m_id;
        return *this;
    }

    std::string const& string() const { return m_token_str; }
    int                id()     const { return m_id;        }

protected:

    std::string m_token_str;
    int         m_id;

};

} // namespace castle
