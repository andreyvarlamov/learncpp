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



# 11.7 - std::string\_view (part 2)

C-style strings are fast, but not as easy to use and as safe as `std::string`.

But `std:;string` has its own downsides, particularly when it comes to const strings.

`std::string` makes a copy of the string used to initialize it? A `std:string` provides
some useful guarantees about the string data it manages:

* The string data will be valid for as long as the string object is alive, and cleaned up
  when the string object dies.
* The string's value can only be modified by the string object.
* The string's value can be modified without affecting other objects (for non-const
  strings).

Make sure that the value and lifetime of the string is independent from other objects.

In some cases, we don't need these benefits (particularly for const `std::string` objects,
which can't modify their value). E.g. when we know a `std::string` won't outlive its
initialization string, and that the initialization string won't be modified.

### Introducing std::string\_view
C++17 introduces another way of using string. <string\_view> header.

Provides a *view* of a string that is defined elsewhere.

```c++
#include <iostream>
#include <string_view>

int main()
{
    std::string_view text { "hello" }; // view of the text "hello", which is stored in the binary
    std::string_view str { text }; // view of the same "hello"
    std::string_view more { str }; // view of the same "hello"

    std::cout << text << ' ' << str << ' ' << more << '\n';

    return 0;
}
```

The string "hello" is stored in *the binary* and is *not allocated at run-time*. Text is
only a view onto the string "hello".

Because `std::string_view` doesn't create a copy of the string, if we change the viewed
string, the changes are reflected in the `std::string_view`.

```c++
#include <iostream>
#include <string_view>

int main()
{
    char arr[] { "Gold" };
    std::string_view str { arr };

    std::cout << str << '\n'; // Gold

    arr[3] = 'f';

    std::cout << str << '\n'; // Golf

    return 0;
}
```

