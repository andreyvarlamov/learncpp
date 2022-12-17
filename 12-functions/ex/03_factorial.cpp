// 12.4 - Quiz - Q1

#include <iostream>

int factorial(int n)
{
    if (n <= 0)
    {
        return 0;
    }

    if (n == 1)
    {
        return 1;
    }

    if (n == 2)
    {
        return 2;
    }

    return n * factorial(n - 1);
}

int main()
{
    for (int i { 0 }; i < 7; ++i)
    {
        std::cout << i + 1 << "! = " << factorial(i + 1) << '\n';
    }
    return 0;
}
