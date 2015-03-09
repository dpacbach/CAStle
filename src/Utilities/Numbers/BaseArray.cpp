#include <stdexcept>
#include "BaseArray.h"

namespace DS {
namespace Numbers {

#ifdef USE_SHARED_PTR
#    define DIGITS_REF (*digits)
#else
#    define DIGITS_REF digits
#endif

BaseArray::BaseArray(size_t size)
#ifdef USE_SHARED_PTR
    : digits(new vector<unit_t>(size)) // does not initialize
#else
    : digits(size) // does not initialize
#endif
{
#ifndef USE_SHARED_PTR
    m_digits_size = size;
#endif
    finalized = false;
    startPadding = 0;
    startNumbers = 0;
    end = size;
}

BaseArray::BaseArray(const BaseArray& src)
{
    // commented out for testing
    //if (!src.isFinalized())
    //    throw logic_error("src not finalized in DigitArray::DigitArray(const DigitArray&)");
    digits = src.digits;

    startPadding = src.startPadding;
    startNumbers = src.startNumbers;
    end = src.end;
    finalized = true;
}

void BaseArray::finalize(void)
{
    finalized = true;
}

bool BaseArray::isFinalized(void) const
{
    return finalized;
}

// **********************************************************
// * Always

unsigned int BaseArray::size(void) const
{
    return static_cast<unsigned int>(end-startPadding);
}

const BaseArray::unit_t& BaseArray::operator[] (unsigned int index) const
{
    static const unit_t _dummyZero = 0;
    int temp = startPadding + static_cast<int>(index);
    if (temp < startNumbers)
        return _dummyZero;
    if (temp >= end)
        throw out_of_range("index out of range in DigitArray::operator[] const");
    return DIGITS_REF[temp];
}

// **********************************************************
// * Before Finalization

void BaseArray::set(BaseArray::unit_t c, unsigned int index)
{
    if (isFinalized())
        throw logic_error("*this is finalized in DigitArray::operator[]");
    if (static_cast<int>(index) >= end)
        throw out_of_range("index out of range in DigitArray::operator[]");
    DIGITS_REF[(size_t)index] = c;
}

// **********************************************************
// * After finalization

BaseArray& BaseArray::operator= (const BaseArray& src)
{
    // commented out for testing
    //if (!isFinalized())
    //    throw logic_error("*this not finalized in DigitArray::operator=(const DigitArray&)");
    //if (!src.isFinalized())
    //    throw logic_error("src not finalized in DigitArray::operator=(const DigitArray&)");
    digits = src.digits;
    startPadding = src.startPadding;
    startNumbers = src.startNumbers;
    end = src.end;
    return *this;
}

void BaseArray::cutToSize(unsigned int size)
{
    if (!isFinalized())
        throw logic_error("*this not finalized in DigitArray::cutToSize");
    if (static_cast<int>(size) > (end-startPadding))
        throw invalid_argument("size > (end-startPadding) in DigitArray::cutToSize");
    end = startPadding+static_cast<int>(size);
    if (end >= startNumbers)
        return;
    startNumbers = end;
    if (end >= 0)
        return;
    startPadding += (-end);
    end = startNumbers = 0;
}

unsigned int BaseArray::removeTrailingZeros(void)
{
    if (!isFinalized())
        throw logic_error("*this not finalized in DigitArray::removeTrailingZeros");
    unsigned int count = 0;

    if (startPadding < startNumbers)
    {
        count += static_cast<unsigned int>(startNumbers-startPadding);
        startPadding = startNumbers;
    }
    while (startPadding < end)
    {
        if (DIGITS_REF[startPadding] != 0)
            break;
        count++;
        startPadding++;
        startNumbers++;
    }
    return count;
}

unsigned int BaseArray::removeLeadingZeros(void)
{
    if (!isFinalized())
        throw logic_error("*this not finalized in DigitArray::removeLeadingZeros");
    unsigned int count = 0;
    while (end > startNumbers)
    {
        if (DIGITS_REF[end-1] != 0)
            break;
        count++;
        end--;
    }
    if (end == startNumbers)
    {
        count += static_cast<unsigned int>(startNumbers-startPadding);
        end = startNumbers = startPadding = 0;
    }
    return count;
}

void BaseArray::shiftLeft(unsigned int i)
{
    if (!isFinalized())
        throw logic_error("*this not finalized in DigitArray::shiftLeft");

    startPadding -= static_cast<int>(i);
}

void BaseArray::shiftRight(unsigned int i)
{
    if (!isFinalized())
        throw logic_error("*this not finalized in DigitArray::shiftRight");

    startPadding += static_cast<int>(i);
    if (startPadding > startNumbers)
        startNumbers = startPadding;
    if (startPadding > end)
        startNumbers = startPadding = end;
}

} /* namespace Numbers */
} /* namespace DS */
