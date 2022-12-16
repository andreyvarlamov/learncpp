// 11.12 - Quiz - Question 1

#include <algorithm>
#include <cassert>
#include <iostream>
#include <limits>
#include <string>

int main()
{
    std::cout << "How many names would you like to enter? ";
    int count { };
    std::cin >> count;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    assert(count > 1 && "Invalid count");

    std::string* names { new std::string[count] { } };

    for (int i = 0; i < count; ++i)
    {
        std::cout << "Enter name #" << i + 1 << ": ";
        std::getline(std::cin >> std::ws, names[i]);
    }

    std::sort(names, names + count);

    std::cout << "Here is your sorted list:\n";

    for (int i = 0; i < count; ++i)
    {
        std::cout << "Name #" << i + 1 << ": " << names[i] << '\n';
    }

    delete[] names;

    return 0;
}
