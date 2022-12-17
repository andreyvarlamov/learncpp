# 12.2 - The stack and the heap

Memory of a program is typically divided into segments:

* **Code segment** (text segment), where the compiled program sits in memory
* **Bss segment** (unitialized data segment), where zero-initialized global and static
  variables are stored.
* **Data segment** (initialized data segment), where initialized global and static
  variables are stored.
* **Heap**, where dynamically allocated variables are allocated from
* **Call stack**, where function parameters, local variables, and other function-related
  information are stored.

### The heap segment
Aka "free store".

The heap has advantages and disdvantages:

* Allocating memory on the heap is comparatively slow.
* Allocated memory stays allocated until it is specifically deallocated (beware memory
  leaks) or the application (at which point the OS should clean it up).
* Dynamically allocated memory must be accessed through a pointer. Dereferencing a pointer
  is slower than accessing a variable directly.
* Because the heap is a big pool of memory, large arrays, structures, or classes can be
  allocated here.

### The call stack
Keeps track of all the active functions (those that have been called but have not yet
terminated) from the start of the program to the current point of execution, and handles
allocation of all function parameters and local variables.

### The stack data structure
A **data structure** is a programming mechanism for organizing data so that it it can be
used efficiently.

A stack is a container data structure that holds multiple variables. But whereas an array
lets you access and modify elements in any order you wish (**random access**), a stack is
more limited.

Stack of plates analogy.

Peek, pop and push.

Mailbox and a post-it note analogy

### The call stack segment
The call stack segment holds the memory used for the call stack.

When the application starts, the `main()` function is pushed on the call stack by the
operating system. Then the program begins executing.

When a function call is encountered, the function is pushed onto the call stack. When the
current function ends, the function is popped off the call stack (this is called
**unwinding the stack**).

A **stack frame** keeps track of all the data associated with one function call. The **stack
pointer** ("SP") - "marker" held in a register (small piece of memory in the CPU) that
keeps track of where the top of the call stack currently is.

No need to clean up or zero the memory used by the popped stack frame, just move the stack
pointer down.

### The call stack in action

When a function is called:

1. The program encounters a function call.
2. A stack frame is constructed and pushed on the stack. The stack frame consists of:

   * The address of the instruction beyond the function call (called the **return
     address**). This is how the CPU remembers where to return after the called function
     exits.
   * All function arguments.
   * Memory for any local variables.
   * Saved copies of any registers modified by the function that need to be restored when
     the function returns.

3. The CPU jumps to the function's start point.
4. The instructions inside of the function begin executing.

When a function terminates:

1. Registers are restored from the call stack.
2. The stack frame is popped off the stack. This frees the memory for all local variables
   and arguments.
3. The return value is handled.
4. The CPU resumes execution at the return address.

Return values can be handled in a number of ways, depending on computer's architecture.
Some architectures include the return value as part of the stack frame. Others use CPU
registers.

On some architectures, the call stack grows away from memory address 0. On others, it
grows towards memory address 0.

### A quick and dirty call stack example
...

### Stack overflow
On Visual Studio for Windows, the default stack size is 1MB. With g++/Clang for Unix
variants, it can be as large as 8MB.

**Stack overflow** happens when all the memory in the stack has been allocated, further
allocations begin overflowing into other sections of memory.

Too many variables or too many nested calls.

On modern operating systems, overflowing the stack will generally cause your OS to issue
an access violtion and terminate the program.

Advantages and disadvantages:

* Allocaring memory on the stack is comparatively fast.
* Memory allocated on the stack stays in scope as long as it is on the stack. It is
  destroyed when it is popped off the stack.
* All memory allocated on the stack is known at compile. Consequently, this memory can be
  accessed directly througha a variable.
* Because this stack is relatively small, it is generally not a good idea to do anything
  that eats up lots of stack space. This includes passing by value or creating local
  variables of large arrays or other memory-intensive structures.

### How variables on the stack are laid out and receive actual memory addresses at runtime
At compilation time, the compiler will lay out where all of the normal variables are in
memory as offsets from some base address (that will be provided at runtime). So the
compiler will say x is at (base address + 4), y is at (base address + 8), etc. Then
wherever the compiler sees x in our source code, it generates compiled code that uses
(base address + 4) instead.

E.g. when the function containing the variables is called, the base address gets assigned
 -- let's say at memory address 136. So the executable code will access memory (136 + 4)
to access x.
