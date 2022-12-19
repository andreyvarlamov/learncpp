# 14.15 - Overloading the assignment operator

The **assignment operator** is used to copy values from one object to another *already
existing object*.

### Assignment vs Copy constructor
The copy constructor initializes new objects, whereas the assignment operator replaces the
contents of existing objects.

### Overloading the assignment operator

```c++
#include <cassert>
#include <iostream>

class Fraction
{
private:
    int m_numerator { 0 };
    int m_denominator { 0 };

public:
    // Default constructor
    Fraction(int numerator = 0, int denominator = 1)
        : m_numerator { numerator }, m_denominator { denominator }
    {
        assert(denominator != 0);
    }

    // Copy constructor
    Fraction(const Fraction& copy)
        : m_numerator { copy.m_numerator }, m_denominator { copy.m_denominator }
    {
        std::cout << "Copy constructor called\n";
    }

    // Overloaded assignment
    Fraction& operator=(const Fraction& fraction);

    friend std::ostream& operator<<(std::ostream& out, const Fraction& f1);
};

// A simplistic implementation of operator=
Fraction& Fraction::operator=(const Fraction& fraction)
{
    m_numerator = fraction.m_numerator;
    m_denominator = fraction.m_denominator;

    return *this;
}

int main()
{
    Fraction fiveThirds { 5, 3 };
    Fraction f;
    f = fiveThirds; // calls overloaded assignment
    ...
}
```

Our overloaded operator= returns `*this`, so that we can chain multiple assignments
together:

```c++
...
f1 = f2 = f3;
```

### Issues due to self-assignment
Normally not an issue.

But is an issue when the assignment operator needs to dynamically assign memory.

Pointer member with memory allocated on heap.

Implementation of the assignment operator:

```c++
MyString& MyString::operator=(const MyString& str)
{
    // if data exists in the current string, delete it
    // otherwise - memory leak. When m_data is reassigned below.
    if (m_data) delete[] m_data;

    // allocate new memory for m_data
    m_data = new char[str.m_length];

    // copy values from str to the implicit object (i.e. *this)
    for (int i { 0 }; i < str.m_length; ++i)
    {
        m_data[i] = str.m_data[i];
    }

    // return the existing object so we can chain this operator
    return *this;
}
```

With the above, in the case of self-assignment, the data in `m_data` is garbage. Because
str refers to the same object as the implicit object in operator= function (`*this`).

```c++
MyString a { "aaa", 5 };
a = a; // this will cause the issue
```

### Detecting and handling self-assignment

```c++
if (this == &str)
{
    return *this;
}
```

Just a pointer comparison, so it should fast and not require == to be overloaded.

### When not to handle self-assignment
Skipped for copy constructors. Because the object being copy constructed is newly created,
the only case where the newly created object can be equal to the object being copied is
when you try to initialize a newly defined object with itself. In such cases, your
compiler should warn you that `c` is an uninitialized variable.

Can be omitted in classes that can naturally handle self-assignment. E.g. no dynamic
memory allocated.

### The copy and the swap idiom
TODO:
[On Stack Overflow](https://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom)

And:
[The Big Three](https://stackoverflow.com/questions/4172722/what-is-the-rule-of-three)

### Default assignment operator
The compiler will provide a default public assignment operator for your class if you do
not provide one. This assignment operator does memberwise assignment.

Can prevent assignments from being made by making the assignment operator private or using
the delete keyword.
