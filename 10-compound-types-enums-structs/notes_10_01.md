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



# 10.3 - Unscoped enumeration input and output

Enumerators are integral symbolic constants. Similar to the case with chars.

Each enumerator is automatically assigned an integer value based on its position in the
enumerator list.

Possible to explicitly define the value of enumerators.

```c++
enum Animal
{
    cat = -3,
    dog,            // assigned -2
    pig,            // assigned -1
    horse = 5,
    giraffe = 5,    // shares the same value as horse
    chicken,        // assigned 6
}
```

Horse and giraffe become interchangeable. Should generally be avoided

### Unscoped enumerations will implicitly convert to integral values
When an enumerated type is used in a function call or with an operator, the compiler will
first try to find a function or operator that matches the enumerated type. If it can't
find a match, the compiler will then implicitly convert an unscoped enumeration or
enumerator to its corresponding integer value.

### Printing enumerator names
As of C++20, no easy way to do this. Manual solution. E.g.

```c++
enum Color
{
    black,
    red,
    blue,
};

constexpr std::string_view getColor(Color color)
{
    switch (color)
    {
    case black: return "black";
    case red:   return "red";
    case blue:  return "blue";
    default:    return "???";
    }
}
```

`std::string_view` is much less expensive to copy than `std::string`.

### Teaching `operator<<` how to print enumerator

Using operator overloading

```c++
#include <iostream>

enum Color
{
    black,
    red,
    blue,
};

std::ostream& operator<<(std::ostream& out, Color color)
{
    switch (color)
    {
    case black: out << "black"; break;
    case red:   out << "red";   break;
    case blue:  out << "blue";  break;
    default:    out << "???";   break;
    }

    return out;
}

int main()
{
    Color shirt { blue };
    std::cout << "Your shirt is " << shirt;

    return 0;
}
```

Here's what actually hapens. When we try to print `shirt` using `std::cout` and `operator<<`,
the compiler will see that we've overloaded `operator<<` to work with objects of type `Color`.
This overloaded `operator<<` function is then called with `std::cout` as the `out` parameter,
and our shirt as parameter color. Since `out` is a reference to `std::cout`, a statement such
as `out << "blue"` is really just print `"blue"` to `std::cout`.

### Enumeration size and base
Integer family of types. C++ standard says the enum size needs to be large enough to
represent all of the enumerator values. Most often, it will make enum variables the same
size as a standard `int`.

It is possible to specify a different underlying type.

```c++
enum Color : std::uint8_t
{
    black,
    red,
    blue,
};
```

Since enumerators aren't usually used for arithmetic or comparisons with integers, it's
generally safe to use an unsigned integer if desired.

> **Best practice**<br>
> Specify the base type of an enumeration only when necessary.

> **Warning**<br>
> Because `std::int8_t` and `std::uint8_t` are usually type aliases for char types, using
> either of these types as the enum base will most likely cause the enumerators to print
> as char values rather than int values.

### Integer to unscoped enumerator conversion
Compiler will not implicitly convert an integer to an unscoped enumerator.

Use `static_cast<EnumName>(2)`.

In C++17, if an unscoped enumeration has a specifed base, then the compiler will allow you
to initialize (but not assign) an unscoped enumeration using an integral value.

I.e. `enum Pet : int`

### Unscoped enumerator input

```c++
#include <iostream>

enum Pet
{
    cat,
    dog,
    pig,
    whale,
};

int main()
{
    std::cout << "Enter a pet (0=cat, 1=dog, 2=pig, 3=whale): ";

    int input { };
    std::cin >> input;

    Pet pet { static_cast<Pet>(input) };

    return 0;
}
```

Can also overload `operator>>`.

```c++
std::istream& operator>>(std::istream& in, Pet &pet)
{
    int input { };
    in >> input;

    pet = static_cast<Pet>(input);

    return in;
}
```



# 10.4 - Scoped enumerations (enum classes)
Problem: unscoped enumerations are distinct types in C++, but they are not type safe,
allows to do thing that don't make sense.

```c++
enum Color
{
    red,
    blue,
};

enum Fruit
{
    banana,
    apple,
};

Color color { red };
Fruit fruit { banana };

// red == banana = true
```

The compiler will look to see if it know how to compaare a `Color` and a `Fruit`. It
doesn't. Next it will try convertin `Color` and/or `Fruit` to integers to see if it can
find a match. Eventually, the compiler sees that if it converts them both to ints, it can
do the comparison.

Because of this + namespace pollution problem, C++ designers determined that a cleaner
solution for enumerations would be of use.

### Scoped enumerations
**Enum class**.

```c++
#include <iostream>
int main()
{
    enum class Color
    {
        red,
        blue,
    };

    enum class Fruit
    {
        banana,
        apple,
    };

    Color color { Color::red }; // red is not directly accessible; have to use Color
    Fruit fruit { Fruit::banana }; // banana is not directly accessible; have to use Fruit

    if (color == fruit) // compile error.
    {
        ...
    }

    return 0;
}
```

> *Note*<br>
> The `class` keyword (along with the `static` keyword) is one of the most overloaded
> keywords in the C++ language, and can have different meanings depending on context.
> Although scoped enumerations use the `class` keyword, they aren't considered to be a
> "class type" (which is reserved for structs, classes, and unions).

### Scoped enumerations define their own scope regions
Scoped enumerations act like a namespace for their enumerators.

### Scoped enumerations don't implicitly convert to integers
But can explicitly convert using a `static_cast<int>(...)`.

Conversely can `static_cast` an integer to a scoped enumerator.

> **Best practice**<br>
> Favor scoped enumerations unless there's a reason not to.

But unscoped enumerations are still commonly used in C++ because there are situations
where we desire the implicit conversion to int and we don't need extra namespacing.

### Easing the conversion of scoped enumerators to integers
There is a useful hack that overloads the unary `operator+` to perform this conversion

```c++
#include <iostream>

enum class Animals
{
    chicken,
    dog,
    cat,
    elephant,
    duck,
    snake,

    maxAnimals,
};

constexpr auto operator+(Animals a) noexcept
{
    return static_cast<std::underlying_type_t<Animals>>(a);
}

int main()
{
    std::cout << +Animals::elephant << '\n';

    return 0;
}
```

### `using enum` statements (C++20)

```c++
enum class Color
{
    black,
    red,
    blue
};

constexpr std::string_view getColor(Color color)
{
    using enum Color;

    switch (color)
    {
    case black: return "black";
    case red: return "red";
    case blue: return "blue";
    default: return "???";
    }
}

...
```
