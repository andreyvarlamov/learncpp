# 23.5 - Stream states and input validation

ios\_base class contains several state flags that are used to signal various conditions
that may occur when using streams.

goodbit, badbit, eofbit, failbit

### Input validation
std::isalnum, isalpha, iscntrl, isdigit, isgraph, isprint, ispunct, isspace, isxdigit

### String validation
When it comes to variable lenght inputs, the best way to validate strings is to step
through each character of the string and ensure it meets the validation criteria.

`std::ranges::all_of`

### Numeric validation

### Numeric validation as a string
