# 18.10 - Dynamic casting

Upcasting - convert a Derived pointer into a Base pointer. C++ will do this implicitly.

Downcasting - convert a Base pointer into a Derived pointer. - `dynamic_cast`.
`dynamic_cast` has a few different capabilities, but this one is by far the most common.

```c++
class Base
{
    ...
};

class Derived : public Base
{
    ...

public:
    const std::string& getName() const { return m_name; }
};

Base* getObject(bool returnDerived)
{
    if (returnDerived)
    {
        return new Derived { 1, "Apple" };
    }
    else
    {
        return new Base { 2 };
    }
}

int main()
{
    Base* b { getObject(true) };

    Derived* d { dynamic_cast<Derived*>(b) }; // use dynamic cast to convert Base pointer
                                              // into Derived pointer

    if (d)
    {
        std::cout << "The name of the Derived is: " << d->getName() << '\n';
    }

    delete b;

    return 0;
}
```

If b wasn't pointing to a Derived object (e.g. `getObject(false)`), `dynamic_cast` will
return a `nullptr`.

Several other cases where downcasting using `dynamic_cast` will not work:

* With protected or private inheritance
* For classes that do not declare or inherit any virtual functions (and thus don't have a
  virtual table).
* In certain cases involving virtual base classes.

### Downcasting with `static_cast`
Will "succeed" even if the Base pointer isn't pointing to a Derived object. Undefined
behavior.

If you're absolutely sure downcasting will succeed, then using `static_cast` is
acceptable.

### `dynamic_cast` and references

```c++
Derived apple { 1, "Apple" };
Base& b { apple };
Derived& d { dynamic_cast<Derived&>(b) };
```

### `dynamic_cast` vs `static_cast`
Use `static_cast` unless you're downcasting. However, you should consider avoiding casting
altogether and just use virtual functions.

### Downcasting vs virtual functions
In general, using a virtual function should be preferred over downcasting.

### A warning about `dynamic_cast` and RTTI
Run-time type information is a feature of C++ that exposes information about an object's
data type at runtime. This capability is leveraged by `dynamic_cast`. Because RTTI has a
pretty significant space performance cost, some compiler allow you to turn RTTI off as an
optimizaation. Then `dynamic_cast` won't function correctly.
