#include <iostream>
#include "BigInt.h"

int main()
{
    BigInt a;
    BigInt b;
    std::cin >> a; 
    std::cin >> b;
    a = a / b;
    std::cout << b << "  " << a << "  " << std::endl;
}