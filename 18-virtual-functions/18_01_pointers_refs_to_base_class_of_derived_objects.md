# 18.1 - Pointers and references to the base class of derived objects

C++ will let us set a Base pointer or reference to a Derived object.

```c++
#include <iostream>

// In Base: proctected m_value, public getName (returns "Base") and public getValue (returns m_value)
// In Derived: public getName (returns "Derived") and public getValueDoubled (returns m_value * 2)
int main()
{
    Derived derived { 5 };

    Base& rBase { derived };
    Base* pBase { &derived };

    std::cout << "derived is a " << derived.getName() << " and has value " << derived.getValue() << '\n';
    std::cout << "rBase is a " << rBase.getName() << " and has value " << rBase.getValue() << '\n';
    std::cout << "pBase is a " << pBase.getName() << " and has value " << pBase.getValue() << '\n';

    return 0;
}
```

```
derived is a Derived and has value 5
rBase is a Base and has value 5
pBase is a Base and has value 5
```

Because rBase and pBase are a Base reference and pointer, they can only see members of
Base (or any classes that Base inherited). So even though Derived::getName() shadows
(hides) Base::getName() for Derived objects, the Base pointer/reference can not see
Derived::getName().

### Use of pointer and references to base classes
One function that takes ref to Base, when there are multiple derived classes.

Arrays of Base type, that can hold all derived classes.

Enter virtual functions...

----

Possible to add a member to the base class that will be initialized differently in
different derived classes. But it's non-optimal, because the base class will become large
memory-wise and complicated. Also, only works if the base class member can be determined
at initialization time.
