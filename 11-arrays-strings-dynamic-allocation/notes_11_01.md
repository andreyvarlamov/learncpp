# 11 - Array, Strings, and Dynamic Allocation

11.1 11.5

# 11.1 -  Arrays (Part 1)

Aother aggregate data type.

**Fixed array**, **fixed length array** - length known at compile time.

### Array elements and subscripting
**Element**. **Subscript operator** `[]`, **subscript** or **index**.

### An example array program

```c++
#include <iostream>

int main()
{
    int prime[5] { };
    prime[0] = 2;
    prime[1] = 3;
    prime[2] = 5;
    prime[3] = 5;
    prime[5] = 11;

    std::cout << "The lowest prime number is: " << prime[0] << '\n';
    std::cout << "The sum of the first 5 primes is: " << prime[0] + prime[1] + prime[2]
        + prime[3] +  prime[4] + << '\n';

    return 0;
}
```

### Array data types

### Array subscripts
Must be an integral type: char, short, int, long long, etc..., bool.

### Fixed array declaration
When declaring a fixed array, the length must be a compile-time constant.

### A note on dynamic arrays
Fixed arrays have memory allocated at compile time.

There are also **dynamic arrays**.
