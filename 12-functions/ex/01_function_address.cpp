#include <iostream>

int foo()
{
    return 5;
}

int main()
{
    // std::cout << foo << '\n'; // On gcc 9 this gives a warning

    // int (*fcnPtr)() { foo };
    // std::cout << fcnPtr << '\n'; // On gcc 9 prints 1

    std::cout << reinterpret_cast<void*>(foo) << '\n';
    // The function is in the text (code) segment of memory

    return 0;
}
