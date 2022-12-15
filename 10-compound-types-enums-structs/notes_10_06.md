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
