# 11 - Arrays, Strings, and Dynamic allocations

11.16 - 11.19

# 11.16 - An introduction to `std::array`
Both fixed and dynamic arrays that are built into the C++ language have their downsides:
fices arrays decay into pointers, losing the array information when they do, and dynamic
arrays have messy deallocation issues and are challenging to resize without error.

Enter `std::array` and `std::vector`.

### An introduction to `std::aray`

```c++
#include <array>

std::array<int, 3> myArray;
```

The length of a `std::array` must be known at compile time.

Doesn't decay to a pointer when to a function.

Can deduce the type and size when explicitly initialized.

...

Accessing with a subscript operator `[]` works as expected. Also does not do
bounds-checking: invalid index -> undefined result.

Std lib provides `std::array::at()` - that does runtime bounds checking. Will throw
`std::out_of_range` exceptions. Slower but safer than `[]`.

```c++
myArray.at(1) = 5;
```

### Size and sorting

```c++
myArray.size(); // return the length of myArray
```

> **Best practice**<br>
> Pass `std::array` into functions by reference or const reference.

```c++
void printLength(const std::array<double, 5>& myArray)
...
```

Range-based for-loops work.

Can sort using `std::sort` from the `<algorithm>` header.

### Passing `std::array` of different lengths to a function
Because the element type and array length are part of the type information, when
`std::array` is passed as a function parameter, we have to specify the element type and
array length.

How to pass with different type and length? Using templates.

```c++
#include <array>
#include <cstddef>
#include <iostream>

template <typename T, std::size_t size>
void printArray(const std::array<T, size>& myArray)
{
    for (auto element : myArray)
    {
        std::cout << element << ' ';
    }

    std::cout << '\n';
}

int main()
{
    std::array myArray5 { 9.0, 7.2, 5.4, 3.6, 1.8 };
    printArray(myArray5); // template parameters will be deduced (because myArray5 is of
                          // type std::array<double, 5>
}
```

### Manually indexing `std::array` via `size_type`
Signed/unsigned mismatch

```c++
for (int i { 0 }; i < myArray.size(); ++i)
{
    myArray[i];
    ...
}
```

`size()` and array index parameter to `operator[]` take a type called `size_type`. Not a
global type. Defined inside the definition of `std::array` as an unsigned integral type.

Therefore both `i < myArray.size()` and `myArray[i]` have type mismatches.

The correct way to write this would be:

```c++
for (std::array<int, 5>::size_type i { 0 }; i < myArray.size(); ++i)
```

But it is just an alias for `std::size_t`. So can use that instead.

```c++
for (std::size_t i { 0 }; i < myArray.size(); ++i)
```

A better solution is to avoid indexing `std::array` in the first place and just use use
for-loops or iterators if possible.

Unsingned integers wrap around. E.g. decrementing index that is 0 already when doing
`...; i >= 0; --i`. Infinite loop.

An ugly way to do a reverse for-loop:

```c++
#include <arra>
#include <iostream>

int main()
{
    std::array myArray { 7, 3, 1, 9, 5 };

    // Decrement index in the condition, and use the postfix operator. So that
    // it will check and see that it's 0 and thus stop the loop,
    // before decrementing it and wrapping around.
    for (auto i { myArray.size() }; i-- > 0; )
    {
        std::cout << myArray[i] << ' ';
    }

    std::cout << '\n';

    return 0;
}
```

### Array of struct
Works with structs, but a caveat with initializing the array.

Works:

```c++
struct House
{
    int number{};
    int stories{};
    int roomsPerStory{};
};

std::array<House, 3> houses{};

house[0] = { 13, 4, 30 };
house[1] = { 14, 3, 10 };
house[2] = { 15, 3, 40 };
```

Doesn't work:

```c++
std::array<House, 3> houses { // initializer for houses
    { 13, 4, 30 }, // initializer for the C-style array member inside the std::array struct
    { 14, 3, 10 }, // ?
    { 15, 3, 40 }  // ?
};
```

A `std::array` is defined as a struct that contains a C-style array member (whose name is
implementation defined).

The compiler will interpret `{ 13, 4, 30 }` as the initializer for the entire array. This
has the affect of initializing the struct with index 0 with those values, and
zero-initializing the rest of the struct elements. Then the compiler will discover we've
provided two more initialization values and produce a compilation error saying that we've
provided too many initialization values.

```c++
std::array<House, 3> houses { // initializer for houses
    { // extra set of braces to initializae the C-style array member inside the std::array struct
        { 13, 4, 30 }, // initializer for array element 0
        { 14, 3, 10 }, // initializer for array element 1
        { 15, 3, 40 }  // initializer for array element 2
    }
};
```

Recommended to use `std::array` over built-in fixed arrays for any non-trivial array use.