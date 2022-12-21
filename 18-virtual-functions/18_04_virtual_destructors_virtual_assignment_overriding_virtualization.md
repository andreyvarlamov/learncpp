# 18.4 - Virtual destructors, virtual assignment, and overriding virtualization

You should **always** make your destructors virtual if you're dealing with inheritance.

If deleting a Derived object through a Base pointer, it will only call the Base destructor.
If the destructor is virtual - `virtual ~Base()` - then in the same case it will see if it
can find an override, and call `virtual ~Derived()`.

> **Rule**
> Whenever you are dealing with inheritance, you should make any explicit destructors
> virtual.

### Virtual assignment
Posssible to make the assignmen operator virtual. However it is a bag full of worms and
gets into some advanced topics outside the scope of this tutorial.

### Ignoring virtualization
Simply use the scope resolution operator.

### Should we make all destructors virtual?
Performance penalty (a virtual pointer added to every instance of your class).

Tutorial's recommendations:
* If you intend your class to be inherited from, make sure your destructor is virtual
* If you do not intend your class to be inherited from, mark your class as final. This
  will prevent other classes from inhereting from it in the first place, without imposing
  any other use restructions on the class itself.
