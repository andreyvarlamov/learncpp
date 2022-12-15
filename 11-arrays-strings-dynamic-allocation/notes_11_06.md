# 11 - Array, Strings, and Dynamic Allocation

11.6 - 11.10

# 11.6 - C-style strings

`std::string` is implemented using C-style strings.

An array of characters with a **null terminator**. `\0` - ASCII code 0.

**Null-terminated string**.

```c++
char myString[] { "string" };
```

Although "string" only has 6 letters, C++ automatically adds a null terminator to the end
of the string. So it's an array of length 7.

```c++
#include <iostream>
#include <iterator>

int main()
{
    char myString[] { "string" };
    const int length { static_cast<int>(std::size(myString)) };

    std::cout << myString << " has " << length << " characters.\n";

    for (int i { 0 }; i < length; ++index)
    {
        std::cout << static_cast<int>(myString[index]) << ' ';
    }

    std::cout << '\n';

    return 0;
}
```

```
string has 7 characters.
115 116 114 105 110 103 0
```

C-style string follow *all* the same rules as arrays.

```c++
char myString[] { "string" }; // ok
myString = "rope"; // not ok
```

Can use [] operator to change individual characters in the string

When printing a C-style string, std::cout prints characters until it encounters the null
terminator. If you accidentally overwrite the null terminator in a string, you'll not only
get all the characters in the string, but std::cout will just keep printing everything in
adjacent memory slots until it happens to hit a 0!

It's fine if the array is larger than the string it contains.

### C-style string and std::cin
Don't know in advance how long our string is going to be.

```c++
char name[255] { };
std::cin >> name;
```

Commonly seen, but poor programming practice. Nothing stopping the user from entering more
than 254 characters.

The recommended way of reading C-style string using std::cin is as follows:

```c++
char name[255] { };
std::cin.getline(name, std::size(name));
```

This will read up to 254 characters into name (leaving room for the null terminator!). Any
excess characters will be discarded.

### Manipulating C-style strings
C++ provides many functions to manipulate C-style strings as part of the <cstring> header.

`strcpy`

```c++
char source[] { "Copy this!" };
char dest[50];
std::strcpy(dest, source);
```

But can cause array overflows. If destination is too small.

`strncpy`

```c++
char source[] { "Copy this!" };
char dest[5];
std::strncpy(dest, 5, source); // A runtime error will occur in debug mode
```

But doesn't ensure strings are null terminated.

In C++11, `strcpy_s()` is preferred

```c++
#define __STDC_WANT_LIB_EXT1__ 1
char source[] { "Copy this!" };
char dest[5];
strcpy_s(5, source); // A runtime error will occur in debug mode
```

But not all compiler support it, and have to define `STDC_WANT_LIB_EXT1`

`strlcpy()` is a popular alternative. Even though it's non-standard. Also not included in
a lot of compilers.

No universally recommended solutions.

Another useful function is `strlen()`. Returns the length of the C-style string before
the null terminator.

Other useful functions:
`strcat()` - appends one string to another (dangerous)
`strncat()` - appends one string to another (with buffer length clock)
`strcmp()` - compare two strings (return 0 if equal)
`strncmp()` - compare two strings up to a specific number of characters (returns 0 if
equal)

### Don't use C-style strings
