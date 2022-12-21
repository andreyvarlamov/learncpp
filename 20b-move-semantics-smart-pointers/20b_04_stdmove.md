# M.4 - `std::move`

```c++
#include <iostream>
#include <string>

template<class T>
void myswapCopy(T& a, T& b)
{
    T tmp { a }; // invokes copy constructor
    a = b; // invokes copy assignment
    b = tmp; // invokes copy assignment
}

int main()
{
    std::string x { "abc" };
    std::string y { "de" };

    std::cout << "x: " << x < '\n';
    std::cout << "y: " << y < '\n';

    myswapCopy(x, y);

    std::cout << "x: " << x < '\n';
    std::cout << "y: " << y < '\n';

    return 0;
}
```

### `std::move`

```c++
#include <iostream>
#include <string>
#include <utility> // for std::move

template<class T>
void myswapMove(T& a, T& b)
{
    T tmp { std::move(a) }; // invokes move constructor
    a = std::move(b); // invokes move assignment
    b = std::move(tmp); // invokes move assignment
}

int main()
{
    std::string x { "abc" };
    std::string y { "de" };

    std::cout << "x: " << x < '\n';
    std::cout << "y: " << y < '\n';

    myswapMove(x, y);

    std::cout << "x: " << x < '\n';
    std::cout << "y: " << y < '\n';

    return 0;
}
```

A standard library function that casts (using `static_cast`) its argument into an r-value
reference, so that move semantics can be invoked.

### Another example
Useful when filling elements of a container, e.g. std::vector, with l-value.

```c++
#include <iostream>
#include <string>
#include <utility>
#include <vector>

int main()
{
    std::vector<std::string> v;

    // We use std::string because it is movable (std::string_view is not)
    std::string str { "Knock" };

    std::cout << "Copying str\n";
    v.push_back(str); // calls l-value version of push_back, whcih copies str into the array
                      // element

    std::cout << "str: " << str << '\n';
    std::cout << "vector: " << v[0] << '\n';

    std::cout << "Moving str\n";
    v.push_back(std::move(str)); // calls r-value version of push_back, whcih moves str
                                 // into the array element

    std::cout << "str: " << str << '\n'; // The result of this is indeterminate
    std::cout << "vector: " << v[0] << '\n';
```

```
Copying str
str: Knock
vector: Knock

Moving str
str:                       -- indeterminate, could be different with diff implementations
vector: Knock Knock
```

### Moved from objects will be in valid, but possible indeterminate state
When we move the value from a temporary object, it doesn't matter what value the
moved-from object is left with, because the temporary object will be destroyed
immediately anyway. But we can continue to access lvalues after their values have been
moved.

`std::move()` gives a hint to the compiler that the programmer doesn't need the value of
an object any more. Only use `std::move()` on persistent objects whose value you want to
move, and do not make any assumptions about the value of the object beyond that point.
It is okay to give a moved-from object a new value (e.g. using `operator=`) after the
current value has been moved.

### What else is std::move useful for?
Sorting an array of elements. Many sorting algorithms (such as selection sort and bubble
sort) work by swapping pairs of elements. In previous lessons, we've had to resort to
copy semantics to do the swapping. Now we can use move semantics, which is more efficient.
