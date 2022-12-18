# 13.9 - Destructors

When an object goes out of scope normally, or a dynamically allocated object is
explicitly deleted using the delete keyword, the class destructor is automatically called
(if it exists) to do any necessary cleanup before the object is removed from memory.

Not needed for simple classes (those that just initialize the values of normal member
variables), because C++ will automatically clean up the memory.

Useful when holding any resources (e.g. dynamic memory, a file or a database handle), or
if you need to do any kind of maintenance before the object is detroyed. Last thing to
happens before the object is destroyed.

### Destructor naming

1. Same name as class, precede by a tilde.
2. Take no arguments.
3. Have no return type.

A class can have only one destructor.

Generally, no need to call a destructor explicitly.

Destructors may safely call other member functions since the object isn't destroyed until
after the destructor executes.

### A destructor example

```c++
#include <iostream>
#include <cassert>
#include <cstddef>

class IntArray
{
private:
    int* m_array { };
    int m_length { };

public:
    IntArray(int length)
    {
        assert(length > 0);

        m_array = new int[static_cast<std::size_t>(length)] { };
        m_length = length;
    }

    ~IntArray()
    {
        delete[] m_array;
    }

    void setValue(int index, int value) { m_array[index] = value; }
    int getValue(int index) { return m_array[index]; }

    int getLength() { return m_length; }
};

int main()
{
    IntArray ar ( 10 ); // allocate 10 integers
    // parentheses based initialization should be used when initializing an
    // array/container/list class with a length. (Why?)
    for (int count { 0 }; count < ar.getLength(); ++count)
    {
        ar.setValue(count, count+1);
    }

    std::cout << "The value of element 5 is: " << ar.getValue(5) << '\n';

    return 0;
} // ar is detroyed here, so ~IntArray() destructor is called.
```

This code will generate a compiler error, because it has pointer data members, but does
not override a constructor that takes a const reference of the same class type or operator
= that takes a const reference of the same class type. `-Weffc++`. This will be covered in
14.14.

### Constructor and destructor timing
...

Global variables are constructed before main() and destroyed after main().

### RAII
Resource Acquisition Is Initiliazation. Programming technique whereby resource use is tied
to the lifetime of objects with automatic duration (e.g. non-dynamically allocated
objects).

In C++, RAII is implemented via classes with constructors and destructors. A resource
(such as memory, a file or database handle,etc...) is typically acquired in the object's
constructor (though it can be acquired after the object is created if that makes sense).
That resource can the be used while the object is alive. The resource is released in the
destructor, when the object is destroyed.

Helps prevent resource leaks (e.g. memory not being deallocated).

In the above example, `IntArray` class is an example of a class that implements RAII.

`std::string` and `std::vector` follow RAII - dynamic memory is acquired on
initialization, adn cleaned up automatically on destruction.

### A warning about `std::exit()`
Program will terminate and no destructors will be called. Matters if writing something to
a log file or database before destruction).
