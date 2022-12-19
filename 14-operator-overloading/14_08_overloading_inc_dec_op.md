# 14.8 - Overloading the increment and decrement operators

```c++
class Digit
{
private:
    int m_digit;

public:
    Digit(int digit = 0) : m_digit { digit }
    { }

    Digit& operator++();
    Digit& operator--();

    Digit operator++(int);
    Digit operator--(int);

    friend std::ostream& operator<<(std::ostream& out, const Digit& d);
};

Digit& Digit::operator++()
{
    if (m_digit == 9)
    {
        m_digit = 0;
    }
    else
    {
        ++m_digit;
    }

    return *this;
}

Digit& Digit::operator--()
{
    if (m_digit == 0)
    {
        m_digit = 9;
    }
    else
    {
        --m_digit;
    }

    return *this;
}

// int parameter means this is postfix operator++
Digit Digit::operator++(int)
{
    // Create a temp variable with our current digit
    Digit temp { *this };

    // Use prefix operator to increment this digit
    ++(*this);

    // Return temporary result
    return temp;
}

Digit Digit::operator--(int)
{
    // Create a temp variable with our current digit
    Digit temp { *this };

    // Use prefix operator to increment this digit
    --(*this);

    // Return temporary result
    return temp;
}
...
```

Provided an integer dummy parameter on the postfix version. Because the dummy parameter is
not used in the function implementation, we have not given it a name. This tells the
compiler to treat this variable as a placeholder.

Note the overhead on the postfix overloads, as the object is copied.
