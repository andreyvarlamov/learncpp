# 20.7 - Function try blocks

```c++
#include <iostream>

class A
{
private:
    int m_x;

public:
    A(int x) : m_x { x }
    {
        if (x <= 0)
        {
            throw 1;
        }
    }
};

class B : public A
{
public:
    B(int x) try : A { x }
    {
    }
    catch (...) // Exceptions from member initializer list or constructor body are caught here
    {
        std::cerr << "Exception caught\n";
        throw; // rethrow
    }
};

int main()
{
    try
    {
        B b { 0 };
    }
    catch (int)
    {
        std::cout << "Oops\n";
    }
}
```

```
Exception caught
Oops
```

### Limitations on function catch blocks
A function-level catch block for a constructor must either throw a new exception or
rethrow the existing exception -- they are not allowed to resolved exceptions. Return
statements are also not allowed. Reaching the end of the catch block will implicitly
rethrow.

A function-level catch block for a destructor can throw, rethrow, or resolve the current
exception via a return statement. Reaching the end of the catch block will implicitly
rethrow.

A function-level catch block for other functions can throw, rethrow, or resolve the
current exception via a return statement. Reaching the end of the catch block will
implicitly resolve the exception for non-value (void) returning functions and produce
undefined behavior for value-returning functions.

> **Best practice**<br>
> Avoid letting control reach the end of a function-level catch block. Instead, explicitly
> throw, rethrow, or return.

### Function try blocks can catch both base and the current class exceptions

### Don't use function try to clean up resources
Referring to members of the failed object is considered undefined behavior since the
object is "dead" before the catch block executes.
