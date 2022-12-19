# 14.16 - Shallow vs. deep copying

Memberwise copy = **shallow copy**. Copy each member of the class individually.

But if there's dynamically allocated memory:

```c++
#include <iostream>

int main()
{
    MyString hello { "Hello, world!" };

    {
        MyString copy { hello }; // use default copy constructor
    } // copy gets destroyed here. The destructor deletes copy's string, which leaves
      // hello with a dangling pointer
...
```

### Deep copying

```c++
void MyString::deepCopy(const MyString& source)
{
    // first deallocate any value that this string is holding (in the implicit object)
    // needed for the assignment operator
    delete[] m_data;

    // Not a pointer, can shallow copy.
    m_length = source.m_length;

    if (source.m_data)
    {
        // allocate memory for the copy
        m_data = new char[m_length];

        // copy values
        for (int i { 0 }; i < m_length; ++i)
        {
            m_data[i] = source.m_data[i];
        }
    }
    else
    {
        m_data = nullptr;
    }
}

// Copy constructor
MyString::MyString(const MyString& source)
{
    deepCopy(source);
}

// Assignment operator
MyString& MyString::operator=(const MyString& source)
{
    if (this != &source)
    {
        deepCopy(source);
    }

    return *this;
}
```

### A better solution
Just use std lib.
