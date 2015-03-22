////
//// Implementation of BaseArray
////

#include <stdexcept>
#include <algorithm>

#include "BaseArray.h"

namespace DS {
namespace Numbers {

BaseArray::BaseArray(const BaseArray& src) NOEXCEPT
    : m_indexes(src.m_indexes)
{
    assert(src.invariants());

    if (!src.has_few_digits()) {
        new (&m_digit_data.digits_heap) shared_array<unit_t>(src.m_digit_data.digits_heap);
        m_digits = &m_digit_data.digits_heap[0];
    }
    else {
        std::copy(src.m_digit_data.digits_stack,
                  src.m_digit_data.digits_stack+inline_size,
                  m_digit_data.digits_stack); 
        m_digits = &m_digit_data.digits_stack[0];
    }

    assert(invariants());
    assert(src.invariants());
}

// Return false if any of the class invariants don't hold
bool BaseArray::invariants() const NOEXCEPT
{
    const short& sp = m_indexes.single_index.startPadding;
    const short& sn = m_indexes.single_index.startNumbers;
    const short& e  = m_indexes.single_index.end;
    ///////////////////////////////////////////////////////////
    //// | 1 2 | 3 4 5 6 7 8 9 | 0 1 2 3 4 5 | ? ? ? ? ? |
    ////      end   >=    startNumbers  >=  zero    startPadding
    ////
    //// The above results in the following number:
    ////     345678900000000000
    ///////////////////////////////////////////////////////////
    if (!(e >= sn) || !(sn >= 0) || !(sn >= sp))
        return false;

    if (e == sn)
        return (e == 0) && (sn == 0) && (sp == 0);

    return true;
}

////////////////////////////////////////////////////////////////////////////
//// Always
////

BaseArray::unit_t BaseArray::operator[] (size_t index) const NOEXCEPT
{
    assert(invariants());

    short temp = m_indexes.single_index.startPadding + (short)index;
    if (temp < m_indexes.single_index.startNumbers)
        return 0;

    assert(temp < m_indexes.single_index.end);
    return m_digits[temp];
}

////////////////////////////////////////////////////////////////////////////
//// After finalization
////

BaseArray& BaseArray::operator= (const BaseArray& src) NOEXCEPT
{
    if (this == &src)
        return *this;

    release();
    if (!src.has_few_digits()) {
        new (&m_digit_data.digits_heap)
            shared_array<unit_t>(src.m_digit_data.digits_heap);
        m_digits = &m_digit_data.digits_heap[0];
    }
    else {
        m_digits = &m_digit_data.digits_stack[0];
        std::copy(src.m_digits, src.m_digits+inline_size, m_digits); 
    }

    m_indexes.all_indexes = src.m_indexes.all_indexes;

    assert(invariants());
    assert(src.invariants());
    return *this;
}

////////////////////////////////////////////////////////////////////////////
//// Index-shifting functions
////

void BaseArray::cutToSize(size_t size) NOEXCEPT
{
    assert(size <= (size_t)(m_indexes.single_index.end-m_indexes.single_index.startPadding));

    m_indexes.single_index.end = m_indexes.single_index.startPadding + (short)size;
    if (m_indexes.single_index.end > m_indexes.single_index.startNumbers) {
        assert(invariants());
        return;
    }
    m_indexes.all_indexes = 0;

    assert(invariants());
}

void BaseArray::removeLeadingZeros(void) NOEXCEPT
{
    short& sn = m_indexes.single_index.startNumbers;
    short& e  = m_indexes.single_index.end;

    while (e > sn) {
        if (m_digits[e-1]) {
            assert(invariants());
            return;
        }
        e--;
    }

    m_indexes.all_indexes = 0;

    assert(invariants());
}

void BaseArray::shiftLeft(size_t i) NOEXCEPT
{
    m_indexes.single_index.startPadding -= (short)i;

    assert(invariants());
}

void BaseArray::shiftRight(size_t i) NOEXCEPT
{
    short& sp = m_indexes.single_index.startPadding;
    short& sn = m_indexes.single_index.startNumbers;
    short& e  = m_indexes.single_index.end;

    sp += (short)i;
    if (sp > sn)
        sn = sp;
    if (sp > e)
        sn = sp = e;

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

    const unit_t* ref = m_digits;

    out << "(";
    for (i = m_indexes.single_index.end-1; i >= m_indexes.single_index.startNumbers; i--)
        out << ref[i] << "*2^(" << (exp--)*(sizeof(unit_t)*8) << ")+";
    for (; i > m_indexes.single_index.startPadding; i--)
        out << 0 << "*2^(" << (exp--)*(sizeof(unit_t)*8) << ")+";
    out << "0)";
}

} /* namespace Numbers */
} /* namespace DS */
