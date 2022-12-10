// 4.1
// Smallest unit of memory - a binary digit (bit)
// Memory is organized into sequential units called memory addresses
// Each memory address usually holds 1 byte of data (8 bits)

// E.g.
// ...          ...
// Address 3    11101000
// Address 2    00000000
// Address 1    10010111
// Address 0    01101001

// Data type tells the compiler how to interpret the contents of memory in some meaninful
// way.

// In C++ strings are not a fundamental type, but are a compound type

// The _t suffix
// Many of the types defined in newer versions of C++ (e.g. std::nullptr_t) use a _t
// suffix. It means "type", and it's a common nomenclature applied to modern types.

// 4.2 - Void
// Variables can't be void
// Functions that return nothing
// Functions that do not take params (deprecated)

// 4.3 - Object sizes and the sizeof operator
// The size of a given data type is dependent on the compiler and/or the computer
// architecture. C++ only guarantees that each fundamental data types have a minimum size.
//
// Category    	Type        Min Size        Note
// boolean     	bool        1 byte
// character   	char        1 byte          Always exactly 1 byte
//             	wchar_t     1 byte
//             	char16_t    2 byte
//             	char32_t    4 byte
// integer     	short       2 bytes
//             	int         2 bytes
//             	long        4 bytes
//             	long long   8 bytes
// floating pt.	float       4 bytes
//             	double      8 bytes
//             	long double 8 bytes

// sizeof operator is a unary operator that takes either a type or a variable and
// returns its size in bytes

#include <iostream>

int main()
{
    std::cout << "bool:\t\t" << sizeof(bool) << " bytes\n";
    std::cout << "char:\t\t" << sizeof(char) << " bytes\n";
    std::cout << "wchar_t:\t" << sizeof(wchar_t) << " bytes\n";
    std::cout << "char16_t:\t" << sizeof(char16_t) << " bytes\n";
    std::cout << "char32_t:\t" << sizeof(char32_t) << " bytes\n";
    std::cout << "short:\t\t" << sizeof(short) << " bytes\n";
    std::cout << "int:\t\t" << sizeof(int) << " bytes\n";
    std::cout << "long:\t\t" << sizeof(long) << " bytes\n";
    std::cout << "long long:\t" << sizeof(long long) << " bytes\n";
    std::cout << "float:\t\t" << sizeof(float) << " bytes\n";
    std::cout << "double:\t\t" << sizeof(double) << " bytes\n";
    std::cout << "long double:\t" << sizeof(long double) << " bytes\n";

    std::cout << "\nC+11:\n" << '\n';
    std::cout << "least 8:  " << sizeof(std::int_least8_t) * 8 << " bits\n";
    std::cout << "least 16: " << sizeof(std::int_least16_t) * 8 << " bits\n";
    std::cout << "least 32: " << sizeof(std::int_least32_t) * 8 << " bits\n";
    std::cout << '\n';
    std::cout << "fast 8:  " << sizeof(std::int_fast8_t) * 8 << " bits\n";
    std::cout << "fast 16: " << sizeof(std::int_fast16_t) * 8 << " bits\n";
    std::cout << "fast 32: " << sizeof(std::int_fast32_t) * 8 << " bits\n";

    std::cout << "\nsize_t: " << sizeof(std::size_t) << " bytes\n";

    return 0;
}

// 4.4 - Signed integers
// Sign bit
// (short int=short)
// integral types are signed by default (signed short/int=short/int)

// Integer overflow
// -> Undefined results

// Integer division
// Fractional portion is simply dropped

// 4.5 - Unsigned integers
// unsigned int ui;
// Unsigned integer overflow - wraps around
// store 280 in 1 byte (0-255) -> 280 / 256 = 1; remainder 24 -> 24 is stored
// Compiler will issue warnings about overflow or truncation
// Can wrap around the other way too
// Many developers (and some large development houses, such as Google) believe that
// developers should generally avoid unsigned integers.
// Subtraction of 2 unsigned numbers; decrementing by one, etc. - all dangerous
// Mixing signed and unsigned integers. In a mathematical operation in C++
// (arithmetic or comparison), the signed integer will be converted to unsigned, and because
// unsigned integers can not store negative numbers, this can result in loss of data.
// Compiler should warn about a signed/unsigned mismatch.

