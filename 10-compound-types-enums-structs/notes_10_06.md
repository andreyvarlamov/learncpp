# 10 - Compound Types: Enums and Structs

10.6 - 10.10

# 10.6 - Struct aggregate initialization

### Data members are not initialized by default

Undefined behavior when try to access uninitialized struct's data members.

### What is an aggregate?
In general programming: (e.g.) structs and (e.g.) arrays.

In C++, to be an aggregate, a type must meet the following criteria:
* Is a class type (a struct, class or union), or an array type
* Has no private or protected non-static data members
* Has no user-declared or inherited constructors
* Has no base classes
* Has no virtual member functions

### Aggregate initialization of a struct
Memberwise initialization.

```c++
struct Employee
{
    int id {};
    int age {};
    double wage {};
}
...
Employee frank = { 1, 32, 60000.0 }; // copy-list initialization using braced list
Employee robert ( 3, 45, 62500.0 ); // direct initialization using parenthesized list
Employee joe { 2, 28, 45000.0 }; // list initialization using braced list (preferred)
```

### Missing initializers in an initializer list

```c++
Employee joe {}; // value-initialize all members
```

### Const structs

### Designated initializers (C++20)

```c++
struct Foo
{
    int a{ };
    int b{ };
    int c{ };
};

int main()
{
    Foo f1{ .a{ 1 }, .c{ 3 } };; // ok: f1.a = 1, f1.b = 0 (value initialized), f1.c = 3
    Foo f2{ .a{ 2 }, .c{ 1 } };; // error: initialization order does not match order of declaration in struct

    return 0;
}
```

> **Best practice**
> When adding a new member to an aggregate, it's safest to add it to the bottom of the
> definition list so the initializers for other members don't shift.

### Assignment with an initializer list

```c++
Employee joe { 1, 32, 60000.0 };
joe = { joe.id, 33, 66000.0 };
```

### Assignment with designated initializers (C++20)

```c++
Employee joe { 1, 32, 60000.0 };
joe = { .id = joe.id, .age = 33, .wage = 66000.0 };
```

Any members that aren't designated in such an assignment would be assigned the value 0



# 10.7 - Default member initialization

When we define a struct (or class) type, we can provide a default initialization value for
each member as part of the type definition. This process is called **non-static member
initialization**, and the initialization value is called a **default member initializer**.

```c++
struct Something
{
    int x; // no initialization value (bad)
    int y { }; // value-initialized by default
    int z { 2 }; // explicit default value
}

int main()
{
    Something s1; // s1.x is uninitialized, s1.y is 0, s1.z is 2

    return 0;
}
```

### Explicit initialization values take precedence over default values

```c++
Something s2 { 5, 6, 7 };
```

### Missing initializers in an initializer list when default values exist

```c++
Something s3 { }; // value initialize s3.x, use default values for s3.y and s3.z
```

### Always provide default values for your members

### Default initialization vs value initialization for aggregates

`Fraction f1;` vs `Fraction f2 { };`.

Prefer the latter, even when all members have default initializers

But still not uncommon to use the former. The latter wasn't introduced until C++11, and
there's a similar case (for non-aggregates) where default initialization can be more
efficient (13.5 - Constructors).



# 10.8 - Struct passing and miscellany

### Passing structs (by reference)
Can pass the entire struct to a function that needs to work with the members. Generally
passed by (const) reference to avoid making copies.

### Returning structs
...

Usually returned by value, so as not to return a dangling reference.
```c++
return Point3d { 0.0, 0.0, 0.0 };
```

When not using `auto`, can even omit the type in the return statement:
```c++
return { 0.0, 0.0, 0.0 };
```

Also:
```c++
return { }; // value-initialize all members
```

### Structs with program-defined members

```c++
#include <iostream>

struct Company
{
    struct Employee
    {
        int id { };
        int age { };
        double wage { };
    };

    int numberOfEmployees { };
    Employee CEO { };
};

int main()
{
    Company myCompany { 7, { 1, 32, 55000.0 } };
    std::cout << myCompany.CEO.wage;
}
```

