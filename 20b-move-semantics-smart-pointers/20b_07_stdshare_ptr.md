# M.7 - `std::shared_ptr`

Have multiple `std::shared_ptr` pointing to the same resource. As long as at least one
`std::shared_ptr`is pointing to the resource, the resource will not be deallocated.

The second pointer has to be created from the first shared pointer. If they're created
independently, no way for each to know about the other's existence.

Always make a copy of an existing shared ptr, if you need more than one pointing to the
same resource.

### `std::make_shared`
Same deal as with unique ptr. Also more performant. The second one still has to be created
by copying the first.

### Digging into `std::shared_ptr`
Uses two pointers internally. One pointer - resource being managed. The other - "control
block" - dynamically allocated object that tracks a bunch of stuff, including how many
shared pointers are pointing at the resource.

When created via constructor, the memory for the managed object (which is usually passed
in) and control block (which the constructor creates) are allocated separately. However,
when using `std::make_shared()`, this can be optimized into a single memory allocation,
which leads to better performance.

### Shared pointers can be created from unique pointers
Using a `std::shared_ptr` constructor that accepts a `std::unique_ptr` r-value.

However, shared cannot be safely converted into unique. So it's better to return unique
from a function and assign it to a shared pointer if and when it's appropriate.

### Arrays
In C++17 and earlier, shared doesn't have proper support for managing arrays, and should
not be used to manage a C-style array. As of C++20, `std::shared_ptr` does have support
for arrays.
