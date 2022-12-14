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



# 9.12 - Type deduction with pointers, references, and const

`auto` keyword.

Will drop `const` (because it's copied).

### Type deduction drops references
Will also drop references. Just like with const, can reapply the reference.

`std::string& getRef(); auto& ref2 { getRef() };`

### Top-level const and low-level const
A **top-level const** is a const qualifier that applies to an object itself.

```c++
const int x;
int* const ptr;
```

A **low-level const** is a const qualifier that applies to the object being referenced or
pointed to.

```c++
const int& ref;
const int* ptr;
```

A reference to a const value is always a low-level const. A pointer can have either or
both.

When we say that type deduction drops const qualifiers, it only drops top-level consts.
Low-level consts are not dropped.

### Type deduction and const references
If the initializer is a reference to const, the reference is dropped first (and then
reapplied if applicable), and then any top-level const is dropped from the result.

Can repply either or both.

```c++
#include <string>

const std::string& getConstRef();

int main()
{
    auto ref1 { getConstRef() }; // std::string
    const auto ref2 { getConstRef() }; // const std::string

    auto& ref3 { getConstRef() }; // const std::string&
    // (if reapplying ref, have to reapply const too, or we would have a non-const ref to a const variable)
    const auto& ref4 { getConstRef() }; // const std::string&

    return 0;
}
```

> **Best practice**
> If you want a const reference, reapply the `const` qualifier even when it's not strictly
> necessary.

### Type deduction and pointers
Unlike references, type deduction does not drop pointers. But we can still use asterisk in
conjunction with pointer type deduction.

### The difference between auto and auto\*
With `auto*`, the pointer is reapplied, and the dudced type does not necessarily include a
pointer. In most cases, the practical effect is the same.

But:

```c++
#include <string>

std::string* getPtr();

int main()
{
    auto ptr3 { *getPtr() }; // std:string (already dereferenced)
    auto* ptr4 { *getPtr() }; // does not compile, initializer is not a pointer

    return 0;
}
```

### Type deduction and const pointers

Just like with references, only top-level const is dropped during pointer type deduction.

Returning regular pointer:

```c++
#include <string>

std::string* getPtr();

int main()
{
    // Make whatever the deduced type is const
    const auto ptr1 { getPtr() }; // std::string* const
    auto const ptr1 { getPtr() }; // std::string* const

    // Make the deduced pointer type a pointer to a const
    const auto* ptr1 { getPtr() }; // const std::string*
    // Make the deduced pointer type a const pointer
    auto* const ptr1 { getPtr() }; // std::string* const
}
```

Returning a const pointer to a const value

```c++
#include <string>

const std::string* const getConstPtr();

int main()
{
    // The top level const (the const on the pointer itself) is dropped
    // The low leve const on the object being pointed to is not dropped.
    auto ptr1 { getConstPtr() }; // const std::string*
    auto* ptr2 { getConstPtr() }; // const std::string*

    // The top level const is dropped, but we're reapplying it
    // The low-level const on the object being pointed to is not dropped
    auto const ptr3 { getConstPtr() }; // const std::string* const
    const auto ptr4 { getConstPtr() }; // const std::string* const

    // The top level const is dropped, but reapplied
    auto* const ptr5 { getConstPtr() }; // const std::string* const
    // The top level const is dropped. const applies const to the type being pointed to,
    // but it is already const
    const auto* ptr6 { getConstPtr() }; // const std::string*

    // error: const qualifier can not be applied twice
    const auto const ptr7 { getConstPtr() };
    // Applying const on both sides of the pointer. Allowed, since auto* must be a pointer type.
    const auto* const ptr8 { getConstPtr() }; // const std::string* const
}
```

> **Best practice**<br>
> If you want a const pointer, reapply the const qualifier, even when it's not strictly
> necessary. Makes your intent clear and helps prevent mistakes.