// Also function parameters void doSomething(unsigned int x)
// Can pass -1 - will wrap around, no good way to guard against it
// Best to avoid unsigned types except in specific circumstances.

// What it's useful for?
// Preferred when dealing with bit manipulation
// When well-defined wrap-around behavior is required (e.g. in ecryption and random
// number generator).
// Unsigned numbers is still unavoidable in some cases, e.g. array indexing.

// 4.6 - Fixed-width integers and size_t
// Why isnt' the size of the integer variables fixed?
// Goes back to C, when computers were slow and performance was of the utmost concern.
// C opted to intentionally leave the size of an integer open so that the compiler implementers
// could pick a size for int that performs best on target computer architecture.

// By modern this sucks. Can't assume int is 4 bytes, even though it's most likely, because
// then the program will misbehave on architectures where int is actually 2 bytes.

// C99 defined a set of fixed-width integers (in the stdint.h header) - guaranteed to
// be the same size on any architecture.

// std::int8_t      1 byte signed
// std::uint8_t     1 byte unsigned
// std::int16_t     2 byte signed
// std::uint16_t    2 byte unsigned
// std::int32_t     4 byte signed
// std::uint32_t    4 byte unsigned
// std::int64_t     8 byte signed
// std::uint64_t    8 byte unsigned

// C++ officially adopted these fixed-width integers as part of C++11
// Can be accessed by including the <cstdint> header, where they are defined inside the
// std namespace.

//#include <cstdint>
//#include <iostream>
//
//int main()
//{
//    std::int16_t i { 5 };
//    std::cout << i;
//    return 0;
//}

// 2 downsides:
// 1) not guaranteed to be defined on all architectures. But most modern architectures
// have standardized around 8/16/32/64-bit variables.
// 2) may be slower than a wider type on some architectures.

// Fast and least integers
// To help address the above downsides, C++ also defines two alternative sets of integers
// that are guaranteed to be defined.
// Fast - fastest signed/unsigned integer type with a width of at least # bits
// Least - the smallest signed/unsigned integer type with a width of at least # bits.
// std::int_least8_t
// std::int_least16_t
// std::int_least32_t
// std::int_fast8_t
// std::int_fast16_t
// std::int_fast32_t
// On my system fast 8 = 8 bits; fast 16 = 64 bits; fast 32 = 64 bits

// std::int8_t and std::uint8_t likely to behave like chars instead of integers.
// Due to an oversight in the C++ specification, most compilers define and treat those
// (and the corresponding fast and least fixed-width types) identically to types signed
// char and unsigned char respectively.
// This means that those types may or may not behave differently thatn the rest of the
// fixed-width types, which can lead to errors. System-dependent behavior.
// Best to avoid using these

// Integral best pracices
// Prefer int when the size of the integer doesn't matter (i.e. the number will always
// fit within the range of a 2-byte signed integer)
// Prefer std::int#_t when storing a qunatity that needs a guaranteed range
// Prefer std::uint#_t when doing bit manipulation or where well-defined wrap-around
// behavior is required.
// Avoid the following when possible:
// Unsigned types for holding quantities
// The 8-bit fixed-width integer types
// The fast and least fixed-width types
// Any compiler-specific fixed-width integers - for example, Visual Studio defines __int8,
// __int16, etc.

// sizeof returns a value of type std::size_t - an unsigned integral type
// Can do sizeof of size_t. Also depends on the machine. Guaranteed to be unsigned and at
// least 16 bits.
// On most systems will be equivalent to the address-width of the application.
// That is, for 32-bit applications, size_t will typically be a 32-bit unsigned integer.
// For 64-bit - 64-bits unsigned integer.
// size_t is defined to be big enough to hold the size of the largest object creatable
// on your system (in bytes).
// By definition, any object with a size (in bytes) larger that the largest integral value
// size_t can hold is considered ill-formed (and will cause a compile error).