> **Best practice**<br>
> Prefer `std::string_view` over `std::string` and C-style strings when you only need
> read-only access to a string (unless you can't guarantee the string being viewed will
> stay alive for the lifetime of the `std::string_view`, in which case you should prefer
> `std::string`.

### View modification functions

`std::string_view` contains functions that let us manipulate the *view* of the string.
This allows us to change the view wihtout modifying the viewed string.

`str.remove_prefix(1)` -- remove characters from the left side of the view (ignore the
first character).

`str.remove_suffix(2)` -- remove characters from the firht side of the view (ignore the
last 2 characters).

Cannot be opened back up. The only way to re-widen the view area is to reset the view by
reassigning the source string to it again.

### std::string\_view works with non-null-terminated strings
Unlike C-style strings and `std::string`, `std::string_view` doesn't use null terminators
to mark the end of the string. Rather, it knows where the string ends because it keeps
track of its length.

### Converting a `std::string_view` to a C-style string

```c++
#include <cstring>
#include <iostream>
#include <string>
#include <string_view>

int main()
{
    std::string_view sv { "balloon" };

    sv.remove_suffix(3);

    std::string str { sv };

    auto szNullTerminated { str.c_str() };

    std::cout << str << " has " << std:strlen(szNullTerminated) << " letter(s)\n";

    return 0;
}
```

However, creating a `std::string` every time we want to pass a `std::string_view` as a
C-style string is expensive, and this should be avoided if possible.

### Passing string by `const std::string&` or `std::string_view`?
If we want to write a function that takes a string parameter, making the parameter a
`std::string_view` is the most flexible choice, becuase it can work efficiently with
C-style string arguments (including string literals), `std::string` arguments (which will
implicitly convert to `std::string_view`), and `std::string_view` arguments.

One case where making a parameter a `const std:;string&` is generally better: if your
function needs to call some other function that takes a C-style string or `std::string`
parameter, then `const std::string&` may be a better choice, as `std::string_view` is not
guaranteed to be null-terminated (something that C-style string functions expect) and does
not efficiently convert back to a `std::string`.

> **Best practice**<br>
> Prefer passing strings using `std::string_view` (by value) instead of `const
> std::string&`, unless your function calls other functions that require C-style strings
> or std::string parameters.

### Ownership issues
A `std::string_view`'s lifetime is independent of that of the string it is viewing
(meaning the string being viewed can be destroyed before the `std::string_view` object).
If this happens, then accessing the `std::string_view` will cause undefined behavior.

E.g. think of the case where a function defines and then returns the view to it. Dangling
`std::string_view`.

Also, modifying a `std::string` can cause its internal string to die and be replaced with
a new one in a different place. Then `std::string_view` will still look at where the old
string was, but it's not there anymore.

> **Warning**<br>
> Make sure that the underlying string viewed with a `std::string_view` does not go out of
> scope and isn't modified while using the `std::string_view`.

### The `data()` function and non-null-terminated strings
The string being viewed by a string view can be accessed by using the `data()` function,
which returns a C-style string. This provides fast access to the string being viewed (as a
C-string). But it should only be used in cases where we know the string being viewed is
null-terminated.

`std.data()`

Using `remove_prefix()` and `remove_suffix()` can change the view so that it's no longer
viewing a null-terminated string.

Thus when we call the `data()` function, it returns a pointer to the first character in
the substring being viewed, which is C-style string "alloon" (e.g.). Even though we
removed prefix (1) and removed suffix (3) from "balloon". So we expected "all".

> **Warning**<br>
> Only use `std::string_view::data()` if the `std::string_view`'s view hasn't been
> modified and the string being viewed is null-terminated. Using
> `std::string_view::data()` on a non-null-terminated string can cause undefined behavior.
>
> Otherwise convert your `std::string_view` to a `std::string` and call
> `std::string::data()` which is guaranteed to be null-terminated.

### Incomplete implementation
Relatively recent feature.

```c++
std::string s { "hello" };
std::string_view v { "world" };

// Doesn't work
std::cout << (s + v) << '\n';
std::cout << (v + s) << '\n';

// Potentially unsafe, and not what we want, because we're treating
// the std::string_view as a C-style string.
std::cout << (s + v.data()) << '\n';
std::cout << (v.data() + s) << '\n';

// Ok, but ugly and wasteful because we have to construct a new std::string
std::cout << (s + std::string { v }) << '\n';
std::cout << (std::string { v } + s) << '\n';
std::cout << (s + static_cast<std::string>(v)) << '\n';
std::cout << (static_cast<std::string>(v) + s) << '\n';
```



# 11.8 - Pointers and arrays

### Array decay
In all but two cases when a fixed array is used in an expression, the fixed array will
**decay** (be implicitly converted) into a pointer that points to the first element of the
array.

```c++
#include <iostream>

int main()
{
    int array[5] { 9, 7, 5, 3, 1 };

    std::cout << "Element 0 has address: " << &array[0] << '\n';
    std::cout << "The array decays to a pointer holding address: " << array << '\n';

    return 0;
}
```

Should be the same address.

However, it's a common fallacy in C++ to believe an array and a pointer to the array are
identical. They're not. In the above case, array is of type `int[5]`, and its "value" is
the array elements themselves. A pointer to the array would be of type `int*`, and its
value would be the addresss of the first element of the array.

All elements can still be accessed through the pointer, but information derived from the
array's type (such as how long the array is) can not be accessed from the pointer.

However, this effectively allows us to treat fixed arrays and pointers identically in most
cases.

```c++
int array[5] { 9, 7, 5, 3, 1 };
std::cout << *array; // 9

char name[] { "Jason" };
std::cout << *name <<'\n'; // J
```

Note that we're not actually dereferencing the array itself. The array (of type `int[5]`)
gets implicitly converted into a pointer (of type `int*`), and we dereference the pointer
to get the value at the memory address the pointer is holding (the value of the first
element of the array).

We can also assign a pointer to point at the array.

### Differences between pointers and fixed arrays

```c++
#include <iostream>

int main()
{
    int array[5] { 9, 7, 5, 3, 1 };
    std::cout << sizeof(array) << '\n'; // sizeof(int) * array length

    int* ptr { array };
    std::cout << sizeof(ptr) << '\n'; // print the size of a pointer
}
```

```c++
#include <iostream>

int main()
{
    int array[5] { 9, 7, 5, 3, 1 };
    std::cout << array << '\n'; // type int[5], prints 009DF9D4
    std::cout << &array << '\n'; // type int(*)[5], prints 009DF9D4

    std::cout << '\n';

    int* ptr { array };
    std::cout << ptr << '\n'; // type int*, prints 009DF9D4
    std::cout << &ptr << '\n'; // type int**, prints 009DF9C8

    return 0;
}
```

### Revisiting passing fixed arrays to functions
When passing an array as an argument to a function, a fixed array decays into a pointer,
and the pointer is passed into the function.

```c++
#include <iostream>

void printSize(int* array)
{
    std::cout << sizeof(array) << '\n'; // 4
}

int main()
{
    int array[] { 1, 1, 2, 3, 5, 8, 13, 21 };
    std::cout << sizeof(array) << '\n'; // 32

    printSize(array);

    return 0;
}
```

Same thing happens even if the parameter is declared as a fixed array:

```c++
void printSize(int array[])
...
```

Some programmers prefer using the [] syntax because it makes it clear that the function is
expecting an array, not just a pointer value. However, in most cases, because the pointer
doesn't know how large the array is, you'll need to pass in the array size as a separate
parameter anyways (strings being an exception because they're null terminated).

Recommended to use the pointer syntax, because it makes it clear that the parameter is
being treated as a pointer, not a fixed array.

### An intro to pass by address
The fact that array decays into pointers when passed to a function explains the underlying
reason why changing an array in a function changes the actual array argument passed in.

### Arrays in structs and classes don't decay
When the whole struct or class is passed to a function. This yields a useful way to
prevent decay if desired, and will be valuable later when we write classes that utilize
arrays.



# 11.9 - Pointer arithmetic and array indexing

### Pointer arithmetic
The C++ language allows you to perform integer addition or subtraction operations on
pointers. If `ptr` points to an integer, `ptr + 1` is the address of the next integer in
memory after `ptr`. `ptr - 1` - previous.

Not the *memory address* after `ptr`, but the memory address of the *next object of the
type* that `ptr` points to. If `ptr` points to an integer (assuming 4 bytes), `ptr + 3`
means 3 integers (12 bytes) after `ptr`. `char` (1 byte) - 3 chars (3 bytes).

When calculating the result of a pointer arithmetic expression, the compiler always
multiplies the integer operand by the size of the object being pointed to - **scaling**.

### Arrays are laid out sequentially in memory

### Pointer arithmetic, arrays, and the magic behind indexing

```c++
#include <iostream>

int main()
{
    int array[] { 9, 7, 5, 3, 1 };

    std::cout << &array[1] << '\n'; // 0017FB80 - memory address of array element 1
    std::cout << array + 1 << '\n'; // 0017FB80 - memory address of array pointer + 1

    std::cout << array[1] << '\n'; // 7
    std::cout << *(array + 1) << '\n'; // 7

    return 0;
}
```

It turns out that when the compiler sees the subscript operator `[]`, it actually
translates that into a pointer addition and indirection!

`array[n]` is the same as `*(array + n)`

### Using a pointer to iterate through an array
For loop, pointer addition and indirection

```c++
char name[] { "Mollie" };
int arrayLength { ... };
...
for (char* ptr { name }; ptr != (name + arrayLength); ++ptr)
...
```

Because counting elements is common, the algorithms library offers `std::count_if` which
counts elements that fulfill a condition.

```c++
#include <algorithm> // std::count_if
#include <iostream>
#include <iterator> // for std::begin and std::end

bool isVowel(char ch)
{
    ...
}

int main()
{
    char name[] { "Mollie" };

    auto numVowels { std::coung_if(std::begin(name), std::end(name), isVowel) };

    std::cout << name <, " has " << numVowels << " vowels.\n";

    return 0;
}
```

`std::begin` returns an iterator (pointer) to the first element, while `std::end` returns
an iterator to the element that would be one after the last. The iterator returned by
`std::end` is only used as a marker, accessing it causes undefined behavior, because it
doesn't point to a real element.

`std::begin` and `std::end` only work on arrays with a known size. If the array decayed to
a pointer, we can calculate begin and end manually.

```c++
// nameLength is the number of elements in the array.
std::counf_if(name, name + nameLength, isVowel);

// Don't do this. Accessing invalid indexes causes undefined behavior.
std::counf_if(name, &name[nameLength], isVowel);
```

----

The order of operands of subscript operator can be swapped (same as addition and
indirection).

```c++
arr[2]
// same as
*(arr + 2)
// same as
*(2 + arr)
// same as
2[arr]
```

----

See `find_value.cpp` for the Quiz Q2.

`std::find` is a standard function that does the same thing as `findValue()`. It should be
preferred over writing your own.

```c++
#include <algorithm>
...
auto found { std::found(std::begin(arr), std::end(arr), 20) };
...
```



# 11.10 - C-style string symbolic constants
C-style string symbolic constants using pointers:

```c++
const char* myName { "Andrey" };
```

While `char myName[] { ... }` and `const char* myName { ... }` operate and produce the
same results, C++ deals with the memory allocation for these slightly differently.

In the fixed array case, the program allocates memory for a fixed array of length 5, and
initializes that memory with the string "Andrey\0". Because memory has been specifically
allocated for the array, you're free to alter the contents of the array. The array itself
is treated as a normal local variable, so when the array goes out of scope, the memory
used by the array is freed for other uses.

In the symbolic constant case, how the compiler handles this is implementation defined.
What *usually* happens is that the compiler  places the string"Andrey\0" into read-only
memory somewhere, and then sets the pointer to it. Because the memory may be read-only,
the best practice is to make sure the string is const.

For optimization purposes, multiple string literals may be consolidate into a single
value. For example:

```c++
const char* name1 { "Andrey" };
const char* name2 { "Andrey" };
```

These are two different string literals with the same value. The compiler may opt to
combine these into a single shared strin gliteral, with both name1 and name2 pointed at
the same address. Thus if name1 was not const, making a change to name1 could also impact
name2 (which might not be expected).

As a result of string literals being stored in a fixed location in memory, strin gliterals
have static duration rather than automatic duration (that is, they die at the end of the
program, not at the end of the block in which they are defined). This means that when we
are using string literals, we don't have to worry about scoping issues. Thus the following
is okay:

```c++
const char* getName()
{
    return "Andrey";
}
```

getName will return a pointer to C-style string "Andrey". If this function were returning
any oterh local variable by address, the variable would be destroyed at the end of
getName(), and we'd return a dangling pointer back to the caller.

C-style strings are used in a lot of old or low-level code, because they have a very small
memory footprint. Modern code should favor the use of `std::string` and
`str::string_view`.

### std::cout and char pointers

```c++
#include <iostream>

int main()
{
    int nArray[5] { 9, 7, 5, 3, 1 };
    char cArray[] { "Hello!" };
    const char* name { "Andrey" };

    std::cout << nArray << '\n'; // nArray will decay to type int* -- 003AF738
    std::cout << cArray << '\n'; // cArray will decay to type char* -- Hello!
    std::cout << name << '\n'; // name is already type char* -- Andrey
}
```

`std::cout` makes some assumptions about your intent. It will assume you're indending to
print a string.

This is great 99% of the time, but it can lead to unexpected results.

```c++
#include <iostream>

int main()
{
    char c { 'Q' };
    std::cout << &c;

    return 0;
}
```

```
Q??????????????????4;?????A
```

`&c` has type `char*`. So the compiler assumed it was astring. It printed 'Q' and kept
going until null terminator (it ran into some memory holding a 0 value).
