# 12.5 - Command line arguments

**Command line arguments** are optional string arguments that are passed by the operating
system to the program when it is launced.

### Passing command line arguments

```
./word-count file1.txt file2.txt
```

### Using command line arguments

```c++
int main(int argc, char* argv[])
```

Or:

```c++
int main(int argc, char** argv)
```

Argument count as an int and argument values as an array of C-style strings (pointers to
the first char until null-byte).

```c++
#include <iostream>

int main(int argc, char* argv[])
{
    std::cout << "There are " << argc << " arguments:\n";

    for (int count { 0 }; count < argc; ++count)
    {
        std::cout << count << ' ' << argv[count] << '\n';
    }

    return 0;
}
```

```
There are 3 arguments:
0 C:\MyArgs
1 Myfile.txt
2 100
```

Argument 0 is the path and name of the current program being run.

### Dealing with numeric arguments

The C++ way to do it:

```c++
#include <iostream>
#include <sstream> // for std::stringstream
#include <string>

int main(int argc char* argv[])
{
    if (argc <= 1)
    {
        // On some OS, argv[0] can end up as an empty string instead of the program's name.
        // Conditionalize the response on whether argv[0] is empty or not.
        if (argv[0])
        {
            std::cout << "Usage: " << argv[0] << " <number>" << '\n';
        }
        else
        {
            std::cout << "Usage: <program name> <number>" << '\n';
        }

        return 1;
    }

    std::stringstream convert { argv[1] }; // set up a stringstream variable named convert
                                           // initialized with the input from argv[1]

    int myint { };

    if (!(convert >> myint)) // do the conversion
    {
        myint = 0; // if the conversion fails, set myint to a default value
    }

    std::cout << "Got integer: " << myint << '\n';

    return 0;
}
```

### The OS parses command line arguments first
It is the operating system's responsibility to translate and route that request as
appropriate.

Typically strings passed in double quotes are considered to be part of the same string:

```
MyArgs "Hello world!"
```

Most OS allow to escape the quote with back slash to get the literal value.

```
MyArgs \"Hello world!\"
```
