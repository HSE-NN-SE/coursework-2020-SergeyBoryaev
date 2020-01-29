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
    void AddNumber(BigInt c)
    {
        
    }
}