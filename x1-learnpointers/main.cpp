#include <iostream>

void takes_pointer(int* x)
{
    *x = 600;
    std::cout << '\n' << x << "\n\n";
}

void takes_reference(int& x)
{
    x = 900;
    std::cout << '\n' << &x << "\n";
}

int main() {
    int x = 5;
    int* p_x = &x;
    int& y = x;
    
    std::cout << "Hello world! " << x << '\n';
    
    takes_pointer(p_x);
    
    std::cout << &x << '\n';
    std::cout << &y << '\n';
    std::cout << p_x << '\n';
    std::cout << '\n';
    std::cout << x << '\n';
    std::cout << y << '\n';
    std::cout << *p_x << '\n';
    
    takes_reference(y);
    std::cout << x << '\n';

    return 0;
}
