# 20.3 - Exceptions, functions, and stack unwinding

When an exception is thrown, the program looks to see if the exception can be handled
immediately inside the current function (if there's a try and catch). Then checks each
function up the call stack until either a handler is found, or all of the functions on the
call stack have been checked and no handler found. If a matching exception handler is
found, then execution jumps from the point where the exception is thrown to the top of the
matching catch block. This requires unwinding the stack as many times as necessary to make
the function handling the exception the top function of the call stack. If no matching
handler is found, the stack may or may not be unwound.
