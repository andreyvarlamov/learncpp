# 6 - Scope, Duration, and Linkage (cont.)

------

# 6.9 - Sharing global constants across multiple files (using inline variables)

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



# 6.10 - Static local variables

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

> **Best practice**<br>
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

> **Best practice**<br>
> Avoid `static` local variables unless the variable never needs to be reset.

> Note<br>
> Static on global variables changes its linkage. Static on local variables changes its
> duration.



# 6.11 - Scope, duration and linkage Summary
See *summary_scope_duration_linkage.md*



# 6.12 - Using declarations and using directives

### Qualified and unqualified
A **qualified** name is a name that includes an associated scope. Most often, using `::` or,
for classes, member selection: `.` or `->`.

An **unqualified** name is a name that does not include a scoping qualifier.

### Using declarations
Allows us to use an unqualified name as an alias for a qualified name.

E.g.

```c++
#include <iostream>

int main()
{
    using std::cout;
    cout << "Hello world!\n";

    return 0;
}
```

With this declaration, if there's a naming conflict between std::cout and some other use
of cout, std::cout will be preferred

Generally considered safe and acceptable (when used inside a function).

### Using directives
A **using directive** imports all of the identifiers from a namespace into its own scope.

*Using directives* are  the solution that was provided for old pre-namespace codebases
that used unqualified names for std library functionality.

In modern C++, generally little benifit. And too much risk. "Ambiguous symbol" error. Lack
of clarity.

### The scope of using declarations and directives
If a *using declaration* or *using directive* is used within a block, the names are
applicable to just that block (it follows the normal block scoping rules).

If a *using declaration* or *using directive* is used in the global namespace, the names
are appicable to the entire rest of the file (they have *file scope*).

### Cancelling or replacing a using statement
Once a *using statement* has been declared, there's no way to cancel or replace it with a
different *using statement* within the scope in which it was declared.

The best you can do:

```c++
int main()
{
    {
        using namespace foo;
        // do stuff with foo
    }

    {
        using namespace goo;
        // do stuff with goo
    }

    return 0;
}
```

### Best practices for using statements
Avoid *using directives* (particularly `using namespace std;`), except in specific
circumstances (e.g. `using namespace std::literals` to acces `s` and `sv` literal
suffixes).

*Using declarations* are generally considered safe to use inside blocks. Limit their use
in the global namespace of a code file, and never use them in the global namespace of a
header file.



# 6.13 - Inline functions

One downside of using a function is that every time a function is called, there is a
certain amount of performance overhead that occurs.

The CPU has to store the address of the current instruction it is executing along with the
values of various CPU registers. Params instantiated and then initialzied. Jump to the
code in the function. Then jump back, return value copied.

For large functions, the overhead is insignificant, but for small ones, the overhead cost
can be larger than the time needed to actually execute the function's code.

### Inline expansion
C++ compiler has a trick: **inline expansion** - function call is replaced by the code
from the called function's definition.

Furthermore, the inline expanded code can also be a compile-time constant -> further
optimize.

However, inline expansion has its own potential cost: if the body of the function being
expanded takes more instructions than the function call being replaced, then each inline
expansion will cause the executable to grow larger. Larger executables tend to be slower
due to not fitting as well in caches.

The decision about the cost/benefit is not straightforward.

### When inline expansion occurs
Every function falls into one of three categories, where calls to the function:

1. Must be expanded.
2. May be expanded (most functions are in this category).
3. Can't be expanded.

A function that is eligible to have its function calls expanded is called an inline
function.

A modern compiler will assess each function and each function call to make a determination
about whether that particular function call would benefit from inline expansion.

> Some types of functions are implicitly treated as inline functions:
> * Functions defined inside a class, struct or union type definition.
> * Cosntexpr / consteval functions

### The inline keyword, historically
Historically, compilers didn't have the capability to determine whether the inline
expansion would be beneficial.

`inline` keyword -- (just a) hint to the compiler that a function would benefit from being
expanded inline.

However, in modern C++, the `inline` keyword is no longer used to request that a
function be expanded inline. The compiler will likely ignore or devalue any `inline`
request.

> Note<br>
> Wrong level of granularity: use the `inline` keyword on a function declaration, but
> inline expansion is actually determined on a per function call basis.

### The inline, modernly
It was mentioned before, that you should not implement functions (with extneral linkage)
in header files (include in multiple .cpp -> linker error (one-definition rule))

