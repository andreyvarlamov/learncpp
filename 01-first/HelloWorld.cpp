#include <iostream> // Preprocessor directive

int main()
{
    // int x; // Variable definition
    // x = 5; // Assign value - copy assignment (copy RHS of the = operator to the variable on the LHS)

    // 1.4 - Variable initialization
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
    // int f { };
    // Use int x { 0 }; (explicit) if actually using that value
    // Use int x { }; if the value is temporary and to be replaced
    // (Convention)
    // Best practive is to always initialize variables upon creation (unless perf reasons)

    // If variable unused -> warning (and if -Werror -> error)
    // In C++17 - [[maybe_unused]] attribute
    [[maybe_unused]] int unused { 5 };

    // 1.5 - Intro to iostream
    // std::cout: Send data to the console to print as text (cout = "character output")
    // <<: Insertion Operator
    // E.g. std::cout << "Hello, world!";
    // Can also print numbers: std::cout << 4;
    // Can also print out the value of variables: int x { 5 }; std::cout << x;
    // Insertion operator can be used multiple times to concatenate
    // E.g. std::cout << "Hello" << " world!";
    // Also: int x { 5 }; std::cout << "x is equal to: " << x;
    // No end line with the insertion operator -> std::endl
    // e.g. std::cout << "Hi!" << std::endl; std::cout << "blah" << std::endl;

    // std::endl vs '\n'
    // std::endl does two jobs: moves cursor to next line; makes sure that cached output shows
    // up on the screen immediately (= flusing the output).
    // When writing text to the consolue using std::cout, it often flushes the output anyway
    // (and if it doesn't, it usually doesn't matter), so having std::endl perform a flush
    // is rarely important.
    // '\n' is typically preferred - more efficient (no flush requested)
    std::cout << "Hello, world!\n";

    // std::cin - "character input"; >> - "extraction operator"
    // std::cout << "Enter a num: "; int x { }; std::cin >> x; std::cout << "You entered " << x << '\n';
    // Note that you don't need to use '\n' when accepting input, as the user will need to
    // press the ENTER key to have their input accepted, and this will move the cursor
    // to the next line of the console
    std::cout << "Enter two numbers separated by a space: ";
    int x { };
    int y { };
    std::cin >> x >> y;
    std::cout << "You entered " << x << " and " << y << '\n';

    // iostream does not provide a way to accept keyboard input without the user having to
    // press ENTER. For console, use pdcurses, FXTUI, or cpp-terminal

    // 1.8 - Whitespace and basic formatting
    // If splitting a long line on the operator, the operator should be at the beginning
    // of the next line; not at the end of the current line
    // std::cout << 3 + 4
    //     + 5 + 6
    //     * 7 * 8;

    // 1.9 - Literals and operators
    // std::cout << "Hello world!"; int x { 5 };
    // literals ----^^^^^^^^^^^^^^----------^
    // Chaining operators
    // PEMDAS - Parenthesis, Exponents, Multiplication, Division, Addition, Subtraction
    // (Please execuse my dear aunt Sally)

    // 1.10 - Exressions
    // Sets of literal, variables, operators, function calls, that evaluate to a single value
    // type identifier { expression };
    // Also 'x = 5' - expression; 'x = 5;' - expression statement
    // An expression whose result is discarded - discarded-value expression

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
