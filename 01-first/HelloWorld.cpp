#include <iostream> // Preprocessor directive

int main()
{
    // int x; // Variable definition
    // x = 5; // Assign value - copy assignment (copy RHS of the = operator to the variable on the LHS)

    // Variable initialization
    // No initializer - default initialization - in most cases, leaves a variable with an indeterminate value
    // int a;
    // Copy initialization
    // Not used much in modern C++
    // int b = 5;
    // Direct initialization
    // Was initially introduced to allow for more efficient initialization of complex objects
    // Not used much in modern C++
    // int c( 5 );
    // Brace initialization (or uniform initialization or list initialization)
    // Prior to the introduction of brace initialization, some types of initialization required
    // copy initiation, and others - direct.
    // Brace initialization works in most cases
    // Additionally provides a way to initialize object with a list of values
    // Disallows "narrowing conversions": if you try to brace initialize a variable using
    // a value that the variable can not safely hold, the compiler will produce an error.
    // E.g. int width { 4.5 }; -> error
    // Whereas int width = 4.5; (or direct) -> drop the fractional part
    // The modern way to initialize; should be used by default
    // int d { 5 }; // Direct brace initialization (preferred)
    // int e = { 6 }; // copy brace initialization

    // Value initialization and zero initialization
    // Empty braces -> value initialization; in most cases will initialize to zero (or
    // empty, if that's more appropriate for a given type).
    // If initializing to zero -> zero initialization
    // int f {};
    // Use int x { 0 }; (explicit) if actually using that value
    // Use int x {}; if the value is temporary and to be replaced
    // (Convention)
    // Best practive is to always initialize variables upon creation (unless perf reasons)

    // If variable unused -> warning (and if -Werror -> error)
    // In C++17 - [[maybe_unused]] attribute
    [[maybe_unused]] int x { 5 };

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

/*
 * Multiline
 * Comment
 * */
