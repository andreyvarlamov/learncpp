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



# 7.8 - Do while statements

```
do
    statement;
while (condition);
```

Always executes at least once. AFter the statement has been executed, the do-while loop
checks the condition; if true, the path of execution jumps back to the top of the do-while
loop and executes again.

> **Best practice**<br>
> Favor while loops over do-while loops when an equal choice.



# 7.9 - For statements

```
for (init-statement; condition; end-expression)
    statement;
```

### Evaluation of for statements
1. The init-statement is executed. These variables have "loop scope".
2. The condition is evaluated. If true, the statement is executed. If false, loop
   terminates and execution continues with the next statement beyond the loop.
3. After the statement is executed, the end-expression is evaluated. Then return to step
   2.

```c++
for (int count { 0 }; count < max; ++count) { ... }
```

### The perils of `operator!=` in for-loop conditions
Better to use <, because it will terminate even if the value jumps over.

### "Off-by-one" errors

### Omitted expressions
Possible to write for loops that omit any or all of the statements or expressions.

```c++
int count { 0 };

for ( ; count < 10; )
{
    ...
    count++;
}
```

```c++
for (;;) // infinite loop
{
    statement;
}
```

Recommended to avoid the latter.

### For loops with multiple counters
```c++
for (int x { 0 }, y { 9 }; x < 10; ++x, --y) { ... }
```

> **Best practice**<br>
> Defining multiple variables and using the comma operator in the end-expression is
> acceptable inside a *for statement*.

### Nested for loops



# 7.10 - Break and continue

Causes a while loop, do-while loop, for loop, or switch statement to end.

### Breaking a switch

### Breaking a loop

### Break vs return

### Continue
**Continue statement** - end the current iteration of a loop without terminating the
entire loop.

### The debate over use of break and continue

> **Best practice**<br>
> Use break and continue when they simplify your loop logic.

### The debate over use of early returns

> **Best practice**<br>
> Use early returns when they simplify your function's logic



# 7.11 - Halts (exiting your program early)
What happens when a program exits normally:

When the `main()` function returns (either by reaching the end of the function or via a
`return statement`), all local variables and function parameters are destroyed (as per
usual). Then a special function `std::exit()` is called, with the return value from
`main()` (the *status code*) passed in as an argument.

