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
