/*
 * DigitArray.h
 *
 *  Created on: Feb 20, 2013
 *      Author: davidsicilia
 */

#ifndef BASEARRAY_H_
#define BASEARRAY_H_

#include <iostream>
#include <vector>
#include <memory>

#include "../memory/shared_array.hpp"

using namespace std;

namespace DS {
namespace Numbers {

#define USE_SHARED_PTR

class BaseArray
{
public:
    typedef unsigned int unit_t;
    typedef unsigned long int unit_t_long;
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
            out << ref[i] << "*2^(" << (exp--)*32 << ")+";
        for (; i > startPadding; i--)
            out << 0 << "*2^(" << (exp--)*32 << ")+";
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

} /* namespace Numbers */
} /* namespace DS */
#endif /* DIGITARRAY_H_ */
