# 12.7 - Introduction to lambdas (anonymous functions)

When passing function pointer to a function, there can be a problem: we are forced to
define a function that's only going to be used once, that must be given a name, and that
must be put in the global scope (because functions can't be nested). The function can also
be so short, it's almost easier to discern what it does from the one line of code than
from the name and comments.

### Lambdas to the rescue
**Lambda expression**, **lambda**, **closure**.

Anonymous function.

```
[ captureClause ] ( parameters ) -> returnType
{
    statements;
}
```

* The capture clause can be empty if no captures are needed.
* The parameter list can be either empty or omitted if no parameters are required.
* The return type is optional, and if omitted, `auto` will be assumed.

No name.

A trivial lambda definition:

```c++
int  main()
{
    [] {}; // a lambda with an omitted return type, no captures, and omitted parameters

    return 0;
}
```

```c++
const auto found { std::find_if(arr.begin(), arr.end(),
                    [](std::string_view str) // No capture clause; auto return
                    {
                        return(str.find("nut") != std::string_view::npos);
                    }) };
```

### Type of lambda
Defining a lambda right where it's needed - **function literal** (ex. above).

Can improve readability by initializing a lambda variable.

```c++
auto isEven {
    [](int i)
    {
        return ((i % 2) == 0);
    }
};

return std::all_of(array.begin(), array.end(), isEven);
```

Lambdas don't have a type that we can explicitly use. When we write a lambda, the compiler
generates a unique type just for the lambda that is not exposed to us.

But in actuality, lambdas aren't even functions (which is part of how they avoid the
limitation of C++ not supporting nested functions). They're a special kind of object
called a **functor**. Functors are objects that contain an overloaded `operator()` that
make them callable like a function.

Although we don't know the type of a lambda, there are several ways of storing a lambda
for use post-definition. If the lambda has an empty capture clause, we can use a regular
function pointer. `std::function` or type deduction via `auto` will also work (even if the
lambda has a non-empty capture clause).

```c++
#include <functional>

int main()
{
    // A regular function pointer. Only works with an empty capture clause.
    double (*addNumbers1)(double, double) {
        [](double a, double b) {
            return (a + b);
        }
    };

    addNumbers1(1, 2);

    // Using std::function. The lambda could have a non-empty capture clause
    // Pre-C+17 can't use type deduction: std::function<double(double, double)>
    std::function addNumbers2 {
        [](double a, double b) {
            return (a + b);
        }
    };

    addNumbers2(3, 4);

    // Using auto. Stored the lambda with its real type.
    auto addNumbers3 {
        [](double a, double b) {
            return (a + b);
        }
    };

    addNumbers3(5, 6);

    return 0;
}
```

The only way of using the lambda's actual type is by means of `auto`. It also has no
overhead compared to `std::function`.

Prior to C++20, can't alway use `auto`. In cases where the actual lamgda is unkown (e.g.
because we're passing a lambda to a function as a parameter and the caller determines what
lambda will be passed in), we can't use `auto` without compromises. In such cases,
`std::function` can be used instead.

```c++
// We don't know what fn will be. std::function works with regular functions and lambdas.
void repeat(int repetitions, const std::function<void(int)>& fn)
```

If we had used `auto` for the type of `fn`, the caller of the function wouldn't know what
parameters and return types `fn` needs to have.

This limitation was lifted in C++20 when abbreviated function templates were added.

Furthermore, because they are actually templates, functions with `auto` parameters cannot
be separated into a header and source file.

> **Best practice**<br>
> Use `auto` when initializing variables with lambdas, and `std::function` if you can't
> initialize the variable with the lambda.

### Generic lambdas
For the most part, lambda parameters work by the same rules as regular function
parameters.

One notable exception: `auto` keyword. In C++14, we're allowed to use `auto` for
parameters to lambdas (and in C++20, regular functions are able to use `auto` for
parameters too). When a lambda has one or more `auto` parameter, the compiler will infer
what parameter types are needed from the calls to the lambda.

Because theabove can work with a wide variety of types, they are called **generic
lambdas**.

When used in the context of a lambda, `auto` is just a shorthand for a template parameter.
*I'm guessing since C++20, it's also for regular functions.*

```c++
// Search for two consecutive months that start with the same letter.
const auto sameLetter { std::adjacent_find(months.begin(), months.end(),
                                            [](const auto& a, const auto& b) {
                                                return (a[0] == b[0]);
                                            }) };
```

Capture our strings by `const` reference. Because all string types allow access to their
individual characters via `operator[]`, we don't need to care whether the user is passing
in a `std::string`, C-style string, or something else.

### Generic lambdas and static variables
Unique lambda will be generated for each different type that `auto` resolves to.

Most of the time this is inconsequential, but if a generic lambda uses static duration
variables, those variables are not shared between the generated lambdas.

### Return type deduction and trailing return types
If return types deduction is used, it is deduced from the return statements, and all of
them must return the same type.

Usually if different types, it's best to explicitly specify a return type and let the
compiler do the implicit conversions.

### Standard library function objects
For common operations, the std library comes with many basic callable objects that can be
used instead. Defined in the \<functional\> header.

```c++
#include <functional>
std::sort(arr.begin(), arr.end(), std::greater {} ); // note the curly braces to intsantiate the object
```
