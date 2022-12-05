// Experiment from 1.6

#include <iostream>

void doNothing(int&)
{
}

int main()
{
    int x;
    doNothing(x); // make the compiler think we're assigning a value to this variable
    std::cout << x << '\n';
    return 0;
}

