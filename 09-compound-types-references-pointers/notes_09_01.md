# 9 - Compound Types: References and Pointers

9.1 - 9.5

# 9.1 - Introduction to compound data types

### Compound data types
Or **composite data types**. Data types that can be constructed from fundamental data
types (or other compound data types).

* Functions
* Arrays
* Pointer types
  * Pointer to object
  * Pointer to function
* Pointer to member types
  * Pointer to data member
  * Pointer to member function
* Reference types
  * L-value reference
  * R-value reference
* Enumerated types
  * Unscoped enumerations
  * Scoped enumerations
* Class types
  * Structs
  * Classes
  * Unions



# 9.2 - Value categories (lvalues and rvalues)

### The properties of an expression
To help determine how expressions should evaluate and where they can be used, all
expressions in C++ have 2 properties: a type and a value category.

### The type of an expression
Equivalent to the type of the value, object, or function that results from the evaluated
expression.

The compiler can use the type of an expression to determine whether an expression is valid
in a given context.

Note that type of an expression must be determinable at compile time (otherwise type
checking and type deduction wouldn't work), however, the value of an expression may be
determined at either compile time (if the expression is constexpr) or runtime (if the
expression is not constexpr).

### The value category of an expression

E.g.

```c++
x = 5; // valid
5 = x; // invalid
```

So how does the compiler know which expressions can legally appear on either side of an
assignment statement?

The **value category** of an expression (or subexpression) indicates whether tan
expression resolves to a value, a function, or an of some kind.

Prior to C++11, only two possible value categories: `lvalue` and `rvalue`.

In C++11, three additional value categories introduced (`glvalue`, `prvalue` and `xvalue`)
to support a new feature called *move semantics*.

In this lession, we'll stick to pre-C++11 view of value categories.

### Lvalue and rvalue expressions
Short for "left value" or "locator value". An expression that evaluates to an identifiable
object or function (or bit-field).

The term "identity" is used by the C++ standard, but is not well-defined. An entity (such
as an object or function) that has an identity can be differentiated from other similar
entities (typically by comparing the addresses of the entity).

Entities with identities can be accessed via an identifier, reference, or pointer, and
typically have a lifetime longer than a single expression or statement.

```c++
int x { 5 };
int y { x }; // x is an lvalue expression
```

Expression `x` is an lvalue expression as it evaluates to variable `x` (which has an
identifier).

Since the introduction of constants into the language, lvalues come in two subtypes: a
**modifiable lvalue** and a **non-modifiable lvalue**.

```c++
int x{};
const double d{};

int y { x }; // x is a modifiable lvalue expression
const double e { d }; // d is a non-modifiable lvalue expression
```

An **rvalue** - short for "right value". An expression that is not an l-value. Commonly
seen rvalues include literals (except C-style string literals, which are lvalues) and
return value of functions and operators. Rvalues aren't identifiable (meaning they have to
be used immediately), and only exist withing the scope of the expression in which they are
used.

Produce temporary values that are not identifiable objects.

Now we can answer the question about why `x = 5` is valid but `5 = x` is not. An
assignment operation requires the left operand of the assignment to be a modifiable lvalue
expression, and the right operand to be an rvalue expression. The latter fails because the
left operand expression `5` is not an lvalue.

