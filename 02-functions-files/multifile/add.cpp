int add(int x, int y)
{
    return x + y;
}

// Because the compiler compiles each code file individually (and then forgets what it has
// seen), if std::cout, etc. was used in this file, it would have needed #include<iostream>
