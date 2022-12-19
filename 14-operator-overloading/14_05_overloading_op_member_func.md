# 14.5 - Overloading operators using member functions

* The overloaded operator must be added as a member function of the left operand.
* The left operand becomes the implicit `*this` object.
* All other operands become function parameters.

```c++
#include <iostream>

class Cents
{
private:
    int m_cents { };

public:
    Cents(int cents)
        : m_cents { cents }
    { }

    Cents operator+(int value);

    int getCents() const { return m_cents; }
};

Cents Cents::operator+(int value)
{
    return Cents { m_cents + value };
}

int main()
{
    Cents cents1 { 6 };
    Cents cents2 { cents1 + 2 };
    std::cout << "I have " << cents2.getCents() << " cents.\n";

    return 0;
}
```

`cents1 + 2` -> `cents1.operator+(2)` -> `operator+(&cents1, 2)`

### Not everything can be overloaded as a friend function
assignment =, subscript [], function call (), member selection ->

### Not everything can be overloaded as a member function
Binary operators that need left operand to be something specific. E.g. operator<< sith
std::ostrream, etc.

### When to use a normal, friend, or member function overload

* If you're overloading assignment, subscript, function call or member selection, do so as
  a member function.
* If you're overloading a unary operator, do so as a member function.
* If you're overloading a binary operator that does not modify its left operand (e.g.
  operator+), do as a normal function (preferred) or friend function.
* If you're overloading a binary operator that modifies its left operand, but you can't
  add members to the class definition of the left operand (e.g. operator<<, which has a
  left operand of type ostream), do so as a normal function (preferred) or friend function.
* If you're overloading a binary operator that modifies its left operand, (e.g.
  operator+=), you can modify the definition of the left operand, do so as a member
  function.
