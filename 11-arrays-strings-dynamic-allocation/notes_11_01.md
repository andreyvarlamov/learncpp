# 11 - Array, Strings, and Dynamic Allocation

11.1 - 11.5

# 11.1 -  Arrays (Part 1)

Aother aggregate data type.

**Fixed array**, **fixed length array** - length known at compile time.

### Array elements and subscripting
**Element**. **Subscript operator** `[]`, **subscript** or **index**.

### An example array program

```c++
#include <iostream>

int main()
{
    int prime[5] { };
    prime[0] = 2;
    prime[1] = 3;
    prime[2] = 5;
    prime[3] = 5;
    prime[5] = 11;

    std::cout << "The lowest prime number is: " << prime[0] << '\n';
    std::cout << "The sum of the first 5 primes is: " << prime[0] + prime[1] + prime[2]
        + prime[3] +  prime[4] + << '\n';

    return 0;
}
```

### Array data types

### Array subscripts
Must be an integral type: char, short, int, long long, etc..., bool.

### Fixed array declaration
When declaring a fixed array, the length must be a compile-time constant.

### A note on dynamic arrays
Fixed arrays have memory allocated at compile time.

There are also **dynamic arrays**.



# 11.2 - Arrays (Part 2)

### Initializing fixed arrays
Array elements are treated just like normal variables, and as such, they are not
initialized when created.

```c++
int prime[5];
prime[0] = 2;
prime[1] = 3;
prime[2] = 5;
prime[3] = 7;
prime[4] = 11;
```

But this is not initialization, but assignment. Won't work if the array is `const`.

**Initializer list**.

```c++
int prime[5] { 2, 3, 5, 7, 11 };
```

If there are more initializers in the list than the array can hold -> compiler error.

If there are less - remaining are zero initialized.

To initialize all to zero:

```c++
int prime[5] { };
```

> **Best practice**<br>
> Explicitly initialize your arrays (even when the element type is self-initializing).

### Omitted length
Compiler can figure out the length of the array using initializer.

### Arrays and enums

```c++
enum StudentNames
{
    kenny,
    kyle,
    stan,
    butters,
    cartman,
    max_students,
};

int main()
{
    int testScores[max_students] { };
    testScores[stan] = 76;

    return 0;
}
```

### Arrays and enum classes
Enum classes don't have an implicit conversion to integer. Can static\_cast. Can be a
pain, so it might be better to use a standard enum inside a namespace.

### Passing arrays to functions
C++ *does not* copy an array when it is passed into a function. The actual array is
passed. Side effect of allowing functions to directly change the value of array elements.

If you want to ensure the function does not modify the array elements, you can make the
array const.

### Determining the length of the array

```c++
#include <iostream>
#include <iterator>

int main()
{
    int array[] { 1, 1, 2, 3, 5, 8, 13, 21 };
    std::cout << "The array has: " << std::size(array) << " elements\n";

    return 0;
}
```

> **Warning**<br>
> Due to the way C++ passes arrays to functions, this will not work for arrays that have
> been passed to functions!

`std::size()` will work with other kinds of objects (such as `std::array` and
`std::vector`). Returns an unsigned value. If you need a signed value, can either cast the
result or, since C++, use std::ssize() (stands for signed size).

`std::size()` was added in C++17. On older compilers, can use `sizeof` instead.

```c++
sizeof(array) / sizeof(array[0])
```

Can use the `sizeof` trick when passed to a function. But it will return the size of the
pointer. Not of the whole array.

A properly configured compiler should print a warning when you try to use sizeof() on an
array that was passed to a function.

### Indexing an array out of range.
C++ does not do any checking to make sure that indices are valid for the length of your
array. Undefined behavior: could overwrite the value of another variable, or cause the
program to crash. C++ will also let you use a negative index.



# 11.3 - Arrays and loops

```c++
constexpr int scores[] { 84, 92, 81, 56 };
constexpr int numStudents { static_cast<int>(std::size(scores)) };

int maxScore { 0 };

for (int student { 0 }; student < numStudents; ++student)
{
    if (scores[student] > maxScore)
    {
        maxScores = scores[student];
    }
}
```

### Mixing loop and arrays

### Arrays and off-by-one errors



# 11.4 - Sorting an array using selection sort

### A case for sorting

### How sorting works
Typically comparing pairs of elements and swapping. Can use `std::swap()` from <utility>.

### Selection sort
One of the slower sorts, but easy to understand.

Steps:
1. Start at array index 0, search the entire array to find the smallest value
2. Swap the smallest value found in the array with the value at index 0
3. Repeat steps 1 & 2 starting from the next indeces

### Selection sort in C++

```c++
#include <iostream>
#include <iterator>
#include <utility>

int main()
{
    int array[] { 30, 50, 20, 10, 40 };
    constexpr int length { static_cast<int>(std::size(array)) };

    for (int startIndex { 0 }; startIndex < length - 1; ++startIndex)
    {
        int smallestIndex { startIndex };

        for (int currentIndex { startIndex +1 }; currentIndex < length; ++currentIndex)
        {
            if (array[currentIndex] < array[smallestIndex])
            {
                smallestIndex = currentIndex;
            }
        }

        std::swap(array[startIndex], array[smallestIndex]);
    }

    for (int index { 0 }; index < length; ++index)
    {
        std::cout << array[index] << ' ';
    }

    std::cout << '\n';

    return 0;
}
```

Sorting names works using the same algorithm. Just change the array type from int to
std::string and initialize with appropriate values.

### std::sort
<algorithm> header.

By default, std::sort sorts in aschending order using operator< to compare pairs of
elements and swapping them if necessary.

```c++
std::sort(std::begin(array), std::end(array));
```

See `bubble_sort.cpp` for Quiz Questions 3 and 4
