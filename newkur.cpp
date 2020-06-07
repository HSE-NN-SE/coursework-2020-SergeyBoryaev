#include <iostream>
#include "BigInt.h"

int main()
{
    BigInt b;
    std::string str;
    std::cin >> str;
    std:: cout << str;
    BigInt a(str);
    std::cout << "B: ";
    std::cin >> b;
    std::cout << "A: " << a << std::endl;
    std::cout << "B: " << b << std::endl;
    std::cout << "A+B: " << a+b << std::endl;
    std::cout << "A: " << a << std::endl;
    std::cout << "B: " << b << std::endl;
    std::cout << "A-B: " << a - b << std::endl;
    std::cout << "A: " << a << std::endl;
    std::cout << "B: " << b << std::endl;
    std::cout << "A*B: " << a * b << std::endl;
    std::cout << "A: " << a << std::endl;
    std::cout << "B: " << b << std::endl;
    std::cout << "A/B: " << a / b << std::endl;
    std::cout << "A: " << a << std::endl;
    std::cout << "B: " << b << std::endl;
}