### Struct size and data structure aligment
Typically, the size of a struct is the sum of the size of all its members, but not always!

*At least* as large as the size of all the variables it contains. For performace reasons,
the compiler will sometimes add gaps into structures (**padding**).

See [Data structure aligment](https://en.wikipedia.org/wiki/Data_structure_alignment).

```c++
#include <iostream>

struct Foo1
{
    short a { };
    short qq { };
    int b { };
    double c { };
};

struct Foo2
{
    short a { };
    int b { };
    double c { };
    short qq { };
};

int main()
{
    std::cout << "The size of Foo1 is " << sizeof(Foo1) << '\n'; // 16
    std::cout << "The size of Foo2 is " << sizeof(Foo2) << '\n'; // 24

    return 0;
}
```

See `fractions.cpp` - Quiz Q2



# 10.9 - Member selection with pointers and references

### Member selection for pointers to structs

`.` won't work.

Because pointers hold addresses, we first need to dereference the pointer to get the
object before we can do anything with it.

```c++
Employee joe { 1, 34, 65000.0 };
Employee* ptr { &joe };
(*ptr).id;
```

**Member selection from pointer operator** or **arrow operator**.

```c++
Employee joe { 1, 34, 65000.0 };
Employee* ptr { &joe };
ptr->id;
```

> **Best practice**<br>
> Use `->` instead of `.`.

### Mixing pointers and non-pointers to members

```c++
struct Paw
{
    int claws { };
};

struct Animal
{
    std::string name { };
    Paw paw { };
};

...

Animal puma { "Puma, { 5 } };
Animal* ptr { &puma };

(ptr->paw).claws;
```

Parentheses aren't necessary but help readability.



# 10.10 - Class templates

Remember the problem function templates intend to solve.

### Aggregate types have similar challenges
Can't even overload structs, would be erroneous redeclaration.

### Class templates

```c++
#include <iostream>

template <typename T>
struct Pair
{
    T first { };
    T second { };
};

int main()
{
    Pair<int> p1 { 5, 6 }; // instantiates Pair<int> and creates object p1
    std::cout << p1.first << ' ' << p1.second << '\n';

    Pair<double> p2 { 1.2, 3.4 }; // instantiates Pair<double> and creates object p2
    std::cout << p2.first << ' ' << p2.second << '\n';

    Pair<double> p3 { 7.8, 9.0 }; // creates object p3 using prior definition for Pair<double>
    std::cout << p3.first << ' ' << p3.second << '\n';

    return 0;
}
```

What the compiler actually compiles after all template instnatiation is done.

```c++
#include <iostream>

// A declaration for our Pair class template
// (we don't need the definition any more since it's not used)
template <typename T>
struct Pair;

// Explicitly define what Pair<int> looks like
template <> // tells the compiler this is  a template type with no template parameters
struct Pair<int>
{
    int first { };
    int second { };
};

// Explicitly define what Pair<double> looks like
template <> // tells the compiler this is  a template type with no template parameters
struct Pair<double>
{
    double first { };
    double second { };
};

...
```

### Using our class template in a function

Because the compiler treats `Pair<int>` and `Pair<double>` as separate types, can use
overloaded functions that are differentiated by parameter type.

```c++
constexpr int max(Pair<int> p)
{
    return (p.first > p.second ? p.first : p.second);
}

constexpr int max(Pair<double> p)
{
    return (p.first > p.second ? p.first : p.second);
}
```

Or function template:

```c++
template <typename T>
struct Pair
{
    T first { };
    T second { };
};

template <typename T>
constexpr T max(Pair<T> p)
{
    return (p.first > p.second ? p.first : p.second);
}

...
```

### Class types with template type and non-template type members

### Clas templates with multiple template types

### std::pair
In the <utility> header. Defined identically to the `Pair` class template with multiple
template types in the preceding section(s).

### Using class templates in multiple files
Just like function templates, class templates are typically defined in header files so
they can be included into any code file that needs them. Both template definitions and
type definitions are exempt from the one-definition rule.
