# M.3 - Move constructors and move assignment

### Copy constructors and copy assignment

```c++
#include <iostream>

template <typename T>
class Auto_ptr3
{
    T* m_ptr;

public:
    Auto_ptr3(T* ptr = nullptr)
        : m_ptr(ptr)
    {
    }

    ~Auto_ptr3()
    {
        delete m_ptr;
    }

    // Copy constructor - deep copy
    Auto_ptr3(const Auto_ptr3& a) // note: not by const ref
    {
        m_ptr = new T;
        *m_ptr = *a.m_ptr;
    }

    // Copy assignment - deep copy
    Auto_ptr3& operator=(Auto_ptr3& a) // not: not by const ref
    {
        if (&a == this)
        {
            return *this;
        }

        delete m_ptr;

        m_ptr = new T;
        *m_ptr = *a.m_ptr;

        return *this;
    }

    T& operator*() const { return *m_ptr; }
    T* operator->() const { return m_ptr; }
    bool isNull() const { return m_ptr == nullptr; }
};

class Resource
{
public:
    Resource() { std::cout << "Resource acquired\n"; }
    ~Resource() { std::cout << "Resource destroyed\n"; }
};

Auto_ptr3<Resource> generateResource()
{
    Auto_ptr3<Resource> res { new Resource }; // create res and initialize with a
                                              // dynamically allocated resource
    return res;
}

int main()
{
    Auto_ptr3<Resource> mainres;
    mainres = generateResource();

    return 0;
}
```

```
Resource acquired  -- generateResource() - new Resource
Resource acquired  -- generateResource() - return res - copy constructor with a deep copy
Resource destroyed -- generateResource() is done, res goes out of scope
Resource acquired  -- temporary object is assigned to mainres by copy assignment. Our copy
                      assignment also does a deep copy
Resource destroyed -- assignment expression ends, and the temp object goes out of scope
                      and is destroyed
Resource destroyed -- end of main(), mainres goes out of scope
```

Inefficient.

### Move constructors and move assignment

```c++
#include <iostream>

template <typename T>
class Auto_ptr4
{
    T* m_ptr;

public:
    Auto_ptr4(T* ptr = nullptr)
        : m_ptr(ptr)
    {
    }

    ~Auto_ptr4()
    {
        delete m_ptr;
    }

    // Copy constructor - deep copy
    Auto_ptr4(const Auto_ptr4& a) // note: not by const ref
    {
        m_ptr = new T;
        *m_ptr = *a.m_ptr;
    }

    // Move constructor - transfer ownership from a.m_ptr to m_ptr
    Auto_ptr4(Auto_ptr4&& a) noexcept
        : m_ptr(a.m_ptr)
    {
        a.m_ptr = nullptr;
    }

    // Copy assignment - deep copy
    Auto_ptr4& operator=(Auto_ptr4& a) // not: not by const ref
    {
        if (&a == this)
        {
            return *this;
        }

        delete m_ptr;

        m_ptr = new T;
        *m_ptr = *a.m_ptr;

        return *this;
    }

    // Move assignment - transfer ownership from a.m_ptr to m_ptr
    Auto_ptr4& operator=(Auto_ptr4&& a) noexcept
    {
        if (&a == this)
        {
            return *this;
        }

        delete m_ptr;

        m_ptr = a.m_ptr;
        a.m_ptr = nullptr;

        return *this;
    }

    T& operator*() const { return *m_ptr; }
    T* operator->() const { return m_ptr; }
    bool isNull() const { return m_ptr == nullptr; }
};

class Resource
{
public:
    Resource() { std::cout << "Resource acquired\n"; }
    ~Resource() { std::cout << "Resource destroyed\n"; }
};

Auto_ptr4<Resource> generateResource()
{
    Auto_ptr4<Resource> res { new Resource }; // create res and initialize with a
                                              // dynamically allocated resource
    return res; // this return will invoke the move constructor
}

int main()
{
    Auto_ptr4<Resource> mainres;
    mainres = generateResource(); // this assignment will invoke the move assignment

    return 0;
}
```

