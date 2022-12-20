# 17.7 - Calling inherited functions and overriding behavior

```c++
#include <iostream>

class Base
{
protected:
    int m_value { };

public:
    Base(int value)
        : m_value { value }
    {
    }

    void identify() const { std::cout << "I am a Base\n"; }
};

class Derived : public Base
{
public:
    Derived(int value)
        : Base { value }
    {
    }

    int getValue() const { return m_value; }
};

int main()
{
    Base base { 5 };
    base.identify();

    Derived derived { 7 };
    derived.identify();

    return 0;
}
```

The compiler first looks to see if that member exists in the derived class. If not, it
begins walking up the inheritance chain and checking whether the member has been defined
in any of the parent classes.

Redefine functions. Note, they can a different access specifier, even a higher one. So if
it was private in the base class, it can redefined as public in the derived class.

```c++
class Derived : public Base
{
    // Can call Base's identify too, if needed
    Base::identify();
    ...
    // Redefined identify() from Base
    void identify() const { std::cout << "I am a Derived\n"; }
};
```

For `Base::identify()`, need scope resolution, otherwise it would just refer to itself -
infinite recursion.

A bit tricky with friend functions in base classes. E.g. overloading `operator<<`. Friend
functions are not actually part of the base class, so using the scope resolution qualifier
won't work. Instead we need a way to make our Derived class temporarily look like the Base
class, so that the right version of the function can be called. Use `static_cast`.

```c++
...
// operator<< is defined in Base class; redefining in Derived class:
friend std::ostream& operator<<(std::ostream& out, const Derived& d)
{
    out << "In Derived\n";

    // static_cast Derived to a base object, so we call the right version of operator<<
    out << static_cast<const Base&>(d);
    return out;
}
```
