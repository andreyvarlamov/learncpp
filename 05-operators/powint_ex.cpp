#include <iostream>
#include <cstdint> // for std::int64_t
#include <cassert> // for assert

std::int64_t powint(std::int64_t base, int exp)
{
    assert(exp >= 0 && "powint: exp parameter has negative value");

    std::int64_t result { 1 };
    while (exp)
    {
        if (exp & 1)
        {
            result *= base;
        }
        exp >>= 1;
        base *= base;
    }

    return result;
}

int main()
{
    std::cout << powint(7, 12) << '\n';

    return 0;
}
