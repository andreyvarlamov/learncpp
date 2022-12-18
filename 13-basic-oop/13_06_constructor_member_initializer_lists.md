# 13.6 - Constructor member initializer lists

Problem: assigning values to const or reference member vaariables in the body of the
constructor. They must be initialized on the line they are declared.

### Member initializer lists

```c++
class Something
{
private:
    int a { };
    double b { };
    char c { };
    const int x; // will be initialized in the constructor

public:
    Something(int a, double b, char c, int x = 5)
        : a { a }, b { b }, c { c }, x { x } 
    {
        // no need for assignment here
    }

    ...
};

...
```

> **Best practice**<br>
> Use member initializer lists to initialize your class member variables instead of
> assignment.

### Initializing array member with member initializer lists

Pre C++11, can only zero-initialize:

```c++
...
{
    const int m_array[5];

public:
    Something(): m_array { } // zero initialize the member array
    {
    }
...
```

Since C++11, can only zero-initialize:

```c++
...
{
    const int m_array[5];

public:
    Something(): m_array { 1, 2, 3, 4, 5 } // zero initialize the member array
    {
    }
...
```

### Initializing member variables that are classes

```c++
#include <iostream>

class A
{
public:
    A(int x = 0) { std::cout << "A " << x << '\n'; }
};

class B
{
public:
    B(int y) : m_a { y - 1 } // call A(int) constructor to initialize member m_a
    {
        std::cout << "B " << '\n';
    }
};

int main()
{
    B b { 5 };
    return 0;
}
```

Output:

```
A 4
B 5
```

### Formatting your initializer lists
If fits, on one line:

```c++
Something() : m_value1 { 1 }, m_value2 { 2.2 }, m_value3 { 'c' }
...
```

If doesn't, on two:

```c++
Something(int value1, double value2, char value3='c')
    : m_value1 { value1 }, m_value2 { value2 }, m_value3 { value3 }
...
```

Or, one per line:

```c++
Something(int value1, double value2, char value3='c', float value4=34.6f)
    : m_value1 { value1 }
    , m_value2 { value2 }
    , m_value3 { value3 }
    , m_value4 { value4 }
{
}
...
```

### Initializer list order
Variables in the initializer list are not initialized in the order that they are specified
in the initializer list, but in the order in which they are declared in the class.
