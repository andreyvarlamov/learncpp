// 11.4 - Quiz - Q3 and Q4

#include <iostream>
#include <iterator> // for std::size
#include <utility> // for std::swap

int main()
{
    std::cout << "BUBBLE SORT\n";

    int array[] { 6, 3, 2, 9, 7, 1, 5, 4, 8 };
    int length { static_cast<int>(std::size(array)) };

    std::cout << "Original array: ";
    for (int i { 0 }; i < length; ++i)
    {
        std::cout << array[i] << ' ';
    }
    std::cout << '\n';

    for (int i { 0 }; i < length - 1; ++i)
    {
        bool hasSwapped { false };
        for (int j { 0 }; j < length - 1 - i; ++j)
        {
            if (array[j] > array[j+1])
            {
                std::swap(array[j], array[j+1]);
                hasSwapped = true;
            }
        }

        if (!hasSwapped)
        {
            std::cout << "Early termination on iteration #" << i + 1 << '\n';
            break;
        }
    }

    std::cout << "Sorted array: ";
    for (int i { 0 }; i < length; ++i)
    {
        std::cout << array[i] << ' ';
    }
    std::cout << '\n';
}
