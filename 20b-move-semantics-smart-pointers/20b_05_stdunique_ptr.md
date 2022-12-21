# M.6 - `std::unique_ptr`

Replacement for `std::auto_ptr`.

```c++
std::unique_ptr<Resource> res1 { new Resource() };
std::unique_ptr<Resource> res2 { }; // start as nullptr

// res2 = res1; // won't compile: copy assignment is disabled
res2 = std::move(res1); // res2 assumes ownership, res1 is set to null
```

Copy initialization and copy assignment are disabled. If you want to transfer the contents
managed by `std::unique_ptr`, you must use move semantics.

Overloaded operators * and ->.

May not always be managing and object, or because the resource it was managing got moved
to another `std::unique_ptr`. So before we use either of these operators, should check
that it actually has a resource. It has a cast to bool that returns true if the
`std::unique_ptr` actually has a resource.

### `std::unique_ptr` and arrays
Smart enough to know whether to use scalar delete or array delete. But:

> **Best practice**<br>
> Favor std::array, std::vector, or std::string over a smart pointer managing a fixed
> array, dynamic array, or C-style string.

### `std::make_unique`

```c++
auto f1 { std::make_unique<Fraction>(3, 5) };
```

> **Best practice**<br>
> Use `std::make_unique()` instead of creating `std::unique_ptr` and using new yourself.

Reason below.

### The exception safety issue in more detail

```c++
some_func(std::unique_ptr<T>(new T), func_can_throw());
```

It could create a new T, then call `func_can_throw()`, then create unique ptr. If func
does throw, the T was allocated and won't be deallocated. So T will be leaked.

### Returning `std::unique_ptr` from a function
Can be safely returned from a function by value. In C++14 or earlier, move semantics will
be employed to transfer the Resource from the return value to the object assigned to, and
in C++17 or newer, the return will be elided.

In general, you should not return `std::unique_ptr` by pointer (ever) or reference (unless
you have a specific reason to).

### Passing `std::unique_ptr` to a function
If you want the function to take ownership of the contents of the pointer, pass the
`std::unique_ptr` by value. Note that because copy semantics have been disabled, you'll
need to use `std::move` to actually pass the variable in.

```c++
auto ptr { std::make_unique<Resource>() };

// takeOwnership(ptr); // doesn't work
takeOwnership(std::move(ptr)); // works
```

Ownership of the Resource was transferred to takeOwnership(), so the Resource was
destroyed at the end of takeOwnership(), rather than the end of main().

Most of the time you won't want this. Although you can pass a `std::unique_ptr` by reference
(which will allow the function to use the object without assuming ownership), you should
only do so when the called function might alter or change the object being managed.

Instead, it's better to just pass the resource itself (by pointer or reference, depending
on whether null is a valid argument). This allows the function to remain agnostic of how
the caller is managing its resources. To get a raw pointer from a `std::unique_ptr`, you
can use the get() memeber function.

```c++
auto ptr { std::make_unique<Resource>() };

useResource(ptr.get()); // get() used here to get a pointer to the Resource
```

### Misusing `std::unique_ptr`
Don't let multiple classes manage the same resource. Legal syntactically, but the end
result will be that both res1 and res2 will try to delete the Resource, which will lead to
undefined behavior.

Don't manually delete the resource out from underneath the `std::unique_ptr`.
