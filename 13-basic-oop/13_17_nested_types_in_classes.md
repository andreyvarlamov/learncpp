# 13.17 - Nested types in classes

```c++
class Fruit
{
public:
    enum FruitType
    {
        apple,
        banana,
        cherry
    };

private:
    FruitType m_type { };
    int m_percentageEaten { 0 };

public:
    Fruit(FruitType type) : m_type { type }
    {
    }

    FruitType getType() const { return m_type; }
    int getPercentageEaten() const { return m_percentageEaten; }
};

int main()
{
    Fruit apple { Fruit::apple };

    if (apple.getType() == Fruit::apple)
    {
        std::cout << "I am an apple";
    }
    else
    {
        std::cout << "I am not an apple";
    }

    return 0;
}
```

If it was enum class, would have to access it like: `Fruit::FruitType::apple`.

### Other types can be nested too
Enums probably most common type that is nested inside a class. Can also do typedefs, type
aliases and even other classes.

Like any normal member of a class, nested classes have the same access to members of the
enclosing class that the enclosing class does. However, the nested class does not have any
special access to the "this" pointer of the enclosing class.

One other limitation of nested types -- they can't be forward declared. However, this is
rarely a problem in practice since the entire class definition (including the nested type)
can generally be #included where needed.
