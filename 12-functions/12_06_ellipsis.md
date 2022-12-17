# 12.6 - Ellipsis (and why to avoid them)

There are certain cases where it can be useful to be able to pass a variable number of
parameters to a function.

Ellipsis aka "...".

Recommended to avoid.

```
return_type function_name(argument_list, ...)
```

The *argument_list* is one or more normal function parameters. Must have at least one
non-ellipsis parameter. Arguments passed must match the argument\_list parameters first.
Ellipsis must always be the last parameter in the function.

### An elipsis example

```c++
#include <iostream>
#include <cstdarg> // need to use ellipsis

double findAverage(int count, ...)
{
    int sum { 0 };

    // We access the ellipsis througha va_list
    std::va_list list;

    // We intialize the va_list using va_start. The first argument is the list to
    // initialize. The second argument is the last non-ellipsis parameter.
    va_start(list, count);

    for (int arg { 0 }; arg < count; ++arg)
    {
        // We use va_arg to get values out of our ellipsis
        // The first argument is the va_list we're using
        // The second argument is the type of the value
        // Note that va_arg() also moves the va_list to the next parameter in the ellipsis
        // Note that va_start() can be called again any time we want to reset the va_list
        // to point to the next parameter in the ellipsis.
        sum += va_arg(list, int);
    }

    // Clean up the va_list when we're done.
    va_end(list);

    return static_cast<double>(sum) / count;
}

int main()
{
    std::cout << findAverage(5, 1, 2, 3, 4, 5)  << '\n'; // 3
    std::cout << findAverage(6, 1, 2, 3, 4, 5, 6)  << '\n'; // 3.5
}
```

### Why ellipsis are dangerous: type checking is suspended
It is completely up to the caller to snsure the function is called with ellipsis arguments
that the function can handle.

E.g.:

```c++
std::cout << findAverage(6, 1.0, 2, 3, 4, 5, 6) << '\n';
```

The only way tog et a meaningful value back is to manually tell `va_arg()` what the
expected type of the next parameter is.

So it read 4 bytes of the double 1.0. And the next call will read the second 4 bytes of
the double.

Compiler will not complain even if we do something completely ridicuolous.

### Why ellipsis are dangerous: ellipsis don't know how many parameters were passed
Have to devise our own solution to keeping track of the number of parameters.
Traditionally, three ways.

### Method 1: Pass a length parameter
Problem: provide count = 6, but provide only 5 values. The 6 value = garbage.

### Method 2: Use a sentinel value
A special value that is used to terminate a loop when it is encountered.

E.g.

```c++
double findAverage(int first, ...)
{
    ...

    while (true)
    {
        int arg { va_arg(list, int) };

        if (arg == -1)
        {
            break;
        }

        ...
    }

    ...
}

...

findAverage(1, 2, 3, 4, 5, -1);
```

Need special handling for the first param.

Reliant on the user to pass the sentinel. Can loop continuously until it runs into garbage
that matches the sentinel (or crashes).

What if we wanted to include negative values?

### Method 3: Use a decoder string

```c++
double findAverage(std::string_view decoder, ...)
{
    ...

    for (auto codetype: decoder)
    {
        switch (codetype)
        {
        case 'i':
            sum += va_arg(list, int);
            break;
        case 'd':
            sum += va_arg(list, double);
            break;
        }
    }

    ...
}
```

Cryptic.

Needs to match the number of types of the optional paramters precisely.

This is what `printf` in C does!

### Recommendations for safer use of ellipsis
If possible, don't use it.

If you do use ellipsis, do not mix expected argument types within your ellipsis if
possible.

Using a count parameter or decoder string as part of the argument list is generally safer
than using a sentinel. At least these ensure the loop will terminate, even if it will
produce garbage values.

C++11:

`parameter packs` and `variadic templates`. Offer similar functionality to ellipsis but
with strong type checking. Significant usability challenges impeded adoption of this
feature.

C++17:

Fold expressions: significantly improves the usability of parameter packs, to the point
where they are now a viable option.
