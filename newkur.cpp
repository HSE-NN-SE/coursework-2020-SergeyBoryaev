#include <iostream>
#include "BigInt.h"

int main()
{
    BigInt a;
    BigInt b;
    std::cin >> a; 
    BigInt c = a + b;
    a = a - b;
    a = a * b;
    std::cout << b << "  " << a << "  " << c << std::endl;
}