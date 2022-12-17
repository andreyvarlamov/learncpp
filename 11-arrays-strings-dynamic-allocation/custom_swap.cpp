// 11.x - Q3

#include <iostream>

void swap_custom(int& a, int& b)
{
    int temp { a }; // copy the value of a into a new place of memory (on the stack) - temp
    a = b; // copy the value of b into a's memory address
    b = temp; // copy the value of temp into b's memory address
}

int main()
{
    int a { 10 };
    int b { 100 };

    std::cout << "Swapping variables: a = " << a << " and b = " << b << '\n';
    std::cout << "At the address: &a = " << &a << " and &b = " << &b << '\n';

    swap_custom(a, b);

    std::cout << "After Swap: a = " << a << " and b = " << b << '\n';
    std::cout << "At the address: &a = " << &a << " and &b = " << &b << '\n';
    return 0;
}
