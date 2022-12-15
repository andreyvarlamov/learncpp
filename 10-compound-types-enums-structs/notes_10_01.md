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



# 10.2 - Unscoped enumerations

`enum` keyword

```c++
enum Color
{
    red,
    green,
    blue,
};

int main()
{
    Color apple { red };
    Color shirt { green };
    Color cup { blue };

    Color socks { white }; // error: white is not an enumerator of Color
    Color socks { 2 }; // error: 2 is not an enumerator of Color
}
```

### Naming enumerations and enumerators
> **Warning**<br>
> Enumerations don't have to be named, but unnamed enumerations should be avoided in modern
> C++.

> **Best practice**<br>
> Name your enumerated types starting with a capital letter. Name your enumerators
> starting with a lower case letter.


### Enumerated types are distint types

### Putting enumerations to use

...

Many languages use enumerations to define Booleans -- after all, a Boolean is essentially
just an enumeration with 2 enumerators. However, in C++, true and false are defined as
keyword instead of enumerators.

### The scope of unscoped enumerations
Unscoped enumerations are named such because they put their enumerator names into the same
scope as the enumeration definition itself.

This pollutes the global scope and significantly raises the chance of naming collisions.

Unscoped enumerations also provide a named scope region for their enumerators (much like a
namespace acts as a named scope region for the names declared within).

`Color::red`

### Avoiding enumerator naming collisions
1. Prefix with the name of the enumeration itself.

2. Place the enumerated type inside something that provides a separate scope region. E.g.
   a namespace. (It's also common to put enumerated types related to a class inside the
   scope region of the class.) <- **Best practice**

Or just use scoped enumerations.

### Comparing against enumerators

if-else and ==
