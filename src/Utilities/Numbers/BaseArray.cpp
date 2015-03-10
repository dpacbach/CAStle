#include <stdexcept>
#include "BaseArray.h"

namespace DS {
namespace Numbers {

BaseArray::BaseArray(size_t size)
#ifndef USE_SHARED_ARRAY
    : digits(new vector<unit_t>(size)) // does not initialize
#else
    : digits(size) // does not initialize
#endif
{
#ifdef USE_SHARED_ARRAY
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

#ifdef OPTIMIZE_GET_SET
BaseArray::unit_t BaseArray::operator[] (unsigned int index) const NOEXCEPT
{
    int temp = startPadding + static_cast<int>(index);
    if (temp < startNumbers)
        return 0;
#else
const BaseArray::unit_t& BaseArray::operator[] (unsigned int index) const NOEXCEPT
{
    static const unit_t _dummyZero = 0;
    int temp = startPadding + static_cast<int>(index);
    if (temp < startNumbers)
        return _dummyZero;
#endif
#ifndef NO_EXCEPTIONS
    if (temp >= end)
        throw out_of_range("index out of range in DigitArray::operator[] const");
#endif
    return DIGITS_REF[temp];
}

// **********************************************************
// * Before Finalization

void BaseArray::set(BaseArray::unit_t c, unsigned int index) NOEXCEPT
{
#ifndef NO_EXCEPTIONS
    if (isFinalized())
        throw logic_error("*this is finalized in DigitArray::operator[]");
    if (static_cast<int>(index) >= end)
        throw out_of_range("index out of range in DigitArray::operator[]");
#endif
    DIGITS_REF[(size_t)index] = c;
}

// **********************************************************
// * After finalization

BaseArray& BaseArray::operator= (const BaseArray& src)
{
#ifndef NO_EXCEPTIONS
    // commented out for testing
    //if (!isFinalized())
    //    throw logic_error("*this not finalized in DigitArray::operator=(const DigitArray&)");
    //if (!src.isFinalized())
    //    throw logic_error("src not finalized in DigitArray::operator=(const DigitArray&)");
#endif
    digits = src.digits;
    startPadding = src.startPadding;
    startNumbers = src.startNumbers;
    end = src.end;
    return *this;
}

void BaseArray::cutToSize(unsigned int size)
{
#ifndef NO_EXCEPTIONS
    if (!isFinalized())
        throw logic_error("*this not finalized in DigitArray::cutToSize");
    if (static_cast<int>(size) > (end-startPadding))
        throw invalid_argument("size > (end-startPadding) in DigitArray::cutToSize");
#endif
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
#ifndef NO_EXCEPTIONS
    if (!isFinalized())
        throw logic_error("*this not finalized in DigitArray::removeTrailingZeros");
#endif
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
#ifndef NO_EXCEPTIONS
    if (!isFinalized())
        throw logic_error("*this not finalized in DigitArray::removeLeadingZeros");
#endif
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
#ifndef NO_EXCEPTIONS
    if (!isFinalized())
        throw logic_error("*this not finalized in DigitArray::shiftLeft");
#endif
    startPadding -= static_cast<int>(i);
}

void BaseArray::shiftRight(unsigned int i)
{
#ifndef NO_EXCEPTIONS
    if (!isFinalized())
        throw logic_error("*this not finalized in DigitArray::shiftRight");
#endif
    startPadding += static_cast<int>(i);
    if (startPadding > startNumbers)
        startNumbers = startPadding;
    if (startPadding > end)
        startNumbers = startPadding = end;
}

} /* namespace Numbers */
} /* namespace DS */
