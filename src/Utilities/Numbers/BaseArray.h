#pragma once

#include <iostream>
#include <cstdint>

#include "shared_array.hpp"

namespace DS {
namespace Numbers {

#define OPTIMIZE

#ifdef OPTIMIZE
    #define NO_BA_EXCEPTIONS
    #define NO_INT_EXCEPTIONS
    #define NO_FLOAT_EXCEPTIONS
#endif

#ifdef NO_BA_EXCEPTIONS
    #define NOEXCEPT noexcept
    #define NDEBUG
#else
    #define NOEXCEPT
#endif

#define UNSAFE_DISABLE_STATIC_ASSERTS

#include <cassert>

class BaseArray
{

public:
    ////////////////////////////////////////////////////////////////////////////
    //// Config info
    ////
    using unit_t      = uint64_t;    // If these sizes are changed then it will
    using unit_t_long = __uint128_t; // also be necessary to change the max size
                                     // of the Float.

    // Making this bigger doesn't seem to have further effect
    static constexpr size_t inline_size = 2;

    ////////////////////////////////////////////////////////////////////////////
    //// Construction / Destruction / Copying / Moving
    ////
    BaseArray(size_t size = 0) NOEXCEPT
        : m_indexes(0)
    {
        m_indexes.single_index.end = size;
        if (size > inline_size) {
            new (&m_digit_data.digits_heap) shared_array<unit_t>(size);
            m_digits = &m_digit_data.digits_heap[0];
        }
        else
            m_digits = &m_digit_data.digits_stack[0];
    }

    BaseArray(const BaseArray&) NOEXCEPT;
    // TODO: How does the default know how to move this class?
    //BaseArray(BaseArray&&) = default;
    ~BaseArray() NOEXCEPT { release(); }

    void output(std::ostream& out) const NOEXCEPT;

    ////////////////////////////////////////////////////////////////////////////
    //// Always
    ////
    unit_t operator[] (size_t index) const NOEXCEPT;
    size_t size(void) const NOEXCEPT {
        return m_indexes.single_index.end-m_indexes.single_index.startPadding;
    }

    ////////////////////////////////////////////////////////////////////////////
    //// Before finalization
    ////
    void set(unit_t n, size_t index) NOEXCEPT
    {
        assert(invariants());
        assert(index < (size_t)m_indexes.single_index.end);

        m_digits[index] = n;

        assert(invariants());
    }

    ////////////////////////////////////////////////////////////////////////////
    //// After finalization
    ////
    BaseArray& operator= (const BaseArray&) NOEXCEPT;
    // TODO: how does the default know how to move this class?
    //BaseArray& operator= (BaseArray&&) = default;

    void removeLeadingZeros(void)  NOEXCEPT;
    void cutToSize(size_t)         NOEXCEPT;
    void shiftRight(size_t i)      NOEXCEPT;
    void shiftLeft(size_t i) NOEXCEPT
    {
        m_indexes.single_index.startPadding -= (short)i;
        assert(invariants());
    }

private:

    bool has_few_digits() const NOEXCEPT { return m_digits == m_digit_data.digits_stack; }

    // Destroy shared_array if it's being used
    void release() NOEXCEPT
    {
        if (!has_few_digits())
            m_digit_data.digits_heap.~shared_array<unit_t>();
    }

    bool invariants() const NOEXCEPT;

    ////////////////////////////////////////////////////////////////////////////
    //// Indexing data
    ////
    union indexes_union
    {
        indexes_union(uint64_t _all_indexes)    : all_indexes(_all_indexes)    {}
        indexes_union(const indexes_union& src) : all_indexes(src.all_indexes) {}
        struct indexes
        {
            short startPadding;
            short startNumbers;
            short end;
            short padding;
        }
        single_index;
        uint64_t all_indexes; 
    }
    m_indexes;

    ////////////////////////////////////////////////////////////////////////////
    //// Digit data
    ////
    union digit_data
    {
        digit_data() {}
        ~digit_data() {}
        shared_array<unit_t> digits_heap;
        unit_t digits_stack[inline_size];
    }
    m_digit_data;

    // Holds a pointer to the start of the digit data
    unit_t* m_digits;

    ////////////////////////////////////////////////////////////////////////////
    //// Assertions about sizes
    ////
    static_assert(sizeof(m_indexes) == 8,
                  "flags structure has unintended size");
    static_assert(sizeof(unit_t_long) == 2*sizeof(unit_t),
                  "Size of long type must be double that of unit type");
};

// TODO: Should pull this stuff out into a config file
#define UNIT_T_MAX_AS_LONG     ((DS::Numbers::BaseArray::unit_t_long)(((DS::Numbers::BaseArray::unit_t)0)-1))
#define UNIT_T_LARGEST         (((DS::Numbers::BaseArray::unit_t)0)-1)
#define UNIT_T_LONG_BITS_DIV_2 ((size_t)(sizeof(DS::Numbers::BaseArray::unit_t_long)/2*8))
#define UNIT_T_LONG_BITS       ((size_t)(sizeof(DS::Numbers::BaseArray::unit_t_long)*8))
#define UNIT_T_BITS            ((size_t)(sizeof(DS::Numbers::BaseArray::unit_t)*8))

static_assert(UNIT_T_LONG_BITS_DIV_2 == UNIT_T_LONG_BITS / 2,
              "Error in BaseArray type sizes");
static_assert(UNIT_T_LONG_BITS       == UNIT_T_BITS * 2,
              "Error in BaseArray type sizes");
static_assert(sizeof(BaseArray) <= 24 + BaseArray::inline_size*sizeof(BaseArray::unit_t),
              "BaseArray structure has unintended size");

} /* namespace Numbers */
} /* namespace DS */
