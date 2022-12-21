# 20.5 - Exceptions, classes, and inheritance

### Exceptions and member functions

### When constructors fail
However, the class's destructor is never called, because the object never finished
construction. Because the destructor never executes, you can't rely on said destructor to
clean up any resources that have already been allocated.

Instead of managing dynamic resources directly, wrap in a class that will do it. RAII. C++
std lib comes with RAII-compliant classes to manage common resource types, such as files
(std::fstream) and dynamic memory (`std::unique_ptr` and other smart pointers).

### Exception classes

```c++
#include <iostream>
#include <string>
#include <string_view>

class ArrayException
{
private:
    std::string m_error;

public:
    ArrayException(std::string_view error)
        : m_error { error }
    {
    }

    const std::string& getError() const { return m_error; }
};

class IntArray
{
private:
    int m_data[3] { };

public:
    IntArray() { }

    int getLength() const { return 3; }

    int& operator[](const int index)
    {
        if (index < 0 || index >= getLength())
        {
            throw ArrayException { "Invalid index" };
        }

        return m_data[index];
    }
};

int main()
{
    IntArray array;

    try
    {
        int value { array[5] };
    }
    catch (const ArrayException& exception)
    {
        std::cerr << "An array exception occurred (" << exception.getError() << ")\n";
    }
}
```

Should catch class exception objects by reference instead of by value. Prevents the
compiler from making a copy, and prevents potential object slicing.

### Exceptions and inheritance

```c++
try
{
    throw Derived();
}
catch (const Derived& derived)
{
    std::cerr << "caught Derived\n";
}
catch (const Base& base)
{
    std::cerr << "caught Base\n";
}
```

> **Rule**<br>
> Handlers for derived exception classes should be listed before those for base classes.

### `std::exception`
Base class for all exceptions thrown by the C++ std library.

```c++
try
{
    // code using std lib goes here
}
catch (const std::length_error& exception)
{
    std::cerr << "You ran out of memory!" << '\n';
}
catch (const std::exception& exception)
{
    std::cerr << "Standard ecxeption: " << exception.what() << '\n';
}
```

### Using the standard exceptions directly
Not good to use `std::exception` directly. Should use `std::runtime_error` for generic
errors.

[List of exceptions](https://en.cppreference.com/w/cpp/error/exception)

### Deriving your own classes from `std::exception` and `std::runtime_error`

```c++
class ArrayException : public std::exception
{
private:
    std::string m_error { }; // handle our own string

public:
    ArrayException(std::string_view error)
        : m_error { error }
    {
    }

    const char* what() const noexcept override { return m_error.c_str(); }
};
```

Or `std::runtime_error`, and then no need to handle `what()`.
