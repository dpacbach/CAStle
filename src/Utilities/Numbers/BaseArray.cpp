////
//// Implementation of BaseArray
////

#include <stdexcept>
#include <algorithm>

#include "BaseArray.h"

#ifdef NO_BA_EXCEPTIONS
#define NDEBUG
#endif

// This must come after BaseArray.h and NDEBUG
#include <cassert>

namespace DS {
namespace Numbers {

/*
BaseArray::BaseArray(size_t size) NOEXCEPT
    : m_flags(0, (uint8_t)(size <= inline_size))
    , startPadding(0)
    , startNumbers(0)
    , end(size)
{
    if (size > inline_size)
        new (&m_digit_data.digits) shared_array<unit_t>(size);

    assert(invariants());
}
*/

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

    assert(invariants());
}

////////////////////////////////////////////////////////////////////////////
//// Always
////

BaseArray::unit_t BaseArray::operator[] (size_t index) const NOEXCEPT
{
    assert(invariants());

    short temp = startPadding + (short)index;
    if (temp < startNumbers)
        return 0;

    assert(temp < end);

    if (!m_flags.fewdigits)
        return m_digit_data.digits[temp];
    else
        return m_digit_data.digit[temp];
}

////////////////////////////////////////////////////////////////////////////
//// Before finalization
////

void BaseArray::set(BaseArray::unit_t c, size_t index) NOEXCEPT
{
    assert(!isFinalized());
    assert(invariants());
    assert(index < (size_t)end);

    if (!m_flags.fewdigits)
        m_digit_data.digits[index] = c;
    else
        m_digit_data.digit[index] = c;

    assert(invariants());
}

////////////////////////////////////////////////////////////////////////////
//// After finalization
////

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

    assert(invariants());
    assert(src.invariants());

    return *this;
}

bool BaseArray::invariants() const NOEXCEPT
{
    if (!(end >= startNumbers))
        return false;
    if (!(startNumbers >= 0))
        return false;
    if (!(startNumbers >= startPadding))
        return false;

    if (end == startNumbers)
        return (end == 0) && (startNumbers == 0) && (startPadding == 0);

    if (!isFinalized())
        return (startPadding == 0);

    return true;
}

void BaseArray::cutToSize(size_t size) NOEXCEPT
{
    assert(isFinalized());
    assert(size <= (size_t)(end-startPadding));

    end = startPadding + (short)size;
    if (end > startNumbers) {
        assert(invariants());
        return;
    }
    end = startNumbers = startPadding = 0;

    assert(invariants());
}

void BaseArray::removeLeadingZeros(void) NOEXCEPT
{
    assert(isFinalized());

    BaseArray::unit_t* digit = m_flags.fewdigits ? &m_digit_data.digit[end]
                                                 : &m_digit_data.digits[end];

    while (end > startNumbers && !(*(--digit)))
        end--;

    if (end == startNumbers)
        end = startNumbers = startPadding = 0;

    assert(invariants());
}

void BaseArray::shiftLeft(size_t i) NOEXCEPT
{
    assert(isFinalized());

    startPadding -= (short)i;

    assert(invariants());
}

void BaseArray::shiftRight(size_t i) NOEXCEPT
{
    assert(isFinalized());

    startPadding += (short)i;
    if (startPadding > startNumbers)
        startNumbers = startPadding;
    if (startPadding > end)
        startNumbers = startPadding = end;

    assert(invariants());
}

void BaseArray::output(std::ostream& out) const NOEXCEPT
{
    assert(invariants());
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
