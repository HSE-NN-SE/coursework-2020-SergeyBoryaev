#include <iostream>
#include <cmath>
#include <vector>
#include <string>

using namespace std;

class BigInt
{
private:
    vector<int> numbers;
    bool sign;
    static const int numberBase = 10000; // 10000*10000=100000000-max in int

protected:
    BigInt UnsignAddNumber(BigInt b)
    {
        BigInt a;
        a = (*this);
        int remainder = 0;
        for (long i = 0; i < max(a.numbers.size(), b.numbers.size()); i++)
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

    BigInt UnsignDeductionNumber(BigInt b)
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

    bool UnsignCompare(BigInt b)
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

public:
    void MakeNumber()
    {
        cout << "Enter the number" << endl;
        string number;
        cin >> number;
        sign = 0;

        if (number[0] == '-')
        {
            sign = 1;
            number = number.substr(1);
        }
        for (int i = number.size(); i > 0; i -= 4)
        {
            if (i >= 4)
                numbers.push_back(atoi(number.substr(i - 4, 4).data()));
            else
                numbers.push_back(atoi(number.substr(0, i).data()));
        }
    }

    void PrintNumber()
    {
        cout << "The number is:" << endl;
        if (sign == 1)
            cout << '-';
        printf("%d", numbers.empty() ? 0 : numbers.back());
        for (int i = (int)numbers.size() - 2; i >= 0; i--)
            cout << numbers[i];
        cout << endl;
    }

    BigInt operator+(BigInt &b)
    {
        BigInt temp;
        if (this->sign == b.sign)
        {
            temp = (this->UnsignAddNumber(b));
        }
        else
        {
            if (this->UnsignCompare(b))
                temp = (this->UnsignDeductionNumber(b));
            else
            {
                temp = (b.UnsignDeductionNumber(*this));
                temp.sign = b.sign;
            }
        }
        return temp;
    }

    BigInt operator-(BigInt &b)
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

    BigInt operator*(BigInt &b)
    {
        BigInt temp;
        if (this->sign == b.sign)
            temp.sign = 0;
        else
            temp.sign = 1;
        temp.numbers.resize(this->numbers.size() + b.numbers.size());
        for (int i = 0; i < this->numbers.size(); i++)
            for (int j = 0, remainder = 0; j < (int)b.numbers.size() || remainder; ++j)
            {
                long long cur = temp.numbers[i + j] + this->numbers[i] * 1ll * (j < (int)b.numbers.size() ? b.numbers[j] : 0) + remainder;
                temp.numbers[i + j] = int(cur % this->numberBase);
                remainder = int(cur / this->numberBase);
            }
        while (temp.numbers.size() > 1 && temp.numbers.back() == 0)
            temp.numbers.pop_back();
        return temp;
    }

    BigInt operator/(BigInt &b)
    {
    }

    bool operator==(BigInt &b)
    {
        if (this->sign == b.sign && this->numbers == b.numbers)
            return 1;
        return 0;
    }

    bool operator!=(BigInt &b)
    {
        return !((*this) == b);
    }

    bool operator>=(BigInt &b)
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

    bool operator<=(BigInt &b)
    {
        return !((*this) > b);
    }

    bool operator>(BigInt &b)
    {
        if ((*this) >= b && ((*this) != b))
            return 1;
        return 0;
    }

    bool operator<(BigInt &b)
    {
        return !((*this) >= b);
    }
};

int main()
{
    BigInt a;
    BigInt b;
    a.MakeNumber();
    b.MakeNumber();
    printf("%d\n", a == b);
    BigInt c = a + b;
    a = a - b;
    a.PrintNumber();
    b.PrintNumber();
    c.PrintNumber();
    a = a * b;
    a.PrintNumber();
}