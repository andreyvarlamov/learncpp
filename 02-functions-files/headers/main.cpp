// 2.11 - Header files
// Put all forward declarations in one place and import them when you need them

// # include <iostream> // std::cout has been forward declared in the iostream header file
                        // requesting that the preprocessor copy all of the content (including
                        // forward declarations for std::cout) from the file named iostream
                        // into the file doing the #include

// int main()
// {
//     std::cout << "Hello";
//     return 0;
// }

// main.cpp --- #include <iostream> ---
//     |                              |
//     |                              |
//     V                              V
//  Compile <--------------- iostream (header file)
//     |
//     |
//     V
//   main.o
//     |
//     |
//     V
//    Link <-------- Standard Runtime Library
//     |
//     |
//     V
// main.exe

#include "add.h"
#include <iostream>

int main()
{
    std::cout << "The sum of 3 and 4 is " << add(3, 4) <<'\n';
    return 0;
}

// Source files should include their paired header - best practice; allows the compiler
// to catch certain kinds of errors at compile time instead of link time

// Angled brackets vs double quotes
// It's possible that a header file with the same filename might exist in multiple
// directories.
// Angled - search for the header only in the directories specified by the include
// directories (part of project/IDE settings/compiler settings). Will not search for the 
// header file in source code directory
// Double-quotes - first search in the current directory, then in the include directories

// Why doesn't iostream have a .h extension?
// iostream.h is a different header file than iostream.
// First all files in the standard library had .h suffix. Then the language was standardized
// by the ANSI committee, and they decided to move all of the names used in the standard
// library into the std namespace to help avoid naming conflicts with user-defined
// identifiers. But if they moved all the names into the std namespace, none of the old
// programs would work. To work around this, a new set of header files was introduced that
// lack the .h extension. They define all names inside the std namespace.
// In addition to this, libraries inherited forom C that are still useful in C++ were
// given a c prefix (stdlib.h -> cstdlib.h), and the names moved to std namespace

// Including header files from other directories.
// Bad way to do it is to use relative path e.g. #include "headers/header.h".
// Downside is that if directory structure is updated, the source code won't work anymore.
// Better way is setting an include path or search directory
// For g++ - -I option

// Header files can include other header files -- transitive includes
// However, each file should still explicitly #include all of the header fiels it needs
// to compile, and not rely on transitive includes. (included headers could be changed)

// Order: best practice - to maximize the chance that missing includes will be flagged by
// compiler, order of includes should be as follows:
// 1) The paired header file
// 2) Other header from your project
// 3) 3rd part library headers
// 4) Standard library headers
// Within each grouping, headers should be sorted alphabetically.
// That way, if one of your user-defined headers is missing an #include for a 3rd party
// library or standard library header, it's more likely to cause a compile error so you
// can fix it.

// 2.12 - Header guards
// Duplicated definitions throw a compile error.
// For example:
// square.h:
//int get SquareSides() // should not include function definitions, but will for the sake of example
//{
//    return 4;
//}

// geometry.h:
//#include "square.h"

// main.cpp:
//#include "square.h"
//#include "geometry.h"
//
//int main()
//{
//    return 0;
//}

// After preprocessor runs, result:
//int getSquareSides()
//{
//    return 4;
//int getSquareSides()
//{
//    return 4;
//}
//int main()
//{
//    return 0;
//}

// Header guards:
//#ifndef UNIQUE_NAME
//#define UNIQUE_NAME
//
// declarations (and certain types of definitions) here
//
//#endif
// Convention for the name: square.h -> SQUARE_H

// We can't avoid definitions in header files. Non-function definitions. E.g. user-defined
// types are typically defined in header files, so the type definitions can be propagated
// out to the code fiels that need to use them. Without a header guard, a code file could
// end up with multiple (identical) copies of a given type definitions.

// Modern compilers - #pragma once
// But it is not an official part of the C++ language (and probably will never be, because
// it can't be implemented in a way that works reliably in all cases).
// For maximum compatibility, traditional header guards are recommended
