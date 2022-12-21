# 18.2 - Virtual functions and polymorphism

A **virtual function** is a special type of function that, when called, resolves to the
most-derived version of the function that exists between the base and derived class. This
capability is known **polymorphism**. A derived function is considered a match if it has
the same signature (name, parameter types, and whether it is const) and return type as the
base version of the function. Such functions are called **overrides**.

```c++
#include <iostream>
#include <string>
#include <string_view>

class Animal
{
protected:
    std::string m_name { };

    // Make constructor protected because we don't want people creating Animal objects
    // directly, but still want derived classes to be able to use it.
    Animal(std::string_view name)
        : m_name { name }
    {
    }

public:
    const std::string& getName() const { return m_name; }
    virtual std::string_view speak() const { return "???"; }
};

class Cat : public Animal
{
public:
    Cat(std::string_view name)
        : Animal { name }
    {
    }

    virtual std::string_view speak() const { return "Meow"; }
};

class Dog : public Animal
{
public:
    Dog(std::string_view name)
        : Animal { name }
    {
    }

    virtual std::string_view speak() const { return "Woof"; }
};

void report(const Animal& animal)
{
    std::cout << animal.getName() << " says " << animal.speak() << '\n';
}

int main()
{
    Cat cat { "Fred" };
    Dog dog { "Garbo" };

    report(cat); // Fred says Meow
    report(dog); // Garbo says Woof

    return 0;
}
```

If return types of a virtual function and its override don't match, compilation will fail.

### Do not call virtual functions from constructors or destructors
When a Derived class is created, the Base portion is constructed first. If you were to
call a virtual function from the Base constructor, and Derived portion of the class hadn't
even been created yet, it would be unable to call the Derived version of the function
because there's no Derived object for the Derived function to work on. In C++, it will
call the Base version instead.

Similar issue for destructors, if you call a virtual function in a Base class destructor,
it will always resolve to the Base class version of the function, because the Derived
portion of the class will already have been destroyed.

### Downside
Why not make all functions virtual by default? Inefficient. - resolving a virtual function
call takes longer than resolving a regular one. Furthermore, the compiler also has to
allocate an extra pointer for each class object that has one or more virtual functions.
