# 12.4 - Recursion

A function that calls itself.

If infinite - no function calls are dropped from the stack -> stack overflow.

### Recursive termination conditions

```c++
#include <iostream>

void countDown(int count)
{
    std::cout << "push " << count << '\n';

    if (count > 1) // termination condition
    {
        countDown(count - 1);
    }

    std::cout << "pop " << count << '\n';
}

int main()
{
    countDown(5);
    return 0;
}
```

```
push 5
push 4
push 3
push 2
push 1
pop 1
pop 2
pop 3
pop 4
pop 5
```

```c++
int sumTo(int sumto)
{
    if (sumto <= 0) // base case (termination condition) when unexpected input
    {
        return 0;
    }

    if (sumto == 1) // normal base case (termination condition)
    {
        return 1;
    }

    return sumTo(sumto - 1) + sumto;
}
```

```
sumTo(5) called, 5 <= 1 is false, so we return sumTo(4) + 5.
sumTo(4) called, 4 <= 1 is false, so we return sumTo(3) + 5.
sumTo(3) called, 3 <= 1 is false, so we return sumTo(2) + 5.
sumTo(2) called, 2 <= 1 is false, so we return sumTo(1) + 5.
sumTo(1) called, 1 <= 1 is true, so we return 1. This is the termination condition
```

Now unwind the call stack:

```
sumTo(1) returns 1.
sumTo(2) returns sumTo(1) + 2, which is 1 + 2 = 3.
sumTo(3) returns sumTo(2) + 3, which is 3 + 3 = 6.
sumTo(4) returns sumTo(3) + 4, which is 6 + 4 = 10.
sumTo(5) returns sumTo(4) + 5, which is 10 + 5 = 15.
```

### Recursive algorithms
Typically solve a problem by first finding the solution to a subset of the problem
(recursively), and then modifying that sub-solution to get to a solution.

In many recursive algorithms, some inputs produce trivial outputs. **Base cases**. They act
as termination conditions for the algorithm.

### Fibonacci numbers
Defined mathematically:

```
F(n)=   0 if n = 0
        1 if n = 1
        f(n-1)+f(n-2) if n > 1
```

A not very efficient recursive function to calculate the nth Fibonacci number:

```c++
#include <iostream>

int fibonacci(int count)
{
    if (count == 0)
    {
        return 0;
    }

    if (count == 1)
    {
        return 1;
    }

    return fibonacci(count-1) + fibonacci(count-2);
}

int main()
{
    for (int count { 0 }; count < 13; ++count)
    {
        std::cout << fibonacci(count) << ' ';
    }

    std::cout << '\n';

    return 0;
}
```

### Memoization algorithms
The above is very inefficient. Each call to a Fibonacci non-base case results in 2 more
Fibonacci calls. This produces an exponential number of function calls. In the above case
- 1205 times!

**Memoization**, caches the results of expensive function calls so the result can be
returned when the same input occurs again.

A memoized version of the recursive Fibonacci algorithm

```c++
#include <iostream>
#include <vector>

int fibonacci(int count)
{
    // Create a static vector that will hold the results
    // Indexed by count. The value at the index is the result of the function
    static std::vector results { 0, 1 };

    if (count < static_cast<int>(std::size(results)))
    {
        return results[count];
    }

    results.push_back(fibonacci(count - 1) + fibonacci(count - 2));
    return results[count];
}

int main()
{
    for (int count { 0 }; count < 13; ++count)
    {
        std::cout << fibonacci(count) << ' ';
    }

    std::cout << '\n';

    return 0;
}
```

The memoized version makes 35 function calls, which is much better than the 1205 of the
original algorithm.

### Recursive vs iterative
You can always solve a recursive problem iteratively.

Iterative functions are almost always more efficient. Every time you call a function there
is some amount of overhead that takes place in pushing and popping stack frames.

In general, choose recursion when:

* The recursive code is much simpler to implement.
* The recursion depth can be limited (e.g. there's no way to provide an input that will
  cause it to recurse down 100,000 levels).
* The iterative version of the algorithm requires managing a stack of data.
* This isn't a performance-critical section of code.
