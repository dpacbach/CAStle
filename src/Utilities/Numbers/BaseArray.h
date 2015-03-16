#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <cstdint>

#include "../memory/shared_array.hpp"

namespace DS {
namespace Numbers {

//#define OPTIMIZE

#ifdef OPTIMIZE
    #define SPECIALIZE_SIZE
    //#define NO_EXCEPTIONS
    //#define NO_INT_EXCEPTIONS
    //#define NO_FLOAT_EXCEPTIONS
#endif

#ifdef SPECIALIZE_SIZE
const size_t max_specialize_size = 2; // making this bigger doesn't seem to have further effect
#endif

#define UNSAFE_DISABLE_STATIC_ASSERTS

#ifdef NO_EXCEPTIONS
#define NOEXCEPT noexcept
#else
#define NOEXCEPT
#endif

#ifdef SPECIALIZE_SIZE
#    define DIGITS_REF (m_digit_data.digits)
#else
#    define DIGITS_REF digits
#endif

class BaseArray
{

public:
    using unit_t      = uint64_t;
    using unit_t_long = __uint128_t;

    static_assert(sizeof(unit_t_long) == 2*sizeof(unit_t),
                  "Size of long type must be double that of unit type");

    BaseArray(size_t size = 0); // does not initialize
    BaseArray(const BaseArray&);
    ~BaseArray();
    BaseArray(BaseArray&&) = default;

    // should be inlined
    inline void finalize(void) { m_flags.finalized = 1; }
    inline bool isFinalized(void) const { return m_flags.finalized; }

    void output(std::ostream& out) const
    {
        if (size() == 0)
        {
            out << "0";
            return;
        }
        //int i, exp = size()-1;
/*
        const unit_t* ref = &DIGITS_REF[0];

        out << "(";
        for (i = end-1; i >= startNumbers; i--)
            out << ref[i] << "*2^(" << (exp--)*(sizeof(unit_t)*8) << ")+";
        for (; i > startPadding; i--)
            out << 0 << "*2^(" << (exp--)*(sizeof(unit_t)*8) << ")+";
        out << "0)";
        */
    }

    //**********************************************************
    // Always

    // should be inlined
    inline unsigned int size(void) const { return end-startPadding; }
    unit_t operator[] (unsigned int index) const NOEXCEPT;

    //**********************************************************
    // Before Finalization

    void set(unit_t n, unsigned int index) NOEXCEPT;

    //**********************************************************
    // After finalization

    BaseArray& operator= (const BaseArray&);
    BaseArray& operator= (BaseArray&&) = default;

    void cutToSize(unsigned int);
    unsigned int removeTrailingZeros(void);
    unsigned int removeLeadingZeros(void);
    void shiftLeft(unsigned int);
    void shiftRight(unsigned int);

private:

    void release();

#ifdef SPECIALIZE_SIZE
    union digit_data {
        digit_data() {}
        ~digit_data() {}
        shared_array<unit_t> digits;
        unit_t digit[max_specialize_size];
    } m_digit_data;
#else
    shared_array<unit_t> digits;
#endif

    struct flags {
        flags(uint8_t f, uint8_t o) : finalized(f), fewdigits(o) {}
        uint8_t  finalized : 1;
        uint8_t  fewdigits : 1;
        uint8_t  sign      : 1;
        uint16_t padding   : 13;
    } m_flags;
    static_assert(sizeof(m_flags) == 2, "flags structure has unintended size");

    short startPadding;
    short startNumbers;
    short end;
};

// TODO: Should pull this stuff out into a config file
#define UNIT_T_MAX_AS_LONG     ((DS::Numbers::BaseArray::unit_t_long)(((DS::Numbers::BaseArray::unit_t)0)-1))
#define UNIT_T_LARGEST         (((DS::Numbers::BaseArray::unit_t)0)-1)
#define UNIT_T_LONG_BITS_DIV_2 ((size_t)(sizeof(DS::Numbers::BaseArray::unit_t_long)/2*8))
#define UNIT_T_LONG_BITS       ((size_t)(sizeof(DS::Numbers::BaseArray::unit_t_long)*8))
#define UNIT_T_BITS            ((size_t)(sizeof(DS::Numbers::BaseArray::unit_t)*8))

static_assert(UNIT_T_LONG_BITS_DIV_2 == UNIT_T_LONG_BITS / 2, "Error in BaseArray type sizes");
static_assert(UNIT_T_LONG_BITS       == UNIT_T_BITS * 2,      "Error in BaseArray type sizes");

} /* namespace Numbers */
} /* namespace DS */
