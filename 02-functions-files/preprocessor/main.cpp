// 2.10 - Introduction to the preprocessor
// Prior to compilation, the code file goes through a phase called "translation".
// A code file with translations applied to it is called a translation unit.
// The most noteworthy of the translation phases involved the preprocessor. It's best
// thought of as a separate program that manipulates the text in each code file.
// Scans through the code file, looking for preprocessor directives - instructions that
// start with a # symbol and end with a newline.
// Its own syntax.
// The output of the preprocessor goes through several more translation phases, and then
// is compiled. Preprocessor does not modify the original code files in any way -- changes
// made by it either happen in-memory, or using a temp file
//
// #include - the preprocessor replaces the directive with the contents of the included
// file. The included contents are then preprocessed (along with the rest of the file),
// and then compiled.
//
// Macro defines - in C++, a macro is a rule that defines how input text is converted into
// replacement output text.
// Object-like macros and function-like macros
// Function-like macros act like functions and serve a similar purpose. Won't be discussed
// because their use is generally considered dangerous, and almost anything they can do can
// be done by a normal function.
// Object-like macros can be defined in one of two ways:
// #define identifier
// #define identifier substitution_text
// When the preprocessor encounters the object-liek marco directive, any further occurrence
// of the identifier is replace by substitution_text. Traditionally typed in all capitals,
// using underscores to represent spaces.

#include <iostream>

#define MY_NAME "Andrey"

int main()
{
    std:: cout << "My name is: " << MY_NAME;
    return 0;
}

// converts into VVVVV
// // The contents of iostream inserted here
// int main()
// {
//     std:: cout << "My name is: " << "Andrey";
//     return 0;
// }
//
// Object-macros with substitution text were used (in C) as a way to assign names to
// literals. This is no longer necessary, as better methods are available in C++.
// Object-like macros with substitution text should generally now only be seen in legacy
// code. There are better ways - const variables and symbolic constants (4.13)
//
//
// Object-like macros without substituion text
// Will also substitute with nothing, but it's not its purpose
// Generally accepted to use
//
// Conditional compilation
// # include <iostream>
//
// #define PRINT_JOE
//
// int main()
// {
// #ifdef PRINT_JOE
//     std::cout << "Joe\n"; // will be compiled
// #endif
//
// #ifdef PRINT_BOB
//     std::cout << "Bob\n"; // will be ignored
// #endif
//
// #ifndef PRINT_JOB
//     std::cout << "Job\n"; // will be compiled
// #endif
//
// #if 0
//     std::cout << "Nothing\n"; // will always be excluded
// #endif
//
//     return 0;
// }
//
// Object-like macros don't affect other preprocessor directives
//
// Scope of defines: directives are resolved before compilation, from top to bottom,
// on a file-by-file basis, regardless of C++ syntax
