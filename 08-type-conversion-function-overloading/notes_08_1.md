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



# 8.2 - Floating-point and integral promotion

*The number of bits a data type uses is called its width*

Want 32-bit CPU to modify an 8-bit value (such as a `char`) or a 16-bit value? Some 32 bit
CPUs (such as x86) can manipulate 8-bit or 16-bit values directly. However, doing so is
often slower than manipulating 32-bit values.

### Numeric promotion
Because C++ is designed to be portable and performant across a wide range of
architectures, don't want to assume a given CPU would be able to efficiently manipulate
values that were narrower than the natural data size for that CPU.

To help address this challenge - **numeric promotion** - type conversion of a narrower
numeric type (such as `char`) to a wider numeric type (such as `int` or `double`) that can
be processed efficiently and is less likely to have a result that overflows.

All numeric promotions are **value-preserving** - no loss of data or precision. Safe, the
compiler will freely use numeric promotion as needed, and will not issue a warning when
doing so.

### Numeric promotion reduces redundance
I.e. function versions for different types.

### Numeric promotion categories
`integral promotions` and `floating point promotions`.

### Floating point promotions
Easier.

### Integral promotions
More complicated.

Using integral promotion rules, the following conversions can be made:
* signed char or signed short -> int
* `unsigned char`, `char8_t`, `unsigned short` -> int if int can hold the entire range of
  the type, or unsigned int otherwise.
* if char is signed by default, it follows the signed char conversion rules above. If it
  is unsigned by default, it follows the unsigned char conversion rules above.
* bool can be converted to int, with false becoming 0 and true becoming 1.

### Not all value-preserving conversions are numeric promotions.
Some value-preserving type conversions (e.g. `char` -> `short`; `int` -> `long` or `int ->
`double`) are not considered to be numeric promotions in C++ (they are *numeric
conversions*). This is because such conversions do not assist in the goal of converting
smaller types to larged types that can be processed more efficiently.