```
Resource acquired  -- generateResource() - new Resource
Resource destroyed -- end of main(), mainres goes out of scope
```

### When are the move constructor and move assignment called?
When those functions have been defined, and the argument for construction or assignmen is
an r-value. Most typically, this r-value will be a literal or temp value.

In most cases, a move constructor and move assignment operator will not be provided by
default, unless the class does not have any defined copy constructors, copy assignment,
move assignment, or destructors.

### The key insight behind move semantics
If we construct an object or do an assignment where the argument is an l-value, the only
thing we can reasonbly do is copy the l-value. We can't assume it's safe to alter the
l-value, because it may be used again later in the program. If we have an expression
"a=b", we wouldn't reasonably expect b to be changed in any way.

If we construct an object or do an assignment where the argument is an r-value, then we
know that r-value is just a temporary object of some kind. Instead of copying it (which
can be expensive), we can simply transfer its resources (which is cheap) to the object
we're constructing or assigning. This is safe to do because the temporary object will be
destroyed at the end of the expression anyway, so we know it will never be used again.

C++11, through r-value references, gives us the ability to provide different behaviors
when the argument is an r-value vs an l-value, enabling us to make smarter and more
efficient decisions about how our objects should behave.

### Move functions should always leave both objects in a valid state
When `a` goes out of scope, the destructor for `a` will be called, and `a.m_ptr` will be
deleted. If at that point `a.m_ptr` is still pointing to the same object as `m_ptr`, then
`m_ptr` will be left as a dangling pointer. When the object containing `m_ptr` eventually
gets used (or destroyed), we'll get undefined behavior.

When implementing move semantics, it is important to ensure the moved-from object is left
in a valid state, so that it will destruct properly (without creating undefined behavior).

### Automatic l-values returned by values may be moved instead of copied
Special rule: automatic objects returned from a function by value can be moved even if
they are l-values. Res was going to be destroyed at the end of the function anyway, so
might as well steal its resources instead of making an expensive and unneccesary copy.

Although the compiler can move l-value return values, in some cases it may be able to do
even better by simply eliding the copy altogether (which avoids the need to make a copy or
do a move at all). In such a case, neither the copy constructor nor move constructor would
be called.

### Disabling copying
In move-enabled classes, it is sometimes desirable to delete the copy constructor and copy
assignment functions to ensure copies aren't made. In the case of our `Auto_ptr` class, we
don't want to copy our templated object T - both because it's expensive, and whatever
class T is may not even support copying.

```c++
#include <iostream>

template <typename T>
class Auto_ptr5
{
    T* m_ptr;

public:
    Auto_ptr5(T* ptr = nullptr)
        : m_ptr(ptr)
    {
    }

    ~Auto_ptr5()
    {
        delete m_ptr;
    }

    // Copy constructor - no copying allowed
    Auto_ptr5(const Auto_ptr5& a) = delete;

    // Move constructor - transfer ownership from a.m_ptr to m_ptr
    Auto_ptr5(Auto_ptr5&& a) noexcept
        : m_ptr(a.m_ptr)
    {
        a.m_ptr = nullptr;
    }

    // Copy assignment - no copying allowed
    Auto_ptr5& operator=(Auto_ptr5& a) = delete;

    // Move assignment - transfer ownership from a.m_ptr to m_ptr
    Auto_ptr5& operator=(Auto_ptr5&& a) noexcept
    {
        if (&a == this)
        {
            return *this;
        }

        delete m_ptr;

        m_ptr = a.m_ptr;
        a.m_ptr = nullptr;

        return *this;
    }

    T& operator*() const { return *m_ptr; }
    T* operator->() const { return m_ptr; }
    bool isNull() const { return m_ptr == nullptr; }
};
```

If you were to try to pass an `Auto_ptr5` by value, the compiler would complain that the
copy constructor required to initialize the funciton argument has been deleted.

This is finally a good smart pointer class. The std lib contains a class very much like
this one. `std::unique_ptr`.

### Do not implement move semantics using `std::swap`
It will call both the move constructor and move assignment on move-capable objects.
Infinite recursion.
