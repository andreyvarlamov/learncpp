# 13.4 - Access functions and encapsulation

### Why make member variables private?
Reduce complexity when using these classes by separating implementation and interface.

E.g. a remote is a public interface for a TV. The actual workings are hidden away. Etc.

### Encapsulation
**Information hiding**.

### Benefit: encapsulated classes are easier to use and reduce the complecity of your programs

### Benefit: encapsulated classes help protect your data and prevent misuse

### Benefit: encapsulated classes are easier to change

### Benefit: encapsulated classes are easier to debug
Breakpoint the function.

### Access functions
**Getters** (**accessors**) and **setters** (**mutators**).

Getters should provide "read-only" access to data.

> **Best practice**<br>
> Getters should return by value or const reference.

### Access functions concerns.
Debate whether the use of access functions violates good OOP class design.

Pragmatic approach:

* If nobody outside your class needs access to a member, don't provide access functions
  for that member.
* If someone outside your class needs to access a member, think about whether you can
  expose a behavior or action instead (e.g. instead of `setAlive(false)`, `kill()`.
* If you can't, consider whether you can provide only a getter.
