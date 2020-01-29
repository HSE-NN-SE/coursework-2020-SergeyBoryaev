#include <iostream>
#include <string>

using namespace std;

class BigInt
{
private:
    string number;

public:
    void EnterNumber(string enteredNumber)
    {
        number = enteredNumber;
    }
    void PrintNumber()
    {
        cout << "Your number is: " << number << endl;
    }
    string GetNumber()
    {
        return number;
    }
    void AddNumber(BigInt c)
    {
        string secondNumber = c.GetNumber();
        long long lenDifference = number.size() - secondNumber.size();
        if (lenDifference > 0)
            secondNumber.insert(0, lenDifference, '0');
        else
            number.insert(0, lenDifference, '0');
        short fission = 0;
        for (int i = (number.size() - 1); i >= 0; i--)
        {
            number[i] = (((number[i] - '0') + (secondNumber[i] - '0')) % 10) + '0';
            fission = (((number[i] - '0') + (secondNumber[i] - '0')) / 10) + '0';
            if (i)
                number[i - 1] += fission - '0';
        }
        if (fission != '0')
            number.insert(0, 1, '1');
    }
};

int main()
{
    string str1, str2;
    cin >> str1 >> str2;
    BigInt firstNumber, secondNumber;
    firstNumber.EnterNumber(str1);
    secondNumber.EnterNumber(str2);
    firstNumber.PrintNumber();
    secondNumber.PrintNumber();
    firstNumber.AddNumber(secondNumber);
    firstNumber.PrintNumber();
}