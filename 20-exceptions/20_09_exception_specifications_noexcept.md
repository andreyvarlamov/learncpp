# 20.9 - Exception specifications and noexcept
**Noexcept specifier**.

```c++
void doSomething() noexcept;
```

Doesn't actually prevent the function from throwing exceptions or calling other functions
that are potentially throwing. Rather, when an exception is thrown, if an exception exits
a noexcept function, `std::terminate` will be called.

### The noexcept specifier with a Boolean parameter
`noexcept(true)` and `noexcept(false)`. The former is equivalent to `noexcept`, and the
latter means the function is potentially throwing. Typically used in template functions,
so that a template function can be dynamically created as non-throwing or potentially
throwing base on some parameterized value.

### Which functions are non-throwing and potentially-throwing
Implicitly non-throwing:

* Destructors

Functions that are non-throwing by default for implicitly-declared or defaulted functions:

* Constructors: default, copy, move
* Assignments: copy, move
* Comparison operators (as of C++20)

However, if any of these functions call (explicitly or implicitly) another function which
is potentially throwing, then the listed function will be treated as potentially throwing
as well. For example, if a class has a data member with a potentially throwing
constructor, then the class's constructors will be treated as potentially throwing as
well.

Functions that are potentially throwing (if not implicitly-declared or defaulted):

* Normal functions
* User-defined constructors
* User-defined operators

### The noexcept operator
`noexcept(foo())` - `true` or `false` if the compiler thinks it will throw an exception or
not. The noexcept operator is checked statically at compile-time, and doesn't actually
evaluate the input expression.

Can be used to conditionally execute code depending on whether it is potentially throwing
or not. This is required to fulfill certain **exception safety guarantees**.

### Exception safety guarantees
A contractual guideline about how functions or classes will behave in the event an
exception occurs.

* No guarantee: no guarantees about what will happen if an exception is thrown (e.g. a
  class may be left in an unusable state).
* Basic guarantee: if an exception is thrown, no memory will be leaked and the object is
  still usable, but the program may be left in a modified state.
* Strong guarantee: if an exception is thrown, no memory will be leaked and the program
  state will not be changed. This means the function must either completely succeed or
  have no side effects if it fails. This is easy if the failure happens before anything is
  modified in the first place, but can also be achieved by rolling back any changes so the
  program is returned to the pre-failure state.
* No throw / no fail - the function will always succeed (no-fail) or fail without throwing
  an exception (no-throw).

The no-throw guarantee: if a function fails, then it won't throw an exception. Instead, it
will return an error code or ignore the problem. No-throw guarantees are required during
stack unwinding when an exception is already being handled. Examples of code that should
be no-throw:

* destructors and memory deallocation/cleanup functions.
* functions that higher-level no-throw functions need to call.

The no-fail guarantee: a function will always succeed in what it tries to do (and thus
never has a need to throw an exception). Examples of code that should be no-fail:

* Move constructors and move assignment (move semantics)
* Swap functions
* Clear/erase/reset functions on containers
* Operations on `std::unique_ptr`
* Functions that higher-level no-fail functions need to call

### When to use noexcept

> **Best practice**<br>
> Make constructors and overloaded assignment operators `noexcept` when you can. Use
> `noexcept` on other functions to express a no-fail or no-throw guarantee (e.g. to
> document that they can be safely called from destructors or other noexcept functions).

> **Best practice**<br>
> If you are uncertain whether a function should have a no-fail/no-throw guarantee, err on
> the side of caution and do not mark it with `noexcept`. Reversing a decision to use
> noexcept violates an interface commitment to the user about the behavior of the
> function, and may break existing code. Making guarantess stronger by later adding
> noexcept to a function that was no originally noexcept is considered safe.

### Dynamic exception specifications
Before C++11, and until C++17, *dynamic excpetion specifications* were used in place of
`noexcept`. The **dynamic exception specifications** syntax uses the `throw` keyword to
list which exception types a function might directly or indirectly throw:

```c++
int doSomething() throw(); // does not throw exceptions
int doSomething() throw(std::out_of_range, int*); // may throw either . or .
int doSomething() throw(...) // may throw anything
```

Due to factors such as incomplete compiler implementations, some incompatibility with
template functions, common misunderstanding about how they worked, and the fact that the
std lib mostly didn't use them, the dynamic exception specifications were deprecated in
C++11, and removed from the language in C++17 and C++20.
