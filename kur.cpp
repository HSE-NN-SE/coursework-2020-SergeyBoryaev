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
        cout << "Your number is: " << number;
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
        string secondNumber = c.GetNumber;
        long long lenDifference = numberLen - c.GetLen();
        if (lenDifference > 0)
            secondNumber.insert(0,lenDifference,'0');
        else
            number.insert(0,lenDifference,'0');
        
        
    }
}