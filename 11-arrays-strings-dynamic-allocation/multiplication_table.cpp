#include <iostream>

int main()
{
    constexpr int numRows { 9 };
    constexpr int numCols { 9 };

    int product[numRows][numCols] { };

    for (int row { 0 }; row < numRows; ++row)
    {
        for (int col { 0 }; col < numCols; ++col)
        {
            product[row][col] = (row + 1) * (col + 1);
        }
    }

    for (int row { 0 }; row < numRows; ++row)
    {
        for (int col { 0 }; col < numCols; ++col)
        {
            std::cout << product[row][col] << '\t';
        }

        std::cout << '\n';
    }

    return 0;
}
