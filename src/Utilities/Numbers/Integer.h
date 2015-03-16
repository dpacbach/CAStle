#ifndef INTEGER_H_
#define INTEGER_H_

#include <iostream>
#include "BaseArray.h"

using namespace std;

namespace DS {
namespace Numbers {

class Integer
{
public:

    Integer();
    Integer(int);
    Integer(BaseArray::unit_t);
    Integer(const Integer&);
    Integer(Integer&&) = default;
    Integer& operator= (const Integer&);
    Integer& operator= (Integer&&) = default;
    Integer& operator= (int);
    ~Integer();

    std::ostream& output(std::ostream& out) const
    {
        if (!sign)
            out << "-";
        digits.output(out);
        return out;
    }

    void negate(void);
    void makeAbs(void);

    Integer& operator++ (void);
    Integer& operator-- (void);
    Integer operator++ (int);
    Integer operator-- (int);

    void operator+= (const Integer&);
    void operator-= (const Integer&);
    void operator*= (const Integer&);
    void operator/= (const Integer&);
    void operator%= (const Integer&);

    Integer divideBy(const Integer&);

    void pow(const Integer&);
    void intRoot(const Integer&);

    bool isLessThan(const Integer&) const;
    bool isEqualTo(const Integer&) const;
    bool isNegative(void) const;
    explicit operator bool() const;

    int numberOfDigits(void) const;
    int numberOfTrailingZeros(void) const;

    bool isMultipleOfUnit(void) const;
    bool shiftRightOneBit(void);
    void shiftLeftByUnits(int);
    void shiftRightByUnits(int);
    void modByUnits(int);
    void divideByUnit(BaseArray::unit_t);
    BaseArray::unit_t getModByOneUnit(void) const;
    BaseArray::unit_t getMostSigUnit(void) const;
    BaseArray::unit_t getSecondMostSigUnit(void) const;

private:

    void copyFrom(const Integer&);
    void copyFrom(int);
    void copyFrom(BaseArray::unit_t);
    void multiplyByDigit(int digit);
    void removeZeros(void);
    void setToZero(void);

    void multiply_SchoolBook(const Integer&);
    void multiply_Karatsuba(const Integer&);
    void splitDigits(const Integer& src, Integer& upper, Integer& lower, unsigned int splitPoint);

    BaseArray digits;
    bool sign; // true = +
};

/*
inline Integer pow(const Integer& number, const Integer& power)
{
    Integer temp = number;
    temp.pow(power);
    return temp;
}
template<typename T>
inline Integer pow(const Integer& number, const T& power)
{
    return pow(number, Integer(power));
}
template<typename T>
inline Integer pow(const T& number, const Integer& power)
{
    return pow(Integer(number), power);
}
*/
inline Integer abs(const Integer& number)
{
    Integer result = number;
    result.makeAbs();
    return result;
}


inline std::ostream& operator<< (std::ostream& out, const Integer& number)
{
    number.output(out);
    return out;
}


inline Integer operator+ (const Integer& lhs, const Integer& rhs)
{
    Integer temp = lhs;
    temp += rhs;
    return temp;
}
inline Integer operator- (const Integer& lhs, const Integer& rhs)
{
    Integer temp = lhs;
    temp -= rhs;
    return temp;
}
inline Integer operator* (const Integer& lhs, const Integer& rhs)
{
    Integer temp = lhs;
    temp *= rhs;
    return temp;
}
inline Integer operator% (const Integer& lhs, const Integer& rhs)
{
    Integer temp = lhs;
    temp %= rhs;
    return temp;
}
inline Integer operator/ (const Integer& lhs, const Integer& rhs)
{
    Integer temp = lhs;
    temp /= rhs;
    return temp;
}
/*
template<typename T>
Integer operator+ (const Integer& lhs, const T& rhs)
{
    return lhs+Integer(rhs);
}
template<typename T>
Integer operator+ (const T& lhs, const Integer& rhs)
{
    return Integer(lhs)+rhs;
}
template<typename T>
Integer operator- (const Integer& lhs, const T& rhs)
{
    return lhs-Integer(rhs);
}
template<typename T>
Integer operator- (const T& lhs, const Integer& rhs)
{
    return Integer(lhs)-rhs;
}
template<typename T>
Integer operator* (const Integer& lhs, const T& rhs)
{
    return lhs*Integer(rhs);
}
template<typename T>
Integer operator* (const T& lhs, const Integer& rhs)
{
    return Integer(lhs)*rhs;
}

template<typename T>
Integer operator% (const Integer& lhs, const T& rhs)
{
    return lhs%Integer(rhs);
}
template<typename T>
Integer operator% (const T& lhs, const Integer& rhs)
{
    return Integer(lhs)%rhs;
}
*/
inline Integer operator- (const Integer& number)
{
    Integer copy = number;
    copy.negate();
    return copy;
}

inline bool operator== (const Integer& lhs, const Integer& rhs)
{
    return lhs.isEqualTo(rhs);
}
inline bool operator!= (const Integer& lhs, const Integer& rhs)
{
    return !(lhs.isEqualTo(rhs));
}
inline bool operator< (const Integer& lhs, const Integer& rhs)
{
    return lhs.isLessThan(rhs);
}
inline bool operator<= (const Integer& lhs, const Integer& rhs)
{
    return lhs.isLessThan(rhs) || (lhs == rhs);
}
inline bool operator> (const Integer& lhs, const Integer& rhs)
{
    return !lhs.isLessThan(rhs) && !(lhs == rhs);
}
inline bool operator>= (const Integer& lhs, const Integer& rhs)
{
    return !lhs.isLessThan(rhs);
}

template<typename T>
bool operator== (const Integer& lhs, const T& rhs)
{
    return lhs==Integer(rhs);
}
template<typename T>
bool operator== (const T& lhs, const Integer& rhs)
{
    return Integer(lhs)==rhs;
}
template<typename T>
bool operator!= (const Integer& lhs, const T& rhs)
{
    return !(lhs==Integer(rhs));
}
template<typename T>
bool operator!= (const T& lhs, const Integer& rhs)
{
    return !(Integer(lhs)==rhs);
}
template<typename T>
bool operator< (const Integer& lhs, const T& rhs)
{
    return lhs < Integer(rhs);
}
template<typename T>
bool operator< (const T& lhs, const Integer& rhs)
{
    return Integer(lhs) < rhs;
}
template<typename T>
bool operator<= (const Integer& lhs, const T& rhs)
{
    return lhs <= Integer(rhs);
}
template<typename T>
bool operator<= (const T& lhs, const Integer& rhs)
{
    return Integer(lhs) <= rhs;
}
template<typename T>
bool operator> (const Integer& lhs, const T& rhs)
{
    return lhs > Integer(rhs);
}
template<typename T>
bool operator> (const T& lhs, const Integer& rhs)
{
    return Integer(lhs) > rhs;
}
template<typename T>
bool operator>= (const Integer& lhs, const T& rhs)
{
    return lhs >= Integer(rhs);
}
template<typename T>
bool operator>= (const T& lhs, const Integer& rhs)
{
    return Integer(lhs) >= rhs;
}

} }

#endif /* INTEGER_H_ */
