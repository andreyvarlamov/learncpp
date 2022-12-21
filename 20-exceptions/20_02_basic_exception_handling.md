# 20.2 - Basic exception handling

**throw**, **try**, and **catch**.

**Raising** an exception.

When an exception is raised, execution of the program immediately jumps to the nearest
enclosing **try** block (propagating up the stack if necessary to find an encloding block.
If any of the catch handlers attached to the try block handle that type of exception, that
handler is executed and the exception is considered handled.

```c++
#include <iostream>
#include <string>

int main()
{
    try
    {
        throw -1;
    }
    catch(int x)
    {
        std::cerr << "Int exception with value: " << x << '\n';
    }
    catch(double)
    {
        std::cerr << "Double exception.";
    }
    catch(const std::string&)
    {
        std::cerr << "std::string exception with value";
    }

    std::cout << "Continuing on our merry way\n";

    return 0;
}
```

```
Int exception with value -1
Continuing on our merry way
```

Compiler will not perform implicit conversions or promotions when matching exceptions with
catch blocks.

Can leave the catch block empty too.
