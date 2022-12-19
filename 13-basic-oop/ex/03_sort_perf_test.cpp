#include <algorithm>
#include <array>
#include <chrono> // for std::chrono functions
#include <cstddef> // for std::size_t
#include <iostream>
#include <numeric> // for std::iota

const int g_arrayElements { 10000 };

class Timer
{
private:
    using Clock = std::chrono::steady_clock;
    using Second = std::chrono::duration<double, std::ratio<1>>;

    std::chrono::time_point<Clock> m_beg { Clock::now() };

public:
    void reset()
    {
        m_beg = Clock::now();
    }

    double elapsed() const
    {
        return std::chrono::duration_cast<Second>(Clock::now() - m_beg).count();
    }
};

[[maybe_unused]]
void sortArray(std::array<int, g_arrayElements>& array)
{
    for (std::size_t startIndex { 0 }; startIndex < (g_arrayElements - 1); ++startIndex)
    {
        std::size_t smallestIndex { startIndex };

        for (std::size_t currentIndex { startIndex + 1 }; currentIndex < g_arrayElements; ++currentIndex)
        {
            if (array[currentIndex] < array[smallestIndex])
            {
                smallestIndex = currentIndex;
            }
        }

        std::swap(array[startIndex], array[smallestIndex]);
    }
}

int main()
{
    std::array<int, g_arrayElements> array;
    std::iota(array.rbegin(), array.rend(), 1); // fill the array with values 10000 to 1

    Timer t;

    //sortArray(array);

    // std::ranges::sort(array); // Since C++20
    std::sort(array.begin(), array.end()); // Before C++20

    std::cout << "Time taken: " << t.elapsed() << " seconds\n";

    return 0;
}
