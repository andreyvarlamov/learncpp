#include <iostream>

// Or if doing it with a function, could accept const char* str. This is low-level const.
// So cannot change the underlying value of what the pointer points to. But can still
// change the pointer itself. The argument-pointer is a copy of the paremeter-pointer.
// So if a char* str was passed into the function, the original pointer in main would
// not be lost.
// void printCString(const char* str) { ... }

int main()
{
    char str[] { "Hello" };

    char* str_start { str };
    while (*str_start != '\0')
    {
        std::cout << *str_start << ' ';
        ++str_start;
    }

    std::cout << '\n';

    return 0;
}