// 4.8 - Floating point numbers
// "floating" - supports a variable number of digits before and after the decimal point.
// On modern architectures, almost always follows IEEE 754

// Category         Type        Min size    Typical size
// floating point   float       4 bytes     4 bytes
//                  double      8 bytes     8 bytes
//                  long double 8 bytes     8, 12, or 16 bytes

// When using floating point literals, always include at least one decimal place, to help
// the compiler understand that the number is a floating point number and not an integer.
// int x { 5 };
// double y { 5.0 }; // no suffix - double
// float z { 5.0f }; // f suffix - float

// Printing out
// std::cout << 5.0 << '\n'; // 5 - by default std::cout will not print the fractional
// std::cout << 6.7 << '\n'; // 6.7
// std::cout << 9876543.21 << '\n'; // 9.87654e+06

// Floating point precision
// Number of significant digits (9.87654)

// size            Range                         Precision
// 4 bytes         +-1.18E-38 to +-3.4E38        6-9 sig digits (typically 7)
// 8 bytes         +-2.23E-308 to +- 1.80E308    15-18 sig digits (typically 16)
// 80 bits (typ.   +-3.36E-4932 to +-1.18E4932   18-21 sig digits
//   uses 12 or
//   16 bytes)
// 16 bytes        +-3.36E-4932 to +-1.18E4932   33-36 sig digits

// We can override the default precision that std::cout shows by using an `output
// manipulator` - std::setprecision(). Defined in iomanip header.
// std::cout << std::setprecision(16);
// std::cout << 3.33...f << '\n'; // Will be output with 16 digits of precision
// But won't be actually precise to 16 digits! And floats are less precise than doubles.
// std::cout << std::setprecision(16);
// std::cout << 3.3333333333333333333f << '\n'; // 3.333333253873693
// std::cout << 3.3333333333333333333 << '\n'; // 3.333333333333334
// Loss of precision will also affect large numbers
// Best practice - favor double over float unless space is at a premium.

// Rounding errors make floating point comparisons tricky.
// E.g. in decimal representation: 0.1; in binary: infinite sequence:
// 0.00011001100110011...
// std::cout << 0.1 << '\n'; // double, using the default cout precision of 6
// std::cout << std::setprecision(17);
// std::cout << 0.1 << '\n';
// Outputs:
// 0.1
// 0.10000000000000001
// Comparing floating point numbers is generally problematic - will be discussed more
// later.

// NaN and Inf
//#include <iostream>
//
//int main()
//{
//    double zero { 0.0 };
//    double posinf { 5.0 / zero }; // positive infinity
//    std::cout << posinf << '\n';
//
//    double neginf {-5.0 / zero }; // negative infinity
//    std::cout << neginf << '\n';
//
//    double nan { zero / zero }; // not a number (mathematically invalid)
//    std::cout << nan << '\n';
//
//    return 0;
//}

// Outputs (using VS 2008 on Windows):
// 1.#INF
// -1.#INF
// 1.#IND
// IND = Indeterminate
// Platform specific

// 4.9 - Boolean
// To print out "true" or "false" instead of 0 or 1 in std::cout:
// std::cout << true << '\n'; // Output: 1
// std::cout << std::boolalpha;
// std::cout << true << '\n'; // Output: true

// Int to bool
// bool b { 4 }; // Brace initialization disallows narrowing conversions -> error
// bool b1 = 4; // Copy initialization allows implicit conversion from int to bool -> true
// bool b2 = 0; // -> false
// b1 may generate a warning

// To input bool:
// By default accepts only 0 or 1, anything else -> silently fail
// To allow to accept "false" and "true", set std::cin >> std::boolapha;
// With it enabled, 0 and 1 will no longer be treated as booleans

// 4.10 - Introduction to if statements
// Expression that does not evaluate to a Boolean value gets converted
// if (4) - true

// 4.11 - Chars
// Integral type
// The integer stored by a char variable is interpreted as an ASCII character
// American Standard Code for Information Interchange
// Between numbers 0 and 127 (ASCII code or code point)
// Codes 0-31 - unprintable chars, obsolete

