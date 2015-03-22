#pragma once

#include <iostream>
#include <cstdint>

#include "shared_array.hpp"

namespace DS {
namespace Numbers {

#define OPTIMIZE

//#define NO_BA_EXCEPTIONS

#ifdef OPTIMIZE
    #define NO_BA_EXCEPTIONS
    #define NO_INT_EXCEPTIONS
    #define NO_FLOAT_EXCEPTIONS
#endif

#ifdef NO_BA_EXCEPTIONS
    #define NOEXCEPT noexcept
#else
    #define NOEXCEPT
#endif

#define UNSAFE_DISABLE_STATIC_ASSERTS

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
        : m_flags(0, (uint8_t)(size <= inline_size))
        , startPadding(0)
        , startNumbers(0)
        , end(size)
    {
        if (size > inline_size)
            new (&m_digit_data.digits) shared_array<unit_t>(size);
        //assert(invariants());
    }

    BaseArray(const BaseArray&) NOEXCEPT;
    BaseArray(BaseArray&&) = default;
    ~BaseArray() NOEXCEPT { release(); }

    void output(std::ostream& out) const NOEXCEPT;

    ////////////////////////////////////////////////////////////////////////////
    //// Always
    ////
    unit_t operator[] (size_t index) const NOEXCEPT;
    inline size_t size(void) const       NOEXCEPT { return end-startPadding; }
    inline void finalize(void)           NOEXCEPT { m_flags.finalized = 1; }
    inline bool isFinalized(void) const  NOEXCEPT { return m_flags.finalized; }

    ////////////////////////////////////////////////////////////////////////////
    //// Before finalization
    ////
    void set(unit_t n, size_t index) NOEXCEPT;

    ////////////////////////////////////////////////////////////////////////////
    //// After finalization
    ////
    BaseArray& operator= (const BaseArray&) NOEXCEPT;
    BaseArray& operator= (BaseArray&&) = default;

    void cutToSize(size_t)         NOEXCEPT;
    void shiftLeft(size_t)         NOEXCEPT;
    void shiftRight(size_t)        NOEXCEPT;
    void removeLeadingZeros(void)  NOEXCEPT;

private:

    // Destroy shared_array if it's being used
    inline void release() NOEXCEPT {
        if (!m_flags.fewdigits)
            m_digit_data.digits.~shared_array<unit_t>();
    }

    bool invariants() const NOEXCEPT;

    ////////////////////////////////////////////////////////////////////////////
    //// Non-Digit data
    ////
    struct flags
    {
        flags(uint8_t f, uint8_t o) : finalized(f), fewdigits(o) {}
        uint8_t  finalized : 1;
        uint8_t  fewdigits : 1;
        uint8_t  sign      : 1;
        uint16_t padding   : 13;
    }
    m_flags;
    
    short startPadding;
    short startNumbers;
    short end;

    ////////////////////////////////////////////////////////////////////////////
    //// Digit data
    ////
    union digit_data
    {
        digit_data() {}
        ~digit_data() {}
        shared_array<unit_t> digits;
        unit_t digit[inline_size];
    }
    m_digit_data;

    ////////////////////////////////////////////////////////////////////////////
    //// Assertions about sizes
    ////
    static_assert(sizeof(m_flags) == 2,
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
static_assert(sizeof(BaseArray) == 8 + BaseArray::inline_size*sizeof(BaseArray::unit_t),
              "BaseArray structure has unintended size");

} /* namespace Numbers */
} /* namespace DS */
