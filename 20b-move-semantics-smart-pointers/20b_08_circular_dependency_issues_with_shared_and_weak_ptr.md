# M.8 - Circular dependency issues with `std::shared_ptr`, and `std::weak_ptr`

Problem with shared pointers re circular dependencies:

```c++
#include <iostream>
#include <memory> // for std::shared_ptr
#include <string>

class Person
{
    std::string m_name;
    std::shared_ptr<Person> m_partner; // initially created empty

public:
    Person(const std::string &name) : m_name (name)
    {
        std::cout << m_name << " created\n";
    }

    ~Person()
    {
        std::cout << m_name << " destroyed\n";
    }

    friend bool partnerUp(std::shared_ptr<Person> &p1, std::shared_ptr<Person> &p2)
    {
        if (!p1 || !p2)
        {
            return false;
        }

        p1->m_partner = p2;
        p2->m_partner = p1;

        std::cout << p1->m_name << " is now partnered with " << p2->m_name << '\n';

        return true;
    }
};

int main()
{
    auto lucy { std::make_shared<Person>("Lucy") };
    auto ricky { std::make_shared<Person>("Ricky") };

    partnerUp(lucy, ricky);

    return 0;
}
```

```
Lucy created
Ricky created
Lucy is now partnered with Ricky
```

No deallocation took place. At the end of main(), the ricky shared pointer goes out of
scope first. When that happens, ricky checks if there are any other shared pointers that
co-own the Person "Ricky". There are (Lucy's `m_partner`). Because of this it doesn't
deallocate "Ricky" (or Lucy's `m_partner` would be left dangling). Next lucy goes out of
scope, and the same thing happens...

### `std::weak_ptr`
An observer - it can observe and access the same object as a `std::shared_ptr` but is not
considered an owner.

```c++
#include <iostream>
#include <memory> // for std::shared_ptr and std::weak_ptr
#include <string>

class Person
{
    std::string m_name;
    std::weak_ptr<Person> m_partner;

public:
    Person(const std::string &name) : m_name (name)
    {
        std::cout << m_name << " created\n";
    }

    ~Person()
    {
        std::cout << m_name << " destroyed\n";
    }

    friend bool partnerUp(std::shared_ptr<Person> &p1, std::shared_ptr<Person> &p2)
    {
        if (!p1 || !p2)
        {
            return false;
        }

        p1->m_partner = p2;
        p2->m_partner = p1;

        std::cout << p1->m_name << " is now partnered with " << p2->m_name << '\n';

        return true;
    }
};

int main()
{
    auto lucy { std::make_shared<Person>("Lucy") };
    auto ricky { std::make_shared<Person>("Ricky") };

    partnerUp(lucy, ricky);

    return 0;
}
```

```
Lucy created
Ricky created
Lucy is now partnered with Ricky
Ricky destroyed
Lucy destroyed
```

### Using `std::weak_ptr`
Not direcly usable via operator->. Must first convert it into a `std::shared_ptr`. Can use
`lock()` member function.

```c++
#include <iostream>
#include <memory> // for std::shared_ptr and std::weak_ptr
#include <string>

class Person
{
    std::string m_name;
    std::weak_ptr<Person> m_partner;

public:
    Person(const std::string &name) : m_name (name)
    {
        std::cout << m_name << " created\n";
    }

    ~Person()
    {
        std::cout << m_name << " destroyed\n";
    }

    friend bool partnerUp(std::shared_ptr<Person> &p1, std::shared_ptr<Person> &p2)
    {
        if (!p1 || !p2)
        {
            return false;
        }

        p1->m_partner = p2;
        p2->m_partner = p1;

        std::cout << p1->m_name << " is now partnered with " << p2->m_name << '\n';

        return true;
    }

    // use lock() to convert weak into shared pointer
    const std::shared_ptr<person> getPartner() const { return m_partner.lock(); }

    const std::string& getName() const { return m_name; }
};

int main()
{
    auto lucy { std::make_shared<Person>("Lucy") };
    auto ricky { std::make_shared<Person>("Ricky") };

    partnerUp(lucy, ricky);

    auto partner = ricky->getPartner();
    std::cout << ricky->getName() << "'s parnter is: " << partner->getName() << '\n';

    return 0;
}
```

```
Lucy created
Ricky created
Lucy is now partnered with Ricky
Ricky's partner is: Lucy
Ricky destroyed
Lucy destroyed
```

### Avoding dangling pointers with `std::weak_ptr`
If shared pointers are all destroyed, but weak are still left, sharing the same resource.
They will be left dangling. But they have access to the reference count for an object, it
can determine if it is pointing to a valid object or not. If the reference count is
non-zero, the resource is still valid.

`expired()` member function

```c++
#include <iostream>
#include <memory>

class Resource
{
public:
    Resource() { std::cerr << "Resource acquired\n"; }
    ~Resource() { std::cerr << "Resource destroyed\n"; }
};

// Returns a std::weak_ptr to an invalid object
std::weak_ptr<Resource> getWeakPtr()
{
    auto ptr { std::make_shared<Resource>() };
    return std::weak_ptr { ptr };
} // ptr goes out of scope, Resource is destroyed

// Returns a dumb pointer to an invalid object
Resource* getDumbPtr()
{
    auto ptr { std::make_unique<Resource>() };
    return ptr.get();
} // ptr goes out of scope, Resource is destroyed

int main()
{
    auto dumb { getDumbPtr() };
    std::cout << "Our dumb ptr is: " << ((dumb == nullptr) ? "nullptr\n" : "non-null\n");

    auto weak { getWeakPtr() };
    std::cout << "Our weak ptr is: " << ((weak.expired()) ? "expired\n" : "valid\n");

    return 0;
}
```

```
Resource acquired
Resource destroyed
Our dumb ptr is: non-null
Resource acquired
Resource destroyed
Our weak ptr is: expired
```

`getDumbPtr()` returns a dangling pointer with no way to tell whether the pointer is
dangling or not.

With weak pointer, we do the expired check.

If you call `lock()` on an expired `std::weak_ptr`, it will return a shared pointer to
`nullptr`.
