# 11 - Arrays, Strings, and Dynamic allocations

11.11 - 11.15

### The need for dynamic memory allocation
C++ supports three basic types of memory allocation:

* **Static memroy allocation** happens for static and global variables. Memory for these
  types of variables is allocated once when your program is run and persists through the
  life of your program.
* **Automatic memory allocation** Happens for function parameters and local variables.
  Memory for these types of variables is allocated when the relevant block is entered, and
  freed when the block is exited, as many times as necessary.
* **Dynamic memory allocation**

Both static and automatic allocation have two things in common:

* The size of the variable / array must be known at compile time.
* Memory allocation and deallocation happens automatically (when the variable is
  instantiated / destroyed).

Usually this is just fine, but in some situations this may cause problems, usually when
dealing with external (user or file) input.

If we have to declare the size of everything at compile time, the best we can is try to
make a guess on the maximum size of variablers we'll need and hope that's enough:

```c++
char name[25];
Record record[500];
Monster monster[40];
Polygon rendering[30000];
```

Wasted memory if the variables aren't actually used.

Being able to tell which of these are actually used. 

Most normal variables (including fixed arrays) are allocated in a portion of memory called
the **stack**. Quite small. Visual Studio defaults the stack size to 1MB. If you exceed
this number, stack overflow will result, and the operating system will probably close down
the program.

```c++
int main()
{
    int array[1000000]; // probably 4MB of memory
}
```

Artificial limitations and/or array overflows.

**Dynamic memory allocation** is a way for running programs to request memory from the
operating system when needed. This memory does not come from the program's limited stack
memory; instead, it is allocated from a much larger pool of memory managed by the
operating system called the **heap**. On modern machines, the heap can be gigabytes in
size.

### Dynamically allocating single variables

```c++
new int; // dynamically allocate an integer (and discard the result)
```

Returns the pointer containing the address of the memory that has been allocated.

```c++
int* ptr { new int };
```

### How does dynamic memory allocation work?
Program memory regions. Heap. The program itself is responsible for requesting and
disposing of dynamically allocated memory.

### Unitializing a dynamically allocated variable

```c++
int* ptr1 { new int (5) }; // use direct initiallization
int* ptr2 { new int { 6 } }; // use uniform initiallization
```

### Deleting single variables

```c++
int* ptr { new int (1) };
delete ptr; // return the memory pointed to by ptr to the operating system
ptr = nullptr;
```

### What does it mean to delete memory?
The delete operator doesn't actually *delete* anything, but just returns the memory being
pointed to back to the OS.

Not deleting the actual (pointer) variable. Just returning the memory that it points to
(dangling pointer).

Deleting a pointer that is not pointing to dynamically allocated memory = bad.

### Dangling pointers
A few best practices:

1. Avoid having multiple pointers point at the same piece of dynamic memory. Or be clear
   about which pointer "owns" the memory (and is responsible for deleting it) and which
   pointers are just accessing it.
2. When you delete a opinter, if the pointer is not goind out of scope immediately after,
   set it to `nullptr`.

### Operator `new` can fail
Rare. OS may not have any memory to grant the request with. When that happens, a
`bad_alloc` exception is thrown.

```c++
int* value { new (std::nothrow) int }; // constant std::nothrow
```

But here if it fails to allocate - `nullptr`. Need to check for nullptr.

Because asking new for memory only fails rarely (and almost never in a dev environment),
it is common to forget to do this check.

### Null pointers and dynamic memory allocation

```c++
// If ptr isn't already allocated, allocate i
if (!ptr)
{
    ptr = new int;
}
```

Deleting a null pointer has no effect. So no need to check. Just `delete ptr`.

### Memory leaks

```c++
void doSomething()
{
    int* ptr { new int{} };
}
```

`ptr` goes out of scope. The memory is still allocated, cannot be reclaimed by the OS and
will not be freed until the program terminates.

The program "loses" the address of the dynamically allocated memory.

Eat up memory, making less memory available to this and other programs. In sever cases can
even eat up all the available memory, causing the machine to run slowly or crash.

Other ways:

```c++
int value = 5;
int* ptr { new int{} };
ptr = &value;
```

```c++
int* ptr { new int{} };
ptr = new int{};
```



# 11.12 - Dynamically allocating arrays

```c++
#include <iostream>

int main()
{
    std::cout << "Enter a positive integer: ";
    int length { };
    std::cin >> length;

    int* array { new int[length] { } }; // array new

    std::cout << "I just allocated an array of integers of length " << length << '\n';

    array[0] = 5;

    delete[] array; // array delete

    // Don't need to set array to nullptr/0 here because it's going out of scope
    // immediately after this anyeway

    return 0;
}
```

The length of dynamically allocated arrays has to be a type that's convertible to
`std::size_t`. In practice, using an `int` length is fine, since `int` will convert to
`std::size_t`.

Some might argue that it's best to use lengths of type `size_t`, or explicitly convert
through a `static_cast`.

No literal to represent `size_t`. So unlikely C++ designers intended us to strictly use
`size_t` types.

Some pedantic compiler might flag this as a signed/unsigned conversion error. However the
GCC does not (even with -Wsign-conversion).

Because this memory is allocated not on the stack (where fixed arrays are), we can make
the size very large.

