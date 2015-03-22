#include <stdexcept>
#include <algorithm>
#include <cassert>

#include "BaseArray.h"

#ifdef NO_BA_EXCEPTIONS
#define NDEBUG
#endif

namespace DS {
namespace Numbers {

BaseArray::BaseArray(size_t size) NOEXCEPT
    : m_flags(0, (uint8_t)(size <= inline_size))
    , startPadding(0)
    , startNumbers(0)
    , end(size)
{
    if (size > inline_size)
        new (&m_digit_data.digits) shared_array<unit_t>(size);
}

void BaseArray::release() NOEXCEPT
{
    if (!m_flags.fewdigits)
        m_digit_data.digits.~shared_array<unit_t>();
}

BaseArray::~BaseArray() NOEXCEPT
{
    release();
}

BaseArray::BaseArray(const BaseArray& src) NOEXCEPT
    : m_flags(src.m_flags)
    , startPadding(src.startPadding)
    , startNumbers(src.startNumbers)
    , end(src.end)
{
    assert(src.isFinalized());
    if (!m_flags.fewdigits)
        new (&m_digit_data.digits)
             shared_array<unit_t>(src.m_digit_data.digits);
    else
        std::copy(src.m_digit_data.digit, src.m_digit_data.digit+inline_size,
                  m_digit_data.digit); 
}

// **********************************************************
// * Always

BaseArray::unit_t BaseArray::operator[] (size_t index) const NOEXCEPT
{
    int temp = startPadding + static_cast<int>(index);
    if (temp < startNumbers)
        return 0;

    assert(temp < end);

    if (!m_flags.fewdigits)
        return m_digit_data.digits[temp];
    else
        return m_digit_data.digit[temp];
}

// **********************************************************
// * Before Finalization

void BaseArray::set(BaseArray::unit_t c, unsigned int index) NOEXCEPT
{
    assert(!isFinalized());
    assert(static_cast<int>(index) < end);

    if (!m_flags.fewdigits)
        m_digit_data.digits[(size_t)index] = c;
    else
        // index needs to be bounds checked
        m_digit_data.digit[(size_t)index] = c;
}

// **********************************************************
// * After finalization

BaseArray& BaseArray::operator= (const BaseArray& src) NOEXCEPT
{
    if (this == &src)
        return *this;

    assert(isFinalized());
    assert(src.isFinalized());

    release();
    if (!src.m_flags.fewdigits)
        new (&m_digit_data.digits)
            shared_array<unit_t>(src.m_digit_data.digits);
    else
        std::copy(src.m_digit_data.digit, src.m_digit_data.digit+inline_size,
                  m_digit_data.digit); 
    startPadding  = src.startPadding;
    startNumbers  = src.startNumbers;
    end           = src.end;
    m_flags       = src.m_flags;
    return *this;
}

void BaseArray::cutToSize(unsigned int size) NOEXCEPT
{
    assert(isFinalized());
    assert(static_cast<int>(size) <= (end-startPadding));

    end = startPadding+static_cast<int>(size);
    if (end >= startNumbers)
        return;
    startNumbers = end;
    if (end >= 0)
        return;
    startPadding += (-end);
    end = startNumbers = 0;
}

size_t BaseArray::removeTrailingZeros(void) NOEXCEPT
{
    assert(isFinalized());

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

size_t BaseArray::removeLeadingZeros(void) NOEXCEPT
{
    assert(isFinalized());

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

void BaseArray::shiftLeft(unsigned int i) NOEXCEPT
{
    assert(isFinalized());

    startPadding -= static_cast<int>(i);
}

void BaseArray::shiftRight(unsigned int i) NOEXCEPT
{
    assert(isFinalized());

    startPadding += static_cast<int>(i);
    if (startPadding > startNumbers)
        startNumbers = startPadding;
    if (startPadding > end)
        startNumbers = startPadding = end;
}

void BaseArray::output(std::ostream& out) const NOEXCEPT
{
    if (size() == 0)
    {
        out << "0";
        return;
    }
    int i, exp = size()-1;

    const unit_t* ref;
    if (!m_flags.fewdigits)
        ref = &m_digit_data.digits[0];
    else
        ref = &m_digit_data.digit[0];

    out << "(";
    for (i = end-1; i >= startNumbers; i--)
        out << ref[i] << "*2^(" << (exp--)*(sizeof(unit_t)*8) << ")+";
    for (; i > startPadding; i--)
        out << 0 << "*2^(" << (exp--)*(sizeof(unit_t)*8) << ")+";
    out << "0)";
}

} /* namespace Numbers */
} /* namespace DS */
