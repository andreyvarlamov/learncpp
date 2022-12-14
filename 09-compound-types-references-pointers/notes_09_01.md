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
