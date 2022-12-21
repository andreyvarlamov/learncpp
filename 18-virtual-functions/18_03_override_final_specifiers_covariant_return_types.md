# 18.3 - The override and final specifiers, and covariant return types

Override and final - not keywords - normal identifiers that have special meaning in
certain contexts.

### The override specifier
If the signature of a function override in a derived class doesn't match the base class
function that we intend to override, normally that wouldn't cause a compilation error, but
with the override specifier, it will.

```c++
// In derived class
std::string_view getName2(int x) const override { return "B"; }
// e.g. if in the base class getName2 isn't const, this will not compile
```

> **Best practice**<br>
> Use the virtual keyword on virtual functions in a base class. Use the override specifier
> (but not the virtual keyword) on override functions in derived classes.

### The final specifier
Don't allow to override a virtual function, or inherit from class.

```c++
#include <string_view>

class A
{
public:
    virtual std::string_view getName() { return "A"; }
};

class B : public A
{
public:
    std::string_view getName() override final { return "B"; }
};

class C : public B
{
public:
    std::string_view getName() override { return "C"; } // compile error
};
```

```c++
#include <string_view>

class A
{
public:
    virtual std::string_view getName() { return "A"; }
};

class B final : public A
{
public:
    std::string_view getName() override { return "B"; }
};

class C : public B // compile error
{
public:
    std::string_view getName() override { return "C"; }
};
```

### Covariant return types
One special case in which a derived class virtual function override can have a different
return type than the base class and still be considered a matching override. If the return
type of a function is a pointer or a reference to some class, override functions can
return a pointer or a reference to a derived class. These are called **covariant return
types**.

```c++
#include <iostream>
#include <string_view>

class Base
{
public:
    // This version of getThis() returns a pointer to a Base class
    virtual Base* getThis() { std::cout << "called Base::getThis()\n"; return this; }
    void printType() { std::cout << "returned a Base\n"; }
};

class Derived : public Base
{
public:
    // Normally override functions have to return objects of the same type as the base
    // function. However, because Derived is derived from Base, it's okay to return Derived*
    // instead of Base*
    Derived* getThis() override { std::cout << "called Derived::getThis()\n"; return this; }
    void printType() { std::cout << "returned a Derived\n"; }
};

int main(0
{
    Derived d {  };
    Base* b { &d };

    d.getThis()->printType(); // calls Derived::getThis(), returns a Derived*, calls Derived::printType
    b->getThis()->printType(); // calls Derived::getThis(), returns a Base*, calls Base::printType

    return 0;
}
```

```
called Derived::getThis()
returned a Derived
called Derived::getThis()
returned a Base
```

C++ can't dynamically select types, so you'll always get the type that matches the actual
version of the function being called.

Covariant return types are often used in cases where a virtual member function returns a
pointer or reference to the class containing the member function (e.g. Base::getThis()
returns a Base, and Derived::getThis() returns a Derived). However, this isn't strictly
necessary. Covariant return types can be used in any case where the return type of the
override member function is derived from the return type of the base virtual member
function.
