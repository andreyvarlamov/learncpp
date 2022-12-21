# 18.5 - Early binding and late binding

When a program is compiled, the compiler converts each statement in your C++ program into
one or more lines of machine language. Each line of machine language is given its own
unique sequential address. This is no different for functions - when a funciton is
encountered, it is converted into machine language and given the next available address.
Thus, each function ends up with a unique address.

**Binding** refers to the process that is used to convert identifiers (such as variable
and function names) into addresses.

### Early binding
Most of the function calls the compiler encounters will be direct function calls. Direct
function calls can be resolved using a process known as **early binding**. Aka **static
binding**. Means the compiler (or linker) is able to directly associate the identifier
name (such as a function or variable name) with a machine address. So when the compiler
(or linker) encounters a function call, it replaces the function call with a machine
language instruction that tells the CPU to jump to the address of the function.

### Late binding
In some programs, the function being called can't be resolve until runtime. In C++, this
is sometimes known as **late binding** (or in the case of virtual function resolution,
**dynamic binding**.

In general programming terminology, the term "late binding" means the function being
called is looked up by name at runtime. C++ does not support this. In C++, the term "late
binding" is typically used in cases where the actual function being called is not known by
the compiler or linker at the point where the function call is actually being made.
Instead, the function to be called has been determined (at runtime) somewhere prior to
that point.

In C++, one way to get late binding is to use function pointers. Indirect function call.

Slightly less efficient since it involves an extra level of indirection. With early
binding, the CPU can jump directly to the function's address. With late binding, the
program has to read the address held in the pointer and then jump to that address.
