# 21.3 - STL iterators overview.

An object that can traverse (iterate over) a container class without the user having to
know how the container is implemented.

Best visualized as a pointer to a given element in the container, with a set of overloaded
operators to provide a set of well-defined functions:

* `operator*` -- dereferencing the iterator returns the element that the iterator is
  currently pointing at.
* `operator++` -- moves the iterator to the next element in the container. Most iterators
  also provide `operator--` to move to the previous element.
* `operator==` and `operator!=` -- basic comparison operators to determine if two
  iterators point to the same element. To compare the values that two iterators are
  pointing at, dereference the iterators first, and then use a comparison operator.
* `operator=` -- assign the iterator to a new position (typically at the start or end of
  the container's elements). To assign the value of the element the iterator is pointing
  at, dereference the iterator first, then use the assign operator.

Each container includes four basic member functions to use with `operator=`:

* `begin()` -- returns an iterator representing the beginning of the elements in the
  container.
* `end()` -- returns an iterator representing the element just past the end of the
  elements.
* `cbegin()` -- returns a const iterator representing the beginning of the elements in the
  container.
* `cend()` -- returns a const iterator representing the element just past the end of the
  elements.

All container provie (at least) two types of iterators:

* `container::iterator` provides a read/write iterator
* `conatiner::const_iterator` provides a read-only iterator


----

For maps:
In pairs (`std::pair`). `std::make_pair()` to create an element. Iterators will point to
pairs.

----

Iterators must be implemented on a per-class basis, because the iterator does need to know
how a class is implemented. Thus iterators are always tied to a specific container.
