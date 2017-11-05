#include "parsers.hpp"

#include <stdexcept>

using namespace std;

namespace castle   {
namespace scanners {

scanner::bounds char_str::scan( scanner::bounds bounds ) {

    if( bounds.first == bounds.second )
        return bounds;

    string::const_iterator search_idx = bounds.first;
    string::const_iterator src_idx    = m_scan_str.begin();

    while( src_idx != m_scan_str.end() && search_idx != bounds.second ) {
        if( *search_idx != *src_idx )
            break;
        ++search_idx;
        ++src_idx;
    }
    if( src_idx == m_scan_str.end() ) {
        bounds.second = search_idx;
        return bounds;
    }
    bounds.second = bounds.first;
    return bounds;
}

scanner::bounds not_::scan( scanner::bounds bounds ) {

    if (bounds.first == bounds.second)
        return bounds;

    scanner::bounds curr_bounds = bounds;

    while( curr_bounds.first != curr_bounds.second ) {
        scanner::bounds result = m_repeated->scan( curr_bounds );
        if( result.first != result.second )
            break;
        ++curr_bounds.first;
    }
    bounds.second = curr_bounds.first;
    return bounds;
}

optional_list::optional_list( vector<scanner::ptr> const& ls )
    : m_optional_flags( ls.size(), false ) {
    if (ls.size() == 0 )
        throw invalid_argument( "ls is empty in ..." );
    m_list = ls;
}

optional_list::optional_list( vector<scanner::ptr> const& ls,
                              vector<bool>         const& flag_list ) {
    if( ls.size() == 0 )
        throw invalid_argument("ls is empty in ..." );
    if( flag_list.size() != ls.size() )
        throw invalid_argument("ls.size != flag_list.size in ..." );
    bool all_optional = true;
    for( vector<bool>::const_iterator it = flag_list.begin();
         it != flag_list.end(); ++it )
        all_optional &= *it;
    if( all_optional )
        throw invalid_argument("flag_list all optional in ..." );
    m_list = ls;
    m_optional_flags = flag_list;
}

scanner::bounds optional_list::scan( scanner::bounds bounds ) {

    if( bounds.first == bounds.second )
        return bounds;

    vector<scanner::ptr>::iterator itS = m_list.begin();
    vector<bool>::iterator itB = m_optional_flags.begin();

    scanner::bounds curr_bounds = bounds;

    for( unsigned int i = 0; i < m_list.size(); ++i )
    {
        scanner::ptr cur_scanner = *itS;
        bool optional_flag = *itB;

        scanner::bounds res_bounds = cur_scanner->scan(curr_bounds);
        if( res_bounds.first != res_bounds.second )
            curr_bounds.first = res_bounds.second;
        else if( !optional_flag ) {
            bounds.second = bounds.first;
            return bounds;
        }
        ++itS;
        ++itB;
    }
    bounds.second = curr_bounds.first;
    return bounds;
}

or_list::or_list( vector<scanner::ptr> const& ls ) {
    if( ls.size() == 0 )
        throw invalid_argument("ls.size == 0 in ..." );
    m_list = ls;
}

scanner::bounds or_list::scan( scanner::bounds bounds ) {

    if( bounds.first == bounds.second )
        return bounds;

    vector<scanner::ptr>::iterator itS = m_list.begin();
    scanner::bounds curr_bounds = bounds;

    for( unsigned int i = 0; i < m_list.size(); ++i ) {
        scanner::ptr cur_scanner = *itS;

        scanner::bounds res_bounds = cur_scanner->scan( curr_bounds );
        if( res_bounds.first != res_bounds.second ) {
            curr_bounds.first = res_bounds.second;
            break;
        }
        ++itS;
    }
    bounds.second = curr_bounds.first;
    return bounds;
}

scanner::bounds repeat::scan(scanner::bounds bounds) {

    if( bounds.first == bounds.second )
        return bounds;

    decltype( bounds.first ) index = bounds.first;
    scanner::bounds curr_bounds = scanner::make_bounds( index, bounds.second );

    bool found = false;
    while( curr_bounds.first != curr_bounds.second ) {
        scanner::bounds result = m_repeated->scan( curr_bounds );
        if( result.first == result.second )
            break;
        found = true;
        curr_bounds.first = result.second;
    }
    if( !found ) {
        bounds.second = bounds.first;
        return bounds;
    }
    bounds.second = curr_bounds.first;
    return bounds;
}

} // namespace scanners
} // namespace castle
