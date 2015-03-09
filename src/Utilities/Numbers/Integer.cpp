#include "Integer.h"
#include <stdexcept>
#include <algorithm>

namespace DS {
namespace Numbers {

Integer::Integer() : digits(1), sign(true)
{
    digits.set(0, 0);
    digits.finalize();
}

void Integer::copyFrom(int _number)
{
    BaseArray result(1);
    if (_number < 0)
    {
        sign = false;
        _number = -_number;
    }
    else
        sign = true;
    result.set(_number, 0);
    result.finalize();
    digits.finalize();
    digits = result;

    /*
    long long order = 1;
    long long number = _number;
    sign = true;
    if (number < 0)
    {
        sign = false;
        number = -number;
    }
    unsigned int numDigits = 0;

    while (order <= number)
    {
        order *= 10;
        numDigits++;
    }
    order /= 10;
    if (order == 0)
    {
        setToZero();
        return;
    }
    DigitArray result(numDigits);
    unsigned int position = numDigits;
    while (order > 0)
    {
        char digit = 0;
        while (order <= number)
        {
            digit++;
            number -= order;
        }
        position--;
        result.set(digit, position);
        order /= 10;
    }
    result.finalize();
    digits.finalize();
    digits = result;
    */
}

void Integer::copyFrom(BaseArray::unit_t _number)
{
    BaseArray result(1);
    sign = true;
    result.set(_number, 0);
    result.finalize();
    digits.finalize();
    digits = result;
}

void Integer::copyFrom(const Integer& _number)
{
    digits.finalize();
    digits = _number.digits;
    sign = _number.sign;
}

Integer::~Integer()
{

}

void Integer::negate(void)
{
    if (bool(*this))
        sign = !sign;
}

void Integer::operator+= (const Integer& _number) // need to optimize (-) section
{
    bool zeroThis = !bool(*this);
    bool zeroNumber = !bool(_number);
    if (zeroThis && zeroNumber)
        return;
    else if (zeroNumber)
        return;
    else if (zeroThis)
    {
        copyFrom(_number);
        return;
    }
    if (sign == _number.sign)
    {
        const Integer* _shorter, *_longer;
        _shorter = &_number;
        _longer = this;
        if (digits.size() <= _number.digits.size())
        {
            _shorter = this;
            _longer = &_number;
        }
        const Integer& shorter = *_shorter;
        const Integer& longer  = *_longer;
        const BaseArray& shorterDigits = shorter.digits;
        const BaseArray& longerDigits = longer.digits;
        int shorterSize = shorterDigits.size();
        int longerSize  = longerDigits.size();

        BaseArray result(longerSize+1);

        int i = 0;
        BaseArray::unit_t_long carry = 0;
        for (; i < longerSize; ++i)
        {
            // TODO: verify conversion is happening from small --> big
            BaseArray::unit_t_long twoDigits = longerDigits[i] + carry;
            if (i < shorterSize)
                twoDigits += shorterDigits[i];
            carry = twoDigits >> UNIT_T_LONG_BITS_DIV_2;
            result.set(twoDigits & UNIT_T_MAX_AS_LONG, i);
        }
        if (carry)
            result.set(carry, i);
        else
        {
            result.finalize();
            result.cutToSize(longerSize);
        }
        result.finalize();
        digits = result;
        return;
    }
    else // signs not equal and neither number is zero
    {
        // this needs to be optimized

        const Integer* _smaller, *_larger;
        _smaller = &_number;
        _larger = this;
        if (digits.size() < _number.digits.size())
        {
            _smaller = this;
            _larger = &_number;
        }
        else if (digits.size() == _number.digits.size())
        {
            unsigned int it  = digits.size()-1;
            unsigned int it2 = _number.digits.size()-1;
            while (digits[it] == _number.digits[it2] && it != 0)
            {
                --it;
                --it2;
            }
            if (digits[it] < _number.digits[it2])
            {
                _smaller = this;
                _larger = &_number;
            }
            else if (digits[it] == _number.digits[it2])
            {
                setToZero();
                return;
            }
        }
        const Integer& smaller = *_smaller;
        const Integer& larger  = *_larger;

        BaseArray result(larger.digits.size());

        unsigned int smallerIt = 0;
        unsigned int largerIt  = 0;
        BaseArray::unit_t_long borrow = 0;

        for (; smallerIt < smaller.digits.size(); ++smallerIt, ++largerIt)
        {
            BaseArray::unit_t_long twoDigits = larger.digits[largerIt] - borrow - smaller.digits[smallerIt];
            borrow = 0;
            if (twoDigits & ((BaseArray::unit_t_long)1 << (UNIT_T_LONG_BITS-1))) // is negative
            {
                twoDigits += ((BaseArray::unit_t_long)1 << UNIT_T_BITS); // e.g., 0x0000000100000000;
                borrow = 1;
            }
            result.set(twoDigits, largerIt);
        }
        for (; largerIt < larger.digits.size(); ++largerIt)
        {
            BaseArray::unit_t_long twoDigits = larger.digits[largerIt] - borrow;
            borrow = 0;
            if (twoDigits & ((BaseArray::unit_t_long)1 << (UNIT_T_LONG_BITS-1))) // is negative
            {
                // Doesn't seem to get here much in practice
                twoDigits += ((BaseArray::unit_t_long)1 << UNIT_T_BITS); // e.g., 0x0000000100000000;
                borrow = 1;
            }
            result.set(twoDigits, largerIt);
        }
        if (borrow != 0)
            throw logic_error("borrow != 0 in Integer::operator +=");

        result.finalize();
        digits = result;
        if (larger.sign == true)
            sign = true;
        else
            sign = false;
        removeZeros();
        return;
    }
}

void Integer::multiply_SchoolBook(const Integer& _number)
{
    unsigned int initialSize = this->numberOfDigits() + _number.numberOfDigits();
    BaseArray resultDigits(initialSize);
    for (unsigned int i = 0; i < initialSize; i++)
        resultDigits.set(0, i);
    const Integer* left_ptr, *right_ptr;
    left_ptr = this;
    right_ptr = &_number;
    if (this->numberOfDigits() > _number.numberOfDigits())
    {
        left_ptr = &_number;
        right_ptr = this;
    }
    const Integer& left = *left_ptr; // left holds the smaller-digit number
    const Integer& right = *right_ptr;
    int size = left.digits.size();
    unsigned int rightSize = right.numberOfDigits();

    for (int i = 0; i < size; i++)
    {
        BaseArray::unit_t_long digit = left.digits[i];
        BaseArray::unit_t_long carry = 0;
        for (unsigned int k = 0; k < rightSize; k++)
        {
            BaseArray::unit_t_long product = right.digits[k]*digit;
            product += carry;
            BaseArray::unit_t_long newDigit = product & UNIT_T_MAX_AS_LONG; //UNIT_T_MAX_AS_LONG;
            carry = product >> UNIT_T_LONG_BITS_DIV_2;
            BaseArray::unit_t_long addCarry = 0;
            BaseArray::unit_t_long sum = resultDigits[i+k]+newDigit;
            resultDigits.set(sum & UNIT_T_MAX_AS_LONG, k+i);
            addCarry = sum >> UNIT_T_LONG_BITS_DIV_2;
            if (addCarry)
            {
                for (unsigned int j = i+k+1; j < initialSize; j++)
                {
                    sum = resultDigits[j]+addCarry;
                    resultDigits.set(sum & UNIT_T_MAX_AS_LONG, j);
                    addCarry = sum >> UNIT_T_LONG_BITS_DIV_2;
                    if (!addCarry)
                        break;
                }
            }
        }
        if (carry)
        {
            BaseArray::unit_t_long sum = resultDigits[i+rightSize]+carry;
            resultDigits.set(sum & UNIT_T_MAX_AS_LONG, rightSize+i);
            BaseArray::unit_t_long addCarry = sum >> UNIT_T_LONG_BITS_DIV_2;
            if (addCarry)
            {
                for (unsigned int j = i+rightSize+1; j < initialSize; j++)
                {
                    sum = resultDigits[j]+addCarry;
                    resultDigits.set(sum & UNIT_T_MAX_AS_LONG, j);
                    addCarry = sum >> UNIT_T_LONG_BITS_DIV_2;
                    if (!addCarry)
                        break;
                }
            }
        }
    }
    resultDigits.finalize();
    resultDigits.removeLeadingZeros();
    digits = resultDigits;
    sign = !(sign^_number.sign);
    if (!bool(*this))
        sign = true;
}

void Integer::splitDigits(const Integer& src, Integer& upper, Integer& lower, unsigned int splitPoint)
{
    // error checking?

    lower = src;
    lower.modByUnits(splitPoint);
    upper = src;
    upper.shiftRightByUnits(splitPoint);
}

void Integer::multiply_Karatsuba(const Integer& _number) // only seems to be faster when digits ~ 1000
{
    unsigned int numLeftDigits  = numberOfDigits();
    unsigned int numRightDigits = _number.numberOfDigits();
    if (numLeftDigits <= 50 || numRightDigits <= 50)
    {
        multiply_SchoolBook(_number);
        return;
    }

    unsigned int splitPointLeft  = (numLeftDigits+1)/2;
    unsigned int splitPointRight = (numRightDigits+1)/2;
    unsigned int splitPoint = (splitPointLeft <= splitPointRight) ? splitPointLeft : splitPointRight;

    Integer leftUpper, rightUpper, leftLower, rightLower;
    splitDigits(*this, leftUpper, leftLower, splitPoint);
    splitDigits(_number, rightUpper, rightLower, splitPoint);

    Integer z0(leftLower), z1(leftLower), z2(leftUpper), temp(rightLower);
    z0.multiply_Karatsuba(rightLower);
    z2.multiply_Karatsuba(rightUpper);
    z1 += leftUpper;
    temp += rightUpper;
    z1.multiply_Karatsuba(temp);
    z1 -= z0;
    z1 -= z2;

    z2.shiftLeftByUnits(2*splitPoint);
    z1.shiftLeftByUnits(splitPoint);
    z0 += z1;
    z0 += z2;

    *this = z0;
}

void Integer::operator*= (const Integer& _number)
{
    //multiply_Karatsuba(_number);
    multiply_SchoolBook(_number); // faster for digits <~ 100
}

void Integer::operator%= (const Integer& number)
{
    if (number == 2)
    {
        *this = Integer(digits[0]%2);
        return;
    }
    *this = divideBy(number);
}

bool Integer::isLessThan(const Integer& number) const
{
    if (sign != number.sign)
        return !sign;
    bool signFlip = false;
    if (sign == false)
        signFlip = true;

    if (digits.size() > number.digits.size())
        return false^signFlip;
    else if (digits.size() == number.digits.size())
    {
        unsigned int it  = digits.size()-1;
        unsigned int it2 = number.digits.size()-1;
        while (digits[it] == number.digits[it2] && it != 0)
        {
            --it;
            --it2;
        }
        return (digits[it] < number.digits[it2])^signFlip;
    }
    else
        return true^signFlip;
}

bool Integer::isEqualTo(const Integer& number) const
{
    if (!bool(*this) && !bool(number))
        return true;
    if (sign != number.sign || digits.size() != number.digits.size())
        return false;
    for (unsigned int i = 0; i < digits.size(); i++)
        if (digits[i] != number.digits[i])
            return false;
    return true;
}

bool Integer::isNegative(void) const
{
    return !sign;
}

void Integer::removeZeros(void) // unused?
{
    digits.removeLeadingZeros();
}

/*
void Integer::multiplyByDigit(int digit)
{
    if (digit == 0)
    {
        setToZero();
        return;
    }
    if (digit == 1)
        return;
    BaseArray::unit_t carry = 0;
    BaseArray::unit_t_long twoDigits;
    int size = digits.size();
    BaseArray result(size+1);
    for (int i = 0; i < size; i++)
    {
        twoDigits = digit*digits[i] + carry;
        result.set(twoDigits & 0x0000FFFF, i); // probably incorrect constant
        carry = twoDigits >> UNIT_T_LONG_BITS_DIV_2;
    }
    if (carry)
        result.set(carry, size);
    else
    {
        result.finalize();
        result.cutToSize(result.size()-1);
    }
    result.finalize();
    digits = result;
}
*/

bool Integer::shiftRightOneBit(void)
{
    if (digits.size() == 0)
        throw logic_error("digits.size() == 0 in Integer::shiftRightNBits()");
    if (digits.size() == 1 && getMostSigUnit() <= 1)
    {
            bool result = bool(getMostSigUnit());
            setToZero();
            return result;
    }
    BaseArray result(digits.size());
    BaseArray::unit_t lsb = 0;
    for (int i = digits.size()-1; i >=0; i--)
    {
         result.set((digits[i] >> 1) | (lsb << (UNIT_T_BITS - 1)), i);
         lsb = digits[i] & 1;
    }
    result.finalize();
    if (result[result.size()-1] == 0)
        result.cutToSize(result.size()-1);
    digits = result;
    return bool(lsb);
}

void Integer::shiftLeftByUnits(int power)
{
    if (power < 0)
    {
        shiftRightByUnits(-power);
        return;
    }
    if (power == 0)
        return;
    if (!bool(*this))
        return;
    digits.shiftLeft(static_cast<unsigned int>(power));
}

void Integer::shiftRightByUnits(int power)
{
    if (power < 0)
    {
        shiftLeftByUnits(-power);
        return;
    }
    if (!bool(*this))
        return;
    if (static_cast<unsigned int>(power) >= digits.size())
    {
        setToZero();
        return;
    }
    digits.shiftRight(static_cast<unsigned int>(power));
}

void Integer::modByUnits(int power)
{
    if (power < 0)
        throw logic_error("power < 0 in Integer::modByOneUnit()");
    if (!bool(*this))
        return;
    if (static_cast<unsigned int>(power) >= digits.size())
        return;

    digits.cutToSize(static_cast<unsigned int>(power));
}

BaseArray::unit_t  Integer::getModByOneUnit(void) const
{
    return digits[0];
}

BaseArray::unit_t  Integer::getMostSigUnit(void) const
{
    return digits[digits.size()-1];
}

BaseArray::unit_t  Integer::getSecondMostSigUnit(void) const
{
    if (digits.size() <= 1)
        return 0;
    return digits[digits.size()-2];
}

void Integer::setToZero(void)
{
    BaseArray zero(1);
    zero.set(0, 0);
    zero.finalize();
    digits.finalize();
    digits = zero;
    sign = true;
}

void Integer::makeAbs(void)
{
    sign = true;
}

int Integer::numberOfDigits(void) const
{
    return digits.size();
}

bool Integer::isMultipleOfUnit(void) const
{
    return digits[0] == 0;
}

int Integer::numberOfTrailingZeros(void) const
{
    int result = 0, size = digits.size(), i = 0;
    while (i < size-1)
    {
        if (digits[i++] == 0)
            result++;
        else
            break;
    }
    return result;
}

Integer::operator bool() const
{
    if (digits.size() > 1)
        return true;
    if (digits.size() == 0)
        return false;
    return (digits[0] > 0);
}

// Optional to implement

Integer::Integer(int _number) : digits()
{
    copyFrom(_number);
}
Integer::Integer(BaseArray::unit_t _number) : digits()
{
    copyFrom(_number);
}
Integer::Integer(const Integer& _number) : digits(_number.digits), sign(_number.sign)
{
}
Integer& Integer::operator= (const Integer& _number)
{
    copyFrom(_number);
    return *this;
}
Integer& Integer::operator= (int _number)
{
    copyFrom(_number);
    return *this;
}

Integer& Integer::operator++ (void)
{
    *this += 1;
    return *this;
}
Integer& Integer::operator-- (void)
{
    *this -= 1;
    return *this;
}
Integer Integer::operator++ (int)
{
    Integer copy = *this;
    *this += 1;
    return copy;
}
Integer Integer::operator-- (int)
{
    Integer copy = *this;
    *this -= 1;
    return copy;
}

void Integer::operator-= (const Integer& _number)
{
    Integer temp(_number);
    temp.negate();
    *this += temp;
}

void Integer::divideByUnit(BaseArray::unit_t b)
{
    Integer cInt, acc, temp = *this;
    unsigned long c, numberOfDividends;

    do
    {
        if (temp.digits.size() == 1 && temp.digits[0] < b)
            break;
        c = temp.digits[temp.digits.size()-1] / b;
        numberOfDividends = 1;
        if (!c)
        {
            c = ((((BaseArray::unit_t_long)temp.digits[temp.digits.size()-1])<<UNIT_T_BITS) + temp.digits[temp.digits.size()-2] )/b;
            numberOfDividends = 2;
        }
        static_assert(sizeof(BaseArray::unit_t) >= sizeof(c), "BaseArray::unit_t not big enough");
        cInt = Integer((BaseArray::unit_t)c); //(unsigned int)c);
        cInt.shiftLeftByUnits((int)temp.digits.size()-(int)numberOfDividends);
        acc += cInt;
        temp -= cInt * Integer(b);
    }   while(1);

    // temp holds modulus
    *this = acc;
/*
 *
 * Division by a Single Unit (a / b)

    if (a is only one unit and it's < b)
        return 0
    if (top unit of a > b)
        divide top unit of a by b => c
    else
        divide top two units by b => c
    c = c*b
    shift c left by number of units in a - # of dividends
    acc += c
    subtract c from a
    repeat
    a holds modulus
 */
}

Integer Integer::divideBy(const Integer& _b)
{
    //cout << endl << "dividing ";
    //this->output(cout);
    //cout << " by ";
    //_b.output(cout);
    //cout << endl;
    if (!_b)
        throw invalid_argument("divide by zero in Integer::divideBy");

    if (!(*this))
        return (BaseArray::unit_t)0;

    if (_b.numberOfDigits() == 1 && _b.digits[0] == 1)
    {
        if (_b.isNegative())
            negate();
        return (BaseArray::unit_t)0;
    }

    bool negativeFlag = this->isNegative() ^ _b.isNegative();
    Integer b = _b;
    b.makeAbs();
    this->makeAbs();

    Integer temp = *this, acc;
    do
    {
        //cout << endl;
        //cout << "   temp = ";
        //temp.output(cout);
        if (temp.isLessThan(b))
            break;
        unsigned int tempSize = temp.digits.size();
        unsigned int bSize = b.digits.size();
        if (tempSize == bSize && temp.digits[tempSize-1] == b.digits[bSize-1])
        {
            temp -= b;
            Integer oneShift(1);
            //oneShift.shiftLeftByUnits(tempSize-1);
            acc += oneShift;
            break;
        }
        int shiftCount = b.digits.size()-1;
        Integer tempA = temp, tempB = b;
        tempA.shiftRightByUnits(shiftCount);
        tempB.shiftRightByUnits(shiftCount);
        ++tempB;
        if (tempB.digits.size() > 1)
            tempA.divideBy(tempB);
        else
            tempA.divideByUnit(tempB.digits[0]);
        //cout << endl << "   tempA = ";
        //tempA.output(cout);
        temp -= b*tempA;
        //tempA.shiftLeftByUnits(b.digits.size()-1);
        acc += tempA;
    }   while(1);

    *this = acc;
    if (negativeFlag)
    {
        negate();
        temp = b - temp;
    }
    //cout << endl << "   result = ";
    //this->output(cout);
    return temp; // remainder
    /*
     *
     * Division Algorithm (a / b)

    if (a < b)
        return a;
    if (first unit of a == first unit of b)
        return a-b;
    r = 0
    shift a and b right until b has only one unit
    add one to b
    if (b overflowed)
        c = DivideBy(a / b)
    else
        c = DivideBySingleUnit(a / b)
    multiply original b by c => d
    r += c << (number of units in b-1)
    subtract d from a to get new a and repeat
    a holds modulus at end
     *
     *
     */
}

void Integer::operator/= (const Integer& _number)
{
    divideBy(_number);
}

void Integer::intRoot(const Integer& n)
{
    Integer one(1), two(2), b;

    b = Integer((BaseArray::unit_t)(this->digits.size()*UNIT_T_BITS));
    BaseArray::unit_t shift = this->digits[this->digits.size()-1];
    while (shift > 0)
    {
        shift >>= 1;
        b++;
    }
    b -= Integer((BaseArray::unit_t)UNIT_T_BITS);
    b /= n;
    Integer x(2);
    x.pow(b);
    Integer test(x);
    test.pow(n);
    if (this->isLessThan(test))
        x /= two;
    while (1)
    {
        //cout << endl;
        //x.output(cout);
        Integer xToN(x);
        xToN.pow(n);
        Integer correction = (x*(two*(xToN - *this)))/(xToN*(n+one) + (*this)*(n-one));
        if (bool(correction))
            x = x - correction;
        else
            x += one;
        Integer exact = x, overShot = x+one;
        exact.pow(n);
        overShot.pow(n);
        if (exact.isEqualTo(*this) || this->isLessThan(overShot))
            break;
    }
    *this = x;
}

void Integer::pow(const Integer& _power) // Needs to be optimized
{
    static Integer one(1), two(2);
    if (!_power)
    {
        if (!(*this))
        {
            *this = one;
            return;
        }
        *this = one;
        return;
    }
    if (!(*this))
        return;
    if (_power.isNegative())
    {
        setToZero();
        return;
    }
    Integer power = _power, result = 1, temp = *this;
    while (one.isLessThan(power))
    {
        if (power.getModByOneUnit() & 1)
        {
            power -= one;
            result *= temp;
        }
        temp = temp*temp;
        power /= two;
    }
    result *= temp;
    *this = result;
}

} /* namespace Numbers */
} /* namespace DS */
