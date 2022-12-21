# 19.1 - Template classes

Array.h:

```c++
#ifndef ARRAY_H
#define ARRAY_H

#include <cassert>

template <typename T>
class Array
{
private:
    int m_length { };
    T* m_data { };

public:
    Array(int length)
    {
        assert(length > 0);
        m_data = new T[length] { }; // allocated an array of objects of type T
        m_length = length;
    }

    Array(const Array&) = delete;
    Array& operator=(const Array&) = delete;

    ~Array()
    {
        delete[] m_data;
    }

    void erase()
    {
        delete[] m_data;
        m_data = nullptr;
        m_length = 0;
    }

    T& operator[](int index)
    {
        assert(index >= 0 && index < m_length);
        return m_data[index];
    }

    // tempalted getLength() function defined below
    int getLength() const;
};

// member functions defined outside the class need their own template declaration
template <typename T>
int Array<T>::getLength() const
{
    return m_length;
}

#endif
```

Then:

```c++
...
Array<int> intArray { 12 };
Array<double> doubleArray { 12 };
```

Template classes are instanced in the same way template functions are - the compiler
stencils out a copy upon demand, with the template parameter replaced by the actual data
type the user needs, and then compiles the copy. If you don't ever use a template class,
the compiler won't even compile it.

### Splitting up template classes
With non-template classes, the common procedure is to put the class definition in a header
file, and the member function definitions in a similarly named code file. In this way, the
source for the class is compiled as a separate project file. However, with templates, this
does not work.

In order for the compiler to use a template, it must see both the template definition (not
just a declaration) and the template type used to instantiate the template.

A few to go around this:

Simply put all of your template class code in the header file. Downside: you will end up
with many local copies of the template class, which can increase your compile and link
times. Preferred solution, unless compile or link times start to become a problem.

Move contents of Array.cpp to a new file named Array.inl (.inl - inline), and then include
Array.inl at the bottom of the Array.h header (inside the header guard). Keep sthings more
organized. But the same compile time problem. This file should not be included in
compilation (like headers are not).

temmplates.cpp file...
