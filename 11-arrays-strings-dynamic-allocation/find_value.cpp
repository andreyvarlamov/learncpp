// 11.9 - Quiz - Q2

#include <iostream>
#include <iterator> // for std::begin and std::end

int* findValue(int* arrBegin, int* arrEnd, int value)
{
    // We're using !=, rather than <, because != is compatible with more types than <.
    // This is common practice around iterators, which are covered later.
    // It has no advantage when used with pointers, but makes code consistent
    for (int* i { arrBegin }; i != arrEnd; ++i)
    {
        if (*i == value)
        {
            return i;
        }
    }

    return arrEnd;
}

int main()
{
    int arr[] { 2, 5, 4, 10, 8, 20, 16, 40 };
    
    int* found { findValue(std::begin(arr), std::end(arr), 20) };

    if (found != std::end(arr))
    {
        std::cout << *found << '\n';
        return 0;
    }

    std::cout << "Not found" << '\n';
    return 0;
}
