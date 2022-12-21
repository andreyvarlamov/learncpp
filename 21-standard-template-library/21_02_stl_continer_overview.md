# 21.2 - STL containers overview

### Sequence Containers
As of C++11, the STL contains 6 sequence containers: std::vector, std::deque, std::array,
std::list, std::forward\_list, and std::basic\_string.

* Vector - dynamic array capable of growing as needed to contain its elements. The vector
  class allows random access to its elements via `operator[]`, and inserting and removing
  elements from the end of the vector is generally fast.
* Deque - double-ended queue class, implemented as a dynamic array that can grow from both
  ends.
* List - doubly linked list. Each element in the container contains pointers that point at
  the next and previous elements in the list. No random access. If you want to find a
  value in the middle, you have to start at one end and "walk the list" until you reach the
  element you want to find. The advantage: inserting is very fast if you already know where
  you want to insert them. Generally iterators are used to walk through the list.
* Although the STL string (and wstring) class aren't generally included as a type of
  sequence container, they essentially are, as the can be though of as a vetor with data
  elements of type char (or wchar).

### Associative Containers

* A set - stores unique elements, with duplicate elements disallowed. The elements are
  sorted according to their values.
* A multiset - a set where duplicate elements are allowed.
* A map (aka associative array) is a set where each element is a pair, called a key/value
  pair. They key is used for sorting and indexing the data, and must be unique. The value
  is the actual data.
* A multimap (aka a dictionary) - a map that allows duplicate keys.

### Container Adapters

* A stack - is a container where elements operate in a LIFO (Last In, First Out) context.
  Stacks default to using deque as their default sequence container (which seems odd,
since vector seems like a more natural fit), but can use vector or list as well.
* A queue - FIFIO (First In, First Out). Default to using deque, but can also use list.
* A priority queue - is a type of queue where elements are kept sortd (via operator<).
  When elements are pushed, the element is sorted in the queue. Removing an element from
  the front returns the highest priority item in the priority queue.
