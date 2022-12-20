# 17.3 - Order of construction of derived classes

C++ constructs derived classes in phases, starting with the most-base class (at the top of
the inheritance tree) and finishing with the most-child class (at the bottom of the
inheritance tree). As each class is contructed, the appropriate constructor from that
class is called to initialize that part of the class.

```c++
#include <iostream>

class A
{
public:
    A()
    {
        std::cout << "A\n";
    }
};

class B
{
public:
    B()
    {
        std::cout << "B\n";
    }
};

class C
{
public:
    C()
    {
        std::cout << "C\n";
    }
};

class D
{
public:
    D()
    {
        std::cout << "D\n";
    }
};

int main()
{
    std::cout << "Constructing A: \n";
    A a;

    std::cout << "Constructing B: \n";
    B b;

    std::cout << "Constructing C: \n";
    C c;

    std::cout << "Constructing D: \n";
    D d;
}
```

```
Constructing A:
A
Constructing B:
A
B
Constructing C:
A
B
C
Constructing D:
A
B
C
D
```
