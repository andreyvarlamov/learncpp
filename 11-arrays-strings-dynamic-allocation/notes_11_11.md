# 11 - Arrays, Strings, and Dynamic allocations

11.11 - 11.15

### The need for dynamic memory allocation
C++ supports three basic types of memory allocation:

* **Static memroy allocation** happens for static and global variables. Memory for these
  types of variables is allocated once when your program is run and persists through the
  life of your program.
* **Automatic memory allocation** Happens for function parameters and local variables.
  Memory for these types of variables is allocated when the relevant block is entered, and
  freed when the block is exited, as many times as necessary.
* **Dynamic memory allocation**

Both static and automatic allocation have two things in common:

* The size of the variable / array must be known at compile time.
* Memory allocation and deallocation happens automatically (when the variable is
  instantiated / destroyed).

Usually this is just fine, but in some situations this may cause problems, usually when
dealing with external (user or file) input.

If we have to declare the size of everything at compile time, the best we can is try to
make a guess on the maximum size of variablers we'll need and hope that's enough:

```c++
char name[25];
Record record[500];
Monster monster[40];
Polygon rendering[30000];
```

Wasted memory if the variables aren't actually used.

Being able to tell which of these are actually used. 

Most normal variables (including fixed arrays) are allocated in a portion of memory called
the **stack**. Quite small. Visual Studio defaults the stack size to 1MB. If you exceed
this number, stack overflow will result, and the operating system will probably close down
the program.

```c++
int main()
{
    int array[1000000]; // probably 4MB of memory
}
```

Artificial limitations and/or array overflows.

**Dynamic memory allocation** is a way for running programs to request memory from the
operating system when needed. This memory does not come from the program's limited stack
memory; instead, it is allocated from a much larger pool of memory managed by the
operating system called the **heap**. On modern machines, the heap can be gigabytes in
size.

### Dynamically allocating single variables

```c++
new int; // dynamically allocate an integer (and discard the result)
```

Returns the pointer containing the address of the memory that has been allocated.

```c++
int* ptr { new int };
```

### How does dynamic memory allocation work?
Program memory regions. Heap. The program itself is responsible for requesting and
disposing of dynamically allocated memory.

### Unitializing a dynamically allocated variable

```c++
int* ptr1 { new int (5) }; // use direct initiallization
int* ptr2 { new int { 6 } }; // use uniform initiallization
```

### Deleting single variables

```c++
int* ptr { new int (1) };
delete ptr; // return the memory pointed to by ptr to the operating system
ptr = nullptr;
```

### What does it mean to delete memory?
The delete operator doesn't actually *delete* anything, but just returns the memory being
pointed to back to the OS.

Not deleting the actual (pointer) variable. Just returning the memory that it points to
(dangling pointer).

Deleting a pointer that is not pointing to dynamically allocated memory = bad.

### Dangling pointers
A few best practices:

1. Avoid having multiple pointers point at the same piece of dynamic memory. Or be clear
   about which pointer "owns" the memory (and is responsible for deleting it) and which
   pointers are just accessing it.
2. When you delete a opinter, if the pointer is not goind out of scope immediately after,
   set it to `nullptr`.

### Operator `new` can fail
Rare. OS may not have any memory to grant the request with. When that happens, a
`bad_alloc` exception is thrown.

```c++
int* value { new (std::nothrow) int }; // constant std::nothrow
```

But here if it fails to allocate - `nullptr`. Need to check for nullptr.

Because asking new for memory only fails rarely (and almost never in a dev environment),
it is common to forget to do this check.

### Null pointers and dynamic memory allocation

```c++
// If ptr isn't already allocated, allocate i
if (!ptr)
{
    ptr = new int;
}
```

Deleting a null pointer has no effect. So no need to check. Just `delete ptr`.

### Memory leaks

```c++
void doSomething()
{
    int* ptr { new int{} };
}
```

`ptr` goes out of scope. The memory is still allocated, cannot be reclaimed by the OS and
will not be freed until the program terminates.

The program "loses" the address of the dynamically allocated memory.

Eat up memory, making less memory available to this and other programs. In sever cases can
even eat up all the available memory, causing the machine to run slowly or crash.

Other ways:

```c++
int value = 5;
int* ptr { new int{} };
ptr = &value;
```

```c++
int* ptr { new int{} };
ptr = new int{};
```
