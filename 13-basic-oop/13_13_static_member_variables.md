# 13.13 - Static member variables

Static member variables are shared by all objects of the class.

```c++
#include <iostream>

class Something
{
public:
    static int s_value;
};

int Something::s_value { 1 };

int main()
{
    Something first;
    Something second;

    first.s_value = 2;

    std::cout << first.s_value << '\n'; // 2
    std::cout << second.s_value << '\n'; // 2

    return 0;
}
```

### Static members are not associated with class objects

```c++
#include <iostream>

class Something
{
public:
    static int s_value; // declares the static member variable
};

int Something::s_value { 1 }; // defines the static member variable

int main()
{
    // We're not instantiating any objects of type Something

    Something::s_value = 2;
    std::cout << Something::s_value << '\n'; // 2

    return 0;
}
```

They are created when the program starts, and destroyed when the program ends.

> **Best practice**<br>
> Access static members by class name (using the scope resolution operator) rather than
> through an object of the class (using the member selection operator).

### Defining and initializing static member variables
When we declare a static member variable inside a class, we're telling the compiler about
the existence of a static member variable, but not actually defining it (much like a
forward declaration). Because static member variables are not part of the individual class
objects (they are treated similarly to global variables), you must explicitly define the
static member outside of the class, in the global scope.

In the example above:

```c++
int Something::s_value { 1 };
```

Instatiate the static member variable and (optionally) initialize it. If no initializer is
provided, C++ initializes the value to 0.

Not subject to access controls: you can define and initialize the variable even if it's
declared as private (or protected) in the class.

If the class is defined in a .h file, the static member definition is usually place in the
associated code file for the class (e.g. Something.cpp). If the class is defined in a .cpp
file, the static member definition is usually place directly underneath the class.

Do not put the static member definition in a header file (much like a global variable, if
the header file gets included more than once, you'll end up with multiple definitions,
which will cause a linker error).

### Inline initialization of static member variables
The static member can be initialized inside the class definition when:

1. The static member is a const integral type (which includes char and bool) or a
   const enum.
2. It is a static constexpr member
3. (As of C++17) the static member is declared inline

### An example of static member variables

```c++
#include <iostream>

class Something
{
private:
    static inline int s_idGenerator { 1 }; // C++17
//  static int s_idGenerator; // before C++17
    int m_id { };

public:
    Something() : m_id { s_idGenerator++ }
    { }

    int getID() const { return m_id; }
};

// Before C++17, we have to initialize the non-const static member outside the class
// definition.
// int something::s_idGenerator { 1 };

int main()
{
    Something first;
    Something second;
    Something third;

    std::cout << first.getID() << '\n';
    std::cout << second.getID() << '\n';
    std::cout << third.getID() << '\n';

    return 0;
}
```

(This can be really helpful when debugging multiple instances to tell them apart!)

Another use of static member variables is when you need an internal look up table. If you
make it static, only one copy will exist for all objects, saving memory.
