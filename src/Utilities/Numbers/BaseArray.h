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
#include <boost/shared_ptr.hpp>

using namespace std;

namespace DS {
namespace Numbers {

class BaseArray
{
public:
    typedef unsigned int unit_t;
    typedef unsigned long int unit_t_long;

    BaseArray(unsigned int size); // does not initialize
    BaseArray(const BaseArray&);
    ~BaseArray();

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
        const vector<unit_t>& ref = *digits;
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

protected:
    bool finalized;

    boost::shared_ptr<vector<unit_t> > digits;
    int startPadding;
    int startNumbers;
    int end;
};

} /* namespace Numbers */
} /* namespace DS */
#endif /* DIGITARRAY_H_ */
