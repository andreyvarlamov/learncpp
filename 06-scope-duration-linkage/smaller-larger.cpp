// 6.3 - Quiz - Question 1

#include <iostream>

int main()
{
    int smaller { };
    int larger { };

    std::cout << "Enter an integer: ";
    std::cin >> smaller;

    std::cout << "Enter a larger integer: ";
    std::cin >> larger;

    if (smaller > larger)
    {
        std::cout << "Swappping the values" << '\n';

        // In the future can use std::swap() from the <utility> header
        // E.g. std::swap(larger, smaller);
        int temp = smaller;
        smaller = larger;
        larger = temp;
    } // temp is destroyed

    std::cout << "The smaller value is " << smaller << '\n';
    std::cout << "The larger value is " << larger << '\n';

    return 0;
} // smaller and larger are destroyed
