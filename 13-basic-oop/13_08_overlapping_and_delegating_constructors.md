# 13.8 - Overlapping and delegating constructors

Not uncommon to have a class with multiple constructors that have overlapping
functionality.

### The obvious solution doesn't work
Can't call another constructor within a constructor.

### Delegating constructors
Constructor chaining.

```c++
#include <iostream>
#include <string>
#include <string_view>

class Employee
{
private:
    int m_id { };
    std::string m_name { };

public:
    Employee(int id = 0, std::string_view name="")
        : m_id { id }, m_name { name }
    {
        std::cout << "Employee " << m_name << " created.\n";
    }

    Employee(std::string_view name) : Employee { 0, name }
    { }
};
```

A constructor that delegates to another constructor is not allowed to do any member
initialization itself. One or the other.

Possible for one constructor to delegate to another constructor, which delegates back to
the first constructor. Infinite loop, stack overflow, crash.

### Using a normal member function for setup

```c++
#include <iostream>

class Foo
{
private:
    const int m_value { 0 };

    void setup()
    {
        // e.g. open a file or database
        std::cout << "Setting things up...\n";
    }

public:
    Foo()
    {
        setup();
    }

    Foo(int value) : m_value { value }
    {
        setup();
    }
};
```

`setup()` won't be able to initialize members. By the time constructor calls `setup()`,
the members have already been created (and initialized if an initialization value was
provided). It can only assign values to members, or do other tasks. Can't do things like
bind a reference ro set a const value, or assign values to members that don't support
assignment.

### Resetting a class object
If the class is assignable (has an accessible assignment operator), we can create a new
class object, and then use assignment to overwrite the values in the object we want to
reset.

```c++
void reset()
{
    *this = Foo{}; // create new Foo object, and use assignment to overwrite our implicit object
}
```

Here, first we create a default `Foo` object (which will have default values). Then we
assign that default `Foo` object to the object that member function `reset()` was called
on (`*this`). The compiler will do a memberwise copy.
