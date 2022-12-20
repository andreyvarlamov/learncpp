# 16.3 - Aggregation

* The part (member) is part of the object (class).
* The part (member) can (if desired) belong to more than one object (class) at a time.
* The part (member) does not have its existence managed by the object (class).
* The part (member) does not know about the existence of the object (class).

In aggregation, we also add parts as member variable, but they will be typically either
references or pointers that are used to point at objects that have been created outside
the scope of the class. When the class is destroyed, the pointer or reference member
variable will be destroyed (but not deleted). So the parts themselves will still exist.

> **Best practice**
> Implement the simplest relationship type that meets the needs of your program, not what
> seems right in real life.

Compositions should be favored over aggregations. Potentially more dangerous.

### `std::reference_wrapper`

```c++
std::vector<const Teacher&> m_teachers { }; // Illegal
```

```c++
#include <functional>
#include <iostream>
#include <vector>
#include <string>

int main()
{
    std::string tom { "Tom" };
    std::string berta { "Berta" };

    std::vector<std::reference_wrapper<std::string>> names { tom, berta };

    std::string jim { "Jim" };

    names.push_back(jim);

    for (auto name : names)
    {
        name.get() += " Beam";
    }

    std::cout << jim << '\n'; // Jim Beam

    return 0;
}
```
