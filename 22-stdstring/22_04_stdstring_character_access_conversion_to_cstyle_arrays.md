# 22.4 - std::string character access and conversion to C-style arrays

### Character access

`char& string:operator[](size_type nIndex)`

`char& string:at(size_type nIndex)` - identical, but slower - performs nIndex validation
and uses exceptions.

### Conversion to C-style arrays

`const char* string::c_str() const`

`const char* string::data() const`

Null terminator appended. The C-style string is owned by the std::string and should not be
deleted.

`size_type string::copy(char* szBuf, size_type nLength ,size_type nIndex = 0) const`

Copy at most nLength characters of the string to szBuf, beginning with character nIndex

The number of characters copied is returned.

No null is appended. Up to caller to ensure szBUF is initialized to NULL or terminate the
string using the returned length.

The caller is responsible for not overflowing szBuf.
