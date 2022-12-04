#include <iostream>

int main()
{
    std::cout << "Hello, world!";
    return 0;
}

// g++ is equivalent to gcc -xc++ -lstdc++ -shared-libgcc
// To disable compiler extensions, add -pedantic-errors to compile command
// To show more warnings:
// -Wall: enable all common compiler warnings
// -Weffc++: effective-c++ warnings (Scott Meyers)
// -Wextra: extra compiler warnings
// -Wsign-conversion
// -Werror: treat errors as warnings
// -std=c++11, -std=c++14, -std=c++17, -std=c++20 to support that language standard
// For GCC 8 or 9, use -std=c++2a for c++20
//
// In the end: g++ -o HelloWorld.out HelloWorld.cpp -std=c++2a -pedantic-errors -Wall -Weffc++ -Wextra -Wsign-conversion -Werror
