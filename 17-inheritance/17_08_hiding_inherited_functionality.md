# 17.8 - Hiding inherited functionality

### Changing an inherited member's access level

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

protected:
    void printValue() const { std::cout << m_value; }
};

class Derived : public Base
{
public:
    Derived(int value)
        : Base { value }
    {
    }

    // Inherited as protected, but we're chaning to public
    // Note: no parentheses here
    using Base::printValue;
};

int main()
{
    Base base { 5 };
    base.printValue(); // compile error

    Derived derived { 7 };
    derived.printValue(); // works

    return 0;
}
```

### Hiding functionality

```c++
#include <iostream>

class Base
{
public:
    int m_value { };
};

class Derived : public Base
{
private:
    using Base::m_value;

public:
    Derived(int value)
        : Base { value }
    {
    }
};

int main()
{
    Derived derived { 7 };
    std::cout << derived.m_value(); // error

    Base& base { static_cast<Base&>(derived) };
    std::cout << base.m_value(); // okay

    return 0;
}
```

Can encapsulate a poorly designed base class. But can bypass by casting inherited to base.

Can mark member functions as deleted

```c++
// getValue() is public in base class
int getValue() = delete; // make the function inaccessible in inherited class
```

But can still access in two ways:

```c++
int main()
{
    Derived derived { 7 };

    std::cout << derived.Base::getValue();

    std::cout << static_cast<Base&>(derived).getValue();

    return 0;
}
```
