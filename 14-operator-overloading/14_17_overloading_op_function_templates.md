# 14.17 - Overloading operators and function templates

Overload operators used by template functions, so that when the compiler creates a
function overload bases on template with user-defined types, and they're passed down into
the functions, the operators are applied properly.

E.g.

```c++
template <typename T>
const T& max(const T& x, const T& y)
{
    return (x < y) ? y : x;
}
```

If there's no < overload for the user-defined type that is passed into this function, the
compiler will complain.
