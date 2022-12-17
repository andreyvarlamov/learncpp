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



# 11.17 - An introduction to std::vector

Dynamic arrays faster and easier. Comes with additional tricks. One of the most useful and
versatile tools in C++.

Introduced in C++03.

Handles its own memory management.

```c++
#include <vector>

std::vector<int> array;
std::vector<int> array2 = { 9, 7, 5, 3, 1 }; // use initializer list to initialize array (before C++11)
std::vector<int> array2 = { 9, 7, 5, 3, 1 }; // use uniform initialization to initialize array

// the type can be omitted since C++17
std::vector array4 { 9, 7, 5, 3, 1 }; // deduced to std::vector<int>
```

Accessing can be done via `[]`, which does no bounds checking. Or `at()` which does bounds
checking. If you request an element that is off the end of the array, the vector will not
automatically resize.

As of C++11, can also *assign* values to a `std::vector` using an initializer-list. Then
the vector will self-resize to match the number of elements provided.

### Self-cleanup prevents memory leaks
When a vector variable goes out of scope, it automatically deallocates the memory it
controls.

### Vectors remember their length
Unlike built-in dynamic arrays, which don't know the length of the array they are pointing
to, std::vector keeps track of its length.

`size()` function. Just like with `std::array` returns `size_type`, which is an alias of
`size_t`.

### Resizing a vector
`std::vector::resize`. Existing element values were preserved. May be resize to smaller.

```c++
std::vector vector { 0, 1, 2, 3, 4 };
vector.resize(10);
```

### Initializing a vector to a specific size
Resizing a vector is computationally expensive, so you should strive to minimize the
number of times you do so. If you need a vector with a specific number of elements but
don't know the values of the elements at the point of declaration, you can create a vector
with default elements using direct initialization.

```c++
std::vector a { 1, 2, 3 }; // allocate 3 elements with values 1, 2, and 3; type deduced
std::vector b { 3 }; // allocate 1 element with value 3; type deduced
std::vector<int> c ( 3 ); // allocate 3 elements with values 0, 0, 0
```

16.7 will cover how this works.

### Compacting bools
Special implementation for `std::vector` of type bool that will compact 8 booleans into a
byte. Happens behind the scenes, and doesn't change how you use the std::vector.

```c++
std::vector<bool> vector { true, false, false, true, true, false, false, true };
```

Recommended to use in most cases where dynamic arrays are needed.



# 11.18 - Introduction to iterators

Ranged-based for-loops use iterators.

### Iterators
An object designed to treverse through a container (e.g. the values in an array, or the
characters in a string), providing access to each element along the way.

A container may provide different kinds of iterators. E.g., an array container might offer
a forward iterator that walks through the array in forward order, and a reverse one that
walks through the array in reverse order.

Once the appropriate type of iterator is created, the programmer can then use the
interface provided by the iterator to traverse and access elements without having to worry
about what kind of traversal is being done or how the data is being stored in the
container.

C++ iterators typically use the same interface for traversal (`operator++` to move to the
next element) and access (`operator*` to access the current element).

### Pointers as an iterator
The simplest kind of iterator. Using pointer arithmetic.

```c++
#include <array>
#include <iostream>

int main()
{
    std::array data { 0, 1, 2, 3, 4, 5, 6 };

    auto begin { &data[0] };
    auto end { begin + std::size(data) }; // this points to one spot beyond the last element

    for (auto ptr { begin }; ptr != end; ++ptr) // ++ to move to the next element
    {
        std::cout << *ptr << ' '; // * to get value of current element
    }

    std::cout << '\n';

    return 0;
}
```

### Standard library iterators
`std::array` provides `begin()` and `end()`.

```c++
auto begin { array.begin() };
auto end { array.end() };
```

`<iterator>` header - two generic functions `std::begin` and `std::end`.

```c++
auto begin { std::begin(array) };
auto end { std::end(array) };
```

### Back to range-based for loops
All types that have both `begin()` and `end()` member functions, or that can be used with
`std::begin()` and `std::end()`, are usable in range-based for-loops.

Behind the scenes for-each calls `begin()` and `end()` of the type to iterate over.
`std::array` has `begin` and `end` member functions. C-style fixed arrays can be used with
`std::begin` and `std::end` functions. Dynamic arrays don't work though, because there is
no `std::end` function for them (because the type information doesn't contain the array's
length).

Possible to add those functions to your own types, so that they can be used with
range-based for-loops too.

Iterators are also used in `std::sort` and other algorithms.

### Iterator invalidation (dangling iterators)
Iterators can be left dangling if the elements being iterated over change address or are
destroyed. When this happens, we say the iterator has been **invalidated**. Accessing an
invalidated iterator produces undefined behavior.

> **Warning**<br>
> Some operations that modify containers (such as adding an element to a `std::vector`!) can
> have the side effect of causing the elements in the container to change addresses. When
> this happens, existing iterators to those elements will be invalidated. Good C++ reference
> documentation should note which container operations may or will invalidate iterators.



# 11.19 - Introduction to standard library algorithms

Because searching, counting and sorting are such common operations to do, the C++ standard
library comes with a bunch of functions to do these things in just a few lines of code.
Additionally, these standard library functions come pre-tested, are efficient, work on a
variety of different container types, and many support parallelization.

The functionality provided in the algorithms library generally fall into one of three
categories:

* **Inspectors** -- used to view (but not modify) data in a container. E.g. searching and
  counting.
