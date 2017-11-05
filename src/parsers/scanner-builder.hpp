#pragma once

#include "scanner.hpp"

#include <string>
#include <stack>

namespace castle {

class scanner_builder
{
public:
    scanner_builder()                                    = default;
    scanner_builder( scanner_builder const& )            = delete;
    scanner_builder& operator=( scanner_builder const& ) = delete;

    ~scanner_builder() {}

    void push( scanner::ptr );
    scanner::ptr pop();

    void clear_stack();
    int  stack_size();

    void clear_flag_stack();
    int  flag_stack_size();
    void push_flag( bool );
    bool pop_flag();

    void char_string( std::string const& );
    void notted();
    void repeat();
    void or_list( int );
    void optional_list( int );

    void space( bool include_new_line = true );
    void digit();
    void alpha();
    void alphas();
    void digits();

    void non_space();
    void spaces( bool include_new_line = true );
    void non_spaces();
    void alpha_num_string();
    void non_alpha_num_space();
    void or_char_string( std::string const& );

    void list( int );
    void list_spaces( int, bool include_new_line = true );
    void optional_list_spaces( int, bool include_new_line = true );

    void variable();

    void integer();
    void pos_integer();
    void float_number();
    void pos_float_number();
    void float_scientific();
    void pos_float_scientific();
    void img_float();
    void img_scientific();

    void duplicate();

protected:
    std::stack<scanner::ptr> m_scanner_stack;
    std::stack<bool>         m_flag_stack;
};

} // namespace castle
