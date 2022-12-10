#include <iostream>

void print_result(double x, double y, char op, double result)
{
    std::cout << x << ' ' << op << ' ' << y << " is " << result << '\n';
}


int main()
{
    double x = 0.0;
    double y = 0.0;
    char op = 0;

    std::cout << "Enter a double value: ";
    std::cin >> x;
    std::cout << "Enter a double value: ";
    std::cin >> y;
    std::cout << "Enter one of the following: +, -, *, or /: ";
    std::cin >> op;

    if (op == '+')
    {
        print_result(x, y, op, x + y);
    }
    else if (op == '-')
    {
        print_result(x, y, op, x - y);
    }
    else if (op == '*')
    {
        print_result(x, y, op, x * y);
    }
    else if (op == '/')
    {
        print_result(x, y, op, x / y);
    }
    else
    {
        std::cout << "Unknown operation" << '\n';
        return 1;
    }

    return 0;
}
