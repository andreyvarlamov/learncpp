int main()
{
    return 0;
}

// 6.1 - Compound statements (blocks)
// A compound statement (also called a block, or block statement) is a group of zero or
// more statements that is treated by the compiler as if it were a single statement.
// Blocks begin with a {, and end with a }
// Blocks can be used anywhere a signle statement is allowed.
// Function body is a block.

// Blocks inside other blocks
// Although functions can't be nested inside other functions, blocks can be nested inside
// other blocks.
//int main()
//{ // outer block
//    // multiple statements
//    int value {};
//
//    { // inner/nested block
//        add(3, 4);
//    } // end inner/nested block
//
//    return 0;
//} // end outer block

// Using blocks to execute multiple statements conditionally.
// By default, an if statement executes a single statement if the condition evaluates to
// true. However, we can replace this single statement with a block of statements if we
// want multiple statements to execute when the condition evaluates to true.
// E.g.
//if (check_value)
//    do_thing();
// VVV
//if (check_value)
//{
//    do_thing_1();
//    do_thing_2();
//}

// Block nesting levels; (nesting depth)
// The C++ standard says that C++ compilers should support 256 levels of nesting --
// however, not all do (e.g. Visual Studio supports less).

// Best practice is to keep the nesting level of your functions to 3 or less



// 6.2 - User-defined namespaces and the scope resolution operator
// The best way to avoid collisions is to put your functions into your own namespaces

// Defining your own namespaces
// Namespaces provided by C++ (such as the global namespace) or by libraries (such as
// namespace std) are not considered user-defined namespaces.
//namespace foo
//{
//    int doSomething(int x, int y)
//    {
//        return x + y;
//    }
//}

// Acccessing a namespace with the scope resolution operator (::)
// The scope resolution operator tells the compiler that the identifier specified by the
// right-hand operand should be looked for in the scope of the left-hand operand.
//namespace foo
//{
//    int doSomething(int x, int y)
//    {
//        return x + y;
//    }
//}
//
//namespace goo
//{
//    int doSomething(int x, int y)
//    {
//        return x - y;
//    }
//}
//
//int main()
//{
//    std::cout << foo:doSomething(4, 3) << '\n';
//    return 0;
//}

// Using the scope resolution operator with no name prefix - global namespace
//#include <iostream>
//
//void print()
//{
//    std::cout << " there\n";
//}
//
//namespace foo
//{
//    void print()
//    {
//        std::cout << "Hello";
//    }
//}
//
//int main()
//{
//    foo::print(); // call print in foo namespace
//    ::print(); // call print in global namespace (same as just calling print() in this case)
//
//    return 0;
//}
// :: superfluous here

// Identifier resolution from within a namespace
// If an identifier inside a namespace is used and no scope resolution is provided, the
// compiler will first try to find a matching declaration in that same namespace. If no
// matching identifier is found, the compiler will then check each containing namespace
// in sequence to see if a match is found, with the global namespace being checked last.
//#include <iostream>
//
//void print()
//{
//    std::cout << " there\n";
//}
//
//namespace foo
//{
//    void print()
//    {
//        std::cout << "Hello";
//    }
//
//    void printHelloThere()
//    {
//        print(); // calls print() in foo namespace
//        ::print(); // calls print() in global namespace
//    }
//}
//
//int main()
//{
//    foo::printHelloThere();
//
//    return 0;
//}

// Multiple namespace blocks are allowed
// It is legal to declare namespace blocks in multiple locations (either across multiple
// files, or multiple places within the same file). All declarations within the namespace
// are considered part of the namespace.
// BUT: Do not add custom functionality to the std namespace
// Doing so causes undefined behavior most of the time, because the std namespace
// has a special rule, prohibiting extension from user code.
// When separating code into multiple files, you'll have to use a namespace in both the
// header and the source files.

// Nested namespaces
// Namespaces can be nested inside other namespaces. E.g.:
//#include <iostream>
//
//namespace foo
//{
//    namespace goo
//    {
//        int add(int x, int y)
//        {
//            return x + y;
//        }
//    }
//}
//
//int main()
//{
//    std::cout << foo::goo::add(1, 2) << '\n';
//    return 0;
//}
// Since C++17 can also be declared this way:
// namespace foo::goo { ... }

// Namespace aliases
// Temporarily shorten a long sequence of namespaces into something shorter.
//#include <iostream>
//
//namespace foo::goo
//{
//    int add(int x, int y)
//    {
//        return x + y;
//    }
//}
//
//int main()
//{
//    namespace active = foo::goo;
//
//    std::cout << active::add(1, 2) << '\n';
//
//    return 0;
//}
// In C++, namespaces were primarily designed as a mechanism for preventing naming collisions,
// not as a way to implement an information hierarchy.
// As evidence of this, note that the entirety of the standard library lives under the singular
// namespace std:: (with some nested namespaces used for newer library features). Some
// newer languages (such as C#) differ from C++ in this regard.
// In general, you should avoid deeply nested namespaces.

