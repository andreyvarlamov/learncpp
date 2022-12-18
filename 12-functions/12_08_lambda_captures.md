# 12.8 - Lambda captures

### Capture clauses and capture by value

```c++
std::string search { };
std::cin >> search;

auto found { std::find_if(arr.begin(), arr.end(), [](std::string_view str) {
    return (str.find(search) != std::string_view::npos); // Error: search not accessible in this scope
}) };
```

Unlike nested blocks, where any identifier defined in an outer block is accessible in the
scope of the nested block, lambdas can only access specific kinds of identifiers: global
identifiers, entities that are known at compile time, and entities with static storage
duration. `search` fulfills none of these requirements, so the lambda can't see it.

### The capture clause
Used to (indirectly) give a lambda access to variables available in the surrounding scope
that it normally would not have access to.

In the above example:

```c++
std::string search { };
std::cin >> search;

// Capture @search                                 vvvvvv
auto found { std::find_if(arr.begin(), arr.end(), [search](std::string_view str) {
    return (str.find(search) != std::string_view::npos);
}) };
```

### So how do captures actually work?
When the compiler encounters a lambda definition, it creates a custom object definition
for the lambda. Each captured variable becomes a data member of the object.

At runtime, when the lambda definition is encountered, the lambda object is instantiated,
and the members of the lambda are initialized at that point.

### Captures default to const value

### Mutable capture by value
Removes `const` qualification from all variables captured by value.

```c++
auto shoot {
    [ammo]() mutable {
        --ammo;
        ...
    }
};
```
But this still copied ammo, so the original value has not been modified.

BUT `ammo` will be preserved across calls to the lambda! Captured variables are members of
the lambda object.

### Capture by reference
Prepend `&`.

Unlike variables that are captured by value, variables that are captured by reference are
non-const, unless the variable they're capturing is `const`.

Capture by reference should be preferred over capture by value whenever you would normally
prefer passing an argument to a function by reference (e.g. for non-fundamental types).

```c++
auto shoot {
    // don't need mutable anymore
    [&ammo]() { // &ammo means ammo is captured by reference
        // Changes to ammo will affect main's ammo (this is supposed to be inside main())
        --ammo;
        ...
    }
};
```

### Capture multiple variables

### Default captures
Capture all variables that are mentioned in the lambda.

Ex:

```c++
int health { 33 };
int armor { 33 };
std::vector<CEnemey> enemies { };

[health, armor, &enemies](){};

// Capture enemies by reference and everything else by value
[=, &enemies](){}

// Capture armor by value and everything else by reference
[&, armor](){}

// Illegal
[&, &armor](){}

// Illegal
[=, armor](){}

// Illegal
[armor, &health, &armor](){};

// Illegal, the default capture has to be the first element in the capture group
[armor, &](){};
```

### Defining new variables in the lambda-capture
*As I understand, pre-C++14, you could not declare variables in lambda body.*

```c++
auto found { std::find_if(areas.begin(), areas.end(),
                            [userArea{ width * height }](int knownArea) {
                                return (userArea == knownArea);
                            }) };
```

In this example, `userArea` will only be calculated once when the lambda is defined. The
calculated area is stored in the lambda object and is the same for every call. If a lambda
is mutable and modifies a variable that was defined in the capture, the original value
will be overriden.

> **Best practice**<br>
> Only initialize variables in the capture if their value is short and their type is
> obvious. Otherwise it's best to define the variable outside of the lambda and capture
> it.

### Dangling captured variables

Consider this case:

```c++
#include <iostream>
#include <string>

// returns a lambda
auto makeWalrus(const std::string& name)
{
    return [&]() {
        std::cout << "I am a walrus, my name is " << name << '\n'; // Undefined behavior
    };
}

int main()
{
    // Create a new walrus whose name is Roofus.
    // sayName is the lambda returned by makeWalrus.
    auto sayName { makeWalrus("Roofus") };

    // Call the lambda function that makeWalrus returned
    sayName();

    return 0;
}
```

