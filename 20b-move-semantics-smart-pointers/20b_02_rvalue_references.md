# M.2 - R-value references

### L-value references recap
Prior to C++11, only one type of reference. It was just called reference. In C++11, it
became an l-value reference.

Can only be initialized with modifiable l-values.

L-value references to const objects can be initialized with modifiable and non-modifiable
l-values and r-values alike. But they cannot be modified.

Particularly useful because they allow us to pass any type of argument (l-value or
r-value) into a function without making a copy of the argument.

### R-value references
C++11 adds a new type of reference called an r-value reference. Can only be initialized
with an r-value.

```c++
int x { 5 };
int &lref { x };
int &&rref { 5 };
```

Non-const can be changed.

Not used very often like above.

### R-value references as function parameters
Most useful for function overloads when you want to have different behavior for l-value
and r-value arguments. (Important for move semantics, will be discussed later.)

```c++
void fun(const int t&lref) // l-value arguments will select this function
{
}

void fun(int &&ref) // r-value arguments will select this function
{
}

int main()
{
    int x { 5 };
    fun(x); // l-value argument calls l-value version of the function
    fun(5); // r-value argument calls r-value version of the function
}
```

Note:

```c++
int &&ref { 5 };
fun(ref); // will call l-value version of the function
```

### Returning an r-value reference
You should almost never return an r-value reference, for the same reason you should almost
never return an l-value reference. In most cases, you'll end up returning a hanging
reference when the referenced object goes out of scope at the end of the function.
