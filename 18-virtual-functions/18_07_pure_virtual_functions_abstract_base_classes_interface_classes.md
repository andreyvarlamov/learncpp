# 18.7 - Pure virtual functions, abstract base classes, and interface classes

### Pure virtual (abstract) functions and abstract base classes
Simply assign the function the value 0.

Any class with one or more pure virtual functions becomes an **abstract base class**.
Cannot be instantiated. Any derived class must define a body for this function, or that
derived class will be considered an abstract base class as well. Compiler should give a
warning.

```c++
virtual int getValue() const = 0; // a pure virtual function
```

### Pure virtual functions with definitions
When providing a definition for a pure virtual function, the definition must be provided
separately (not inline).

Useful when you want your base class to provide a default implementation for a function,
but still force any derived classes to provide their own implementation. However, if the
derived class is happy with the default implementation provided by the base class, it can
simple call the base class implementation directly.

A destructor can be made pure virtual, but must be given a definition so that it can be
called when a derived object is destructed.

### Interface classes
Class that has no member variables, and where *all* of the functions are pure virtual.
Purely a definition, with no actual implementation.

```c++
#include <string_view>

class IErrorLog
{
public:
    virtual bool openLog(std::string_view filename) = 0;
    virtual bool closeLog() = 0;

    virtual bool writeError(std::string_view errorMessage) = 0;

    virtual ~IErrorLog() { } // make a virtual destructor in case we delete an IErrorLog
                             // pointer, so the proper derived destructor is called
};

class FileErrorLog : public IErrorLog
{
    ...
};

class ScreenErrorLog : public IErrorLog
{
    ...
};

double mySqrt(double value, IErrorLog& log)
{
    if (value < 0.0)
    {
        log.writeError("Tried to take square root of value less than 0");
        return 0.0;
    }
    else
    {
        return std::sqrt(value);
    }
}

int main()
{
    ...
    mySqrt(1.1, FileErrorLog);
    // or
    mySqrt(1.1, ScreenErrorLog);
}
```

Have become extremely popular because they are easy to use, easy to extend, and easy to
maintain. In fact, some modern languages, such as Java and C#, have added an "interface"
keyword that allows programmers to directly define an interface class without having to
explicitly mark all of the member functions as abstract. Furthermore, although Java (prior
to version 8) and C# will not let you use multiple inheritance on normal classes, they
will let you multiple inherit as many interfaces as you like. Because interfaces have no
data and no function bodies, they avoid a lot of the traditional problems with multiple
inheritance while still providing much of the flexibility.

### Pure virtual functions and the virtual table
Abstract classes still have virtual tables, as these can still be used if you have a
pointer or reference to the abstract class. The virtual table entry for a class with a
pure virtual function will generally either contain a null pointer, or point to a generic
function that prints an error (sometimes this function is named `__purecall`).
