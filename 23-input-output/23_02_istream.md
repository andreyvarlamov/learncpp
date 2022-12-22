# 23.2 - Input with istream

...

Extraction operator skips whitespace.

`get()` - get single char; also a string version that takes a max num of chars to read.
Does not read newline char.

`getline()` - works like get, but reads newline as well

A special version of getline() that lives outside the istream class that is used for
reading in variables of type std::string. getline.

ignore(), ignore(int), peek(), unget(), putback(char).
