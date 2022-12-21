# 18.11 - Printing inherited classes using operator<<

Can't make the friend function operator<< virtual.

Delegate the responsibility to print to a normal member function that is virtualized.

```c++
#include <iostream>

class Base
{
public:
    // Overloaded operator<<
    friend std::ostream& operator<<(std::ostream& out, const Base& b)
    {
        // Delegate printing responsibility to member function print()
        return b.print(out);
    }

    // Because this is normal member function, it can be virtualized
    virtual std::ostream& print(std::ostream& out) const
    {
        out << "Base";
        return out;
    }
};

class Derived : public Base
{
public:
    // Override print function to handle the Derived case
    std::ostream& print(std::ostream& out) const override
    {
        out << "Derived";
        return out;
    }
};

int main()
{
    Base b { };
    std::cout << b << '\n'; // Base

    Derived d { };
    std::cout << d << '\n'; // Derived

    Base& bref { d };
    std::cout << bref << '\n'; // Derived

    return 0;
}
```

In the first case, we call operator<<, which calls virtual function print(). Since our
Base reference parameter points to a Base object, b.print() resolves to Base::print(),
which does the printing.

In the second case, the compiler first looks to see if there's an operator<, that takes a
Derived object. There isn't one, because we didn't define one. Next the compiler looks to
see if there's an operator<< that takes a Base object. There is, so the compiler does an
implicit upcast of our Derived object to a Base& and calls the function. This function
calls virtual print(), which resolves to Derived::print().

The third case. First, the compiler matches variable bref with operator<< that take a
Base. That calls our virtual print() function. Since the Base reference is actually
pointing to a Derived object, this resolves to Derived::print(), as we intended.
