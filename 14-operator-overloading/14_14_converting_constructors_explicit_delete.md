# 14.14 - Converting constructors, explicit, and delete

By default, C++ will treat any constructor as an implicit conversion operator.

```c++
class Fraction
{
public:
    Fraction(int numerator = 0, int denominator = 1) ...

...
};

void printFraction(const Fraction& f)
{...}

printFraction(6);
```

Will use Fraction(int, int) constructor.

This implicit conversion for all kinds of initialization (direct and copy).

### The `explicit` keyword
The above is not always disereable. E.g.:

```c++
class MyString
{
public:
    MyString(int x)
    {
        m_string.resize(x);
    }

    MyString(const char* string)
    {
        m_string = string;
    }

    ...
};

void printString(const MyString& s)
{...}

MyString mine = 'x';
printString('x');
```

`explicit` keyword to make this constructor ineligible for implicit conversions.

`explicit MyString(int x)`.

Then `MyString mine = 'x'`, etc. will cause a compile error.

But only prevents implicit conversions. Explicit - still allowed.

> **Best practice**<br>
> Consider making your constructors and user-defined conversion member functions explicit
> to prevent implicit conversion errors.

### The `delete` keyword
If you really want to completely disallow a char being converted to MyString in the above
example.

Could make it private, but would still be available from inside the class.

A better way is to use "delete" keyword to delte the function.

`MyString(char) = delete`.
