# 17.4 - Constructors and initialization of derived classes

```c++
#include <iostream>

class A
{
public:
    A(int a)
    {
        std::cout << "A: " << a << '\n';
    }
};

class B : public A
{
public:
    B(int a, double b) : A { a }
    {
        std::cout << "B: " << b << '\n';
    }
};

class C : public B
{
public:
    C(int a, double b, char c) : B { a, b }
    {
        std::cout << "C: " << c << '\n';
    }
};

int main()
{
    C c { 5, 4.3, 'R' };
}
```

```
A: 5
B: 4.3
C: R
```

(Below is for a different ex):

1. Memory for derived is allocated.
2. The Derived(double, int) construct is called, where cost = 1.3, id = 5
3. The compiler looks to see if we've asked for a particular Base class constructor. We
   have! So it calls Base(int) with id = 5.
4. The base class constructor member initializer list sets `m_id` to 5.
5. The base class constructor body executes, which does nothing.
6. The base class constructor returns.
7. The derived class constructor member initializer list sets `m_cost` to 1.3.
8. The derived class constructor body executes, which does nothing.
9. The derived class constructor returns.

----

Can make members private now, since they're only called from each respective constructor.

----

When a derived class is destroyed, each destructor is called in the reverse order of
construction. E.g. when c is destroyed, the C destructor is called first, then the B
destructor, then the A destructor.
