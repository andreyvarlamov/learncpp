# 18.9 - Object slicing

```c++
int main()
{
    Derived derived { 5 };
    Base base { derived };

    std::cout << "base is a " << base.getName() << " and has value " << base.getValue() << '\n';

    return 0;
}
```

derived has a Base part and a Derived part. When we assign a Derived object to a Base
object, only the Base portion of the Derived object is copied. The Derived portion is not.
In the example above, base receives a copy of the Base portion of derived, but not the
Derived portion. The Derived portion has been effectively "sliced off" -- **object
slicing**.

Can usually happen: when a function takes a Base passed by value. When in a std::vector.

With vector, have to either use a pointer to Base, or `std::reference_wrapper<Base>>`.

### The Frankenobject

```c++
int main()
{
    Derived d1 { 5 };
    Derived d2 { 6 };
    Base& b { d2 };

    b = d1;

    return 0;
}
```

Since b points at d2, and we're assigning d1 to b, you might think that the result would
be that d1 would get copied into d2 -- and it would, if b were a Derived. But b is a
Base, and the operator= that C++ provides for classes isn't virtual by default.
Consequently, only the Base portion of d1 is copied into d2.

You just created a Frankenobject -- composed of parts of multiple object.

### Conclusion
Although C++ supports assigning derived objects to base objects via object silcing, in
general, this is likely to cause nohting but headaches, and you should generally avoid
slicing. Try to avoid any kind of pass-by-value when it comes to derived classes.
