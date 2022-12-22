# 23.6 - Basic file I/O

### File output

```c++
#include <fstream>
#include <iostream>

int main()
{
    std::ofstream outf { "Sample.txt" };

    if (!outf)
    {
        std::cerr << "Can't open\n";
        return 1;
    }

    outf << "This is line 1\n";
    outf << "This is line 2\n";

    return 0;

    // When outf goes out of sceope, the ofstream destructor will close the file
}
```

### File input

```c++
#include <fstream>
#include <iostream>
#include <string>

int main()
{
    std::ifstream inf { "Sample.txt" };

    if (!outf)
    {
        std::cerr << "Can't open\n";
        return 1;
    }

    // While there's still stuff left to read
    while (inf)
    {
        // read stuff from the file into a string and print it.
        std::string strInput;
        std::getline(inf, strInput);
        std::cout << strInput << '\n';
    }

    return 0;

    // When outf goes out of sceope, the ofstream destructor will close the file
}
```

### Buffered output
Anything that is output to a file stream may not be written to disk immediately.

### File modes
app, ate, binary, in, out, trunc

### Explicitly opening files using open()
open() and close()
