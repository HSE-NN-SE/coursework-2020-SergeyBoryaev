#include <iostream>
#include <string>

using namespace std;

class BigInt
{
private:
    string number;
    long long numberLen = number.size();

public:
    void EnterNumber(string enteredNumber)
    {
        number = enteredNumber;
    }
    void PrintNumber()
    {
        cout << "Your number is: " << number << endl;
    }
    long long GetLen()
    {
        return numberLen;
    }
    string GetNumber()
    {
        return number;
    }
    void AddNumber(BigInt c)
    {
        string secondNumber = c.GetNumber();
        long long lenDifference = numberLen - c.GetLen();
        if (lenDifference > 0)
            secondNumber.insert(0, lenDifference, '0');
        else
            number.insert(0, lenDifference, '0');
        short fission = 0;
        for (int i = numberLen; i >= 0; i--)
        {
            number[i] = ((number[i] + secondNumber[i]) - '0' * 2) % 10;
            fission = ((number[i] + secondNumber[i]) - '0' * 2) / 10;
            if (i)
                number[i - 1] += fission;
        }
        if (fission)
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