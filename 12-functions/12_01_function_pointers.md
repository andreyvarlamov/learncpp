# 12.1 - Function Pointers

Functions have their own l-value function type, e.g. a function type that returns an
integer and takes no parameters.

When a function is called via the `()` operator, execution jumps to the address of the
function being called.

Possible to print out address of the function:

```c++
#include <iostream>

int foo()
{
    return 5;
}

int main()
{
    // Tell C++ to interpret function foo as a void pointer
    std::cout << reinterpret_cast<void*>(foo) << '\n';

    return 0;
}
```

### Pointers to functions

```c++
// fcnPtr is a pointer to a function that has no parameters and returns an integer.
// Can point to any function that matches that signature.
int (*fcnPtr)();
```

```c++
int (*const fcnPtr)(); // const function pointer
```

```c++
const int (*fcnPtr)(); // pointer to a function that returns a const int
```

### Assigning a function to a function pointer
Can use `&` - address-of operator.

```c++
int (*fcnPtr)() { &foo }; // fcnPtr points to function int foo()
fcnPtr = &goo; // fcnPtr points to function int goo()
```

The type (parameters and return type) must match the type of the function.

Unlike C++ *will* implicitly convert a function into a function pointer if needed. So
don't need `&`. However pointers will not convert to void pointers.

Can also be initialized or assigned the value `nullptr`.

### Calling a function using a function pointer
Can call it explicitly dereferencing or implicitly dereferencing. `(*fcnPtr)(5);` or
`fcnPtr(5)`.

The implicit dereference method looks just like a normal function call -- which is what
you'd expect, since normal function names are pointers to functions anyway! However some
older compilers do not support the implicit dereference method, but all modern compilers
should.

Default parameters won't work for functions called through pointers. Default parameters
are resolved at compile-time (that is, if you don't supply an argument for a default
parameter, the compiler substitutes one in for you when the code is compiled). However,
function pointers are resolved at run-time.

Because a function pointer can be set to `nullptr`, it's a good idea to assert or
conditionally test whether your function pointer is a null before calling it.
Dereferencing a null function pointer can lead to undefined behavior.

### Passing functions as arguments to other functions
**Callback functions**.

See `2_custom_sort_2.cpp`.

A way to allow a caller to "hook" their own functionality into something you wrote.

Note: if a function parameter is of a function type, it will be converted to apointer to
the function type.

```c++
void selectionSort(int* array, int size, bool (*comparisonFcn)(int, int))
```

Can be written as:

```c++
void selectionSort(int* array, int size, bool comparisonFcn(int, int))
```

### Providing default functions

### Making function pointers prettier with type aliases

```c++
using ValidateFunction = bool(*)(int, int);
```

Now, instead of:

```c++
bool validate(int x, int y, bool (*fcnPtr)(int, int));
```

Do this:

```c++
bool validate(int x, int y, ValidateFunction pfcn);
```

### Using `std::function`
From header \<functional\>.

Passing a function to a function:

```c++
bool validate(int x, int y, std::function<bool(int, int)> fcn);
```

Declaring function pointers

```c++
std::function<int()> fcnPtr { &foo }; // declare function pointer that returns an int and
                                      // takes no parameters

fcnPtr = &goo;

std::cout << fcnPtr() << '\n'; // call the function like normal
```

Type aliasing can be helpful:

```c++
using ValidateFunctionRaw = bool(*)(int, int);
using ValidateFunction = std::function<bool(int, int)>;
```

`std::function` only allows calling the function via implicit dereference, not explicit
dereference.

As of C++17, CTAD can be used to deduce the template parameters of a std::function from an
initializer.

```c++
std::function fcnPtr { &foo };
```

### Type inference for function pointers

```c++
auto fcnPtr { &foo };
```

### Conclusion
Function pointers are useful primarily when you want to store functions in an array (or
other structure), or when you need to pass a function to another function. Because the
native syntax to declare function pointers is ugly and error prone, it is recommended to
use `std::function`.

In places where a function pointer type is used only once, `std::function` can be used
directly. In places where a function pointer type is used multiple times, a type alias to
a `std::function` is a better choice.
