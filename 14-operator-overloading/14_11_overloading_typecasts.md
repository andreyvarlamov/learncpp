# 14.11 - Overloading typecasts

User-defined conversions.

```c++
#include <iostream>

class Cents
{
private:
    int m_cents;

public:
    Cents(int cents = 0)
        : m_cents { cents }
    {
    }

    operator int() const { return m_cents; }

    int getCents() const { return m_cents; }
    void setCents(int cents) { m_cents = cents; }
};

class Dollars
{
private:
    int m_dollars;

public:
    Dollars(int dollars = 0)
        : m_dollars { dollars }
    {
    }

    operator Cents() const { return Cents { m_dollars * 100 }; }
};

void printCents(Cents cents)
{
    std::cout << cents;
}

// from another example
void printInt(int value)
{
    std::cout << value;
}

int main()
{
    Dollars dollars { 9 };
    printCents(dollars); // dollars will be implicitly cast t o a Cents here
    std::cout << '\n';

    Cents cents { 7 };
    printInt(cents.getCents());

    std::cout << '\n';

    return 0;
}
```

Also allows to cast explicitly:

```c++
int c { static_cast<int>(cents) };
```

### Converting constructors vs overloaded typecasts
Perform similar roles: an overloaded typecast allows us to define a function that converts
some program-defined type A into some other type B.

In general, prefer a converting constructor to an overloaded typecast. Allows the type
being constructed to own the construction.

A few exceptions:

* When providing a conversion to a fundamental type (since you can't define constructors
  for these types). Most idiomatically, conversion to `bool`, for cases where it makes
  sense to be able to use an object in a conditional statement.
* When providing a conversion to a type you can't add members to (e.g. a conversion to
  `std::vector`, since you can't define constructors for these types either).
* When you do not want the type being constructed to be aware of the type being converted
  to. This can be helpful for avoiding circular dependencies. E.g. `std::string` provides
  an overloaded typecast to `std::string_view` so that `std::string_view` doesn't have to
  `#include <string>`.
