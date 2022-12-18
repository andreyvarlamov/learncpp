# 13.2 - Classes and class members

### Classes
In C++, classes and structs are essentially the same. The only significant difference is
in accessibility level (public, etc.).

```c++
struct DateStruct
{
    int year { };
    int month { };
    int day { };
};

class DateStruct
{
public:
    int year { };
    int month { };
    int day { };
};
```

### Member functions
Sometimes **methods**.

Member functions can be defined inside or outside of the class definition.

```c++
#include <iostream>

class DateClass
{
public:
    int m_year { };
    int m_month { };
    int m_day { };

    void print()
    {
        std::cout << m_year << '/' << m_month << '/' << m_day;
    }
};

int main()
{
    DateClass today { 2020, 10, 14 };

    today.m_day = 16;
    today.print();

    DateClass tomrrow { 2020, 10, 15 };
    tomorrow.print();

    return 0;
}
```

Cf: the case without OOP.

```c++
struct Date
{
    ...
};

void print(Date date)
{
    ...
}

...

Date today ...;
today.print(today);
today.print(tomorrow);
```

The associated object is passed into the function.

In OOPs, the associated object is essentially implicitly passed to the member function.
For this reason, it is often called **the implicit object**.

Using the "m_" prefix for member variables helps distinguish member variables from
function parameters or local variables inside member functions. When we see an assignment
to a variable with the "m_" prefix, we know that we are changing the state of the class
instance. Unlike function parameters or local variables, which are declared within the
function, member variables are declared in the class definition. So if we want to know how
a variable with the "m_" prefix is declared, we know to look in the class definition
instead of within the function.

With member functions, there is no limitation of the order of declaration of functions.

### Member types

Possible to declare member types and nested types (including type aliases).

```c++
class Employee
{
public:
    using IDType = int;

    ...
};
```

In such a context, the class name effectively acts like a namespace for the nested type.
From inside the class, we only need refernce `IDType`. From outside the class, can access
the type via `Employee::IDType`.

Nested types cannot be forward declared. Generally, nested types should only be used when
the nested type is used exclusively within that class.

Note that since classes are types, it's possible to nest classes inside other classes.

### A not about structs in C++
In C, structs only have data members, not member functions.

In C++, after designing classes, structs were also granted the ability to have member
functions. Partially to have a unified ruleset for both.

Can lead to dangerous assumptions. For example, it's fair to assume a class will clean up
after itself (e.g. a class that allocated memory will deallocate it before being
destroyed), but it's not safe to assume a struct will.

Recommended to use the struct keyword for data-only structures, and the class keyword for
defining objects that require both data and functions to be bundled together.

### You have already been using classes without knowing it
C++ standard library is full of classes. E.g. `std::string`, `std::vector` and
`std::array` are all class types.
