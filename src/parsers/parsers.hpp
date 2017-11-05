#pragma once

#include "scanner.hpp"
#include "scanner-builder.hpp"

#include <string>
#include <vector>

namespace castle   {
namespace scanners {

//_______________________________________________________________

class char_str : public scanner {

public:

    char_str( std::string const& s ) : m_scan_str( s    ) {}
    char_str( char        const  c ) : m_scan_str( 1, c ) {}

    virtual scanner::bounds scan( scanner::bounds );

    std::string const& get_string() const { return m_scan_str; }

protected:

    std::string m_scan_str;

};

//_______________________________________________________________

class not_ : public scanner {

public:

    not_( scanner::ptr repeated ) : m_repeated( repeated ) {}

    virtual scanner::bounds scan( scanner::bounds );

protected:

    scanner::ptr m_repeated;

};

//_______________________________________________________________

class optional_list : public scanner {

public:

    optional_list( std::vector<scanner::ptr> const& );
    optional_list( std::vector<scanner::ptr> const&,
                   std::vector<bool> const& );

    virtual scanner::bounds scan( scanner::bounds );

protected:

    std::vector<scanner::ptr> m_list;
    std::vector<bool>         m_optional_flags;

};

//_______________________________________________________________

class or_list : public scanner {

public:

    or_list( std::vector<scanner::ptr> const& );

    virtual scanner::bounds scan( scanner::bounds );

protected:

    std::vector<scanner::ptr> m_list;

};

//_______________________________________________________________

class repeat : public scanner {

public:

    repeat( scanner::ptr repeated ) : m_repeated( repeated ) {}

    virtual scanner::bounds scan( scanner::bounds );

protected:

    scanner::ptr m_repeated;

};

} // namespace scanners
} // namespace castle
