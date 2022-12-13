# 8 - Type Conversion and Function Overloading

8.11 - 8.15

# 8.11 - Function overload resolution and ambiguous matches

The process of matching function calls to a specific overloaded function is called
**overload resolution**.

### Resolving overloaded function calls

Compiler steps through a sequence of rules to determine which (if any) of the overloaded
functions is the best match. At each step, the compiler applies a bunch of different type
conversions to the argument(s) in the function call. For each conversion applied, the
compiler checks if any of the overloaded functions are now a match. After all different
type conversions have been applied and checked for matches, the step is done. The result:

* No matching functions were found. The compiler moves to the next step in the sequence.
* A single matching function was found. This function is considered the best match. The
  matching process is now complete, and subsequent steps are not executed.
* More than one matching function was found. The compiler will issue and ambiguous match
  compile error.

If the compiler reaches the end of the entire sequence without finding a match, it will
generate a compile error that no matching overloaded function could be found for the
function call.

### The argument matching sequence

1. Compiler tries to find an exact match. 2 phases.

   Is there an overloaded function where the type of the arguments in the function call
   exactly matches the type of the parameters in the overloaded functions? Apply a number
   of trivial conversions to the arguments in the function call. Modify the type without
   modifying the value. For example a non-const type can be trivially converted to a const
   type.

   Converting a non-reference type to a reference type (or vice-versa) is also a trivial
   conversion.

   Matches made via the trivial conversions are considered exact matches.

2. If no match is found, the compiler tries to find a match by applying numeric promotion
   to the argument(s).

```c++
void print(int)
{
}

void print(double)
{
}

int main()
{
    print('a'); // promoted to match print(int)
    print(true); // promoted to match print(int)
    print(4.5f); // promoted to match print(double)

    return 0;
}
```

3. If no match is found via numeric promotion, the compiler tries to find a match by
   applying numeric conversions.

```c+++
#include <string>

void print(double)
{
}

void print(std::string)
{
}

int main()
{
    print('a'); // converted to match print(double) !

    return 0;
}
```

4. If no match is found via numeric conversion, the compiler tries to find a match through
   any user-defined conversions. (Haven't covered yet.)

```c++
class X
{
public:
    operator int() { return 0; } // user-defined conversion from X to int
}
```

   After applying a user-defined vonersion, the compiler may apply additional implicit
   promotions or conversions to find a match.

5. If no match is found via user-defined conversion, the compiler will look for a matching
   function that uses ellipsis (...). 12.6.

6. If no matches by this point, the compiler issues an error about not being able to find
   a matching function.

### Ambiguous matches
Two or more functions that can be made to match in the same step. When this occurs, the
compiler will stop matching and issue a compiler error stating that it has found an
ambiguous function call.

```c++
void print(int x)
{
}

void print(double d)
{
}

int main()
{
    print(5L); // long

    return 0;
}
```

...(other steps) -> Numeric conversions. 2 potential matches. If the long argument is
numerically converted into an int then match print(int), if converted into a double, then
print(double). This is considered ambiguous.

Another example:

```c++
void print(unsigned int x)
{
}

void print(float x)
{
}

int main()
{
    print(0); // int can be numerically converted to unsigned int or to float
    print(3.14159); // double can be numerically converted to unsigned int or to float

    return 0;
}
```

### Resolving ambiguous matches
Often the best way is to simply define a new overloaded function that takes those exact
params. or explicitly cast the ambiguous argument(s).

### Matching for functions with multiple arguments
The compiler applies matching rules to each argument in turn. At least one argument
matching better than all the other functions. E.g. numeric promotion is better than
numeric conversion, etc.



# 8.12 - Default arguments

```c++
#include <iostream>

void print(int x, int y=4)
{
    std::cout << "x: " << x << '\n';
    std::cout << "y: " << y << '\n';
}

int main()
{
    print(1, 2);
    print(3);

    return 0;
}
```

### When to use default arguments
Reasonable default value, but which can be overridden by the caller.

**Optional parameter**. (However the term is also used to refer to several other types of
parameters (including parameters passed by address, and parameters using std::optional),
so recommended to avoid this term.)

### Multiple default parameters

> **Rule**<br>
> Default arguments can only be provided for the rightmost parameters.

### Default arguments can not be redeclared
Once declared, a default argument can not be redeclared (in the same file). That means for
a function with a forward declaration and a function definition, the default argument can
be declared in either the forward declaration or the function definition, but not both.

Best practice is to declare the default argument in the forward declaration and not in the
function defintion, as the forwarded declaration is more likely to be seen by other files
(particularly if it in a header file).

### Default arguments and function overloading
May be overloaded.

But consider this case:

```c++
void print(int x);
void print(int x, int y = 10);
void print(int x, double y = 20.5);
...
print(1, 2); // wil resolve to print(int, int)
print(1, 2.5); // will resolve to print(int, double)
print(1); // ambiguous function call
```