### The std::exit() function
Causes the program to terminate normally (in an expected way). (Does not imply anything
about whether the program was successful, that's what the *status code* is for.)

`std::exit()` performs a number of cleanup functions:
1. Objects with static storage duration are destroyed.
2. Some other miscellaneous file cleanup is done if any files were used.
3. Control is returned back to the OS, with the argument passed to std::exit() used as the
   *status code*.

### Calling std::exit() explicitly
`#include <cstdlib>`
`std::exit(0);`

> **Warning**<br>
> `std::exit()` does not clean up local variables in the current function or up the call
> stack. Because of this, it's generally better to avoid calling `std::exit()`

### std::atexit
Because `std::exit()` terminates the program immediately, you may want to manually do some
cleanup before terminating. E.g. closing database or network connections, deallocating any
memory you have allocated, writing information to a log file, etc...

```c++
#include <cstdlib>
#include <iostream>

void cleanup()
{
    // do any kind of cleanup required
}

int main()
{
    // register cleanup() to be called automatically when std::exit() is called
    std::atexit(cleanup);
    ...
    std::exit(0);
    ...
}
```

Notes:

* `std::exit()` is called implicitly when main() terminates, so it will invoke any
   functions registered by `std::atexit()`
* The function being registered must take no parameters and have no return value
* Can register multiple cleanup functions using std::atexit(), they will be called in
  reverse order of registration (the last one registered will be called first).

In multi-threaded programs, calling `std::exit()` can cause your program to crash (because
the thread calling `std::exit()` will cleanup static objects that may still be accessed by
other threads. For this reason, C++ has introduced another pair of functions that work
similarly: `std::quick_exit()` and `std::at_quick_exit()`. The former terminates the
program normally, but does not clean up static objects, and may or may not do other types
of cleanup.

### std::abort and std::terminate
`std::abort()` - terimate abnormally - unusal runtime error and the program couldn't
continue to run. E.g., trying to divide by 0 will result in an abnormal termination.
`std::abort()` does not do any cleanup.

The `std::terminate()` function is typically used in conjunction with *exceptions*.
Although `std::terminate()` can be called explicitly, it is more often called implicitly
when an exception isn't handled (and in a few other exception-related cases). By default,
`std::terminate()` calls `std::abort()`.

### When should you use a halt?
Short answer - almost never. Destroying local objects is an important part of C++
(particularly when we get into classes), and none of the above-mentioned functions clean
up local variables. Exceptions are a better and safer mechanism for handling error cases.

> **Best practice**<br>
> Only use a halt if there is no safe way to return normally from the main function. If
> you haven't disabled exceptions, prefer using exceptions for handling errors safely.



# 7.12 - Introduction to testing your code

### The testing challenge

### Test your programs in small pieces

### Informal testing

### Preserving your tests

### Automating your test functions

### Unit testing frameworks

### Integration testing



# 7.13 - Code coverage

How much of the source code of a program is executed while testing.

### Statement coverage
Percentage of statements in your code that have been exercised by your testing routines

E.g.

```c++
int foo(int x, int y)
{
    int z { y };
    if (x > y)
    {
        z = x;
    }
    return z;
}
```

Calling this function as `foo(1, 0)` will give you complete statement coverate, as every
statement in the function will execute.

If there are branches, might need to call more than 1 test to cover all statements.

### Branch coverage
Percentage of branches that been executed, each possible branch counted separately.

E.g. in the example above, `foo(1, 0)` gives 100% statement coverage, but only 50% branch
coverage. Need also `foo(0, 1)`

### Loop coverage
**the 0, 1, 2 test** - ensure it works properly when it iterates 0 times, 1 time and 2
times.

### Testing different categories of input
Some basic guidelines:

For integers, make sure you've considered how your function yhandles negative values, zero
and positive values. You should also check for overflow if that's relevant.

For floating point numbers, make sure you've considered how your function handles values
that have precision issues (values that are slightly larger or smaller than expected).
Good double type values to test are 0.1 and -0.1 (to test nubmers that are slightly larger
than expected) and 0.6 and -0.6 (to test numbers that are slightly smaller than expected).

For strings, make sure you've considered how your function handles an empty string (just a
null terminator), normal valid strings, strings that have whitespace, and strings that are
all whitespace.

If your function takes a pointer, don't forget to test *nullptr* as well.



# 7.14 - Common semantic errors in C++

### Conditional logic errors

### Infinite loops

### Off-by-one errors

### Incorrect operator precedence

### Precision issues with floating point types

### Integer division

### Accidental null statements
`if(check);`

### Not using a compound statement when one is required



# 7.15 - Detecting and handling errors
Most of the errors in a program occur due to faulty assumptions made by the programmer
and/or a lack of proper error detection/handling. Happy path testing.

### Handling errors in functions: 4 strategies

### Handling the error within the function
Retry until successful, or cancel the operation being executed

### Passing errors back to the caller

### Fatal errors
Non-recoverable error. Halt

### Exceptions



# 7.16 - std::cin and handling invalid input

### std::cin, buffers, and extraction
How the operator>> works - extraction

When the extraction operator is used, the following procedure happens:
1. If there is data already in the input that data is used for extraction.
2. If the input buffer contains no data, the user is asked to input data for extraction
   (this is the case most of the time). When the user hits enter, a '\n' character will be
   placed in the  input buffer.
3. operator>> extracts as much data from the input buffer as it can into the variable
   (ignoring any leading whitespace characters, such as spaces, tabs, or '\n').
3. Any data that can not be extracted is left in the input buffer for the next extraction.

Extraction succeeds if at least one character is extracted from the input buffer.

E.g.

```c++
int x { };
std::cin >> x;
```

If a user enters "5a", 5 will be extracted, converted to an integer, and assigned to a
variable x. "a\n" will be left in the input buffer for the next extraction.

Extraction fails if the input data does not match the type of the variable being
extracted to. For example, if the user were to enter 'b', extraction would fail because
'b' can not be extracted into an integer variable.

### Validating input
Three basic ways:
* Inline (as the user types)
  * Prevent the user from typing invalid input in the first place.
* Post-entry (after the user types)
  * Let the user enter whatever they want into a string, then validate whether the string
    is correct, and if so, convert the string to the variable format.
  * Let the user enter whatever they want, let std::cin and operator>> try to extract it,
    and handle the error cases.

Most often, we let std::cin and the extraction operator do the hard work. We deal with the
fallout if it fails.

### A sample program
... Calculator ...

Consider where invalid user input might break the program.

* We ask the user to enter some numbers. What if they enter something other than a number?
  In this case, extraction will fail.

* We ask the user to enter one of four possible symbols. What if they enter a character
  other than one of the symbols we're expecing? We'll be able to extract the input, but
  need to handle what happens afterwards.

* If the user enters a string like "q hello". Although we can extract the character we
  need, there's additional input left in the buffer that could cause problems down the
  road.

### Types of invalid text input
* Input extraction succeeds but the input is meaningless to the program.
* Input extraction succeeds but the user enters additional input
* Input extraction fails
* Input extraction succeeds but the user overflows a numeric value

### Error case 1: Extraction succeeds but input is meaningless
Do input validation. Check wheter the user's input was what you were expecting. If so
return to the caller. If not tell the user something went wrong and have them try again.

### Error case 2: Extraction succeeds but with extraneous input
To fix use this:

```c++
#include <iostream>
#include <limits>
std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
```

`std::numeric_limits<std::streamsize>::max()` returns the largest value that can be stored
in a variable of type std::streamsize.

`std::cin.ignore(x, '\n');` will clear up to x characters out of buffer, or until a '\n'
character is removed

### Error case 3: Extraction fails
E.g. if extracting into a double:

When the user enters 'a', that character is placed in the buffer. then operator>> tries to
extract 'a' to variable x, which is of type double. Since 'a' can't be converted to a
double, operator>> can't do the extraction. Two things happen at this point: 'a' is left
in the buffer, and std::cin goes into "failure mode".

Once in "failure mode", future requests for input extraction will silently fail. Thus any
output prompts (if e.g. in a loop) will still print, but any requests for further
extraction are ignored. -> Infinite loop, because there's no way to reach one of the valid
cases.

Can do this:

```c++
if (std::cin.fail()) // has a previous extraction failed?
{
    std::cin.clear() // put us back in 'normal' operation mode
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // remove bad input
}
```

Because std::cin has a Boolean conversion indicating whether the last input succeeded,
it's more idiomatic to write the above with `if(!std::cin) { ... }`

### Error 4: Extraction succeeds but the user overflows a numeric value
E.g. when extracting into a `std::int16_t x`, what happens if the user enters a number that
is too large (e.g. 40000)?

std::cin immediately goes into "failure mode", but also assigns the closest in-range value
to the variable. Consequently, x is left with the assigned value of 32767. Additional
inputs are skipped, leaving y with the initialized value of 0.

We can handle this kind of error in the same way as a failed extraction.

### Putting it all together
See `calculator.cpp`



# 7.17 - Assert and `static_assert`

### Preconditions, invariants and postconditions
**Precondition** - condition prior to execution of some component

**Invariant** - condition while some component is executing

**Postcondition** - condition after the execution of some component

### Assertions
Shortcut method for detecting an invalid parameter, along with printing an error message.

If an expression evaluates to true, do nothing, if the expression evaluates to false,
display an error message and terminate the program via `std::abort()`.

Runtime assertions are implemented via the **assert** preprocessor macro, from <cassert>.

(Function-like preprocessor macro; recall object-like preprocessor macro #define FOO 1.)

Good to use these assert statements very liberally.

### Making your assert statements more descriptive
Trick: `assert(found && "Car could not be found in database");`

Then assert message:

```
Assertion failed: found && "Car could not be found in database", ......., line 34
```

This works because a string literal always evaluates to `true`.

### Asserts vs error handling
The goal of asserts is to catch programming errors.

On the other hand, error handling is designed to gracefully handle cases that could happen
in release configurations.

### NDEBUG
assert macro - small performance cost. Should ideally never be encountered in production
code (should already be thoroughly tested).

C++ comes with a way to turn off asserts in production code. Macro `NDEBUG` - when
defined, the assert macro is disabled. Some IDEs set NDEBUG by default for release
configurations.

### Some assert limitations and warnings

1. Assert itself can have a bug.
2. Asserts should have no side effects -- the program should run the same with and without
   assert. Otherwise what you're testing in a debug configuration != release
   configuration.

### `static_assert`
Assertion that is checked at compile-time, not runtime. Causes compile error.

It is a keyword, no header needed.

```
static_assert(condition, diagnostic_message)
```

If the condition is not true, the diagnostic message is printed.

Because it is evaluated by the compiler, the condition must be able to be evaluated at
compile time.

Can be placed anywhere in the code file (even in the global namespace).



# 7.18 - Introduction to random number generation

Computers are generally incapable of generating truly random numbers (at least through
software). Instead, modern programs typically simulate randomness using an algorithm.

### Algorithms and state
**Algoritm** - finite sequence of instructions to be followed to produce some result.

Algorithm is **stateful** if it retains some information across calls. **Stateless** -
converse. **State** - current values held in stateful variables.

**Deterministic**: same input - same output

### Pseudo-random number generators (PRNGs)
Algorithm that generates a sequence of numbers whose properties simulate a sequence of
random numbers.

A very basic PRNG algorithm:

```c++
unsigned int LCG16()
{
    static unsigned int s_state { 5323 };

    // Due to large constants and overflow, it would be
    // hard to causally predict what the next number is going to be
    s_state = 8253729 * s_state + 2396403;

    return s_state % 32768;
}
```

Not a very good PRNG, but most work similarly.

### Seeding a PRNG
Deterministic. Initial value (or sometimes set of values) - **random seed**.

Most PRNGs that produce quality results use at least 16 bytes of state, if not
significantly more. However, the size of the seed value can be smaller than the size of
the state of the PRNG - **underseeded**.

### What makes a good PRNG
* Distribution uniformity (see `prng_histogram.cpp`)
* Unpredictability. LCG16 would be trivially predictable by someone who is motivated.
* Good dimensional distribituion of numbers. E.g. if it was all high numbers first and then
  all low numbers that would not be good (even if it's still uniform and unpredictable).
* PRNG should have a high period for all seeds.
* PRNG should be efficient

### There are many different kinds of PRNG algorithms
[Wikipeda list here](https://en.wikipedia.org/wiki/List_of_random_number_generators)

### Randomization in C++
<random> header of the standard library.

6 PRNG families as of C++20:

| Type name               | Family                                | Period  | State size | Perf   | Qual   | Should use? |
|-------------------------|---------------------------------------|---------|------------|--------|--------|-------------|
| `minstd_rand` (`0`)     | Linear congruential generator         | 2^32    | 4 bytes    | Bad    | Awful  | No          |
| `mt19937`(`_64`)        | Mersenne twister                      | 2^19937 | 2500 bytes | Decent | Decent | Probably    |
| `ranlux24` (`48`)       | Subtract and carry                    | 10^171  | 96 bytes   | Awful  | Good   | No          |
| `knuth_b`               | Shifted linear congruential generator | 2^31    | 1028 bytes | Awful  | Bad    | No          |
| `default_random_engine` | Any of above (implementation defined) | Varies  | Varies     | ?      | ?      | No          |
| `rand()`                | Linear congruential generator         | 2^31    | 4 bytes    | Bad    | Awful  | No          |

No reason to use `knuth_b`, `default_random_engine` and `rand()` ( which is a random
number generator provided for compatibility with C).

As of C++20, the Mersenne Twister algorithm is the only PRNG that ships with C++ that has
both decent performance and quality.

[Test PRNG quality](https://pracrand.sourceforge.net/)

[Pracrand output for all C++ PRNGs](https://arvid.io/2018/06/30/on-cxx-random-number-generator-quality/)

### So we should use MT, right?
For most applications it's fine. But by modern standard it is a bit outdated. Can be
predicted after seeing 624 generated numbers.

If require the highest quality random results, need to use a 3rd part library.

Xoshiro family, Wyrand: non-cryptographic; Chacha family: cryptographic (non-predictable).