// When you should use namespaces
// In applications, namespaces can be used to separate application-specific code that
// might be reusable later (e.g. math functions). For example, physical and math functions
// could go into one namespace (e.g. mat::), while language and localiation functions in
// another (e.g. lang::)
// When you write a library or code that you want to distribute to others, always
// place your code inside a namespace. The code your library is used in may not follow
// best practices -- in such a case, if your library's declarations aren't in a
// namespace, there's an elevated chance for naming conflicts to occur.
// As an additional advantage, placing library code inside a namespace also allows the user
// to see the contents of your library by using their editor's auto-complete and suggestion
// feature.



// 6.3 - Local variables
// Local variables have block scope

// All variable names within a scope must be unique

// Local variables have automatic storage duration
// Variable's storage duration (usually just duration) determines what rules govern when
// and how a variable will be created and destroyed. In most cases, a variable's storage
// duration directly determines its lifetime.

// Local variables can be defined inside nested blocks. The scope of those variables is
// limited to the inner block in which they are defined.

// Local variables have no linkage.
// Identifiers have another property named linkage. An identifier's linkage determines
// whether other declarations of that name refer to the same object or not.
// Local variables have no linkage, which means that each declaration refers to a
// unique object
// E.g.
//int main()
//{
//    int x { 2 }; // local variable, no linkage
//
//    {
//        int x { 3 }; // this identifier x refers to a different object than the previous x
//    }
//
//    return 0;
//}

// Variables should be  defined in the most limited scope.
// E.g. if a variable is only used within a nested block, it should be defined inside that
// nested block.
// Best practice: Define variables in the most limited existing scope. Avoid creating
// new blocks whose only purpose is to limit the scope of variables.

// Scope/lifetime/duration recap
// A variable's scope determines where the variable is accessible
// Duration defines the rules that govern when a variable is created and destroyed.
// A variable's lifetime is the actual time between its creation and destruction.
// Local variables have block scope, which means they can be accessed inside the block in
// which they are defined.
// Local variables have automatic duration, which means they are created at the point of
// definition, and destroyed at the end of the block in which they are defined.



// 6.4 - Introduction to global variables
// In C++, variables can also be declared outside a function. Such variables are called
// global variables.

// Declaring and naming global variables
// By convention, global variables are declared at the top of a file, below the includes,
// but above any code. E.g.:
// int g_x { };
// Best Practice: prefix using "g" or "g_"

// Global variables have file scope and static duration
// File scope ("global scope", "global namespace scope"). Visible from the point of
// declaration to until the end of the file in which they are declared. Once declared, a
// global variable can be used anywhere in the file from that point onward.
// Because they are defined outside of a function, global variables are considered to be
// part of the global namespace.
// Global variables are created when the program starts, and destroyed when it ends. This
// is called static duration. Variables with static duration are sometimes called static
// variables.

// Global variable initialization.
// Unlike local variables, which are uninitialized by default, variables with static duration
// are zero-initialized by default.
// int g_y; // no explicit initializer (zero-initialized by default)
// int g_y { }; // zero-initialized

// Constant global variables. Must be initialized

// Should generally be avoided.



// 6.5 - Variable shadowing (name hiding)
// When we have a variable inside a nested block that has the same name as a variable in
// an outer block, the nested variable hides the outer variable in areas where they are
// both in scope.
// Name hiding or shadowing.

// Shadowing of local variables
// When inside the nested block, there's no way to directly access the shadowed variable
// from the outer block.

// Shadowing of global variables.
// Local variables with the same name as a global variable will shadow the global
// variable wherever the local variable is in scope.
// However, because global variables are part of the global namespace, we can use the
// scope operator with no prefix to tell the compiler we mean the global variable

// Avoid variable shadowing
// Some compilers will issue a warning when a variable is shadowed



// 6.6 - Internal linkage
// In 6.3, we said, an identifier's linkage determines whether other declarations of that
// name refer to the same object or not.
// We discussed how local variables have no linkage.
// Global variable and function identifiers can have either internal linkage or external
// linkage.
// An identifier with internal linkage can be seen and used within a single file, but it
// is not accessible from other files (that is, it is not exposed to the linker).
// This means that if two files have identically named identifiers with internal linkage,
// those identifiers will be treated as independent.

// Global variables with internal linkage
// Sometimes called internal variables.
// To make a non-constant global variable internal, we use the `static` keyword
// Const and constexpr global variables have internal linkage by default (and thus don't
// need the static keyword - if it is used, it will be ignored).

// The use of the static keyword above is an example of a storage class specifier, which
// sets both the name's linkage and its storage duration (but not its scope). The most
// comonly used storage class specifiers are static, extern and mutable.

// The one-definition rule and internal linkage
// Internal objects (and functions) that are defined in different files are considered to
// be independent entiteis (even if their names are identical), so there is no violation
// of the one-defintion rule. Each internal object only has one definition.

// Functions with internal linkage
// Because linkage is a property of an identifier (not of a variable), function identifiers
// have the same linkage property that variable identifiers do.
// Functions default to external linkage, but can be set to internal linkage via the
// static keyword
// E.g. static int add(int x, int y) { ... }
