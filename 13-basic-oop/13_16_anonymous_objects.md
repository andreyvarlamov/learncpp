# 13.16 - Anonymous objects

Previously, with fundamental types. Can return using an expression. Without defining a
temporary local variable. Same with passing into functions.

### Anonymous class objects

```c++
#include <iostream>

class Cents
{
private:
    int m_cents { };

public:
    Cents(int cents)
        : m_cents { cents }
    { }

    int getCents() const { return m_cents; }
};

Cents add(const Cents& c1, const Cents& c2)
{
    // List initialization looks at the return type of the function
    // and creates the correct object accordingly
    return { c1.getCents() + c2.getCents() };
}

int main()
{
    std::cout << "I have " << add(Cents { 6 }, Cents{ 8 }).getCents() << " cents.\n";

    return 0;
}
```

### Summary
...

Because anonymous objects have expression scope, they can only be used once (unless bound
to a constant l-value references, which will extend the lifetime of the temporary object
to match the lifetime of the reference). If you need to reference a value in multiple
expressions, you should use a named variable instead.
