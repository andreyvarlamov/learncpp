// 12.8 - Quiz - Q3

#include <algorithm>
#include <cassert>
#include <ctime>
#include <cmath>
#include <iterator>
#include <iostream>
#include <random>
#include <vector>

int getMultiplier()
{
    static std::mt19937 mt { static_cast<std::mt19937::result_type>(std::time(nullptr)) };
    std::uniform_int_distribution die3 { 2, 4 };
    return die3(mt);
}

std::vector<int> generateNumbers(int startNum, int totalCount, int multiplier, bool cheating)
{
    std::vector<int> numbers ( static_cast<size_t>(totalCount) );

    int i { startNum };

    std::cout << "Generating numbers...";
    for (auto& number : numbers)
    {
        number = i * i * multiplier;
        if (cheating)
        {
            std::cout << ' ' << number;
        }
        ++i;
    }

    std::cout << '\n';

    return numbers;
}

int main()
{
    std::cout << "Start where? ";

    int startNum { };
    std::cin >> startNum;

    std::cout << "How many? ";

    int totalCount { };
    std::cin >> totalCount;

    int multiplier { getMultiplier() };

    std::vector<int> numbers { generateNumbers(startNum, totalCount, multiplier, false) };

    std::cout << "I generated " << totalCount << " square numbers. "
        << "Do you know what each number is after multiplying it by " << multiplier << "?\n";

    for (int i { totalCount }; i > 0; --i)
    {
        std::cout << "> ";

        int guess { };
        std::cin >> guess;

        auto isGuessed {
            [guess](int num)
            {
                return num == guess;
            }
        };

        auto found { std::find_if(numbers.begin(), numbers.end(), isGuessed) };

        if (found != numbers.end())
        {
            std::cout << "Nice! ";

            if (i - 1 > 0)
            {
                std::cout << i - 1 << " nubmers left.\n";
            }
            else
            {
                std::cout << "You found all numbers, good job!\n";
            }

            numbers.erase(found);
        }
        else
        {
            std::cout << guess << " is wrong!";

            auto isCloserToGuess {
                [guess](int& a, int& b)
                {
                    return (std::abs(a - guess) < std::abs(b - guess));
                }
            };

            auto min { std::min_element(numbers.begin(), numbers.end(), isCloserToGuess) };

            assert(min != numbers.end() && "Could not find min");

            if (std::abs(*min - guess) <= 4)
            {
                std::cout << " Try " << *min << " next time.\n";
            }
            else
            {
                std::cout << '\n';
            }

            break;
        }
    }

    return 0;
}
