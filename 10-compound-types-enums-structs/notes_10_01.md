# 10 - Compound Types: Enums and Structs

10.1 - 10.5

# 10.1 - Introduction to program-defined (user-defined) types

### What are user-defined / program-defined types?
Enums and structs.

### Defining program-defined types
**Type definition**.

Program-defined types always end in a semicolon.

### Naming program-defined types
Capital letter.

### Using program-defined types throughout a multi-file program
Every code file that uses a program-defined type needs to see the full type definition
before it is used. A forward declaration is not sufficient.

Program-defined types are typically defined in header files, and then #included into any
code file that requires that type definition. These header files are typically given the
same name as the program-defined type.

### Type definitions are partially exempt from one-definition rule
Two caveats: 1) still can only have one type definition per code file -- header guards. 2)
All of the type definitions for a given type must be identical, otherwise undefined
behavior will result.

### Nomenclature: user-defined types vs program-defined types
* Type: fundamental

    A type built into the core C++ language

    int, std::nullptr_t

* Type: user-defined

    A non-fundamental type (in casual use, typically means program-defined types)

    std::string, Fraction

* Type: Program-defined

    A class type or enumeration type defined yourself

    Fraction
