// 12.x - Q3

#include <iostream>
#include <iterator>

int binarySearch(const int* array, int target, int min, int max)
{
    while (min <= max)
    {
        int center { min + ((max - min) / 2) };

        if (target == array[center])
        {
            return center;
        }
        else if (target > array[center])
        {
            min = center + 1;
        }
        else
        {
            max = center - 1;
        }
    }

    return -1;
}

int binarySearchRec(const int* array, int target, int min, int max)
{
    if (min > max)
    {
        return -1;
    }

    int center { min + ((max - min) / 2) };
    if (target == array[center])
    {
        return center;
    }
    else if (target > array[center])
    {
        return binarySearchRec(array, target, center + 1, max);
    }
    else
    {
        return binarySearchRec(array, target, min, center - 1);
    }
}

int main()
{
    //                      0                         7                          14
    constexpr int array[] { 3, 6, 8, 12, 14, 17, 20, 21, 26, 32, 36, 37, 42, 44, 48 };

    constexpr int numTestValues { 9 };
    constexpr int testValues[numTestValues] { 0,  3, 12, 13, 22, 26, 43, 44, 49 };
    int expectedValues[numTestValues]       { -1, 0, 3,  -1, -1, 8,  -1, 13, -1 };

    std::cout << "Testing iterative function\n";
    for (int count { 0 }; count < numTestValues; ++count)
    {
        int index { binarySearch(array, testValues[count], 0, static_cast<int>(std::size(array)) - 1) };

        if (index == expectedValues[count])
        {
            std::cout << "test value " << testValues[count] << " passed!\n";
        }
        else
        {
            std::cout << "test value " << testValues[count] << " failed.\n";
        }
    }

    std::cout << "Testing recursive function\n";
    for (int count { 0 }; count < numTestValues; ++count)
    {
        int index { binarySearchRec(array, testValues[count], 0, static_cast<int>(std::size(array)) - 1) };

        if (index == expectedValues[count])
        {
            std::cout << "test value " << testValues[count] << " passed!\n";
        }
        else
        {
            std::cout << "test value " << testValues[count] << " failed.\n";
        }
    }

    return 0;
}