* **Mutators** -- used to modify data in a container. E.g. sorting and shuffling.
* **Facilitators** -- used to generate a result based on values of the data members. E.g.
  objects that multiple values, or objects that determine what order pais of elements
  should be sorted in.

[Reference](https://en.cppreference.com/w/cpp/algorithm)

All of these make use of iterators.

### Using `std::find` to find an element by value

```c++
std::array arr { 13, 90, 99, 5, 40, 80 };

auto found { std::find(arr.begin(), arr.end(), 99) };

// Algorithms that don't find what they were looking for return the end iterator.
if (found == arr.end())
{
    // Not found
}
else
{
    *found = 199
}
```

### Using `std::find_if` to find an element that matches some condition

```c++
#include <algorithm>
#include <array>
#include <string_view>

bool containsNut(std::string_view str)
{
    // std::string_view::find returns std::string_view::npos if it doesn't find the
    // substring. Othrewise it returns the index where the substring occurs in str.
    return (str.find("nut") != std::string_view::npos);
}

int main()
{
    std::array<std::string_view, 4> arr { "apple", "banana", "walnut", "lemon" };

    auto found { std::find_if(arr.begin(), arr.end(), containsNut) };

    if (found == arr.end())
    {
        // Not found
    }
    else
    {
        // Found
    }

    return 0;
}
```

### Using `std::count` and `std::count_if` to count how many occurences there are
E.g. in the previous program replace `find_if` statement with:

```c++
auto nuts { std::count_if(arr.begin(), arr.end(), containsNut) };
```

Or replace `find` with `count`.

### Using `std::sort` to custom sort
Passing, as a third argument, a function that takes two parameters to compare, and returns true if the first
argument should be ordered before the second.

E.g. to sort an array in reverse order can do:

```c++
bool greater(int a, int b)
{
    return (a > b);
}

...
std::sort(arr.begin(), arr.end(), greater);
```

This is passing a function pointer. `std::sort` will use the pointer and call the actual
function with any 2 elements of the array.

C++ provides a custom type (named `std::greater`) for sorting in descending order. From
the `<functional>` header.

```c++
std::sort(arr.begin(), arr.end(), std::greater { } );
```

Note that `std::greater { }` needs the curly braces because it is not a callable function.
It's a type, and in order to use it, we need to instantiate an object of that type. The
curly braces instantiate an anonymous object of that typ (which then gets passed as an
argument to `std::sort`.

To understand how sort with custom sort function works:

```c++
#include <functional> // std::function
#include <iterator>
#include <utility>

void sort (int* begin, int* end, std::function<bool(int, int)> compare)
{
    for (auto startElement { begin }; startElement != end - 1; ++startElement)
    {
        auto smallestElement { startElement };

        for (auto currentElement { std::next(startElement) }; currentElement != end; ++currentElement)
        {
            if (compare(*currentElement, *smallestElement))
            {
                smallestElement = currentElement;
            }
        }

        std::swap(*startElement, *smallestElement);
    }
}

int main()
{
    int array[] { 2, 1, 9, 4, 5 };

    // use std::greater to sort in descending order
    // (We have to use the global namespace selector to prevent a collision
    // between our sort function and std::sort.)
    ::sort(std::begin(array), std::end(array), std::greater { });

    for (auto i : array)
    {
        // print sorted array elements
    }

    return 0;
}
```

### Using `std::for_each` to do something to all elements of a container

```c++
void doubleNumber(int& i)
{
    i *= 2;
}

...

std::for_each(arr.begin(), arr.end(), doubleNumber);
```

Can also skip elements at teh beginning or end of a container, e.g.:

```c++
std::for_each(std::next(arr.begin()), arr.end(), doubleNumber);
```

Like many algorithms, `std::for_each` can be parallelized to achieve faster processing,
making it better suited for large projects and big data than a range-based for-loop.

### Order of execution

> **Best practice**<br>
> Unless otherwise specified, do not assume that standard library algorithms will execute
> in a particular seqyence. `std::for_each`, `std::copy`, `sdt::copy_backward`,
> `std::move`, and `std::move_backward` have sequential guarantees.

### Ranges in C++20
C++20 addes *ranges*, which allows us to simply pass `arr`, instead of `arr.begin()` and
`arr.end()`.

### Conclusion
> **Best practice**<br>
> Favor using functions from the algorithms library over writing you own functionality to
> do the same thing.



# Additional algorithms (from the quiz 11.x)

### `std::reduce`

Applies a function, by default the `+` operator, to all elements in a list, resulting in a
single value.

There's also `std::accumulate`, but it cannot be parallelized, because it applies the
function left-to-right.

`std::reduce` segments the list, which means that the funciton is applied in an unknown
order, allowing the operation to be parallelized. If we want to sum up a list, we don't
care about the order and we use `std::reduce`.

`std::reduce` is currently not fully implemented in all major standard libraries. If it
doesn't work for you, fall back to `std::accumulate`.

```c++
int sum = std::reduce(arr.begin(), arr.end());
```

```c++
// The 0 is the initial value of the result
int sum = std::accumulate(arr.begin(), arr.end(), 0);
```

### `std::shuffle`

Randomly re-orders its elements. Needs a rng.

E.g.

```c++
std::mt19937 mt { static_cast<std::mt19937::result_type>(std::time(nullptr)) };
std::shuffle(arr.begin(), arr.end(), mt);
```
