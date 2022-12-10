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

    return 0;
}

