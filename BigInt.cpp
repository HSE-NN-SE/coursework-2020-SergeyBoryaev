#include "BigInt.h"

std::vector<unsigned> karatsubaMul(const std::vector<unsigned>& x, const std::vector<unsigned>& y);

BigInt BigInt::UnsignAddNumber(const BigInt &b) const
{
    BigInt a;
    a = (*this);
    int remainder = 0;
    for (long i = 0; i < std::max(a.numbers.size(), b.numbers.size()); i++)
    {
        if (i == a.numbers.size())
            a.numbers.push_back(0);
        a.numbers[i] += remainder + (i < b.numbers.size() ? b.numbers[i] : 0);
        remainder = a.numbers[i] >= numberBase;
        if (remainder)
            a.numbers[i] -= numberBase;
    }
    if (remainder)
        a.numbers.push_back(1);
    return a;
}

BigInt BigInt::UnsignDeductionNumber(const BigInt &b) const
{
    BigInt a;
    a = (*this);
    int remainder = 0;
    for (long i = 0; i < b.numbers.size() || remainder; ++i)
    {
        a.numbers[i] -= remainder + (i < b.numbers.size() ? b.numbers[i] : 0);
        remainder = a.numbers[i] < 0;
        if (remainder)
            a.numbers[i] += remainder;
    }
    while (a.numbers.size() > 1 && a.numbers.back() == 0)
        a.numbers.pop_back();
    return a;
}

bool BigInt::UnsignCompare(const BigInt &b) const
{
    if (numbers.size() > b.numbers.size())
        return 1;
    if (numbers.size() < b.numbers.size())
        return 0;
    int i = 0;
    for (; i < numbers.size(); i++)
        if (numbers[i] != b.numbers[i])
            break;
    if (numbers[i] >= b.numbers[i])
        return 1;
    return 0;
}

//конструкторы
BigInt::BigInt()
{
    this->numbers.push_back(0);
    this->sign = 0;
}

BigInt::BigInt(const std::string str)
{
    std::string number = str;
    BigInt a;
    if (number[0] == '-')
    {
        this->sign = 1;
        number = number.substr(1);
    }
    for (int i = number.size(); i > 0; i -= 4)
    {
        if (i >= 4)
            this->numbers.push_back(atoi(number.substr(i - 4, 4).data()));
        else
            this->numbers.push_back(atoi(number.substr(0, i).data()));
    }
}

//операции
BigInt BigInt::operator+(const BigInt &b) const
{
    BigInt temp;
    if (this->sign == b.sign)
    {
        temp = (this->UnsignAddNumber(b));
    }
    else
    {
        if ((*this) >= b)
            temp = (this->UnsignDeductionNumber(b));
        else
        {
            temp = (b.UnsignDeductionNumber(*this));
            temp.sign = b.sign;
        }
    }
    return temp;
}

BigInt BigInt::operator-(const BigInt &b) const
{
    BigInt temp;
    if (this->sign != b.sign)
        temp = (this->UnsignAddNumber(b));
    else
    {
        if (this->UnsignCompare(b))
            temp = (this->UnsignDeductionNumber(b));
        else
        {
            temp = (b.UnsignDeductionNumber(*this));
            temp.sign = !(b.sign);
        }
    }
    return temp;
}

BigInt BigInt::operator*(const BigInt &b) const
{
    BigInt temp;
    if(this->sign!=b.sign)
        temp.sign = 1;
    temp.numbers = karatsubaMul(this->numbers, b.numbers);
    return temp;
}

BigInt BigInt::operator/(const BigInt &b) const
{
}

BigInt BigInt::operator-() const
{
    BigInt temp = (*this);
    temp.sign = !temp.sign;
    return temp;
}

BigInt BigInt::abs() const
{
    BigInt temp = (*this);
    temp.sign = 0;
    return temp;
}

//булевые операции
bool BigInt::operator==(const BigInt &b) const
{
    if (this->sign == b.sign && this->numbers == b.numbers)
        return 1;
    return 0;
}

bool BigInt::operator!=(const BigInt &b) const
{
    return !((*this) == b);
}

bool BigInt::operator>=(const BigInt &b) const
{
    if (this->sign == 0)
    {
        if (b.sign == 1)
            return 1;
        return this->UnsignCompare(b);
    }
    if (b.sign == 0)
        return 0;
    return !(this->UnsignCompare(b));
}

bool BigInt::operator<=(const BigInt &b) const
{
    return !((*this) > b);
}
bool BigInt::operator>(const BigInt &b) const
{
    if ((*this) >= b && ((*this) != b))
        return 1;
    return 0;
}

bool BigInt::operator<(const BigInt &b) const
{
    return !((*this) >= b);
}

//in/out
std::ostream &operator<<(std::ostream &stream, const BigInt &b)
{
    if (b.sign == 1)
        stream << '-';
    for (int i = (int)b.numbers.size() - 1; i >= 0; i--)
        stream << b.numbers[i];
}

std::istream &operator>>(std::istream &stream, BigInt &b)
{
    std::string str;
    stream >> str;
    b = BigInt(str);
    return stream;
}

// Алгоритм умножения
std::vector<unsigned> naive_mul(const std::vector<unsigned>& x, const std::vector<unsigned>& y) {
        auto len = x.size();
        std::vector<unsigned> res(2 * len);
        
        for (auto i = 0; i < len; ++i) {
            for (auto j = 0; j < len; ++j) {
                res[i + j] += x[i] * y[j];
            }
        }
        
        return res;
    }

std::vector<unsigned> karatsubaMul(const std::vector<unsigned>& x, const std::vector<unsigned>& y) {
        auto len = x.size();    
        std::vector<unsigned> res(2 * len);
        
        auto k = len / 2;
        
        if (len <= 4) {
            return naive_mul(x, y);
        }

        std::vector<unsigned> Xr {x.begin(), x.begin() + k};
        std::vector<unsigned> Xl {x.begin() + k, x.end()};
        std::vector<unsigned> Yr {y.begin(), y.begin() + k};
        std::vector<unsigned> Yl {y.begin() + k, y.end()};
        
        std::vector<unsigned> P1 = karatsubaMul(Xl, Yl);
        std::vector<unsigned> P2 = karatsubaMul(Xr, Yr);    
            
        std::vector<unsigned> Xlr(k);
        std::vector<unsigned> Ylr(k);
        
        for (auto i = 0; i < k; ++i) {
            Xlr[i] = Xl[i] + Xr[i];
            Ylr[i] = Yl[i] + Yr[i];
        }
        
        std::vector<unsigned> P3 = karatsubaMul(Xlr, Ylr);
        
        for (auto i = 0; i < len; ++i) {
            P3[i] -= P2[i] + P1[i];
        }
        
        for (auto i = 0; i < len; ++i) {
            res[i] = P2[i];
        }

        for (auto i = len; i < 2 * len; ++i) {
            res[i] = P1[i - len];
        }

        for (auto i = k; i < len + k; ++i) {
            res[i] += P3[i - k];
        }
        
        return res;
    }