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



# 7.4 - Switch statement basics
```c++
switch(x)
{
    case 1:
        std::cout << "One";
        break;
    case 2:
        std::cout << "Two";
        break;
    case 3:
        std::cout << "Three";
        break;
    default:
        std::cout << "Unknown";
        break;
}
```

Switch only allows conditions that evaluate to an integral type or enumerated type. I.e.
no strings, floats, etc.

Reason: designed to be highly optimized. Historically, most commonly implemented by
compilers via [jump tables](https://en.wikipedia.org/wiki/Branch_table), which only work
with integral values.

A jump table works much like an array, an integral value is used as the array index to
"jump" directly to a result.

No requirement for compilers to implement switch using jump tables.

### Switch statement

### Case labels
Followed by constant expression

### Default label
Default label is optional

### No matching case label and no default case
If the value of the conditional expression does not match any of the case labels, and no
default case has been provided, then no cases inside the switch are executed. Execution
continues after the end of the switch block.

### Break statement
