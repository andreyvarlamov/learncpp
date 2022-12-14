# 9 - Compouned Types: References and Pointers

9.11 - 9.12

# 9.11 - Return by reference and return by address
Similar situation with returns, a copy of the return value is passed back to the caller.

### Return by reference
```c++
std::string& returnByReference();
const std::string& returnByReferenceToCosnt();
```

```c++
#include <iostream>
#include <string>

const std::string& getProgramName()
{
    static const std::string s_programName { "Calculator" };
    // has static duration, destroyed at the end of the program

    return s_programName;
}

int main()
{
    std::cout << "This program is named " << getProgramName();

    return 0;
}
```

### The object being returned by reference must exist after the function returns
Otherwise the reference being returned will be left dangling.

E.g. in above example, it had to be static.

Modern compilers will produce a warning or error if you try to return a local variable by
reference, but compilers sometimes have trouble detecting more complicated cases.

### Don't return non-const local static variables by reference

```c++
#include <iostream>
#include <string>

const int& getNextId()
{
    static int s_x { 0 };
    ++s_x;
    return s_x;
}

int main()
{
    const int& id1 { getNextId() };
    const int& id2 { getNextId() };

    std::cout << id1 << id2 << '\n'; // 22

    return 0;
}
```

Returning a const reference to a const local static variable is sometimes done if the
local variable being returned by reference is expensive to create (so we don't have to
recreate the variable every function call).

### Assigning/initializing a normal variable with a returned reference makes a copy

```c++
#include <iostream>
#include <string>

const int& getNextId()
{
    static int s_x { 0 };
    ++s_x;
    return s_x;
}

int main()
{
    const int id1 { getNextId() }; // makes a copy into id1
    const int id2 { getNextId() }; // makes a copy into id2

    std::cout << id1 << id2 << '\n'; // 12

    return 0;
}
```

But this also defeats the purpose of returning a value by reference

### It's okay to return reference parameters by reference

```c++
#include <iostream>
#include <string>

const std::string& firstAlphabetical(const std::string& a, const std::string& b)
{
    return (a < b) ? a : b; // We can use < on std::string to determine which comes first alphabetically
}

int main()
{
    std::string hello { "Hello" };
    std::string world { "World" };

    std::cout << firstAlphabetical(hello, world) << '\n';

    return 0;
}
```

### The caller can modify values through the reference

```c++
#include <iostream>

int& max(int& x, int& y)
{
    return (x > y) ? x : y;
}

int main()
{
    int a { 5 };
    int b { 6 };

    max(a, b) = 7;

    std::cout << a << b << '\n'; // 57

    return 0;
}
```

### Return by address
It works almost identically to return by reference, except a pointer to an object is
returned, instead of a reference to an object.

The same primary caveat as return by reference -- the object being returned by address
must outlive the scope of the function returning the address, otherwise the caller will
receive a dangling pointer.

The major advantage is that we can have the funcion return nullptr if there's no valid
object to return.

The major disdvantage is that the caller has to remember to do a nullptr check before
dereferencing the return value.

> **Best practice**<br>
> Prefer return by reference over return by address unlesss the ability to return
> `nullptr` is important.
