// Two identical identifiers -> naming collision; if in one file by compiler; if across
// multiple by linker.
//
// Namespace - provides a scope region (namespace scope) to the names declared inside
// of it. Within a namespace, all names must be unique
//
// Any name that is not defined inside a class, function or a namespace is considered to
// be part of an implicitly defined namespace called the global namespace (global scope)
//
// Only declarations and definition statements can appear in the global namespace.
// Can define variables in the global namespace, but should generally be avoided ("global
// variable")
// Other types of statements (e.g. expression statements) cannot be placed in the global
// namespace (initializers for global variables being an exception).
//
// The std namespace:
// When C++ was originally designed, all of the identifiers in the C++ standard library
// were part of the global namespace. But potential conflicts (include new file from std
// and get a conflict with one of your own definitions; or compiles on one version, but
// not under a future version).
//
// Explicit namespace qualifier, e.g. std::cout
// :: symbol - scope resolution operator; if no identifier to the left of the symbol is
// provided, the global namespace is assumed
// using namespace std; - bad practice

int main()
{
    return 0;
}
