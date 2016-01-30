#pragma once

#include <sstream>
#include <string>
// TODO: try to get rid of this header
#include "Integer.hpp"

namespace DS {
namespace Numbers {

class Float
{
public:

    typedef Integer intType;

    Float();
    Float(const Float&);
    Float(Float&&) = default;
    Float(const intType& mantissa, int exponent = 0);
    Float(int mantissa, int exponent = 0);
    Float(double); // very expensive
    Float& operator= (double); // very expensive
    Float& operator= (const Float&);
    Float& operator= (Float&&) = default;
    ~Float();

    std::ostream& output(std::ostream& out) const
    {
        mantissa.output(out);
        out << "*2^(" << (int)(exponent*UNIT_T_BITS) << ")";
        return out;
        /*
        if (mantissa == 0)
        {
            out << "0";
            return out;
        }
        if (mantissa < 0)
            out << "-";
        ostringstream s;
        string mantissaString;
        s << abs(mantissa);
        mantissaString = s.str();
        if (mantissa.numberOfDigits() > 1)
            mantissaString.insert(1, ".");
        out << mantissaString;
        int newExponent = exponent + mantissa.numberOfDigits() - 1;
        if (newExponent != 0)
            out << "e" << newExponent;
        return out;
        */
    }
    double toDouble(void) const;

    void negate(void);
    void makeAbs(void);
    void floor(void);

    void inverse(void);
    void sqrt(void);
    void AG_mean(const Float&);
    void exp(void);
    void ln(void);
    void sin(void);
    void atan(void);

    static const Float& pi(void);
    static const Float& lnTwo(void);

    void operator+= (const Float&);
    void operator-= (const Float&);
    void operator*= (const Float&);
    void operator/= (const Float&);
    void operator%= (const Float&);

    void pow(const Float&);

    bool isLessThan(const Float&) const;
    bool isEqualTo(const Float&) const;
    bool isNegative(void) const;
    bool isZero(void) const;

    int  numberOfMantissaUnits(void) const;
    void multiplyByBase(int);
    void divideByBase(int);
    void divideByTwo(void);

private:

    void copyFrom(const Float&);
    void copyFrom(double); // very expensive
    void setToZero(void);
    void removeExcessMantissa(void);

    friend Float gcd(const Float& a, const Float& b);

    static const int maxMantissaDigits;
    intType mantissa;
    int exponent;
};

inline std::ostream& operator<< (std::ostream& out, const Float& number)
{
    number.output(out);
    return out;
}

inline Float floor(const Float& number)
{
    Float result = number;
    result.floor();
    return result;
}

inline void createPi(Float& number)
{
    number = Float::pi();
}
inline Float operator+ (const Float& lhs, const Float& rhs)
{
    Float temp = lhs;
    temp += rhs;
    return temp;
}
inline Float operator- (const Float& lhs, const Float& rhs)
{
    Float temp = lhs;
    temp -= rhs;
    return temp;
}
inline Float operator* (const Float& lhs, const Float& rhs)
{
    Float temp = lhs;
    temp *= rhs;
    return temp;
}
inline Float operator/ (const Float& lhs, const Float& rhs)
{
    Float temp = lhs;
    temp /= rhs;
    return temp;
}
inline Float operator% (const Float& lhs, const Float& rhs)
{
    Float temp = lhs;
    temp %= rhs;
    return temp;
}

inline Float operator- (const Float& number)
{
    Float copy = number;
    copy.negate();
    return copy;
}

inline bool operator== (const Float& lhs, const Float& rhs)
{
    return lhs.isEqualTo(rhs);
}
inline bool operator!= (const Float& lhs, const Float& rhs)
{
    return !(lhs.isEqualTo(rhs));
}
inline bool operator< (const Float& lhs, const Float& rhs)
{
    return lhs.isLessThan(rhs);
}
inline bool operator<= (const Float& lhs, const Float& rhs)
{
    return lhs.isLessThan(rhs) || (lhs == rhs);
}
inline bool operator> (const Float& lhs, const Float& rhs)
{
    return !lhs.isLessThan(rhs) && !(lhs == rhs);
}
inline bool operator>= (const Float& lhs, const Float& rhs)
{
    return !lhs.isLessThan(rhs);
}

template<typename T>
bool operator== (const Float& lhs, const T& rhs)
{
    return lhs==Float(rhs);
}
template<typename T>
bool operator== (const T& lhs, const Float& rhs)
{
    return Float(lhs)==rhs;
}
template<typename T>
bool operator!= (const Float& lhs, const T& rhs)
{
    return !(lhs==Float(rhs));
}
template<typename T>
bool operator!= (const T& lhs, const Float& rhs)
{
    return !(Float(lhs)==rhs);
}
template<typename T>
bool operator< (const Float& lhs, const T& rhs)
{
    return lhs < Float(rhs);
}
template<typename T>
bool operator< (const T& lhs, const Float& rhs)
{
    return Float(lhs) < rhs;
}
template<typename T>
bool operator<= (const Float& lhs, const T& rhs)
{
    return lhs <= Float(rhs);
}
template<typename T>
bool operator<= (const T& lhs, const Float& rhs)
{
    return Float(lhs) <= rhs;
}
template<typename T>
bool operator> (const Float& lhs, const T& rhs)
{
    return lhs > Float(rhs);
}
template<typename T>
bool operator> (const T& lhs, const Float& rhs)
{
    return Float(lhs) > rhs;
}
template<typename T>
bool operator>= (const Float& lhs, const T& rhs)
{
    return lhs >= Float(rhs);
}
template<typename T>
bool operator>= (const T& lhs, const Float& rhs)
{
    return Float(lhs) >= rhs;
}

inline Float sin(const Float& number)
{
    Float result = number;
    result.sin();
    return result;
}
inline Float cos(const Float& number)
{
    static Float piOverTwo(Float::pi()/Float(Integer(2)));
    Float result = number;
    result += piOverTwo;
    result.sin();
    return result;
}
inline Float exp(const Float& number)
{
    Float result = number;
    result.exp();
    return result;
}
inline Float ln(const Float& number)
{
    Float result = number;
    result.ln();
    return result;
}
inline Float logBase(const Float& number, const Float& base)
{
    Float result = number;
    Float tempBase = base;
    result.ln();
    tempBase.ln();
    result /= tempBase;
    return result;
}

inline Float sqrt(const Float& number)
{
    Float result = number;
    result.sqrt();
    return result;
}
inline Float AG_Mean(const Float& _a, const Float& _g)
{
    Float result(_a);
    result.AG_mean(_g);
    return result;
}

inline Float pow(const Float& number, const Float& power)
{
    Float temp = number;
    temp.pow(power);
    return temp;
}
template<typename T>
inline Float pow(const Float& number, const T& power)
{
    return pow(number, Float(power));
}
template<typename T>
inline Float pow(const T& number, const Float& power)
{
    return pow(Float(number), power);
}

inline Float abs(const Float& number)
{
    Float result = number;
    result.makeAbs();
    return result;
}
inline Float atan(const Float& number)
{
    Float result = number;
    result.atan();
    return result;
}

Float gcd(const Float& a, const Float& b);

} }
