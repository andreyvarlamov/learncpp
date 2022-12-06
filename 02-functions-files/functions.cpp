// 2.1 - 2.6
// Main return codes: 0 or EXIT_SUCCESS; or EXIT_FAILURE -- preprocessor macros defined in <cstdlib> header

// A value-returning function that does not return (or not all paths returning) will only generate a warning.
// Main will return implicitly if the return statement is not provided

// Parameters - what function accepts; arguments - what is passed into the function when it's call
// When a function is called, all of the parameters of the function are created as variables,
// and the value of each of the arguments is copied into the matching parameter.
// ^ pass by value
// Object lifetime and scope - lifetime is a runtime property; scope is a compile-time property
//
// 2.7 - Forward declarations
// The compiler compiles the contents of code files sequentially.
// If the forward declaration is made, but the function is never called, the program
// will compile and run fine.
// However, if forward declaration is made and the function is called, the program will compile,
// but the linker will complain that it can't resolve the function call.
// In C++, all defninitions also serve as declarations. In most cases a definition satisfies
// both the compiler and the linker. We only need to provide an explicit declaration when
// we want to use an identifier before it's been defined.
// Declarations that are not definitions are called pure declarations.
// Can have as many pure declarations for an identifier as we want, although redundant.
// In common language, "declaration" usually refers to pure declaration. And "definition"
// refers to a definition that is also a declaration.

# include <iostream>

int getValueFromUser()
{
    std::cout << "Enter on integer: ";
    int input {};
    std::cin >> input;

    return input;
}

void printDouble(int value); // function declaration (function prototype) - compiler
                             // can also do void printDouble(int);
                             // but best practice is to just keep the param name

int main()
{
    int num { getValueFromUser() };

    printDouble(num);

    return 0;
}

void printDouble(int value) // function definition - linker
{
    std::cout << value << " doubled is: " << value * 2 << '\n';
}
