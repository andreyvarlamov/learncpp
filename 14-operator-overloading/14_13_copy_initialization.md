# 14.13 - Copy initialization

```c++
Fraction six = Fraction(6);
```

Will be evaluated in the same way as the following:

```c++
Fraction six(Fraction(6));
```

Which, prior to C++17, may or may not get elided by the compiler for performance reasons.

So:

> **Best practice**<br>
> Avoid using copy initialization, and use uniform initialization instead.

### Other places copy initialization is used.
When you pass or return a class by value, that process uses copy initialization

```c++
Fraction makeNegative(Fraction f) // Copy argument when called
{
    f.setNumerator(-f.getNumerator());
    return f; // copy when returned
}
```
