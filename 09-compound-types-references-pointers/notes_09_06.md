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



# 9.9 - Pass by address

With **pass by address**, instead of providing an object as an argument, the caller
provides an object's address (via a pointer). The pointer argument is copied into a pointer
parameter of the called function.

```c++
void print_by_address(const std::string* ptr)
{
    std::cout << *ptr << '\n';
}

std::string str { "Hello, world!" };
print_by_address(&str);
```

### Pass by address does not make a copy of the object being pointed to

### Pass by address allows the function to modify the argument's value
If non-const

### Null checking
When passsing a parameter by address, care should be taken to ensure the pointer is not a
null pointer before you dereference the value.

```c++
void print(int* ptr)
{
    if (ptr)
    {
        std::cout << *ptr;
    }
}
```

Or test as a precondition in the beginning of a function.

Assert can also be used. `assert(ptr)`.

### Prefer pass by (const) reference
An object being passed by address must have an address, so only lvalues can be passed by
adress (as rvalues don't have addresses). Pass by const reference is more flexible, it can
accept both lvalues and rvalues.

The syntax for pass by reference is more natural.

In modern C++, most things that can be done with pass by address are better accomplished
through other methods.

> **Best practice**<br>
> Pass by reference when you can, pass by address when you must.



# 9.10 - Pass by address (part 2)

### Pass by address for "optional" arguments

```c++
void greet(std::string* name=nullptr)
{
    std::cout << "Hello ";
    std::cout << (name ? *name : "guest") << "\n";
}
```

However, in many cases, function overloading is a better alternative. Number of
advantages: no longer need to worry about null dereferences, could pass in a string
literal if we wanted to.

### Changing what a pointer parameter points at

```c++
void nullify([[maybe_unused]] int* ptr2)
{
    ptr2 = nullptr;
}
```

Has no impact on the address held bey the argument. A copy of the address is passed in.

### Pass by address ... by reference?

```c++
void nullify(int*& refptr)
{
    refptr = nullptr;
}
```

Will modify the original pointer.

### Why using `0` and `NULL` is no longer preferred
`0` can be interpreted as either an integrral literal or a null pointer literal. Can cause
unintended consequences to the behavior of our program.

The definition of preprocessor macro `NULL` is not defined by the language standard. Can
be defined as `0`, `0L`, `((void*)0), or something else entirely.

This can cause issues with overloaded functions. When passing integer value `0` as a
parameter, the compiler will prefer `print(int)` over `print(int*)`.

### std::nullptr\_t
Since `nullptr` can be differentiated from integer values in function overloads, it must
have a different type. The type is `std::nullptr_t` (defined in header <cstddef>).

But pointers will not implicitly convert to a `std::nullptr_t`, they will stay as (e.g.)
`int*`, even when assigned null. So that doesn't work for function overloading, because it
matches on types, not values.

### There is only pass by value
While the compiler can often optimize references away entirely, there are cases where this
is not possible, and a reference is actually needed. References are normally implemented
by the compiler using pointers. So behind the scenes, pass by reference is essentially
just a pass by address.

As mentioned previously, the pass by address just copies an address from the caller to the
called function -- which is just passing an address by value.

Therefore, C++ really passes everything by value. The properties of pass by address (and
reference) come solely from the fact that we can dereference the passed address to change
the argument.
