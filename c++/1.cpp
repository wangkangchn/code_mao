#include <iostream>

int main()
{   
    int a = 1, b = 10;
    int c = a << b;
    std::cout << c << std::endl;
    std::cout << a << b << std::endl;

    c = -b >> 1; /* 1010 */
    std::cout << c << std::endl;
    int d = 1024;
    std::cout << (d >> 11) << std::endl;

    return 0;
}