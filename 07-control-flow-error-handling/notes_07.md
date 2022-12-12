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

Advantage over other methods: `x` gets evaluated only once

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



# 7.5 - Switch fallthrough and scoping

### Fallthrough
When a switch expression matches a case label or optional default label, execution begins
at the first statement following the matching label. Exeuction will then continue
sequentially until one of the following termination conditions happens:

1. The end of the switch block is reached
2. Another control flow statement (typically a `break` or `return` causes the switch block
   or function to exit
3. Something else interrupts the normal flow of the program (e.g. the OS shuts down the
   program, etc.)

Since fallthrough is rarely desired or intentional, many compilers and code analysis tools
wiil flag fallthrough as a warning.

### The [[fallthrough]] attribute
Since C++17

**Attributes** are a modern C++ feature that allows the programmer to provide the compiler
with some additional data about the code. Not statements.

The `[[fallthrough]]` attribute modifies a *null statement* to indicate that fallthrough
is intentional.

E.g.

```c++
switch (var)
{
    ...
    case 2:
        do();
        [[fallthrough]];
    ...
}
```

### Sequential case labels

```c++
bool isVowel(char c)
{
    switch (c)
    {
        case 'a':
        case 'e':
        ...
            return true;
        default:
            return false;
    }
}
```

We can stack case labels to make all of those case labels share the same set of statements
afterward. This is not considered fallthrough behavior, so use of comments of
`[[fallthrough]]` is not needed here.

### Switch cas scoping
With switch statements, the statements after labels are all scoped to the switch block. No
implicit blocks are created.

### Variable declaration and initialization inside case statements
You can declare or define (**but not initialize**) variables inside the switch both before
and after the case labels.

```c++
switch (1)
{
    int a; // okay; definition is allowed before the case labels
    int b { 5 }; // illegal: initialization is not allowed before the case labels

    case 1:
        int y; // okay, but bad practice: definition is allowed within a case
        y = 4; // okay: assignment is allowed
        break;

    case 2:
        int z { 4 }; // illegal: initialization is not allowed if subsequent cases exist
        y = 5; // okay: y was declared above, so we can use it here too
        break;

    case 3:
        break;
}
```

All statements inside the switch are considered part of the same scope. Thus, a variable
declared or defined in one case can be used in a later case, even if the case in which the
variable is defined is never executed (because the switch jumped over it)!

Initialization of variables does require the definition to execute at runtime (since the
value of the initializer must be determined at that point). Initialization of variables is
disallowed in any case that is not the last case, as those statements will never be
executed, as there is no way for the switch to reach them.

If a case needs to define and/or initialize a new variable, the best practice is to do so
inside an explicit block underneath the case statement.



# 7.6 - Goto statements
Unconditional jump

```c++
#include <iostream>
#include <cmath> // for sqrt() function

int main()
{
    double x { };
tryAgain:
    std::cout << ...;
    std::cin >> x;

    if (x < 0.0)
    {
        goto tryAgain;
    }

    ...

    return 0;
}
```

### Statement labels have function scope
Which means the label is visible throughout the function even before its point of
declartion. The *goto statement* and its corresponding *statement label* must appear in
the same function.

Must be associated with a statement ("*statement* label")

```c++
void func()
{
    goto skip;
    ...
skip:
    ;
}
```

Bad form: just use if or loops, etc.

Two limitations:
1. You can only jump within the bound of a single function
2. You can't jump forward over the initialization of any variable that is still in scope
   at the location being jumped to.

Note that you can jump backwards over a variable initialization, and the variable will be
re-initialized when the initialization is executed.

### Avoid using goto
Dijkstra "Go To Statement Considered Harmful"

Allows a programmer to jump around the code arbitrarily. --> Spaghetti code

One notable exception is when you need to exit a nested loop but not the entire function.



# 7.7 - Introduction to loops and while statements

### While statements

```
while (condition)
    statement;
```

When a while statement is executed, the condition is evaluated, if true, the associated
statement executes; return to the top, repeat.

### While statements that evaluate to false initially are skipped

### Infinite loops
`while(true)`

### Intentional inifinite loops

### Loop variables
i.e. **counter**

Should be signed. Especially if checking if it's greater than zero

### Doing something every N iterations
counter % N

### Nested loops