Same as in 6.9 (inline variables), in modern C++, the inline concept evolved to have a new
meaning: multiple definitions are allowed in the program. Thus if we mark a function
inline, that function is allowed to have multiple definitions (in different files), as
long as those definitions are identical.

Inline functions are typically defined in header files, where they can be #included into
any code file that needs to see the full definition of the function.

> **Best practice**<br>
> Avoid using the `inline` keyword for functions unless there's a specific reason.



# 6.14 - Constexpr and consteval functions

Using functions could be bad for performance, since we lose the ability for that code to
be evaluated at compile-time.

### Constexpr functions can evaluated at compile-time
Function whose return value may be computed at compile-time.

E.g.:

```c++
#include <iostream>

constexpr int greater(int x, int y)
{
    return (x > y ? x : y);
}

int main()
{
    constexpr int x{ 5 };
    constexpr int y{ 6 };

    constexpr int g { greater(x, y) };

    std::cout << g << " is greater!\n";

    return 0;
}
```

Compiler replaces it with this:

```c++
#include <iostream>

int main()
{
    constexpr int x{ 5 };
    constexpr int y{ 6 };

    constexpr int g{ 6 };

    std::cout << g << " is greater!\n";

    return 0;
}
```

To be eligible for compile-time evaluation, a function must have a constexpr return type,
not call any non-constexpr functions, and have constexpr arguments (e.g. constexpr
variables or literals).

> **Best practice**<br>
> Use it for functions that need to return a compile-time constant.

### Constexpr functions are implicitly inline
Constexpr function called in multiple files would need to have its definition included
into each such file -- normally a violation of one-definition rule -- but constexpr
functions are implicitly inline.

As a result contexpr functions are often defined in header files, so they can be #included
into any .cpp file that requires the full definition.

### Constexpr functions can also be evaluated at runtime
E.g. when arguments are not constexpr.

This was allowed so that a single function can serve both cases. Otherwise, you'd need to
have separate functions (a function with a constexpr return type, and a function with a
non-constexpr return type). Duplicate code in 2 functions that have to have different
names.

### So when is a constexpr function evaluated at compile-time?
According to the C++ standard, a constexpr function that is eligible for compile-time
evaluation must be evaluated at compile-time if the return value is used where a constant
expression is required. Otherwise, the compiler is free to evaluate the function at either
compile-time or runtime.

E.g.

```c++
constexpr int greater(int x, int y) { ... }

int main()
{
    constexpr int g { greater(5, 6) }; // case 1: evaluated at compile-time
    int x { 5 }; // not constexpr
    std::cout << greater(x, 6) ... ; // case 2: evaluated at runtime
    std::cout << greater(5, 6) ... ; // case 3: may or may not be evaluated at compile-time

    return 0;
}
```

Compiler's optimization level setting may have an impact on whether it decides to evaluate
a function at compile-time or runtime. Debug vs release builds.

Better to think of a constexpr function, not as "will be evaluated at compile-time", but
as "can be used in a constant expression".

### Determining if a constexpr function call is evaluating at compile-time or runtime
In C++20, `std::is_constant_evaluated()` (in <type_traits> header).

E.g.

```c++
#include <type_traits>

constexpr int some_function()
{
    if (std::is_constant_evaluated()) // if compile-time evaluation
    {
        // do something
    }
    else
    {
        // do something else
    }
}
```

### Consteval (C++20)
Used to indicate that a function *must* evaluate at compile-time, otherwise a compile
error will result. Such functions are called **immediate functions**

`consteval int greater(int x, int y) { ... }`

> **Best practice**<br>
> Use `consteval` if you have a function that must run at compilet time for some reason
> (e.g. performance).

### Using consteval to make constexpr execute at compile-time (C++20)
Downside: such functions can't evaluate at runtime -- less flexible.

Convinent way to force constexpr functions to evaluate at compile-time (even when the
return value is being used where a constant expression is not required), so that we can
have compile-time evaluation when possible, and runtime evaluation when not.

```c++
#include <iostream>

consteval auto compile_time(auto value)
{
    return value;
}

constexpr int greater(int x, int y) { ... }

int main()
{
    std::cout << greater(5, 6) ... ; // may or may not execute at compile-time
    std::cout << compile_time(greater(5, 6)) ... ; // will execute at compile-time
    int x { 5 };
    std::cout << greater(x, 6) ... ; // can still call the constexpr version at runtime

    return 0;
}
```

Consteval function returns by value.

We cover `auto` return types in 8.8; abbreviated function templates (`auto` param) in 8.15.
