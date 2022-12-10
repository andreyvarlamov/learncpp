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