[Full list of lvalue and rvalue expressions](https://en.cppreference.com/w/cpp/language/value_category)

### Lvalue to rvalue conversion
Lvalues will implicitly convert to rvalues, so an lvalue can be used wherever an rvalue is
required.

`x = x + 1` -- On the left side of the assignment operator, x is an lvalue expression that
evaluates to variable x. On the right side of the assignment operator, x + 1 is an rvalue
expression that evaluates to the value 3.

Now we get to the first compound type: the `lvalue reference`.

As a rule of thumb to identify lvalue and rvalue expressions:

* lvalues expressions are those that evaluate to variables or other identifiable objects
  that persist beyond the end of the expression.

* rvalues expressions are those that evaluate to literals or the returned value of
  functions and operators that are discarded at the end of the expression.



# 9.3 - Lvalue references

**Reference** - alias for an existing object. Once a reference has been defined, any
operation on the reference is applied to the object being referenced.

2 types of references: **lvalue references** and **rvalue references**.

### Lvalue reference types
**Lvalue reference** (commonly just reference, prior to C++11 the only type of reference)
acts as an alias for an existing lvalue.

`int&`

### Lvalue reference variables

```c++
int x { 5 };
int& ref { x };
```

To the compiler, it doesn't matter whether the ampersand is attached to the type name or
the variable's name.

> **Best practice**<br>
> `int& ref;`

"lvalue reference to", not "address of".

### Initialization of lvalue references

All references must be initialized.

"Bound" to an object (or function). The process = "reference binding". The object -
referent.

Must be bound to a modifiable value.

```c++
const int x { 5 };
int& ref { x }; // invalid
int& ref { 0 }; // invalid
```

"Lvalue references to non-const". "Non-const reference".

In most cases the type of reference must match the type of the referent (exceptions -
inheritance).

### References can't be reseated (changed to refer to another object)

This will compile and run, but not function as expected.

```c++
int x { 5 };
int y { 6 };

int& ref { x }; // ref is now alias for x

ref = y; // assigns 6 (the value of y) to x (the object being referenced by ref)
```

### Lvalue reference scope and duration
Same scoping and duration.

### References and referents have independent lifetimes

* A reference can be destroyed before the object it is referencing
* The object being referenced can be destroyed before the reference.

### Dangling references
When an object referenced is destroyed before a reference to it, the reference is left
referencing an object that no longer exists.

### References aren't objects
Not required to exist or occupy storage. If possible, the compiler will optimize
references away by replacing all occurrences of a reference with the referent. However,
this isn't always possible, and in such cases, references may require storage.

Because references aren't objects they can't be used anywhere an objected is required
(e.g. a reference to a reference, since an lvalue reference must reference an identifiable
object).

In cases where you need a reference that is an object or a reference that can be reseated,
`std::reference_wrapper` provides a solution

```c++
int var { };
int& ref1 { var }; // an lvalue reference bound to var
int& ref2 { ref1 }; // an lvalue reference bound to var
```

A reference to a reference (e.g. an `int&`) would have syntax `int&&`, but since C++
doesn't support references to references, this syntax was repurposed in C++11 to indicate
an rvalue reference.



# 9.3 - Lvalue references to const

```c++
const int x { 5 };
int& ref { x };
```

Disallowed because it would allow us to modify a const variable through the non-const
reference.

### Lvalue reference to const

```c++
const int x { 5 };
const int& ref { x };
```

^ allowed.

Can be accessed but not modified

### Initializing an lvalue reference to const with a modifiable lvalue
Can also bind to modifiable values. In such a case, the object being referenced is treated
as const when accessed through the reference, even though the underlying object is
non-const.

> **Best practice**<br>
> Favor *lvalue references to const* over *lvalue references to non-const*, unless you
> need to modify the object being referenced.

### Initializing an lvalue reference to const with an rvalue
Allowed. When this happens, a temporary object is created and initialized with the rvalue,
and the reference to const is bound to that temporary object.

A **temporary object** (**anonymous object**) - created for temporary use (and then
destroyed) within a single expression. They have no scope at all (this makes sense, since
scope is a property of an identifier, and temporary objects have no identifier).

### Const references bound to temporary objects extend the lifetime of the temporary object



# 9.5 - Pass by lvalue reference
*Pass by value* - an argument passed to a function is coped into the function's parameter.
E.g.:

```c++
void print_value(int y) { ... }

int x { 2 };
print_value(x);
```

`x` is copied into parameter `y`, then at the end of the function, object `y` is
destroyed.

### Some objects are expensive to copy
Most of the types provided by the standard library (such as `std::string`) are *class
types*. Usually expensive to copy.

```c++
void print_value(std::string y) { ... }

std::string x { "Hello, world" };
print_value(x);
```

This time, `std::string` is a class that is expensive to copy.

### Pass by reference

```c++
void print_value(std::string& y) { ... }

std::string x { "Hello, world" };
print_value(x);
```

No copy is made, lvalue reference paramter `y` is bound to argument `x`. Always
inexpensive.

### Pass by reference allows us to change the value of an argument
This can be useful.

### Pass by reference to non-const can only accept modifiable lvalue arguments

### Pass by const reference

```c++
void print_value(const std::string& y) { ... }

std::string x { "Hello, world" };
print_value(x);
```

Guarantee the function can not change the value being referenced.

In most cases, we don't want our functions modifying the value of arguments.

> **Best practice**
> Favor const ref, unless there's a specific reason not to.

Now we understand the motivation for allowing const lvalue references to bind to rvalues.

### Mixing pass by value and pass by reference

### When to pass by reference
> **Best practice**<br>
> Because class types can be expensive to copy (sometimes significantly so), class types are
> usuallly passed by const reference instead of by value to avoid making an expensive copy
> of the argument. Fundamental types are cheap to copy, so they are typically passed by
> value.

### The cost of pass by value vs pass by reference (advanced)
So why not pass everything by reference?

Two key points that will help us understand when we should pass by value vs pass by
reference.

1. The cost of copying an object is generally proportional to 2 things:

   * The size of the objects
   * Any additional setup costs. Some class types do additional setup when they are
     instantiated (e.g. opening a file or database, or allocating a certain amount of
     dynamic memory to hold an object of a variable size). This cost must be paid each
     time when an object is copied

   On the other hand, binding a reference to an object is always fast (about the same
   speed as copying a fundamental type).

2. Accessing an object through a reference is slightly more expensive than accessing an
   object through a normal variable identifier.

   With a variable identifier, the running program can just go the memory address assigned
   to that variable and access the value directly.

   With a reference, there usually is an extra step: the program must first access the
   reference to determine which object is being referenced, and only then can it go to that
   memory address for that object and access the value.

   The compiler can also sometimes optimize code using objects passed by value more highly
   than code using objects passed by reference. This means code generated to access objects
   passed by reference is typically slower than the code generated for objects passed by
   value.

> **Best practice**<br>
> * For objects that are cheap to copy, the cost of copying is simiilar to the cost of
>   binding, so  we favor pass by value so the code generated will be faster.
>
> * For objects that are expensive to copy, the cost of the copy dominates, so we favor pass
>   by (const) reference to avoid making a copy.

Cost of copy varies by compiler, use case and architecture. An object is cheap to copy if
it uses 2 or fewer "words" of memory (where "word" is approximated by the size of a memory
address) and it has no setup costs.

This program defines a macro that can be used to determine if a type uses 2 or fewer
memory addresses worth of memory.

```c++
#define is_small(T) (sizeof(T) <= 2 * sizeof(void*))

struct S
{
    double a, b, c;
};

is_small(int); // true
is_small(double); // true
is_small(S); // false
```

Note: we use a preprocessor macro here so that we can substitute in a type (normal
functions disallow this).

It's best to assume that most standard library claseses have setup costs, unless you know
otherwise that they don't.
