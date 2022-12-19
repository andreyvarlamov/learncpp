# 14.1 - Introduction to operator overloading

In C++, operators are implemented as functions. Using function overloading to overload
operators is called **operator overloading**.

### Operators as functions

`w + z` -> `operator+(w, z)`

### Resolving overloaded operators
Compiler rules:

* If all of the operands are fundamental data types, the compiler will call a built-in
  routine if one exists. If one does not exist, the compiler will produce a compiler
  error.
* If any of the operands are user data types (e.g. one of your classes, or an enum type),
  the compiler looks to see whether the type has a matching overloaded operator function
  that it can call. If it can't find one, it will try to convert one or more of the
  user-defined type operands into fundamental data types so it can use a matching built-in
  operator (via an overloaded typecast). If that fails - compiler error.

### What are the limitations on operator overloading?
1. Almost any existing operator in C++ can be overloaded. The exceptions are: (?:),
   sizeof, scope (::), member selector (.), pointer member selector (.\*), typeid, and the
   casting operators
2. You can only overload the operators that exist. Can't create new or rename existing.
3. At least one of the operands in an overloaded operator must by a user-defined type.
4. Not possible to change the number of operands an operator supports.
5. All operators keep their default precedence and associativity.

> **Best practice**<br>
> When overloading operators, it's best to keep the function of the operators as close to
> the original intent of the operators as possible (because of the precedence issue).

> **Best practice**<br>
> If the meaning of an overloaded operator is not clear and intuitive, use a named
> function instead.

Still plenty of useful functionality: overload + to concatenate user-defined string class,
or add two Fraction class objects together. Overload << to make it easy to print your
class to the screen (or a file). Overload == to compare two class objects.
