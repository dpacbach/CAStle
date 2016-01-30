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
    // Needs to be optimized for the complete inline case
    assert(src.invariants());

    if (!src.has_few_digits()) {
        new (&m_digit_data.digits_heap) shared_array<unit_t>(src.m_digit_data.digits_heap);
        m_digits = &m_digit_data.digits_heap[0];
    }
    else {
        // TODO: This seems to call memmove -- replace it with manual moves
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
    ///////////////////////////////////////////////////////////
    //// | 1 2 | 3 4 5 6 7 8 9 | 0 1 2 3 4 5 | ? ? ? ? ? |
    ////      end   >=    startNumbers  >=  zero    startPadding
    ////
    //// The above results in the following number:
    ////     345678900000000000
    ///////////////////////////////////////////////////////////
    const short& sp = m_indexes.single_index.startPadding;
    const short& sn = m_indexes.single_index.startNumbers;
    const short& e  = m_indexes.single_index.end;

    if (!(e >= sn) || !(sn >= 0) || !(sn >= sp))
        return false;

    if (e == sn)
        return (e == 0) && (sn == 0) && (sp == 0);

    return true;
}

////////////////////////////////////////////////////////////////////////////
//// Always
////

// TODO: this should probably be inlined
BaseArray::unit_t BaseArray::operator[] (size_t index) const NOEXCEPT
{
    const short& startPadding = m_indexes.single_index.startPadding;
    const short& startNumbers = m_indexes.single_index.startNumbers;

    assert(invariants());

    short temp = startPadding + (short)index;
    if (temp < startNumbers)
        return 0;

    assert(temp < end);

    return m_digits[temp];
}

////////////////////////////////////////////////////////////////////////////
//// After finalization
////
// TODO: do we really need this function?
BaseArray& BaseArray::operator= (const BaseArray& src) NOEXCEPT
{
    // Needs to be optimized for the complete inline case
    if (this == &src)
        return *this;

    release();
    if (!src.has_few_digits()) {
        new (&m_digit_data.digits_heap) shared_array<unit_t>(src.m_digit_data.digits_heap);
        m_digits = &m_digit_data.digits_heap[0];
    }
    else {
        m_digits = &m_digit_data.digits_stack[0];
        // TODO: This seems to call memmove -- replace it with manual moves
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

void BaseArray::shiftRight(size_t i) NOEXCEPT
{
    short& startPadding = m_indexes.single_index.startPadding;
    short& startNumbers = m_indexes.single_index.startNumbers;
    short& end          = m_indexes.single_index.end;

    startPadding += (short)i;
    if (startPadding > startNumbers)
        startNumbers = startPadding;
    if (startPadding > end)
        end = startPadding;
    //if (startPadding > end)
    //    startNumbers = startPadding = end;
    assert(invariants());
}

void BaseArray::cutToSize(size_t size) NOEXCEPT
{
    short& startPadding = m_indexes.single_index.startPadding;
    short& startNumbers = m_indexes.single_index.startNumbers;
    short& end          = m_indexes.single_index.end;

    assert(size <= (size_t)(end-startPadding));

    end = startPadding + (short)size;
    if (end > startNumbers) {
        assert(invariants());
        return;
    }
    m_indexes.all_indexes = 0;

    assert(invariants());
}

void BaseArray::removeLeadingZeros(void) NOEXCEPT
{
    short& startNumbers = m_indexes.single_index.startNumbers;
    short& end          = m_indexes.single_index.end;

    while (end > startNumbers) {
        if (m_digits[end-1]) {
            assert(invariants());
            return;
        }
        end--;
    }

    m_indexes.all_indexes = 0;

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
