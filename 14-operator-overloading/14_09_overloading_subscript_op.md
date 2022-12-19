# 14.9 - Overloading the subscript operator

```c++
#include <cassert>
#include <iostream>

class IntList
{
private:
    int m_list[10] { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

public:
    int& operator[] (int index);
    int operator[] (int index) const; // could also return const int& if returning a
                                      // non-fundamental type
};

int& IntList::operator[] (int index) // for non-const objects: can be used for assignment
{
    // Advantege: can add proper error checking making it safer than accessing arrays
    // directly
    // This is probably the most common method of doing error checking of this sort
    assert(index >= 0 && index < std::size(m_list));

    return m_list[index];
}

int IntList::operator[] (int index) const // for const objects: can only be used for access
{
    assert(index >= 0 && index < std::size(m_list));

    return m_list[index];
}

int main()
{
    IntList list { };
    list[2] = 3; // okay: calls non-const version of operator[]
    std::cout << list[2] << '\n';

    const IntList clist { };
    clist[2] = 3; // compile error: calls const version of operator[], which returns by
                  // value. Cannot assign to this because it is an rvalue.
    std::cout << clist[2] << '\n';

    return 0;
}
```

### Pointers to objects and overloaded `operator[]` don't mix

```c++
...
IntList* list { new IntList { } };
list[2] = 3; // error, this will assume we're accessing index 2 of an array of IntLists
(*list)[2] = 3 // get our IntList object, then call overloaded operator[]
delete list;
...
```

> **Rule**<br>
> Make sure you're not trying to call an overloaded operator[] on a pointer to an object.

### The function parameter does not need to be an integer
(But you should make this overload sensible.)

Overloading `operator[]` to take a `std::string` can be useful when writing certain kinds
of classes, such as those that use words as indices.

----

`std::map`
