// 3.1 - Errors
// Syntax errors - statement invalid according to the grammar rules of C++
// Semantiv errors - syntactically valid, but does not do what's intended
// --> Debugging

#include <iostream>

void print_value(int value)
{
    int x = 10;
    ++x;
    std::cout << value << " " << x << '\n';
}

int main()
{
    print_value(5);
    return 0;
}

// 3.4 - Basic Debugging Tactics
// Use std::cerr, instead of std::cout for debugging messages (unbuffered)

// gdb legend
// break main or break 11
// start
// continue
// step
// next
// finish (step over)
// info local, info args, info variables
// explore x
// backtrace
