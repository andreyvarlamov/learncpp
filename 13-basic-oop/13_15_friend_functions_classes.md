# 13.15 - Friend functions and classes

### Friend functions

```c++
#include <iostream>

class Value
{
private:
    int m_value { };

public:
    Value(int value) : m_value { value }
    {
    }

    friend bool isEqual(const Value& value1, const Value& value2);
};

// Friend function to Value
// Can access private member m_value of Value
bool isEqual(const Value& value1, const Value& value2)
{
    return (value1.m_value == value2.m_value);
}

int main()
{
    Value v1 { 5 };
    Value v2 { 6 };
    std::cout << std::boolalpha << isEqual(v1, v2);
}
```

Note that a friend function does not have an implicit `*this` pointer

### Multiple friends
A function can a friend of more than one class at the same time. E.g.:

```c++
class Humidity; // Notice the class prototype that tells the compiler that we are
// going to define a class called Humidity in the future. Without this the compiler
// wouldn't know what Humidity is.

class Temperature
{
private:
    int m_temp { };

public:
    Temperature(int temp = 0) : m_temp { temp }
    {
    }

    friend void printWeather(const Temperature& temperature, const Humidity& humidity);
};

class Humidity
{
private:
    int m_humidity { };

public:
    Humidity(int humidity = 0) : m_humidity { humidity }
    {
    }

    friend void printWeather(const Temperature& temperature, const Humidity& humidity);
};

void printWeather(const Temperature& temperature, const Humidity& humidity)
{
    std::cout << "..." << temperator.m_temp << "..." << humidity.m_humidity;
}
```

### Friend classes

```c++
#include <iostream>

class Storage
{
private:
    int m_nValue { };
    double m_dValue { };

public:
    Storage(int nValue, double dValue) : m_nValue { nValue }, m_dValue { dValue }
    {
    }

    friend class Display;
};

class Display
{
private:
    bool m_displayIntFirst;

public:
    Display(bool displayIntFirst) : m_displayIntFirst { displayIntFirst }
    {
    }

    void displayItem(const Storage& storage)
    {
        if (m_displayIntFirst)
        {
            std::cout << storage.m_nValue << ' ' << storage.m_dValue << '\n';
        }
        else
        {
            std::cout << storage.m_dValue << ' ' << storage.m_nValue << '\n';
        }
    }
};

int main()
{
    Storage storage { 5, 6.7 };
    Display display { false };

    display.displayItem(storage);

    return 0;
}
```

Even though Display is a friend of Storage, Display has no direct access to `*this`
pointer of Storage objects.

Just because Display is a friend of Storage, doesn't mean that Storage is a friend of
Display.

If class A is a friend of B, and B is a friend of C, doesn't mean A is a friend of C.

### Friend member functions

```c++
#include <iostream>

class Storage; // forward declaration for class Storage

class Display
{
private:
    bool m_displayIntFirst;

public:
    Display(bool displayIntFirst) : m_displayIntFirst { displayIntFirst }
    {
    }

    void displayItem(const Storage& storage); // forward declaration above needed for this
                                              // declaration line
};

class Storage // full definition of Storage class
{
private:
    int m_nValue { };
    double m_dValue { };

public:
    Storage(int nValue, double dValue) : m_nValue { nValue }, m_dValue { dValue }
    {
    }

    // Make the Display::displayItem member function a friend of the Storage class
    // (requires seeing the full definition of class Display, as above)
    friend class Display::displayItem(const Storage& storage);
};

// Now we can define Display::displayItem, which needs to have seen the full
// definition of class Storage
void Display::displayItem(const Storage& storage)
{
    if (m_displayIntFirst)
    {
        std::cout << storage.m_nValue << ' ' << storage.m_dValue << '\n';
    }
    else
    {
        std::cout << storage.m_dValue << ' ' << storage.m_nValue << '\n';
    }
}

int main()
{
    Storage storage { 5, 6.7 };
    Display display { false };

    display.displayItem(storage);

    return 0;
}
```

A better solution is to put each class definition in a separate header file, with the
member functions in corresponding .cpp files. That way, all of the class definitions would
have been visible immediately in the .cpp files, and no rearranging of classes or
functions is necessary.

### Summary
Friending is commonly used when defining overloaded operators, or less commonly, when two
or more classes need to work together in an intimate way.

### Quiz
See `ex/02-point-vector` for the Q1
