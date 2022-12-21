# 21.4 - STL algorithms overview

A number of generic algorithms for working with the elements of the container classes.
Search, sort, insert, reorder, remove and copy elements of the container class.

Implemented as functions that operate using iterators. This means that each algorithm only
needs to be implemented once, and it will generally automatically work for all containers
that proides a set of iterators (including your custom container classes).

But some combination of algorithms and container types may not work, may cause infinite
loops, or may work but be extremely poor performing. Use at your own risk.

* `std::min_element` and `std::max_element`. (`std::iota` to generate a contiguous series
  of values. -- numeric header)

* `std::find()`

* `std::sort()` and `std::reverse()`. Sort can accept custom comparison functions. Several
  in the functional header. Doesn't work on list container classes. The list class
  provides its own sort member function, which is much more efficient than the generic
  version would be.
