#include <iostream>

unsigned int LCG16()
{
    static unsigned int s_state { 7272 };

    s_state = 8234233 * s_state + 2372983;

    //return s_state % 32768;
    return s_state % 50; // for the histogram it won't be actually 16-bit
}

int main()
{
    int occurences[50] { };

    for (int i { 0 }; i < 500; ++i)
    {
        // Fine to static cast unsigned int to signed int here, because we know it
        // only goes from 0 to 49
        int random = static_cast<int>(LCG16());

        occurences[random]++;
    }

    // Histogram for 50 numbers
    for (int i { }; i < 50; ++i)
    {
        std::cout << i << ")\t";

        for (int j { }; j < occurences[i]; ++j)
        {
            std::cout << '*';
        }

        std::cout << "\t\t(" << occurences[i] << ")\n";
    }
}
