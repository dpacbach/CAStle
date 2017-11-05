#include "tokenizer.hpp"

#include <stdexcept>

using namespace std;

namespace castle {

bool tokenizer::tokenize_priority( string const&               source,
                                   vector<scanner::ptr> const& scanners,
                                   vector<token>&              destination )
{
    if( scanners.empty() )
        return true;
    scanner::bounds current_bounds =
        scanner::make_bounds( source.begin(), source.end() );
    m_stop_loc = current_bounds.first;

    while( current_bounds.first != current_bounds.second ) {
        int id = 0;
        vector<scanner::ptr>::const_iterator it;
        for( it = scanners.begin(); it != scanners.end(); ++it, ++id ) {
            scanner::bounds resultBounds = (*it)->scan( current_bounds );
            if( resultBounds.first == resultBounds.second )
                continue;
            else {
                string match( resultBounds.first, resultBounds.second );
                destination.push_back( token( match, id ) );
                current_bounds.first = resultBounds.second;
                m_stop_loc = current_bounds.first;
                break;
            }
        }
        if( it == scanners.end() )
            return false;
    }
    return true;
}

bool tokenizer::tokenize_ordered( string const&               source,
                                  vector<scanner::ptr> const& scanners,
                                  vector<bool> const&         optional_flags,
                                  vector<token>&              destination,
                                  bool                        dummies )
{
    if( scanners.empty() ) {
        destination.clear();
        return true;
    }
    if( scanners.size() != optional_flags.size() ) {
        destination.clear();
        throw invalid_argument( "optional_flags.size() != scanners.size() "
                                "in tokenizer::tokenizeOrdered" );
    }

    scanner::bounds current_bounds =
        scanner::make_bounds( source.begin(), source.end() );
    m_stop_loc = current_bounds.first;
    int id = 0;
    vector<scanner::ptr>::const_iterator it;
    vector<bool>::const_iterator bIt = optional_flags.begin();
    for( it = scanners.begin(); it != scanners.end(); ++it, ++id, ++bIt ) {
        scanner::bounds resultBounds = (*it)->scan( current_bounds );
        if( resultBounds.first == resultBounds.second ) {
            if( *bIt ) {
                if( dummies )
                    destination.push_back( token( "", id ) );
                continue;
            }
            else
                return false;
        } else {
            string match( resultBounds.first, resultBounds.second );
            destination.push_back( token( match, id ) );
            current_bounds.first = resultBounds.second;
            m_stop_loc = current_bounds.first;
        }
    }
    if( current_bounds.first != current_bounds.second )
        return false;
    return true;
}

} // namespace castle
