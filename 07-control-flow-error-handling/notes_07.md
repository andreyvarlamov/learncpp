# 7 - Control Flow and Error Handling

-----

# 7.1 - Control flow introduction

**Control flow statements**
**Branching**

### Categories of flow control statements

* Conditional statements
  * Conditional statements cause a sequence of code to execute only if some condition is
    met
  * `if`, `switch`

* Jumps
  * Jumps tell the CPU to start executing the satements at some other location.
  * `goto`, `break`, `continue`

* Function calls
  * Jumps to some other location and back
  * *function calls*, `return`

* Loops
  * Repeatedly execute some sequence of code 0 or more times, until some condition is met.
  * `while`, *do-while*, `for`, `ranged-for`

* Halts
  * Halts tell the program to quit running.
  * `std::exit()`, `std::abort()`

* Exceptions
  * Special kind of flow control structure designed for error handling
  * `try`, `throw`, `catch`



# 7.2 - If statements and blocks
...

> **Best practice**<br>
> Use blocks in if statements

Middle ground: put single-lines on the same line as the `if` or `else`

### Implicit blocks
Common mistake

```c++
...
if (cond)
    int x { 5 };
else
    int x { 6 };

std::cout << x << ... ;
```

x isn't defined. The blocks here are implicit.

# 7.3 - Common if statement problems

### Nested if statements and the dangling else problem

```c++
if (x >= 0)
    if (x <= 20)
        // do something
    else
        // do something else
```

What if statement is the else referring to? Last unmatched if statement.

### Flattening nested if statements

### Null statements

`;` - expression statement that does nothing

Common error.

```c++
if (a);
    do();
```

Equivalent to:

```c++
if (a)
    ;

do()
```

### == vs =
