# M.5 - `std::move_if_noexcept`

To uphold the `string exception guarantee`. If the move operation is interrupted by an
exception after the transfer of ownership occurs, then our source object will be left in a
modified state. Not a problem for temp objects. But is for non-temp.

```c++
#include <iostream>
#include <utility>
#include <stdexcept>

class MoveClass
{
private:
    int* m_resource { };

public:
    MoveClass() = default;

    MoveClass(int resource)
        : m_resource { new int { resource } }
    {
    }

    // Copy constructor
    MoveClass(const MoveClass& that)
    {
        // deep copy
        if (that.m_resource != nullptr)
        {
            m_resource = new int { *that.m_resource };
        }
    }

    // Move constructor
    MoveClass(MoveClass&& that) noexcept
        : m_resource { that.m_resource }
    {
        that.m_resource = nullptr;
    }

    ~MoveClass()
    {
        std::cout << "destroying " << *this << '\n';

        delete m_resource;
    }

    friend std::ostream& operator<<(std::ostream& out, const MoveClass& moveClass)
    {
        out << "MoveClass(";

        if (moveClass.m_resource == nullptr)
        {
            out << "empty";
        }
        else
        {
            out << *moveClass.m_resource;
        }

        out << ')';

        return out;
    }
};

class CopyClass
{
public:
    bool m_throw { };

    CopyClass() = deafult;

    // Copy constructor throws an exception when copying from a CopyClass object where its
    // m_throw is true
    CopyClass(const CopyClass& that)
        : m_throw { that.m_throw }
    {
        if (m_throw)
        {
            throw std::runtime_error { "abort!" };
        }
    }
};

int main()
{
    // We can make a std::pair without any problems:
    std::pair my_pair { MoveClass { 13 }, CopyClsas { } };

    std::cout << "my_par.first: " << my_pair.first << '\n';

    // But the problem arises when we try to move that pair into another pair
    try
    {
        my_pair.second.m_throw = true; // To trigger copy constructor exception

        // The following line will throw an exception
        std::pair moved_pair { std::move(my_pair) };
        // std::pair moved_pair { std::move_if_noexcept(my_pair) };

        std::cout << "moved pair exists\n"; // Never prints
    }
    catch (const std::exception& ex)
    {
        std::cerr << "Error found: " << ex.what() << '\n';
    }

    std::cout << "my_pair.first: " << my_pair.first << '\n';

    return 0;
}
```

```
destroying MoveClass(empty)
my_pair.first: MoveClass(13)
destroying MoveClass(13)
Error found: abort!
my_pair.first: MoveClass(empty)
destroying MoveClass(empty)
```

`std::move_if_noexcept` will return a movable r-value if the object has a noexcept move
constructor, otherwise it will return a copyable l-value. We can use the `noexcept`
specifier in conjunction with `std::move_if_no_except` to use move semantics only when a
strong exception guarantee exists (and use copy semantics otherwise).

```c++
// std::pair moved_pair { std::move(my_pair) };
std::pair moved_pair { std::move_if_noexcept(my_pair) };
```

```
destroying MoveClass(empty)
my_pair.first: MoveClass(13)
destroying MoveClass(13)
Error found: abort!
my_pair.first: MoveClass(13)
destroying MoveClass(13)
```

> **Warning**<br>
> If a type has both potentially throwing move semantics and deleted copy semantics (the
> copy constructor and copy assignment operator are unavailable), then
> `std::move_if_noexcept` will waive the strong guarantee and invoke move semantics. This
> conditional waiving of the strong guarantee is ubiquotous in the std lib container
> classes, since they use `std::move_if_noexcept` often.
