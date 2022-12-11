# 6 - Scope, Duration, and Linkage (cont.)

## 6.9 - Sharing global constants across multiple files (using inline variables)

### Global constants as internal variables
Prior to C++17, the following was the easiest and most common solution:
1. Create a header file to hold these constants
2. Inside the header file, define a namespace
3. Add all your constants inside the namespace (make sure they're constexpr)
4. #include the header file wherever you need it

Because const globals have internal linkage, each .cpp file gets an independent version of
the global variable that the linker can't see. In most cases, because these are const, the
compiler will simply optimize the variables away.

> The term "optimizing away" refers to any process where the compiler optimizes the
> performance of your program by removing things in a way that doesn't affect the output
> of your program. For example, let's say you have some const variable `x` that's
> initialized to value `4`. Wherever your code refences variable `x`, the compiler can
> just replace `x` with `4` (since `x` is const, we know it won't ever change to a
> different value) and avoid having to create and initialized a variable altogether.

### Global constants as external variables
Downsides to the above method:
constants.h gets #included into different code files. 1) So changing a single constant value
would require recompiling every file that includes the constants header. Long rebuild
times. 2) If the constants are large in size and can't be optimized away, this can use a
lot of memory

One way to avoid this is to turn these constants into external variables. Define the
constants in a .cpp file, and put forward declarations in the header (i.e constants.cpp
and constants.h using `extern const` for all of them). Can't use constexpr, because those
can't be forward declared.

Namespace them.

Downsides to this method:
1. Compile-time constants only within the file they are actually defined in
   (constants.cpp). In other files, these are treated as runtime constant values. Thus
   outside of constants.cpp, these variables can't be used anywhere that requires a
   compile-time constant.
2. The compiler may not be able to optimize these as much.
3. Inability to use constexpr.

> In order for variables to be usable in compile-time contexts, such as array sizes, the
> compiler has to see the variable's definition (not just a forward declaration).

### Global constants as inline variables (C++17)
The term `inline` has evolved to mean "multiple definitions are allowed". -> Allowed to be
defined in multiple files without violating the one defintion rule. Inline variables have
external linkage by default.

The linker will consolidate all inline definitions of a variable into a single variable
definition (thus meeting the one definition rule).

With inline, the compiler picks 1 definition to be the canonical definition. So save
memory.

Define these in a header file, in a namespace, using `inline` keyword. 
E.g.:

constants.h:
```c++
namespace constants
{
    inline constexpr double pi { ... };
    ...
}
```

main.cpp:
```c++
#include "constants.h"
int main()
{
    ...
    constants::pi
}
```

Two restrictions:
1. All definitions of the inline variable must be identical (otherwise, undefined
   behavior)
2. The inline variable definition (not a forward declaration) must be present in any file
   that uses the variable

This method retains the downside of requiring every file that includes the constants
header to be recompiled if any constant value is changed. As a remedy, could move the
often changing constants into their own header, to reduce the number of files needed to be
recompiled.

**Best practice is to use inline constexpr global variables**

> Use `std::string_view` for `constexpr` strings.



## 6.10 - Static local variables

`static` has different meanings in different contexts.

*static duration*

`static` keyword - gives a global identifier *internal linkage*.

And now: `static` keyword when applied to a local variable.

### Static local variables
Local variables have *automatic duration* by default. (Created at the point of definition,
destroyed when the block is exited).

Using the `static` keyword on a local variable changes it to *static duration*. -- Created
at the start of the program, destroyed at the end of the program. As a result the static
variable will retain its value even after it goes out of scope.

```c++
void incrementAndPrint()
{
    static int s_value { 1 };
    ++s_value;
    std::cout << s_value << '\n';
}

int main()
{
    incrementAndPrint(); // 2
    incrementAndPrint(); // 3
    incrementAndPrint(); // 4

    return 0;
}
```

Static local variables that are zero initialized or have a constexpr initializer can be
initialized at program start. Ones with non-constexpr initializers are initialized the
first time the variable definition is encountered. The definition is skipped on subsequent
calls, so no reinitialization happens). Static local variables that are not explicitly
initialized will be zero-initialized by default.

Common to use "s_" prefix.

Most common use case: unique ID generator.

Advantage over global variable is that the
scope of the variable is still within that one block.

> **Best practice**:
> Initialize your static variables. Static local variables are only initialized the first
> time the code is executed, not on subsequent calls.

### Static local constants
Static local variables can be made const (or constexpr).
Use case: you have a function that needs to use a const value, but creating or
initializing the object is expensive (e.g. query db). With a const/constexpr static local
variable, you can create and initialize the expensive object once, and then reuse it on
subsequent calls. *(Is that what lazy loading is?)*

### Don't use static local variables to alter flow
Makes the code harder to understand. "It worked last time" problem. Not reusable.

Better to implement that passing that as a parameter.

> **Best practice**:
> Avoid `static` local variables unless the variable never needs to be reset.

> Note:
> Static on global variables changes its linkage. Static on local variables changes its
> duration.

<br>
<br>
<br>
## 6.11 - Scope, duration and linkage Summary
See *summary_scope_duration_linkage.md*

<br>
<br>
<br>
## 6.12 -
