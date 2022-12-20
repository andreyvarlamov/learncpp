# 17.9 - Multiple inheritance

Inherit members from more than one parent.

E.g. a Teacher is an Employee and a Person.

```c++
class Teacher : public Person, public Employee
{
}
```

### Mixins
A small class that can be inherited from in order to add properties to a class. "Mixed
into" other classes, not instantiated on its own.

```c++
#include <string>

struct Point2D
{
    int x;
    int y;
}

class Box // mixin Box class
{
public:
    void setTopLeft(Point2D point) { m_topLeft = point; }
    void setBottomRight(Point2D point) { m_bottomRight = point; }
private:
    Point2D m_topLeft { };
    Point2D m_bottomRight { };
};

class Label // mixin Box class
{
public:
    void setText(const std::string_view str) { m_text = str; }
    void setFontSize(int fontSize) { m_fontSize = fontSize; }
private:
    std::string m_text { };
    int m_fontSize { };
};

class Button : public Box, public Label { };

int main()
{
    Button button { };
    button.Box::setTopLeft({ 1, 1 });
    button.Box::setBottomRight({ 10, 10 });
    button.Label::setText("Username: ");
    button.Label::setFontSize(6);
}
```
Because mixins are designed to add functionality to the derived class, not to provide an
interface, mixins typically do not use virtual functions. Instead, if it needs to be
customized to work in a particular way, templates are typically used.

A derived class can inherit from a mixin base class using the derived class as a template
type parameter. **Curiously Recurring Template Pattern** (CRTP).

```c++
// The Curiously Recurring Template Pattern (CRTP)

template<class T>
class Mixin
{
    // Mixin<T> can use template parameter T to access members of Derived
    // via (static_cast<T*>(this))
};

class Derived : public Mixin<Derived>
{
};
```

### Problems with multiple inheritance
Ambiguity can result when multiple base classes contain a function with the same name.

[Diamond problem](https://en.wikipedia.org/wiki/Multiple_inheritance#The_diamond_problem)

E.g. scanners and printers are both powered devices, so they derived from PoweredDevice.
However, a copy machine incorporates the functionality of both Scanners and Printers. So
the Copier will have references to PoweredDevice twice.

Can be resolved through explicit scoping, but complexity.

> **Best practice**<br>
> Avoid multiple inheritance unless alternatives lead to more complextity.
