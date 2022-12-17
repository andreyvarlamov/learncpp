# 12.3 - `std::vector` capacity and stack behavior

### Length vs capacity
With built in dynamic arrays:

```c++
int* array { new int[10] { 1, 2, 3, 4, 5 } };
```

Could say array has length of 10, even though we're only using 5 of the elements that we
allocated.

However, what if we only wanted to iterate over the elements we've initialized, reserving
the unused ones for future expansion? We'll need to separately keep track how many
elements were "used" from how many elements were allocated.

A built-in array or `std::array` only remembers its length. `std::vector` contains two
separate attribitues:
    * **Length** - how many elements are being used in the array.
    * **Capacity** - how many elements were allocated in memory.

```c++
#include <vector>
#include <iostream>

int main()
{
    std::vector array { 0, 1, 2 };
    array.resize(5);

    std::cout << "The length is: " << array.size() << '\n'; // 5
    std::cout << "The capacity is: " << array.capacity() << '\n'; // 5
}
```

The `resize()` function caused the `std::vector` to change both its length and capacity.
Note that the capacity is guaranteed to be at least as large as the array length.

### More length vs capacity
Why differentiate between length and capacity? `std::vector` will reallocate its memory if
needed, but it would prefer not to, because resizing is computationally expensive.

```c++
#include <vector>
#include <iostream>

int main()
{
    std::vector<int> array { };
    array = { 0, 1, 2, 3, 4 };
    std::cout << "The length is: " << array.size() << '\n'; // 5
    std::cout << "The capacity is: " << array.capacity() << '\n'; // 5

    array = { 9, 8, 7 };
    std::cout << "The length is: " << array.size() << '\n'; // 3
    std::cout << "The capacity is: " << array.capacity() << '\n'; // 5
}
```

So it simply assigned 3 values and changed the length to 3, without resizing.

### Array subscripts and `at()` are based on length, not capacity

### Stack behavior with `std::vector`
A reason to worry about vector's capacity.

`std::vector` can be used as a stack.

* `push_back()` - pushes an element on the stack
* `back()` - returns the value of the top element on the stack
* `pop_back()` - pops an element off the stack.

```c++
#include <vector>
#include <iostream>

void printStack(const std::vector<int>& stack)
{
    for (auto element : stack)
    {
        std::cout << element << ' ';
    }

    std::cout << "(cap " << stack.capacity() << " length " << stack.size() << ")\n";
}

int main()
{
    std::vector<int> stack { };

    stack.reserve(5); // Set the capacity to (at least) 5
                      // If we don't do this, the vector will be resized with every push,
                      // which is expensive

    printStack(stack);

    stack.push_back(5);
    printStack(stack);

    stack.push_back(3);
    printStack(stack);

    stack.push_back(2);
    printStack(stack);

    std::cout << "top: " << stack.back() << '\n';

    stack.pop_back();
    printStack(stack);

    stack.pop_back();
    printStack(stack);

    stack.pop_back();
    printStack(stack);

    return 0;
}
```


```
(cap 5 length 0)
5 (cap 5 length 1)
5 3 (cap 5 length 2)
5 3 2 (cap 5 length 3)
top: 2
5 3 (cap 5 length 2)
5 (cap 5 length 1)
(cap 5 length 0)
```

### Vectors may allocate extra capacity
To minimize the number of resizes

```c++
#include <vector>
#include <iostream>

int main()
{
    std::vector v { 0, 1, 2, 3, 4 };
    std::cout << "size: " << v.size() << " cap: " << v.capacity() << '\n';

    v.push_back(5);
    std::cout << "size: " << v.size() << " cap: " << v.capacity() << '\n';

    return 0;
}
```

On author's machine:

```
size: 5 cap: 5
size: 6 cap: 7
```

Up to the compiler implementer.
