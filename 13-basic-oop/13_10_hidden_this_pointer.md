# 13.10 - The hidden "this" pointer

Somehow when we call `object1.setA(2);`, C++ knows that `setA()` should operate on object
`object1`, and that `m_a` inside `setA(int)` refers to `object1.m_a`.

### The hidden `*this` pointer

`object1.setA(2)` >> when compiled >> `setA(&object1, 2)`.

And `void setA(int a) { m_a = a; }` >> `void setA(Object* const this, int a) { this->m_a = a; }`

The **this pointer** is a hidden const pointer that holds the address of the object the
member frunction was called on.

### "this" always points to the object being operated on
Each member function has a "this" pointer parameter that is set to the address of the
object being operated on.

Because "this" is just a function parameter, it doesn't add any memory usage to your class
(just to the member function call, since the parameter needs to be passed to the function
and stored in memory).

### Explicitly referencing "this"
Most of the time no need. But:

```c++
class Something
{
private:
    int data;

public:
    Something(int data)
    {
        this->data =data;
    }
};
```

But better to use "m_" prefixes.

Some developers prefer to explicitly add this-> to all class members. But it is still
better to just use "m_" prefixes.

### Chaining member functions

```c++
std::cout << "Hello, " << userName;
(std::cout << "Hello, ") << userName;
// vv
(std::cout) << userName;
```

```c++
class Caslc
{
private:
    int m_value { };

public:
    Calc& add(int value) { m_value += value; return *this; }
    Calc& sub(int value) { m_value -= value; return *this; }
    Calc& mult(int value) { m_value *= value; return *this; }

    int getValue() { return m_value; }
};

int main()
{
    Calc calc { };
    calc.add(5).sub(3).mult(4);

    std::cout << calc.getValue()  << '\n';
}
```

"this" is a const pointer.