// std::cin - can input many chars, but if extracted into char, will hold only the first one
// Always 1 byte in size

// Escape sequences:
// Name                 Symbol      Meaning
// Alert                \a          Makes an alert, such as a beep
// Backspace            \b          Moves the cursor back one space
// Formfeed             \f          Moves the cursor to the next logical page
// Newline              \n          Moves cursor to next line
// Carriage return      \r          Moves cursor to beginning of line
// Horizontal tab       \t          Prints a horizontal tab
// Vertical tab         \v          Prints a vertical tab
// Signle quote         \'          Prints a single quote
// Double quote         \"          Prints a double quote
// Question mark        \?          Prints a question mark
//                                      No longer relevant. Can use unescaped.
// Octal number         \(number)   Translates into char represented by octal
// Hex number           \x(number)  Translates into char represented by hex number


// Best practice is to always put stand-alone chars in single quotes. This helps
// compiler optimize more effectively.

// Avoid multicharacter literals (e.g. '56')
// For backwards compatibility reasons, not part of the C++ standard

// Other char types
// wchar_t should be avoided in almost all cases (except when interfacing with the
// Windows API). Has largely been deprecated.
// char16_t and char32_t were added to C++11 to provide explicit support for 16-bit and
// 32-bit Unicode characters
// char8_t has been added in C++20

// 4.12 - Introduction to type conversion and static_type
// Type conversion
// Implicit type conversion - when the compiler does type conversion on our behalf.

// Type conversion produces a new value

// A few cases where implicit type conversion is not sufficient
// E.g. passing a double to a function that accepts int
// Will generate a warning about possible loss of data
// -> Unsafe implicit conversion

// Explicit type conversion via static_cast operator
// static_cast<new_type>(expression)
// Can static cast double to int, that will not generate a warning
// Can static cast char to int
// Can static cast unsigned numbers to signed numbers
//      Does not do any range checking. unsigned int -> unpredictable results if
//      the value of the unsigned int is greater than the maximum value a signed int can hold.

// (Repeat) std::int8_t and std::uint8_t behave like chars in most compilers
// E.g. when doing std::cout
// Can static cast to int to output as a number

// 4.13 - Const variables and symbolic constants
// const double gravity { 9.8 };
// must be initialized

// Naming convention
// Programmers who have transitioned from C often prefer underscored, upper-case names for
// const variables (e.g. EARTH_GRAVITY). More common in C++ is to use intercapped names
// with a 'k' prefix (e.g. kEarthGravity)
// But because const variables act like normal variables (except they can not be assigned
// to), there is no reason that they need a special naming convention. For this reason,
// this guide suggests to use the same naming convention as for non-const variables

// Function params can be made constant, e.g. void printInt(const int x)
// But when arguments are passed by value, there's usually no reason to make them const,
// because we don't care if the function changes the original value.

// A function's return value may also be made coonst
// However, since the returned value is a copy, there's little point in making it const.
// It can also impede certain kinds of compiler optimizations.

// For symbolic constants, prefer constant variables to object-like macros.
// Harder to debug.
// Macros can have naming conflicts.

// 4.14 - Compile-time constants, contant expressions and constexpr
// A constant expression is an expression that can be evaluated by the compiler at
// compile-time
// To be a constant expression, all the values in the expression must be known at
// compile-time (and all of the operators and functions called must support compile-
// time evaluation).
// Modern compilers will usually evaluate a constant expression at compile-time

// Compile-time constant  - a constant whose value is know at compile-time
// Const variables may or may not be compile-time consants.
// A const variable is a compile-time constant if its initializer is a constant expression.

// Runtime const - any const variable that is initialized with a non-constant expression.
// E.g. initialized with a return of a function

// constexpr keyword - varaiable can only be a compile-time constant.
// If the initialization value of constexpr variable is not a constant expression, the
// compiler will error.
// Best practice is to use both constexpr and const, (whenever possible?)

// Compilers have long been able to optimize constant subexpressions, including constexpr
// variables). This optimization process is called "constant folding".
