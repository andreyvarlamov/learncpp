# 18.6 - The virtual table

Lookup table of functions used to resolve function calls in a dynamic/late binding manner.
"Vtable", "virtual function table", "virtual method table", "dispatch table".

Every class that uses virtual functions (or is derived from a class that uses virtual
functions) is given its own virtual table. Static array that the compiler sets up at
compile time. A virtual table contains one entry for each virtual function that can be
called by objects of the class. Each entry in this table is simply a function pointer that
points to the most-derived function accessible by the class.

The compiler also adds a hidden pointer that is a member of the base class, and is
inherited by derived classes. Automatically set when a class object is created, so that
it points to the virtual table for that class. 

![Diagram](https://www.learncpp.com/images/CppTutorial/Section12/VTable.gif)

For example, when an object of type Base is created, `*__vptr` is set to point to the
virtual table for Base. When objects of type D1 or D2 are constructed, `*__vptr` is set to
point to the virtual table for D1 or D2 respectively.

This is why calling a virtual function is slower than calling a non-virtual function. We
have to use the `*__vptr` to get the appropriate virtual table. Second we have to index
the virtual table to find the correct function to call. 3 operations to find the function
to call.
