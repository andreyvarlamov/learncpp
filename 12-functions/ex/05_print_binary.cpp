// 12.4 - Quiz - Q3a,b

#include <iostream>

// Casting negative signed int to unsigned, will turn negative integer into the positive
// unsigned number, that in binary will correspond to two's complement signed negative.
// E.g. -15 (assuming 32-bit int) -> (2,147,483,647 - 15) = 2,147,483,632 ->
// 1111,1111,1111,1111,1111,1111,1111,0001
void print_binary(unsigned int num)
{
    if (num == 0)
    {
        std::cout << 0 << '\n';
        return;
    }

    if (num / 2 == 0)
    {
        std::cout << num % 2 << ' ';
        return;
    }

    print_binary(num / 2);

    std::cout << num % 2 << ' ';
    return;
}

int main()
{
    int num { -15 };
    std::cout << "Binary representation of " << num << " is ";
    print_binary(static_cast<unsigned int>(num));

    std::cout << '\n';

    return 0;
}
