// O.4 - Quiz - Question 6

#include <iostream>

void print_converted(unsigned int x)
{
    if (x >= 128)
    {
        std::cout << '1';
        x -= 128;
    }
    else
    {
        std::cout << '0';
    }

    if (x >= 64)
    {
        std::cout << '1';
        x -= 64;
    }
    else
    {
        std::cout << '0';
    }

    if (x >= 32)
    {
        std::cout << '1';
        x -= 32;
    }
    else
    {
        std::cout << '0';
    }

    if (x >= 16)
    {
        std::cout << '1';
        x -= 16;
    }
    else
    {
        std::cout << '0';
    }

    if (x >= 8)
    {
        std::cout << '1';
        x -= 8;
    }
    else
    {
        std::cout << '0';
    }

    if (x >= 4)
    {
        std::cout << '1';
        x -= 4;
    }
    else
    {
        std::cout << '0';
    }

    if (x >= 2)
    {
        std::cout << '1';
        x -= 2;
    }
    else
    {
        std::cout << '0';
    }

    if (x >= 1)
    {
        std::cout << '1';
    }
    else
    {
        std::cout << '0';
    }

    std::cout << '\n';
}

int main()
{
    unsigned int x { };

    std::cout << "Enter a number between 0 and 255: ";
    std::cin >> x;

    std::cout << "In binary: ";
    print_converted(x);

    return 0;
}
