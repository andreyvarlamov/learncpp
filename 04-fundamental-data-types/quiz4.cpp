#include <iostream>

constexpr double GRAVITY { 9.8 };

double height_at_t(double initial_height, int seconds)
{
    return initial_height - ((GRAVITY * seconds * seconds) / 2);
}

void print_height_at_t(int seconds, double height)
{
    if (height > 0.0)
    {
        std::cout << "At " << seconds << " seconds, the ball is at height: "
            << height << " meters\n";
    }
    else
    {
        std::cout << "At " << seconds << " seconds, the ball is on the ground.\n";
    }
}

int main()
{
    int total_t { 0 };

    double initial_height { 0.0 };

    std::cout << "Enter the height of the tower in meters: ";
    std::cin >> initial_height;

    std::cout << "Enter the total time to simulate for: ";
    std::cin >> total_t;

    for (int i=0; i < total_t+1; i++)
    {
        print_height_at_t(i, height_at_t(initial_height, i));
    }

    return 0;
}
