# 20.8 - Exception dangers and downsides

### Cleaning up resources

### Exceptions and destructors
Never throw exceptions in a destructor. What happens when an exception is thrown from a
destructor during the stack unwinding process? Compiler wouldn't know whether to continue
unwinding the stack or handle the new exception. The end result is that your program will
be terminated immediately.

### Performance concerns
Increase the size of your executable, may cause it to run slower due to the additional
checking that has to be performed. However, the main performance penalty for exceptions
happens when an exception is actually thrown. In this case, the stack must be unwound and
an appropriate exception handler found, which is a relatively expensive operation.

Zero-cost exceptions. If supported, have no additional runtime cost in the non-error case.
However, they incur an even larger penalty in the cases where an exception is found.

### So when should I use exceptions?

* The error being handled is likely to occur only infrequenetly
* The error is serious and execution could not continue otherwise
* The error cannot be handled at the place where it occurs
* There isn't a good alternative way to return an error code back to the caller.