### Dynamically deleting arrays
Have to use the array version. One of the most common mistakes new programmers make -
using the non-array version. Undefined behavior - data corruption, memory leaks, crashes,
etc.

How does array delete know how much memory to delete? Array `new[]` keeps track of how
much memory was allocated. Unfortunately, this size/length is not accessible to the
programmer.

### Dynamic arrays are almost identical to fixed arrays
But now the programmer is responsible for deallocating.

### Initializing dynamically allocated arrays
Zero-initialize: `int* array { new int[length]{} }`

Non-zero-initialize: pre C++11 - no easy way. Had to loop. Starting with C++11,
initializer lists:

```c++
int* array { new int[5] { 9, 7, 5, 3, 1 } };
```

### Resizing arrays
Can set the array length at the time of allocation, but no built-in way to resize an array
that has already been allocated. Workaround: allocate a new array, copy the elements,
delete the old array. Error prone, especially when the element type is a class (which have
special rules governing how they are created).

Recommended to avoid doing this yourself. Use `std::vector`.

See `sort_names.cpp` for Quiz Question 1

# 11.13 - For-each loops

**Range-based for-loop**.

```c++
constexpr int fibonacci[] { ... };
for (int num : fibonacci)
{
    std::cout << number << '\n';
}
```

### For each loops and the auto keyword
Ideal case in which to use `auto`.

```c++
for (auto number : fibonacci)...
```

### For-each loops and references

```c++
for (auto element : array) // element will be a copy of the current array element
...
```

Can be expensive. Most of the time we really just want to refer to the original element.

```c++
for (auto& element : array) // makes the element a reference to the actual array element
// preventing a copy from being made
...
```

Also good to make it a const:

```c++
for (const auto& element : array)
...
```

-

An array that decayed to a pointer cannot be used in a for-each loop. It needs to know how
big the array is. For the same reason, for-each won't work for dynamic arrays either.

### For-each loops and non-arrays
Works for `std::vector`, linked lists, trees maps, etc.

### Can I get the index of the current element?
No direct way. (Because many structures that for-each loops can be used with (such as
linked lists) are not directly indexable).

Since C++20, possible to add an init statement. So you can create an index variable
without polluting the function scope.

```c++
for (int i { 0 }; auto score : score)
{
    ...

    ++i;
}
```

### 11.14 - Void pointers
Special type of pointer that can point at objects of any data type.

```c++
void* ptr;
```

But dereferencing a void pointer is illegal. Have to cast the pointer to another pointer
type and then dereference.

```c++
*static_cast<int*>(ptr)
```

### Miscellany
Can be set to a null value:

```c++
void* ptr{ nullptr };
```

Although some compilers allow deleting a void pointer that points to dynamically allocated
memory, doing so should be avoided, as it can result in undefined behavior.

Not possible to do pointer arithmetic on a null pointer, because it needs to know the size
of the object it is pointing to.

### Conclusion
Very occasionally useful, but in generatl should be avoided. Because they effectively
allow you to avoid type checking. Can do things that don't make sense, and the compiler
won't complain about it.



# 11.15 - Pointers to pointers and dynamic multidimensional arrays

### Pointers to pointers

```c++
int value { 5 };

int* ptr { &value };
*ptr; // dereference pointer and get underlying int

int** ptrptr { &ptr };
**ptrptr // dereference pointer to pointer and get underlying pointer to int
```

Cannot do this:

```c++
int value { 5 };
int** ptrptr { &&value };
```

Because the address-of operator requires an lvalue, but &value is an rvalue.

Can be set to null

```c++
int ** ptr { nullptr };
```

### Arrays of pointers
The most common use for pointers to pointers: allocate an array of pointers.

```c++
int** array { new int*[10] }; // allocate an array of 10 int pointers
```

### Two-dimensional dynamically allocated arrays
Easy for fixed arrays:

```c++
int array[10][5];
```

Won't work:

```c++
int** array { new int[10][5] };
```

If the right most array dimension (*column count in each row*) is contexpr (*known at
compile time*):

```c++
int x { 7 }; // non-constant
int (*array)[5] { new int [x][5] }; // array of 5 (constexpr) pointers to int. Called "array".
```

If both dimensions are not known at compile time. Have to loop:

```c++
int** array { new int*[10] }; // An array of 10 int pointers - pointers to row arrays.

for (int i { 0 }; i < 10; ++i)
{
    array[i] = new int[5]; // Allocate memory for 5 ints and point each row pointer to
                           // that block of 5 ints in memory
```

Can access array as usual:

```c++
array[9][4] = 3;

// Same as
(array[9])[4] = 3;

// Same as
*(*(array + 9) + 4) = 3;
```

Deleting has to be in a loop too:

```c++
for (int i { 0 }; i < 10; ++i)
{
    delete[] array[i];
}
delete[] array; // delete the array of pointers to "rows" too
```

Easier to just flatten into a one-dimensional array of size x\*y.

Then each index is:

```c++
(row * colCount) + col;
```

### Passing a pointer by address
We can pass a pointer-to-a-pointer to a function and use that pointer to change the value
of the pointer it points to.

Or can pass the pointer by reference as in 9.10.

### Pointer to a pointer...

```c++
int*** ptrx3;
```

And more...

Very rare.

Recommended to avoid pointers to pointers unless no other options are available.
