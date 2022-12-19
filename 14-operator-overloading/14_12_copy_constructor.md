# 14.12 - The copy constructor

### Initialization recap

```c++
int x(5); // Direct initialize an integer
Fraction fiveThirds(5, 3); // Direct initialize a Fraction, calls Fraction(int, int) constructor
```

```c++
int x { 5 }; // Uniform initialize an integer
Fraction fiveThirds { 5, 3 }; // Uniform initialize a Fraction, calls Fraction(int, int) constructor
```

```c++
int x = 6; // Copy initialize an integer
Fraction six = Fraction(6); // Copy initialize a Fraction, will call Fraction(6, 1)
Fraction seven = Fraction(7); // Copy initialize a Fraction. The compiler will try to find
// a way to convert 7 to a Fraction, which will invoke the Fraction(7, 1) constructor.
```

### The copy constructor
If you do not provide a copy constructor, C++ will create a public copy constructor. By
default, it's simply **memberwise initialization**. Each member of the copy is initialized
directly from the member of the class of the class being copied.

```c++
// Copy constructor
Fraction(const Fraction& fraction)
    : m_numerator { fraction.m_numerator }, m_denominator { fraction.m_denominator }
{ }
```

We can access the members of the parameter fraction direcly, even though they're private,
because we're inside the Fractionclass.

Then initialize via copy:

```c++
Fraction fiveThirds { 5, 3 };
Fraction fCopy { giveThirds };
```

### The copy constructor's parameter must be a reference
If not, would try to *copy* object into the function and cause an infinite recursion.

### Preventing copies
We can prevent copies of our class from being made by make the copy constructor private

```c++
Fraction fCopy { giveThirds }; // Then this will cause a compile error
```

### The copy constructor may be elided

```c++
Fraction fiveThirds { Fraction { 5, 3 } };
```

The compiler may change this to:

```c++
Fraction fiveThirds { 5, 3 };
```

**Elision**.

Prior to C++17, compiler are permitted (but not required) to perform copy elision in
certain cases. In such cases, a copy constructor must be accessible (e.g. non-private),
even if the actual copy is alided.

As of C++17, some cases of copy elisison (including the example) above have been made
mandatory. In those mandatory elision cases, the copy constructor does not need to be
accessible (or even presen) since it is guaranteed not to be needed.
