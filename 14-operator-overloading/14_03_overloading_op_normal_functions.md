# 14.3 - Overloading operators using normal functions

Cents.h:

```c++
#ifndef CENTS_H
#define CENTS_H

class Cents
{
private:
    int m_cents { };

public:
    Cents(int cents)
        : m_cents { cents }
    { }

    int getCents() const { return m_cents; }
};

// Need to explicitly provide prototype for operator+, so uses of operator+ in other files
// know this overload exists
Cents operator+(const Cents& c1, const Cents& c2);
```

Cents.cpp:

```c++
#include "Cents.h"

// This function is not a member function nor a friend function
Cents operator+(const Cents& c1, const Cents& c2)
{
    return { c1.getCents() + c2.getCents() };
}
```

main.cpp:

```c++
#include "Cents.h"
#include <iostream>

int main()
{
    Cents cents1 { 6 };
    Cents cents2 { 8 };
    Cents centsSum { cents1 + cents2 };
    std::cout << "I have " << centsSum.getCents() << " cents.\n";

    return 0;
}
```

> **Best practice**<br>
> Prefer overloading operators as normal functions instead of friends if it's possible to
> do so without adding additional member functions. The less functions touching your
> classes's internals, the better.
