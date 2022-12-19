# 13.11 - Class code and header files

### Defining member functions outside the class definition

Calc.h:

```c++
#ifndef CALC_H
#define CALC_H
class Calc
{
private:
    int m_value = 0;

public:
    Calc(int value=0);

    Calc& add(int value);
    Calc& sub(int value);
    Calc& mult(int value);

    int getValue() { return m_value; }
};

#endif
```

Calc.cpp:

```c++
#include "Date.h"

Calc::Calc(int value) : m_value { value }
{
}

Calc& Calc::add(int value)
{
    m_value += value;
    return *this;
}

Calc& Calc::sub(int value)
{
    m_value -= value;
    return *this;
}

Calc& Calc::mult(int value)
{
    m_value *= value;
    return *this;
}
```

Now any other header or code file that wants to use the Date class can simply `#include
"Date.h"`.

### Doesn't defining a class in a header file violate the one-definition rule?

### Doesn't defining member functions in the header violate the one-definition rule?
Member functions defined inside the class definition are considered implicitly inline.

Member functions defined outside the class definition are treated like normal functions,
and are subject to the one definition per program part of the one-definition rule. So
those should be defined in a code file, not inside the header. One exception is for
template functions, which are also implicitly inline.

### So what should I define in the header file vs the cpp file, and what inside the class definition vs outside?
You might be tempted to put all your member functions definitions into the header file,
inside the class. Will compile, but downsides. Clutters up the class definition. Anytime
you change the code in the header, you'll need to recompile every file that includes that
header.

Recommended:
* For classes used in only one file that aren't generally reusable, define them directly
  in the single .cpp they're used in.
* For classes used in multiple files, or intended for general reuse, define them in a .h
  file that has the same name as the class.
* Trivial member functions (trivial constructors or destructors, access functions, etc.)
  can be defined inside the class
* Non-trivial member functions should be defined in a .cpp file that has the same name as
  the class.

### Default parameters
Should be declared in the class definition (in the header file), where they can be seen by
whomever #includes the header.

### Libraries
Separating the class definition and class implementation is very common for libraries that
you can use to extend your program. Std lib: iostream, string, vector, array, etc. Your
program needs the declarations from the header files in order for the compiler to validate
you're writing programs that are syntactically correct. However, the implementations for
the classes that belong to the C++ standard library are contained in a precompiled file
that is linked at the link stage. You never see the code.

Outside of some open source software (where both .h and .cpp files are provided), most 3rd
party libraries provide only header files, along with a precompiled library file. Several
reasons. It's faster to link a precompiled library than to recompile it every time you
need it. A single copy of a precompiled library can be shared by many applications,
whereas compiled code gets compiled into every executable that uses it (inflating file
sizes). Intellectual property reasons.
