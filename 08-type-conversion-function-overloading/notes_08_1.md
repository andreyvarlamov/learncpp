# 8 - TypeConversion and Function Overloading

8.1-8.5
-------

# 8.1 - Implicit type conversion (coercion)

### Introduction to type conversion
Different data types may represent the "same" number differently. For example 3 as a two's
complement binary, and 3.0 as a floating point number.

So what happens when we do something like this?

```c++
float f { 3 };
```

**Type conversion**

### Implicit type conversion
Also **automatic type conversion** or **coercion**. Performed automatically by the
compiler when one data type is required, but a different data type is supplied.

Happens all the time.

E.g.

```c++
double d { 3 }; // int -> double
d = 6;

float doSomething()
{
    return 3.0; // double -> float
}

double division { 4.0 / 3 }; // int -> double

if (5) // int -> bool
{
}

void doSomething2(long l) { ... }
doSomethin2(3); // int -> long
```

### What happens when a type conversion is invoked

The compiler will determine whether it can convert the value from the current type to the
desired type. If a valid conversion can be found, then the compiler will produce a new
value of the desired type. If the compiler can't find an acceptable conversion, then the
compilation will fail with a compile error. Can fail for a number of reasons: compiler
might not know how to convert a value between the original type and the desired type. In
other cases, statements may disallow certain type of conversion (e.g. brace initialization
disallowing narrowing conversions). Also cases where the compiler may not be able to
figure out which of several possible type conversions is unambiguously the best one to
use.

### The standard conversions
C++ standard defines how different fundamental types (and in some cases, compound types)
can be converted to other types.

Broadly, 4 categories:
* Numeric promotions
* Numeric conversions
* Arithmetic conversions
* Other conversions (which includes various pointer and reference conversions)

When a type conversion is needed, the compiler will see if there are standard conversions
that it can use to convert the value to the desired type. The compiler may apply zero,
one, or more than one standard conversions in the conversion process.

How do you have a type conversion with zero conversions? E.g. architectures where `int`
and `long` both have the same size and range. Therefore, no actual conversion is needed to
convert a value between those types, the value can simply be copied.
