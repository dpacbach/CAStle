#include <stdexcept>
#include <algorithm>

#include "BaseArray.h"

namespace DS {
namespace Numbers {

#ifdef SPECIALIZE_SIZE
    BaseArray::BaseArray(size_t size)
        : m_flags(0, (uint8_t)(size <= max_specialize_size))
        //: finalized(false)
        , startPadding(0)
        , startNumbers(0)
        , end(size)
        //, m_digits_size(size)
    {
        if (size > max_specialize_size)
    #ifdef USE_SHARED_ARRAY
            new (&m_digit_data.digits) shared_array<unit_t>(size);
    #else
            new (&m_digit_data.digits) std::shared_ptr<std::vector<unit_t>>(new std::vector<unit_t>(size));
    #endif
    }
#else
    BaseArray::BaseArray(size_t size)
    #ifdef USE_SHARED_ARRAY
        : digits(size) // does not initialize
    #else
        : digits(new std::vector<unit_t>(size)) // does not initialize
    #endif
        , m_flags(0, 0)
        //, finalized(false)
        , startPadding(0)
        , startNumbers(0)
        , end(size)
        //, m_digits_size(size)
    { }
#endif

void BaseArray::release()
{
#ifdef SPECIALIZE_SIZE
    if (!m_flags.fewdigits)
    #ifdef USE_SHARED_ARRAY
        m_digit_data.digits.~shared_array<unit_t>();
    #else
        m_digit_data.digits.~shared_ptr<std::vector<unit_t>>();
    #endif
#endif
}

BaseArray::~BaseArray()
{
    release();
}

BaseArray::BaseArray(const BaseArray& src)
    : m_flags(src.m_flags)
    //: finalized(true)
    , startPadding(src.startPadding)
    , startNumbers(src.startNumbers)
    , end(src.end)
    //, m_digits_size(src.m_digits_size)
{
    // commented out for testing
    //if (!src.isFinalized())
    //    throw logic_error("src not finalized in DigitArray::DigitArray(const DigitArray&)");
#ifdef SPECIALIZE_SIZE
    if (!m_flags.fewdigits)
    #ifdef USE_SHARED_ARRAY
        new (&m_digit_data.digits) shared_array<unit_t>(src.m_digit_data.digits);
    #else
        new (&m_digit_data.digits) std::shared_ptr<std::vector<unit_t>>(src.m_digit_data.digits);
    #endif
    else
        //m_digit_data.digit = src.m_digit_data.digit;
        std::copy(src.m_digit_data.digit, src.m_digit_data.digit+max_specialize_size, m_digit_data.digit); 
#else
    digits = src.digits;
#endif

}

// **********************************************************
// * Always

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
        throw std::out_of_range("index out of range in DigitArray::operator[] const");
#endif
#ifdef SPECIALIZE_SIZE
    if (!m_flags.fewdigits)
        return DIGITS_REF[temp];
    else
        return m_digit_data.digit[temp];
#else
    return DIGITS_REF[temp];
#endif
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
#ifdef SPECIALIZE_SIZE
    if (!m_flags.fewdigits)
        DIGITS_REF[(size_t)index] = c;
    else
        m_digit_data.digit[(size_t)index] = c; // index needs to be bounds checked
#else
    DIGITS_REF[(size_t)index] = c;
#endif
}

// **********************************************************
// * After finalization

BaseArray& BaseArray::operator= (const BaseArray& src)
{
    if (this == &src)
        return *this;
#ifndef NO_EXCEPTIONS
    // commented out for testing
    //if (!isFinalized())
    //    throw std::logic_error("*this not finalized in DigitArray::operator=(const DigitArray&)");
    //if (!src.isFinalized())
    //    throw std::logic_error("src not finalized in DigitArray::operator=(const DigitArray&)");
#endif
    release();
#ifdef SPECIALIZE_SIZE
    if (!src.m_flags.fewdigits)
    #ifdef USE_SHARED_ARRAY
        new (&m_digit_data.digits) shared_array<unit_t>(src.m_digit_data.digits);
    #else
        new (&m_digit_data.digits) std::shared_ptr<std::vector<unit_t>>(src.m_digit_data.digits);
    #endif
    else
        //m_digit_data.digit = src.m_digit_data.digit;
        std::copy(src.m_digit_data.digit, src.m_digit_data.digit+max_specialize_size, m_digit_data.digit); 
#else
    digits = src.digits;
#endif
    startPadding  = src.startPadding;
    startNumbers  = src.startNumbers;
    end           = src.end;
    m_flags       = src.m_flags;
    //m_digits_size = src.m_digits_size;
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
#ifdef SPECIALIZE_SIZE
        if (!m_flags.fewdigits) {
            if (DIGITS_REF[startPadding] != 0)
                break;
        }
        else {
            if (m_digit_data.digit[startPadding] != 0)
                break;
        }
#else
        if (DIGITS_REF[startPadding] != 0)
            break;
#endif
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
#ifdef SPECIALIZE_SIZE
        if (!m_flags.fewdigits) {
            if (DIGITS_REF[end-1] != 0)
                break;
        }
        else {
            if (m_digit_data.digit[end-1] != 0)
                break;
        }
#else
        if (DIGITS_REF[end-1] != 0)
            break;
#endif
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
