# 18.8 - Virtual base classes

```c++
#include <iostream>

class PoweredDevice
{
public:
    PoweredDevice(int power)
    {
        std::cout << "PoweredDevice: " << power << '\n';
    }
};

class Scanner: virtual public PoweredDevice // PoweredDevice is now a virtual base class
{
public:
    Scanner(int scanner, int power)
        : PoweredDevice { power } // this line is required to create Scanner objects, but
                                  // ignored if creating Copier objects.
    {
        std::cout << "Scanner: " << scanner << '\n';
    }
};

class Printer: virtual public PoweredDevice // PoweredDevice is now a virtual base class
{
public:
    Printer(int scanner, int power)
        : PoweredDevice { power } // this line is required to create Printer objects, but
                                  // ignored if creating Copier objects.
    {
        std::cout << "Printer: " << printer << '\n';
    }
};

class Copier: public Scanner, public Printer
{
public:
    Copier(int scanner, int printer, int power)
        : PowerDevice { power }, // PoweredDevice is constructed here
        Scanner { scanner, power }, Printer { printer, power }
    {
    }
};

int main()
{
    Copier copier { 1, 2, 3 };

    return 0;
}
```

```
PoweredDevice: 3
Scanner: 1
Printer: 2
```

Virtual base classes are always created before non-virtual base classes, which ensures
all bases get created before their derived classes.

The Scanner and Printer constructors still have calls to the PoweredDevice constructor.
When creating an instance of Copier, these constructors are simply ignore because Copier
is responsible for creating the PoweredDevice, not Scanner or Printer. However, if we were
to create an instance of Scanner or Printer, those constructor calls would be used, and
normal inheritance rules apply.

If a class inherits one or more classes that have virtual parents, the most derived class
is responsible for constructing the virtual base class. In this case, Copier inherits
Printer and Scanner, both of which have a PoweredDevice virtual base class. Copier, the
most derived class, is responsible for creation of PoweredDevice. Note that this is true
even in a single inheritance case: if copies singly inherited from Printer, and Printer
virtually inherited from PoweredDevice, Copier is still responsible for creating
PoweredDevice.

All classes inherting a virtual base class will have a virtual table, even if they would
normally not have one otherwise, and thus instances of the class will be larger by a
pointer.

Because Scanner and Printer derive virtually from poweredDevice, Copier will only be one
PoweredDevice subobject. Scanner and Printer both need to know how to find that single
PoweredDevice subobject, so they can access its members. This is typically done through
some virtual table magic (which essentially stores the offset from each subclass to the
PoweredDevice subobject).
