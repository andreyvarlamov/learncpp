# 8 - Type Conversion and Function Overloading

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
Some value-preserving type conversions (e.g. `char` -> `short`; `int` -> `long` or `int` ->
`double`) are not considered to be numeric promotions in C++ (they are *numeric
conversions*). This is because such conversions do not assist in the goal of converting
smaller types to larged types that can be processed more efficiently.



# 8.3 - Numeric conversions

There are 5 basic types of numeric conversions

1. Converting an integral type to any other integral type (excluding integral promotions):

```c++
short s = 3; // convert int to short
long l = 3; // convert int to long
char ch = 3; // convert short to char
```

2. Converting a floating point type to any other floating point type (excluding floating
   point promotions):

```c++
float f = 3.0; // convert double to float
long double ld = 3.0; // convert double to long double
```

3. Converting a floating point type to any integral type:

```c++
int i = 3.5; // convert double to int
```

4. Converting an integral type to any floating point type:

```c++
double d = 3; // convert int to double
```

5. Converting an integral type or a floating point type to a bool:

```c++
bool b1 = 3; // convert int to bool
bool b2 = 3.0; // convert double to bool
```

> Note<br>
> Because brace initialization disallows some numeric conversions, we use copy
> initialization in this lesson (which does not have such limitations) in order to keep
> the examples simple.

### Narrowing conversions
May or may not result in data or precision loss.

* Floating point type -> integral type
* Wider floating point type -> narrower floating point type, unless the value being
  converted is constexpr and is in range of the destination type (even if the narrower
  type doesn't have the precision to store the whole number).
* From an integral to a floating point type, unless the value being converted is constexpr
  and is in range of the destination type and can be converted back into the original type
  without data loss.
* From a wider integral type to a narrower integral type, unlees the value being converted
  is constexpr and after integral promotion will fit into the destination type.

Compiler will usually issue a warning (or error) when it determines that an implicit
narrowing conversion is required.

> **Warning**<br>
> Compilers will often not warn when converting a signed int to an unsigned int and
> vice-versa, even though these are the narrowing conversions. Be careful.

> **Best practice**<br>
> In general, narrowing conversions should be avoided, but there are situational cases
> where you might need to do one. In such cases, you should make the implicit narrowing
> conversion explicit by using `static_cast`.

### Brace initialization disallows narrowing conversions.

### More on numeric conversions
In all cases, converting a value into a type whose range doesn't support that value will
lead to results that are probably unexpected.

Converting from a larger integral or floating point type to a smaller type from the same
family will generally work so long as the value fits in the range of the smaller type.

In the case of floating point values, some rounding may occur due to a loss of precision
in the smaller type.

Converting from an integer to a floating point number generally works as long as the value
fits within the range of the floating point type.

Converting from a floating point to an integer works as long as the value fits within the
range of the integer, but any fractional values are lost.

Compiler will generally warn you if you try to do something dangerous.



# 8.4 - Arithmetic conversions

```c++
??? y { 2 + 3.5 };
```

### The operators that require operands of the same type

* The binary arithmetic operators: +, -, \*, /, %
* The binary relational operators, <, >, <=, >=, ==, !=
* The binary bitwise arithmetic operators: &, ^, |
* The conditional operator ?: (excluding the condition, which is expected to be of type
  `bool`)

### The usual arithmetic conversion rules
The compiler has a prioritized list of types that look something like this:
* long double (highest)
* double
* float
* unsigned long long
* long long
* unsigned long
* long
* unsigned int
* int (lowest)

2 rules:
* If the type of at least one of the operands is on the priority list, the operand with
  lower priority is converted to the type of the operand with higher priority.
* Otherwise (the type of neither operand is on the list), both operands are numerically
  promoted.

### Some examples

```c++
#include <typeinfo>
...
int i{ 2 };
double d{ 3.5 };
std::cout << typeid(i + d).name() << i + d << '\n';

// double 5.5
```

```c++
short a{ 4 };
short b{ 5 };
std::cout << typeid(a + b).name() << a + b << '\n';

// int 9
```

### Signed and unsigned issues

`unsigned int` operand has higher priority, so `int` operand will be converted to an
`unsigned int`. Unexpected result.

`5u - 10 = 4294967291`

`-3 < 5u = true` -- -3 -> unsigned, overflows, converted to a large `unsigned int`.

> **Warning**<br>
> This is one of the primary reasons to avoid unsigned integers -- mix with signed ints 
> and get unexpected results. The compiler probably won't even issue a warning.



# 8.5 - Explicit type conversion (casting) and static\_cast

`double d = 10 / 4; // -> d = 2.0`

**Type casting operators** (**casts**) -> **explicit type conversion**

### Type casting
C++ supports 5 different types of casting: `C-style casts`, `static casts`, `const casts`,
`dynamic casts` and `reinterpret casts`. The latter four - **named casts**.

`const casts` and `reinterpret casts` should generally be avoided because they are only
useful in rare cases and can be harmful if used incorrectly.

### C-style casts

`int x{ 10 }; int y{ 4 }; (double) x / y` -> 2.5

Although it appears to be a single cast, it can perform a variety of different conversions
depending on context. This can include a `static cast`, a `const cast` or a `reinterpret
case`. The latter of the two should be avoided.

> **Best practice**<br>
> Avoid using C-style casts.

### static\_cast

`char c{ 'a' }; static_cast<int>(c)` -> 97

Best used to convert one fundamental type into another.

The main advantage of `static_cast` is that it provides a compile-time type checking. Also
intentionally less powerful than C-style casts, so you can't inadvertently remove `const`
or do other things you may have not intended to do.

> **Best practice**<br>
> Favor static\_cast when you need to convert a value from one type to another type.

### Using static\_cast to make narrowing conversions explicit
Explicitly tell the compiler that this conversion is intended, and we accept
responsibility for the consequences (e.g. overflowing the range of a `char` if that
happens). Since the output of this `static_cast` is (e.g.) of type `char`, the
initialization of (e.g.) variable `ch` doesn't generate any type mismatches, and hence no
warnings or errors.
