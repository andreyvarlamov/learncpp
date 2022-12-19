# 13.12 - Const class objects and member functions

### Const classes
Instantiated class objects can be made const by using const keyword. Initialization is
done via class constructors. Once a const class object has been initialized via
constructor any attempt to modify the member variables of the object is disallowed, as it
would violate the const-ness of the object.

### Const member functions
Const class objects can only explicitly call const member functions. A const member
function guarantees it will not modify the object or call any non-const member functions.

```c++
class Something
{
    public m_value { };

    Something() : m_value { 0 } { }

    void resetValue() { m_value = 0; } // if you attempted to make this const, you would
    // get a compiler error -- const functions can't change member variables
    void setValue(int value) { m_value = value; }

    int getValue() const;
};

int Something::getValue() const
{
    return m_value;
}
```

### Const objects via pass by const reference
Instantiating const class objects is not as common of a scenario as this one: passing an
object to a function by const reference.

Usually the way to pass class-type objects to functions (avoid copying).

### Const members can not return non-const references to members

### Overloading const and non-const function
Not done very often, but possible. Possible because the const qualifier is considered part
of the function's signature. 2 functions which differ only in const-ness are considered
distinct.

The const version of the function will be called on any const objects, and the non-const
version will be called on any non-const objects.

```c++
#include <string>

class Something
{
private:
    std::string m_value { };

public:
    Something(const std::string& value="") : m_value { value } { }

    const std::string& getValue() const { return m_value; }
    std::string& getValue() { return m_value; }
};

int main()
{
    Something something;
    something.getValue() = "Hi"; // calls non-const getValue();

    const Something something2;
    something2.getValue() = "Hi"; // calls const getValue();

    return 0;
}
```

Overloading a function with a const and non-const version is typically done when the
return value needs to differ in constness. In the example above, the non-const version of
getValue() will only work with non-const objects, but is more flexible in that we can use
it to both read and write `m_value` (which we do by assigning the string "Hi").

The const version of getValue() will work with either const or non-const objects, but
returns a const reference, to ensure we can't modify the const object's data.

### Summary
Because passing objects by const reference is common, your classes should be
const-friendly. That means making any member function that does not modify the state of
the class object const!
