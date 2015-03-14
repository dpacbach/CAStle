#ifndef BASEARRAY_H_
#define BASEARRAY_H_

#include <iostream>
#include <vector>
#include <memory>
#include <cstdint>

#include "../memory/shared_array.hpp"

namespace DS {
namespace Numbers {

#define OPTIMIZE

#ifdef OPTIMIZE
    #define SPECIALIZE_SIZE
    #define USE_SHARED_ARRAY
    #define OPTIMIZE_UNIT_T
    #define NO_EXCEPTIONS
    #define NO_INT_EXCEPTIONS
    #define NO_FLOAT_EXCEPTIONS
    #define OPTIMIZE_GET_SET
    #define ENABLE_MOVES
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

#ifdef ENABLE_MOVES
#    define MOVE(a) a;
#else
#    define MOVE(a)
#endif

#ifndef USE_SHARED_ARRAY
#    ifdef SPECIALIZE_SIZE
#        define DIGITS_REF (*(m_digit_data.digits))
#    else
#        define DIGITS_REF (*digits)
#    endif
#else
#    ifdef SPECIALIZE_SIZE
#        define DIGITS_REF (m_digit_data.digits)
#    else
#        define DIGITS_REF digits
#    endif
#endif

class BaseArray
{

public:
#ifdef OPTIMIZE_UNIT_T
    using unit_t      = uint64_t;
    using unit_t_long = __uint128_t;
#else
    using unit_t      = uint32_t;
    using unit_t_long = uint64_t;
#endif
    static_assert(sizeof(unit_t_long) == 2*sizeof(unit_t),
                  "Size of long type must be double that of unit type");

    BaseArray(size_t size = 0); // does not initialize
    BaseArray(const BaseArray&);
    ~BaseArray();
    MOVE(BaseArray(BaseArray&&) = default)

    // should be inlined
    void finalize(void);
    bool isFinalized(void) const;

    void output(std::ostream& out) const
    {
        if (size() == 0)
        {
            out << "0";
            return;
        }
        //int i, exp = size()-1;
/*
#ifndef USE_SHARED_ARRAY
    #ifdef SPECIALIZE_SIZE
        const std::vector<unit_t>& ref = *digits;
    #else
        const std::vector<unit_t>& ref = *digits;
    #endif
#else
        const unit_t* ref = &DIGITS_REF[0];
#endif

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
    unsigned int size(void) const;
#ifdef OPTIMIZE_GET_SET
    unit_t operator[] (unsigned int index) const NOEXCEPT;
#else
    const unit_t& operator[] (unsigned int index) const NOEXCEPT;
#endif

    //**********************************************************
    // Before Finalization

    void set(unit_t n, unsigned int index) NOEXCEPT;

    //**********************************************************
    // After finalization

    BaseArray& operator= (const BaseArray&);
    MOVE(BaseArray& operator= (BaseArray&&) = default)

    void cutToSize(unsigned int);
    unsigned int removeTrailingZeros(void);
    unsigned int removeLeadingZeros(void);
    void shiftLeft(unsigned int);
    void shiftRight(unsigned int);

private:

    void release();

#ifdef SPECIALIZE_SIZE
    #ifdef USE_SHARED_ARRAY
        union digit_data {
            digit_data() {}
            ~digit_data() {}
            shared_array<unit_t> digits;
            unit_t digit[max_specialize_size];
        } m_digit_data;
    #else
        union digit_data {
            digit_data() {}
            ~digit_data() {}
            std::shared_ptr<std::vector<unit_t>> digits;
            unit_t digit[max_specialize_size];
        } m_digit_data;
    #endif
#else
    #ifdef USE_SHARED_ARRAY
        shared_array<unit_t> digits;
    #else
        std::shared_ptr<std::vector<unit_t>> digits;
    #endif
#endif
/*
    struct flags {
        bool finalized : 1,
        bool onedigit  : 1,
        bool sign      : 1
    }
*/
    short finalized;
    short startPadding;
    short startNumbers;
    short end;

    //unsigned char m_digits_size;
    size_t m_digits_size;
    /*
    struct _extra {
        short finalized;
        short startPadding;
        short startNumbers;
        short end;
    } m_extra;
    */
};

// TODO: Should pull this stuff out into a config file
#define UNIT_T_MAX_AS_LONG     ((DS::Numbers::BaseArray::unit_t_long)(((DS::Numbers::BaseArray::unit_t)0)-1))
#define UNIT_T_LARGEST         (((DS::Numbers::BaseArray::unit_t)0)-1)
#define UNIT_T_LONG_BITS_DIV_2 ((size_t)(sizeof(DS::Numbers::BaseArray::unit_t_long)/2*8))
#define UNIT_T_LONG_BITS       ((size_t)(sizeof(DS::Numbers::BaseArray::unit_t_long)*8))
#define UNIT_T_BITS            ((size_t)(sizeof(DS::Numbers::BaseArray::unit_t)*8))

static_assert(UNIT_T_LONG_BITS_DIV_2 == UNIT_T_LONG_BITS / 2, "Error in BaseArray type sizes");
static_assert(UNIT_T_LONG_BITS       == UNIT_T_BITS * 2,      "Error in BaseArray type sizes");
//static_assert(sizeof(BaseArray) <= 16, "BaseArray too big!");

} /* namespace Numbers */
} /* namespace DS */
#endif /* DIGITARRAY_H_ */
