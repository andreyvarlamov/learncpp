# 13.3 - Public vs private access specifiers

The code outside of a struct or class is sometimes called **the public**: the public is
only allowed to access the public members of a struct or class, which makes sense.

All members of a struct are public members by default.

All members of a class are private members by default.

Private members can only be accessed by other members of the class (or by friend of the
class).

### Access specifiers
Determines who has access to the members that follow the specifier.

```c++
class DateClass
{
public:
    ...
private:
    ...
protected:
    ...
}
```

### Mixing access specifiers
No limit to the number of access specifiers in a class.

> **Best practice**<br>
> Make member variables private, and member functions public, unless there's a reson not
> to.

The group of public members of a class are often referred to as a **public interface**.

### Access controls work on a per-class basis

```c++
class DateClass
{
    int m_month {};
    ...

public:
    ...
    void copyFrom(const DateClass& d)
    {
        // Can access the private members of d directly
        // Even though this function is accessing a different instance of a class
        m_month = d.m_month;
        ...
    }
};

int main()
{
    DateClass date;
    date.setDate(...);
    
    DateClass copy { };
    copy.copyFrom(date);
    ...
}
```

Useful when we need to copy members from one object of a class to another object of the
same class. Also overloading `operator<<` to print members of a class.

### Structs vs classes revisited
...

One more minor difference -- structs inherit from other classes publicly and classes
inherit privately.

### Quiz
Question 3 -- see `ex/01_custom_stack.cpp`
