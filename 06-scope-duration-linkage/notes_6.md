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

![C++ test](https://upload.wikimedia.org/wikipedia/commons/thumb/1/18/ISO_C%2B%2B_Logo.svg/640px-ISO_C%2B%2B_Logo.svg.png)
