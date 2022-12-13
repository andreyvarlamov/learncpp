# 8 - Type Conversion and Function Overloading

8.6-8.10

# 8.6 - Typedefs and type aliases

### Type aliases
**using** is a keyword that creates an alias for an existing data type.

`using Distance = double;`

### Naming type aliases
Historically, not a lot of consistency in naming convention.

* Type aliases that end in a "\_t" (short for "type"). This convention has been used by
  the standard library for globally scoped type names (like `size_t` and `nullptr_t`).

    Inherited from C, and used to be popular, but not anymore.

* Type aliases that in a "\_type" suffix (`std::string::size_type`)

* No suffix (e.g. `std::string::iterator`)

In modern C++, the convention is to name type aliases with a capital letter with no
suffix.

### Type aliases are not distinct types
Does not actually define a new, distinct type (one that is considered separate from other
types) -- it just introduces a new identifier for an existing type. A type alias is
completely interchangeable with the aliased type.

```c++
int main()
{
    using Miles = long;
    using Speed = long;

    Miles distance { 5 };
    Speed mhz { 3200 };

    distance = mhz; // syntactically valid

    return 0;
}
```

Not **type safe**. But are still useful.

Some languages support the concept of a **strong typedef** (cannot mix). C++ does not
support it, but there are quite a few 3rd party libs that implement strong typedef-like
behavior.

### The scope of a type alias
Type alias are still *identifiers*, so they follow the same scoping rules as variable
identifiers. A type alias defined inside a block has block scope and is usable only within
that block, whereas a type alias defined in the global namespace has file scope and is
usable to the end of the file. Can be defined in a header file and #included into any code
files that need to use the defintion. -- imported into the global namespace and thus have
global scope.

### Typedefs
Older way of creating an alias of a type. Still in C++ for compatibility reasons, but they
have been largely replaced by type aliases in modern C++. But also just an alias.

> **Best practice**<br>
> Prefer type aliases over typedefs.

### When should we use type aliases?

### Using type aliases for platform independent coding
The fixed-width integer types (such as `std::int16_t` and `std::uint32_t`) and the
`size_t` type are actually just type aliases to various fundamental types.

Something like:

```c++
#ifdef INT_2_BYTES
using int8_t = char;
using int16_t = int;
using int32_t = long;
#else
using int8_t = char;
using int16_t = short;
using int32_t = int;
#endif
```

On machines where integers are 4 bytes `INT_2_BYTES` can be left undefined, etc.

This is also why when you print an 8-bit fixed-width integer using std::cout, you're
likely to get a character value.

### Using type aliases to make complex types easier to read

```c++
using VectPairSI = std::vector<std::pair<std::string, int>>;
```

Probably the best use for type aliases.

### Using types aliases for legibility

```c++
int gradeTest(); // what is it returning?
```

```c++
using TestScore = int;
TestScore gradeTest();
```

Usually not worth it, use a comment instead.

### Using type aliases for easier code maintenance
Type aliases allow you to change the underlying type of an object without having to update
lots of hardcoded types.

Seems like a nice benefit, but the behavior of the program may also change with the
changed type.

### Downsides and conclusions
Benefits, but they introduce yet another identifier that needs to be understood. This
needs to be offset by some benefit to readability or comprehension.

In some cases (such as with smart pointers, which we'll cover in a future chapter),
obscuring the type information can also be harmful to understanding how the type should be
expected to work.
