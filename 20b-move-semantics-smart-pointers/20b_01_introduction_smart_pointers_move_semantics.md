# M.1 - Introduction to smart pointers and move semantics

```c++
#include <iostream>

template <typename T>
class Auto_ptr2 // Smart pointer
{
    T* m_ptr;

public:
    Auto_ptr2(T* ptr = nullptr)
        : m_ptr(ptr)
    {
    }

    ~Auto_ptr2()
    {
        delete m_ptr; // will deallocate the resource when the object goes out of scope
    }

    // A copy constructor that implements move semantics
    Auto_ptr2(Auto_ptr2& a) // note: not by const ref
    {
        m_ptr = a.m_ptr; // transfer our dumb pointer from the source to our local object
        a.m_ptr = nullptr; // make sure the source no longer owns the pointer
    }

    // An assignment operator that implements move semantics
    Auto_ptr2& operator=(Auto_ptr2& a) // not: not by const ref
    {
        if (&a == this)
        {
            return *this;
        }

        delete m_ptr; // make sure we deallocate any pointer the destination is already holding first
        m_ptr = a.m_ptr; // then transfer our dumb pointer from the source to the local object
        a.m_ptr = nullptr; // make sure the source no longer owns the pointer
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

int main()
{
    Auto_ptr2<Resource> res1(new Resource());
    Auto_ptr2<Resource> res2; // Start as nullptr

    std::cout << "res1 is " << (res1.isNull() ? "null\n" : "not null\n");
    std::cout << "res2 is " << (res2.isNull() ? "null\n" : "not null\n");

    res2 = res1; // res2 assumes ownership, res1 is set to null

    std::cout << "Ownership transferred\n";

    std::cout << "res1 is " << (res1.isNull() ? "null\n" : "not null\n");
    std::cout << "res2 is " << (res2.isNull() ? "null\n" : "not null\n");

    return 0;
}
```

```
Resource acquired
res1 is not null
res2 is null
Ownership transferred
res1 is null
res2 is not null
Resource acquired
```

### `std::auto_ptr` and why it was a bad idea
Introduced in C++98 and removed in C++17, was C++'s first attempt at a standardized smart
pointer. Opted to implement move semantics just the `Auto_ptr2` class does.

Number of problems:

Because `std::auto_ptr` implements move semantics through the copy constructor and
assignment operator, passing a `std::auto_ptr` by value to a function will cause your
resource to get moved to the function parameter (and be destroyed at the end of the
function when the function parameters go out of scope). Then when you go to access your
`auto_ptr` argument from the caller (not realizing it was transferred and deleted), you're
suddenlt dereferencing a nullptr.

Always deletes its contents using non-array delete. So won't work correctly with
dynamically allocated arrays. Worse, it won't prevent passing it a dynamic array, which it
will then mismanage, leading to memory leaks.

Doesn't play nice with a lot of other classes in the standard library, including most
containers and algorithms. This occurs because those standard library classes assume that
when they copy an item, it actually makes a copy, not a move.

### Moving forward
The core problem is that prior to C++1, the C++ language simply had no mechanism to
differentiate "copy semantics" from "move semantics". Overriding the copy semantics to
implement move semantics leads to weird edge cases and bugs. For example, you can write
`res1 = res2` and have no idea whether res2 will be changed or not.

Because of this, in C++11, the concept of "move" was formally defined, and "move
semantics" were added to the language to properly differentiate copying from moving.

In C++11, `std::auto_ptr` has been replaced by a bunch of other types of "move-aware"
smart pointers: `std::unique_ptr`, `std::weak_ptr` and `std::shared_ptr`.
