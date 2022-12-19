# 13.14 - Static member functions

```c++
#include <iostream>

class Something
{
private:
    static int s_value;

public:
    static int getValue { return s_value; }
};

int Something::s_value { 1 };

int main()
{
    std::cout << Something::getValue() << '\n';
}
```

Or could be defined outside of the class definition. This works the same way as for normal
member functions.

### Static member functions have no `*this` pointer

### A word of warning about classes with all static members
"Pure static class", aka "monostate".

But it's basically the same as having functions and global variables in a globally
accessible namespace, with all the downsides that global variables have.

### C++ does not support static constructors
No "static constructor" to initialize static variables.

If the static variable can be directly initialized, no constructor is needed -- just
initialize it at the point of definition.

But if initializing the static variable requires executing code, there are multiple ways
to deal with that.

Use a lambda and call it immediately.

```c++
class MyClass
{
public:
    static std::vector<char> s_mychars;
};

std::vector<char> MyClass::s_my_chars { // define the static variable
    [] { // The parameter list of lambdas without parameters can be omitted.
        std::vector<char> v { };

        for (char ch { 'a' }; ch <= 'z'; ++ch)
        {
            v.push_back(ch);
        }

        return v;
    }() // Call the lambda right away
};
```

Or:

```c++
class MyClass
{
public:
    static std::vector<char> s_mychars;

    class init_static // nested class
    {
    public:
        init_static() // its init constructor will initialize our static variable
        {
            for (char ch { 'a' }; ch <= 'z'; ++ch)
            {
                s_mychars.push_back(ch);
            }
        }
    };

private:
    static init_static s_initializer; // we'll use this static object to ensure the
                                      // init_static constructor is called
};

std::vector<char> MyClass::s_mychars { }; // define our static member variable
MyClass::init_static MyClass::s_initializer { }; // define our static initializer, which
// will call the init_static constructor, which will initialize s_mychars
```
