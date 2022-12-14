# 9 - Compound Types: References and Pointers

9.6 - 9.10

# 9.6 - Introduction to pointers

```c++
char x { }; // chars use 1 byte of memory
```

When this is executed, a piece of memory from RAM will be assigned to this object. Let's
say `x` is assigned memory address `140`. Whenever we use variable `x` in an expression or
statement, the program will go to memory address `140` to access the value stored there.

Also true with references. Becauses `ref` acts as an alias for `x`, whenever we use `ref`,
the program will go to memory address `140` to access the value.

### The address-of operator (&)
Although the memory addresses used by variables aren't exposed to use by default, we do
have access to this inormation. The **address-of operator** (&) returns the memory address
of its operand.

```c++
int x { 5 };
std::cout << x << '\n'; // print the value
std::cout << &x << '\n'; // print the memory address
```

For objects that use more than one byte of memory, address-of will return the memory
address of the first byte used by the object.

Note the confusion around & symbol (lvalue reference, address-of operator, bitwise AND).

### The dereference operator (*)
Also **indirection operator**.

```c++
std::cout << *(&x) << '\n'; // print the value at the memory address of variable x
// parentheses not required: *&x
```

### Pointers
A **pointer** is an object that holds a *memory address* (typically of another variable)
as its value. Store the address of some other object to use later.

> Note<br>
> In modern C++, these pointers are sometimes called "raw pointers" or "dumb pointers". To
> differentiate from "smart pointers", introduced more recently.

```c++
int x { 5 }; // normal variable

int& ref { x }; // a reference to an integer (bound to x)

int* ptr { &x }; // a pointer to an integer, initialized with address of var x
```

> **Best practice**<br>
> When declaring a pointer type, place the asterisk next to type name.

When declaring multiple variables on a single line, the asterisk has to be included with
each variable `int *ptr1, *ptr4;`

### Pointer initialization
A pointer that has not been initialized is called a **wild pointer**. Contain a garbage
address, and dereferencing it will result in undefined behavior.

> **Best practice**<br>
> Always initialized your pointers.

```c++
int x { 5 };
std::cout << x << '\n'; // print the value of variable x

int* ptr { &x }; // ptr holds the address of x
std::cout << *ptr << '\n'; // use dereference operator to print the value at the address
// that ptr is holding (x's address)
```

![Conceptually](https://www.learncpp.com/images/CppTutorial/Section6/6-Pointer.png?ezimgfmt=rs:409x145/rscb2/ng:webp/ngcb2)

This is where the pointers get their name fro -- ptr is "pointing to" x.

"An integer pointer" = "a pointer to an integer".

Types have to match.

With one exception that we'll discuss next lession, initializing a pointer with a literal
value is disallowed.

### Pointers and assignment
Can use assignment with pointers in 2 different ways:

1. To change what the pointer is pointing to
2. To change the value being pointed at

```c++
int x { 5 };
int y { 6 };

int* ptr { &x };
int* ptr2 { &x };

ptr = &y; // change ptr to point at y
*ptr2 = y; // assign the object at the address held by ptr (x) the value of y (6).
```

### Pointers behave much like lvalue references
...

References are not objects, pointers are.

### The address-of operator returns a pointer
Not the address as a literal, but an int*.

### The size of pointers
Dependent upon the architecture the executable is compiled for - a 32-bit executable uses
32-bit memory addresses, so a pointer will be 32 bits (4 bytes). With a 64-bit executable,
a pointer would be 64 bits (8 bytes).

### Dangling pointers
Holding the address of an object that is no longer valid (e.g. has been detroyed).
Dereferencing it - undefined results.



# 9.7 - Null pointers

### Null pointers
Besides a memory address, there is one additional value that a pointer can hold: a null
value. A **null value** (often shortened to **null**) is a special value that means
something has no value.

When a pointer is holding a null value, it means it's not pointing to anything.

`int* ptr { };`

> **Best practice**<br>
> Value initializae your pointers (to be null pointers) if you are not initializing them
> with the address of a valid object.

### The nullptr keyword

`nullptr` - null pointer literal.

`int* ptr { nullptr };`

### Dereferencing a null pointer results in undefined behavior
A null pointer doesn't have an address.

Accidentally derefercing null and dangling pointers is one of the most common reasons that
C++ programs crash in practice.

### Checking for nullpointers

`ptr == nullptr`

Pointers will implicitly convert to booleans: a null pointer converts to `false`.

> **Warning**<br>
> Conditionals can only be used to differentiate null pointers from non-null pointers.
> There is no convenient way to deteremine whether a non-null pointer is pointing to a
> valid object or dangling.

### Use nullptr to avoid dangling pointers
Ensure that any pointer that is not pointing at a valid object is set to `nullptr`.

But dangling pointers are not nulled automatically! Programmer's responsibility to ensure
that all pointers to an object that has just been destroyed are properly set to `nullptr`.

### Legacy null pointer literals: 0 and NULL
On modern architectures, the address 0 is typically used to represent a null pointer.
However, the value is not guaranteed by the C++ standard, and some architectures use other
values. The literal 0, when used in context of a null pointer, will be translated into
whatever address the architecture uses to represent a null pointer.

Additionally preprocessor macro `NULL` defined in the <cstddef> header. Inherited from C.

Should be avoided in modern C++.

### Favor references over pointers whenever possible
Pointers are inherently dangerous. References cannot be bound to null, and have to be
bound to a valid object upon creation and cannot be reseated.



# 9.8 - Pointers and const

```c++
const int x { 5 };
int* ptr { &x };
```

This won't compile.

### Pointer to const value

```c++
const int x { 5 };
const int* ptr { &x };
```

The value being pointed to can't be changed. However because a pointer to const is not
itself, we can change what the pointer is pointing to. Can point to non-const variables
too. Treat that value as constant, regardless of whether the object at that address was
initially defined as const or not.

### Const pointers
Make pointer itself constant: `int* const ptr { &x };`

The pointer itself cannot be changed, but we can change the value being to.

### Const pointer to a const value
```c++
const int* const ptr { &x };
```
