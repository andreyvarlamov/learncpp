# 17.5 - Inheritance and access specifiers

1. A class (and friends) can always access its own non-inherited members. The access
   specifiers only affect whether outsiders and derived classes can access those members.

2. When derived classes inherit members, those members may change access specifiers in the
   derived class. This does not affect the derived classes' own (non-inherited) members
   (which have their own access specifiers). It only affects whether outsiders and classes
   derived from the derived class can access those inherited members.

Members from the base class can get a different access specifier if called from a derived
class:

| Base           | Public inherit | Protected inherit | Private inherit |
|----------------|----------------|-------------------|-----------------|
| Public         | Public         | Protected         | Private         |
| Protected      | Protected      | Protected         | Private         |
| Private        | Inaccessible   | Inaccessible      | Inaccessible    |

Also holds true for member functions and types declared inside the class.
