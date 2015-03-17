#include <stdexcept>
#include <algorithm>

#include "BaseArray.h"

namespace DS {
namespace Numbers {

BaseArray::BaseArray(size_t size)
    : m_flags(0, (uint8_t)(size <= max_specialize_size))
    , startPadding(0)
    , startNumbers(0)
    , end(size)
{
    if (size > max_specialize_size)
        new (&m_digit_data.digits) shared_array<unit_t>(size);
}

void BaseArray::release()
{
    if (!m_flags.fewdigits)
        m_digit_data.digits.~shared_array<unit_t>();
}

BaseArray::~BaseArray()
{
    release();
}

BaseArray::BaseArray(const BaseArray& src)
    : m_flags(src.m_flags)
    , startPadding(src.startPadding)
    , startNumbers(src.startNumbers)
    , end(src.end)
{
#ifndef NO_EXCEPTIONS
    if (!src.isFinalized())
        throw std::logic_error("src not finalized in DigitArray::DigitArray(const DigitArray&)");
#endif
    if (!m_flags.fewdigits)
        new (&m_digit_data.digits) shared_array<unit_t>(src.m_digit_data.digits);
    else
        std::copy(src.m_digit_data.digit, src.m_digit_data.digit+max_specialize_size, m_digit_data.digit); 
}

// **********************************************************
// * Always

BaseArray::unit_t BaseArray::operator[] (unsigned int index) const NOEXCEPT
{
    int temp = startPadding + static_cast<int>(index);
    if (temp < startNumbers)
        return 0;
#ifndef NO_EXCEPTIONS
    if (temp >= end)
        throw std::out_of_range("index out of range in DigitArray::operator[] const");
#endif
    if (!m_flags.fewdigits)
        return m_digit_data.digits[temp];
    else
        return m_digit_data.digit[temp];
}

// **********************************************************
// * Before Finalization

void BaseArray::set(BaseArray::unit_t c, unsigned int index) NOEXCEPT
{
#ifndef NO_EXCEPTIONS
    if (isFinalized())
        throw std::logic_error("*this is finalized in DigitArray::operator[]");
    if (static_cast<int>(index) >= end)
        throw std::out_of_range("index out of range in DigitArray::operator[]");
#endif
    if (!m_flags.fewdigits)
        m_digit_data.digits[(size_t)index] = c;
    else
        m_digit_data.digit[(size_t)index] = c; // index needs to be bounds checked
}

// **********************************************************
// * After finalization

BaseArray& BaseArray::operator= (const BaseArray& src)
{
    if (this == &src)
        return *this;
#ifndef NO_EXCEPTIONS
    if (!isFinalized())
        throw std::logic_error("*this not finalized in DigitArray::operator=(const DigitArray&)");
    if (!src.isFinalized())
        throw std::logic_error("src not finalized in DigitArray::operator=(const DigitArray&)");
#endif
    release();
    if (!src.m_flags.fewdigits)
        new (&m_digit_data.digits) shared_array<unit_t>(src.m_digit_data.digits);
    else
        std::copy(src.m_digit_data.digit, src.m_digit_data.digit+max_specialize_size, m_digit_data.digit); 
    startPadding  = src.startPadding;
    startNumbers  = src.startNumbers;
    end           = src.end;
    m_flags       = src.m_flags;
    return *this;
}

void BaseArray::cutToSize(unsigned int size)
{
#ifndef NO_EXCEPTIONS
    if (!isFinalized())
        throw std::logic_error("*this not finalized in DigitArray::cutToSize");
    if (static_cast<int>(size) > (end-startPadding))
        throw std::invalid_argument("size > (end-startPadding) in DigitArray::cutToSize");
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
        throw std::logic_error("*this not finalized in DigitArray::removeTrailingZeros");
#endif
    unsigned int count = 0;

    if (startPadding < startNumbers)
    {
        count += static_cast<unsigned int>(startNumbers-startPadding);
        startPadding = startNumbers;
    }
    while (startPadding < end)
    {
        if (!m_flags.fewdigits) {
            if (m_digit_data.digits[startPadding] != 0)
                break;
        }
        else {
            if (m_digit_data.digit[startPadding] != 0)
                break;
        }
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
        throw std::logic_error("*this not finalized in DigitArray::removeLeadingZeros");
#endif
    unsigned int count = 0;
    while (end > startNumbers)
    {
        if (!m_flags.fewdigits) {
            if (m_digit_data.digits[end-1] != 0)
                break;
        }
        else {
            if (m_digit_data.digit[end-1] != 0)
                break;
        }
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
        throw std::logic_error("*this not finalized in DigitArray::shiftLeft");
#endif
    startPadding -= static_cast<int>(i);
}

void BaseArray::shiftRight(unsigned int i)
{
#ifndef NO_EXCEPTIONS
    if (!isFinalized())
        throw std::logic_error("*this not finalized in DigitArray::shiftRight");
#endif
    startPadding += static_cast<int>(i);
    if (startPadding > startNumbers)
        startNumbers = startPadding;
    if (startPadding > end)
        startNumbers = startPadding = end;
}

} /* namespace Numbers */
} /* namespace DS */
