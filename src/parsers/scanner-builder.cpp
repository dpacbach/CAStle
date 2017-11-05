#include "scanner-builder.hpp"
#include "Templates.hpp"
#include "parsers.hpp"

using namespace std;

namespace castle {

void scanner_builder::char_string( string const& s ) {
    push( scanner::ptr( new scanners::char_str( s ) ) );
}

void scanner_builder::notted() {
    push( scanner::ptr( new scanners::not_( pop() ) ) );
}

void scanner_builder::repeat() {
    push( scanner::ptr( new scanners::repeat( pop() ) ) );
}

void scanner_builder::or_list( int count ) {
    vector<scanner::ptr> ls( count );
    for( int i = 0; i < count; ++i )
        ls[count-i-1] = pop();
    push( scanner::ptr( new scanners::or_list( ls ) ) );
}

void scanner_builder::optional_list( int count )
{
    vector<scanner::ptr> ls( count );
    vector<bool> optional_flags( count );
    for( size_t i = 0; i < (size_t)count; ++i ) {
        ls[count-i-1] = pop();
        optional_flags[count-i-1] = pop_flag();
    }
    push( scanner::ptr(
        new scanners::optional_list( ls, optional_flags ) ) );
}

int scanner_builder::stack_size() {
    return m_scanner_stack.size();
}

void scanner_builder::push( scanner::ptr ptr ) {
    m_scanner_stack.push( ptr );
}

scanner::ptr scanner_builder::pop() {
    return getPop( m_scanner_stack );
}

void scanner_builder::clear_stack() {
    while( !m_flag_stack.empty() )
        m_flag_stack.pop();
}

int scanner_builder::flag_stack_size() {
    return m_flag_stack.size();
}

void scanner_builder::push_flag( bool flag ) {
    m_flag_stack.push( flag );
}

bool scanner_builder::pop_flag() {
    return getPop( m_flag_stack );
}

void scanner_builder::space( bool new_line ) {
    if( new_line )
        or_char_string( " \t\n" );
    else
        or_char_string( " \t" );
}

void scanner_builder::digit() {
    or_char_string( "0123456789" );
}

void scanner_builder::alpha() {
    or_char_string( "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ" );
}

void scanner_builder::non_space() {
    space();
    notted();
}

void scanner_builder::spaces( bool new_line ) {
    space( new_line );
    repeat();
}

void scanner_builder::non_spaces() {
    non_space();
    repeat();
}

void scanner_builder::alphas() {
    alpha();
    repeat();
}

void scanner_builder::digits() {
    digit();
    repeat();
}

void scanner_builder::alpha_num_string() {
    alpha();
    digit();
    or_list( 2 );
    repeat();
}

void scanner_builder::non_alpha_num_space() {
    alpha();
    digit();
    space();
    or_list(3);
    notted();
}

void scanner_builder::or_char_string( string const& s ) {
    string temp = " ";
    for( size_t i = 0; i < s.length(); ++i ) {
        temp[0] = s[i];
        char_string( temp );
    }
    or_list( s.length() );
}

void scanner_builder::list( int count ) {
    for( int i = 0; i < count; ++i )
        m_flag_stack.push( false );
    optional_list( count );
}

void scanner_builder::list_spaces( int count, bool new_line ) {
    for( int i = 0; i < count; ++i )
        m_flag_stack.push( false );
    optional_list_spaces( count, new_line );
}

void scanner_builder::optional_list_spaces( int count,
                                            bool new_line ) {
    stack<scanner::ptr> temp_scanners;
    stack<bool> temp_flags;

    for( int i = 0; i < count; ++i ) {
        temp_scanners.push( pop() );
        temp_flags.push( pop_flag() );
    }
    for( int i = 0; i < count; ++i ) {
        push( getPop( temp_scanners ) );
        push_flag( getPop( temp_flags ) );
        if( i < count-1 ) {
            spaces( new_line );
            push_flag( true );
        }
    }
    optional_list( 2*count-1 );
}

void scanner_builder::variable() {
    alpha();
    push_flag( false );
    alpha_num_string();
    push_flag( true );
    optional_list( 2 );
}

void scanner_builder::integer() {
    char_string( "-" );
    push_flag( true );
    digits();
    push_flag( false );
    optional_list( 2 );
}

void scanner_builder::pos_integer() {
    digits();
}

void scanner_builder::pos_float_number() {
    digits();
    push_flag( true );
    char_string( "." );
    push_flag( true );
    digits();
    push_flag( false );
    optional_list( 3 );

    digits();
    push_flag( false );
    char_string( "." );
    push_flag( true );
    optional_list( 2 );

    or_list( 2 );
}

void scanner_builder::float_number() {
    char_string( "-" );
    push_flag( true );
    pos_float_number();
    push_flag( false );
    optional_list( 2 );
}

void scanner_builder::float_scientific() {
    float_number();
    char_string( "e" );
    integer();
    list( 3 );
}

void scanner_builder::pos_float_scientific() {
    pos_float_number();
    char_string( "e" );
    integer();
    list( 3 );
}

void scanner_builder::img_float() {
    float_number();
    char_string( "i" );
    list( 2 );
}

void scanner_builder::img_scientific() {
    float_scientific();
    char_string( "i" );
    list( 2 );
}

void scanner_builder::duplicate() {
    scanner::ptr temp = pop();
    push( temp );
    push( temp );
}

} // namespace castle