The call to `makeWalrus` creates a temporary `std::string` from the string literal
"Roofus". The lambda in `makeWalrus` captures the temporary string by reference. The
temporary string dies when `makeWalrus` returns, but the lambda still references it. Then
when we call `sayName`, the dangling reference is accessed, causing undefined behavior.

Not that this also happens if `name` is passed to `makeWalrus` by value. The variable
`name` still dies at the end of `makeWalrus`, and the lambda is left holding a dangling
reference.

If we want the captured `name` to be valid when the lambda is used, we need to capture is
by value instead (either explicitly or using a default-capture by value). So that the
value is copied into lambda's member and lambda still has access to it when called at any
point in the future.

### Unintended copies of mutable lambdas

```c++
#include <iostream>
#include <functional>

void myInvoke(const std::function<void()>& fn)
{
    fn();
}

int main()
{
    int i { 0 };

    auto count { [i]() mutable {
        std::cout << ++i << '\n';
    } };

    myInvoke(count);
    myInvoke(count);
    myInvoke(count);

    return 0;
}
```

When `std::function` is created with a lambda, the `std::function` interanally makes a
copy of the lambda object. Thus our call to `fn()` is actually being executed on the copy
of our lambda, not the actual lambda.

Two options:

Use a non-capturing lambda instead, e.g. could use a static local variable instead.

Prevent copies of lambda from being made in the first place. But can't affect how
`std::function` is implemented.

`std::reference_wrapper` allows to pass a normal type as it was a reference. Can be
created with `std::ref()` function. By wrapping our lambda in a `std::reference_wrapper`,
whenever anybody tries to make a copy of our lambda, they'll make a copy of the reference
instead, which will copy the reference rather than the actual object.

```c++
#include <functional>
...
    myInvoke(std::ref(count));
    myInvoke(std::ref(count));
    myInvoke(std::ref(count));
...
```

> **Best practice**<br>
> Standard library functions may copy function objects (reminder: lambdas are function
> objects). If you want to provide lambdas with mutable captured variables, pass them by
> reference using `std::ref`.

> **Best practice**<br>
> Try to avoid mutable lambdas. Non-mutable lambdas are easier to understand and don't
> suffer from the above issues, as well as more dangerous issues that arise when you add
> parallel execution.

### No explicit capture recap

```c++
int i { };
static int j { };

int getValue()
{
    return 0;
}

int main()
{
    int a { };
    constexpr int b { };
    static int c { };
    static constexpr int d { };
    const int e { };
    const int f { getValue() };
    static const int g { };
    static const int h { getValue() };

    []() { // Usable without explicit capture ?
        a; // No. a has automatic storage duration
        b; // Yes. b is usable in a constant expression
        c; // Yes. c has static storage duration
        d; // Yes
        e; // Yes. e is usable in a constatn expression
        f; // No. f's value depends on getValue, which might require the program to run.
        g; // Yes.
        h; // Yes. h has static storage duration
        i; // Yes. i is a global variable
        j; // Yes. j is accessible in the entire file
    }();

    return 0;
}
```

---

### Binary search (from 12.x Q3)
The best algorithm for determining whether a value exists in a sorted array. Because we
can throw out half of the array with each iteration, this algorithm is very fast. Even
with an array of a million elements, it only takes at most 20 iterations to determine
whether a value exists in the array or not. Only works on sorted arrays.

Algorithm:

1. Look at the center alement of the array (if even count, round down).
2. If the center element is greater than the target element, discard the top half of the
   array (or recurse on the bottom half).
3. If the center element is less than the target element, discard the bottom half ot the
   array (or recurse on the top half).
4. If the cetner element equals the target element, return the index of the center
   element.
5. I fyou discard the entire array without finding the target element, return a sentinel
   that represents "not found" (in this case, we'll use -1, since it's an invalid array
   index).

Modifying an array is expensive, so typically we do not modify it, instead, we use two
integers (min and max) to hold the indices of the minimum and maximum elements of the
array that we're interested in examining.

See `08_binary_search.cpp` for both iterative and recursive implementations

`std::binary_search` returns true if a value exists in a sorted list.
`std::equal_range` returns the iterators to the first and last element with a given value.
