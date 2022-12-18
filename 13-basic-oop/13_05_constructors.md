# 13.5 - Constructors

Can't initialize class and members using aggregate initialization when members are
private.

### Constructors
Special kind of class member function that is automatically called when an object of that
class is created.

After a constructor executes, the object should in a well-defined, usable state.

Constructors have specific rules:

1. Have the same name as the class, with the same capitalization
2. Have no return type (not even void).

### Default constructors and default initialization
A constructor that takes no parameters (or has parameters that all have default values).

```c++
#include <iostream>

class Fraction
{
privated:
    int m_numerator { };
    int m_denominator { };

public:
    Fraction()
    {
        m_numerator = 0;
        m_denominator = 0;
    }

    int getNumerator() { return m_numerator; }
    int getDenominator() { return m_denominator; }
    double getValue() { return static_cast<double>(m_numerator) / m_denominator; }
};

int main()
{
    Fraction fraction { }; // calls Fraction() default constructor
    std::cout<< frac.getNumerator() << '/' << grac.getDenominator() << '\n';

    return 0;
}
```

When the line `Fraction fraction { }` executes, the compiler sees that we're instantiating
an object of type Fraction with no arguments. It then performs value-initialization of
`frac`, that is, the default constructor gets called.

Although technically incorrect, this is often called **default initialization**.

### Value-initialization
Value initialization:

```c++
Fraction frac { };
```

Default initialization:

```c++
Fraction frac;
```

For the most part, same outcome.

Many programmers prefer default-initialization for class objects. Because when using
value-initialization, the compiler may zero-initialize the class members before calling
the dedfault constructor in certain cases, which is slightly inefficient.

But downside: have to know wheter a type will initialize itself, i.e. it is a class type
and all members have an initializer, or there is a default-constructor that initializes
all member variables. If you see a defined variable without an initializer, you have to
think whether it's a mistake or not, depending on what type the object is).

> **Best practice**<br>
> Favor value-initialization over default-initialization for class-objects.

### Direct- and list-initialization using constructors with parameters

```c++
class Fraction
{
    ...

public:
    Fraction()
    {
        ...
    }

    Fraciton(int num, int den = 1)
    {
        ...
    }
    ...
};

...

Fraction fiveThirds { 5, 3 }; // List initialization, calls Fraction(int, int)
Fraction threeQuarters(5, 3); // Direct initialization, also calls Fraction(int, int)

Fraction six { 6 }; // calls Fraction(int, int), sec param - default
```

> **Best practice**<br>
> Favor brace initialization to initialize class objects

We'll discover reasons (templates and `std::initializer_list`) to use direct
initialization when calling constructors later.

### Copy initialization with classes

```c++
Fraction seven = 7; // Copy initialize a Fraction. The compiler will try to find a way to
// convert 7 to a Fraciton, which will invoke the Fraction(7, 1) constructors.
```

However, recommended to avoid this, as it may be less efficient. Copy-initialization does
not work the same with classes though the end-result is the same. We'll explore this
later.

### Reducing your constructors
Use default params to simplify and use only constructor as both default and non-default
constructor.

```c++
class Fraction
{
    ...

public:
    Fraciton (int num = 0, int den = 1)
    {
        assert(den != 0);

        ...
    }

    ...
};

...

Fraction zero; // will call Fraction(0, 1)
Fraction zero { }; // will call Fraction(0, 1)
Fraction six { 6 }; // will call Fraction(6, 1)
Fraction fiveThirds { 5, 3 }; // will call Fraction(5, 3)
```

### A reminder about default parameters

### An implicitly generated default constructor
...

When the generated default constructor is called, members will still be initialized if
they have non-static member initializers.

If your class has any other constructors, the implicitly generated constructor will not be
provided.

Can either add default arguments to every param of a constructor with params, or
explicitly define a default constructor.

Or can use the default keyword to tell the compiler to create a default constructor for us
anyways.

```c++
Date() = default;
```

It is also safer, because it can zero-initialzie members even if they have not been
initialized at their declaration.

> **Best practice**<br>
> If you have constructors in your `class` and need a default constructor that does
> nothing (e.g. because all your members are initialized using non-static member
> initialization), use `= default`.

### Classes containing class members
A class may contain other class objects as member variables. By default, when the outer
class is constructed, the member variables will have their default constructors called.
This happens before the body of the constructor executes.

```c++
#include <iostream>

class A
{
public:
    A() { std::cout << "A\n"; }
};

class B
{
public:
    B() { std::cout << "B\n"; }
};

int main()
{
    B b;
    return 0;
}
```

Output:

```
A
B
```

The difference is that class-type members get initialized even if we don't explicitly
initialize them.

### Constructor notes
Constructors do not actually create the objects. The compiler sets up the memory
allocation for the object prior to the constructor call.

Constructors actually serve two purposes:

1. Determine who is allowed to create an object of the class type. I.e. an object of a
   class can only be created if a matching constructor can be found.
2. Can be used to initialize objects. Whether the constructor actually does an
   initialization is up to the programmer. Syntactically valid to have a constructor that
   does no initialization at all. (But it is best practice to always initialize all
   members.)

Constructors are only intended to be used for initialization when the object is created.
You should not try to call a constructor to re-initialize an existing object. While it may
compile, the results will not be what you intended (instead, the compiler will create a
temporary object and then discard it).
