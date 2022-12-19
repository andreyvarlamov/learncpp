# 14.7 - Overloading the comparison operators

```c++
#include <iostream>

class Cents
{
private:
    int m_cents;

public:
    Cents(int cents)
        : m_cents { cents }
    { }

    friend bool operator==(const Cents& c1, const Cents&, c2) { return c1.m_cents == c2.m_cents; };
    friend bool operator!=(const Cents& c1, const Cents&, c2) { return !(operator==(c1, c2)); };

    friend bool operator<(const Cents& c1, const Cents&, c2) { return c1.m_cents < c2.m_cents; };
    friend bool operator>(const Cents& c1, const Cents&, c2) { return operator<(c2, c1); };

    friend bool operator<=(const Cents& c1, const Cents&, c2) { return !(operator>(c1, c2)); };
    friend bool operator>=(const Cents& c1, const Cents&, c2) { return !(operator<(c1, c2)); };
};
```

This is how to minimize the redundancy of overloading operators (re: !=, >, <=, >=).

> **Best practice**<br>
> Only define overloaded operators that make intuitive sense for your class. (e.g. what
> does greater or less mean for Car classes?)

But there's an exception: for sorting. E.g. this could mean sort Cars alphabetically.

### The spaceship operator `<=>` (C++20)

```c++
friend std::strong_ordering operator <=> (const Cents& c1, const Cents& c2)
{
    return c1.m_cents <=> c2.m_cents;
}

int main()
{
    Cents dime { 10 };
    Cents nickel { 5 };

    // return std::strong_ordering as m_cents are ints
    // strong_ordering can be used compared to 0
    // comparison is done only once which is cheap for non-built-in types
    auto comparison = (nickel <=> dime);

    ...

    comparison > 0; // a nickel is greater than dime
    comparison >= 0;
    ...
    comparison == 0
    ...
}
```
