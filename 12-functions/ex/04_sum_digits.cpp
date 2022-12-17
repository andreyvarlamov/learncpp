// 12.4 - Quiz - Q2

#include <iostream>

int sum_digits(int num)
{
    if (num <= 0)
    {
        return 0;
    }

    if (num / 10 == 0)
    {
        return num;
    }

    return sum_digits(num / 10) + (num % 10);
}

int main()
{
    int num { 23423498 };
    std::cout << "Sum of digits of " << num << " = " <<  sum_digits(num) << '\n';

    return 0;
}

// 1236
// (123) + 6
// (12) + 3
// (1) + 2
// 1
// 1 + 2 + 3 + 6 = 12
