// Donald Knuth suggested the following method for checking if 2 floating point numbers
// are "close enough" in The Art of Computer Programming, Volume II: Seminumerical
// Algorithms (Addison-Wesley, 1969)

#include <algorithm> // std::max
#include <cmath> // std::abs
#include <iostream> // std::cout
#include <iomanip> //std::setprecision

// return true if the difference between a and b is within epsilon percent of the larger
// of a and b
bool approximately_equal_rel(double a, double b, double rel_epsilon)
{
    // LHS: std::abs(a - b) - distance between a and b as a positive number
    // RHS: calculate the largest value of "close enough" we're willing to accept.
    // The algorithm chooses the largerof a and b (as a rough indicator of the overall
    // magnitude of the numbers, and then multiplies it by rel_epsilon
    // E.g. within 1% of the larger of a and b -> rel_epsilon = 0.01
    // The value of rel_epsilon can be adjusted to whatever is most approprpriate for the
    // circumstances
    return (std::abs(a - b) <= (std::max(std::abs(a), std::abs(b)) * rel_epsilon));
}

// return true if the difference between a and b is less than abs_epsilon, or within
// rel_epsilon percent of the larger of a and b
bool approximately_equal_abs_rel(double a, double b, double abs_epsilon, double rel_epsilon)
{
    // Check if the numbers are really close -- needed when comaring numbers near zero.
    if (std::abs(a - b) <= abs_epsilon)
    {
        return true;
    }

    // Otherwise fall back to Knuth's algorithm
    return approximately_equal_rel(a, b, rel_epsilon);
}

int main()
{
    double a { 100.0 - 99.999 };
    double b { 10.0 - 9.999 };

    constexpr double rel_epsilon { 0.001 }; // 1%

    std::cout << std::setprecision(16);
    std::cout << "a = 100.0 - 99.99 = " << a << '\n';
    std::cout << "b = 10.0 - 9.99 = " << b << '\n';
    std::cout << "a == b = " << (a == b) << '\n';
    std::cout << "approximately_equal_rel(a, b, " << rel_epsilon << ") = "
        << approximately_equal_rel(a, b, rel_epsilon) << "\n\n";

    double c { 0.9999999999999999 };

    constexpr double rel_epsilon_2 { 1e-8 };
    constexpr double abs_epsilon { 1e-12 };

    std::cout << "c = " << c << '\n';
    std::cout << "approximately_equal_rel(c - 1.0, 0.00, " << rel_epsilon_2 << ") = "
       << approximately_equal_rel(c - 1.0, 0.00, 1e-8) << '\n';
    std::cout << "approximately_equal_abs_rel(c - 1.0, 0.00, " << abs_epsilon << ", "
        << rel_epsilon_2 << ") = "
        << approximately_equal_abs_rel(c - 1.0, 0.00, abs_epsilon, rel_epsilon_2) << '\n';
    std::cout << "approximately_equal_abs_rel(a, b, " << abs_epsilon << ", "
        << rel_epsilon_2 << ") = "
        << approximately_equal_abs_rel(a, b, abs_epsilon, rel_epsilon_2) << '\n';

    return 0;
}

// Problem with using only approximately_equal_rel only - if it's close to 0, it's not going
// to work. E.g.:
// Let's say a ~= 1.0, but slightly smaller than 1.0
// approximately_equal_rel(a - 1.0, 0.0, 1e-8); // returns 0
// Because max between a number slightly smaller than 0 and 0 is 0. 0 * rel_epsilon = 0
// std::abs(a - b) cannot be less than 0
// To resolve use both absolute and relative
