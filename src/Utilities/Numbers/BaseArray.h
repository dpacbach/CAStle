#ifndef BASEARRAY_H_
#define BASEARRAY_H_

#include <iostream>
#include <vector>
#include <memory>
#include <cstdint>

#include "../memory/shared_array.hpp"

using namespace std;

namespace DS {
namespace Numbers {

//#define USE_SHARED_PTR

class BaseArray
{
public:
    // TODO: put noexcept on most methods here after removing
    // the finalization check

    typedef uint64_t    unit_t;
    typedef __uint128_t unit_t_long;
    //typedef uint32_t  unit_t;
    //typedef uint64_t  unit_t_long;

    static_assert(sizeof(unit_t_long) == 2*sizeof(unit_t),
                  "Size of long type must be double that of unit type");

    BaseArray(size_t size = 0); // does not initialize
    BaseArray(const BaseArray&);
    ~BaseArray() = default;

    void finalize(void);
    bool isFinalized(void) const;

    void output(ostream& out) const
    {
        if (size() == 0)
        {
            out << "0";
            return;
        }
        int i, exp = size()-1;

#ifdef USE_SHARED_PTR
        const vector<unit_t>& ref = *digits;
#else
        const unit_t* ref = &digits[0];
#endif

        out << "(";
        for (i = end-1; i >= startNumbers; i--)
            out << ref[i] << "*2^(" << (exp--)*(sizeof(unit_t)*8) << ")+";
        for (; i > startPadding; i--)
            out << 0 << "*2^(" << (exp--)*(sizeof(unit_t)*8) << ")+";
        out << "0)";
    }

    //**********************************************************
    // Always

    unsigned int size(void) const;
    const unit_t& operator[] (unsigned int index) const;

    //**********************************************************
    // Before Finalization

    //void set(char c, unsigned int index);
    void set(unit_t n, unsigned int index);

    //**********************************************************
    // After finalization

    BaseArray& operator= (const BaseArray&);

    void cutToSize(unsigned int);
    unsigned int removeTrailingZeros(void);
    unsigned int removeLeadingZeros(void);
    void shiftLeft(unsigned int);
    void shiftRight(unsigned int);

private:
    bool finalized;
#ifdef USE_SHARED_PTR
    std::shared_ptr<vector<unit_t> > digits;
#else
    size_t m_digits_size;
    shared_array<unit_t> digits;
#endif
    int startPadding;
    int startNumbers;
    int end;
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
#endif /* DIGITARRAY_H_ */
