// 7.7 - Introduction to loops and while statements - Quiz - Question 4

#include <iostream>

int main()
{
    constexpr int times = 5;
    int outer { }; // (zero-initialize)

    while (outer < times)
    {
        int inner { };
        while (inner < times)
        {
            if (inner >= (times - 1) - outer)
            {
                std::cout << times - inner << ' ';
            }
            else
            {
                std::cout << "  ";
            }

            ++inner;
        }

        // or:
//        int inner { 4 };
//        while (inner >= 0)
//        {
//            if (inner <= outer)
//            {
//                std::cout << inner + 1 << ' ';
//            }
//            else
//            {
//                std::cout << "  ";
//            }
//
//            --inner;
//        }


        std::cout << '\n';
        ++outer;
    }
}
