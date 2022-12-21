# 20.4 - Uncaught exceptions and catch-all handlers

### Uncaught exceptions
When no exception handler for a function can be found, std::terminate() is called, and the
application is terminated. In such cases, the call stack may or may not be unwound. If the
stack is not unwound, local variables will not be destroyed, and any cleanup expected upon
destruction of said variables will not happen. (If the stack were unwound, then all of the
debug information about the state of the stack that led up to the throwing of the
unhandled exception would be lost. By not unwinding, we preserve that information, making
it easier to determine an unhandled exception was thrown, and fix it.

### Catch-all handlers

```c++
catch(...)
{
    // catch all errors
}
```

> **Best practice**<br>
> If your program uses exceptions, consider using a catch-all handler in main, to help
> ensure orderly behavior when an unhandled exception occurs. Also consider disabling the
> catch-all handler for debug builds, to make it easier to identify how unhandled
> exceptions are occurring.
