#include <iostream>
#include <limits>

void ignoreLine()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

double getDouble()
{
    while (true) // Loop until user enters a valid input
    {
        std::cout << "Enter a double value: ";
        double x { };
        std::cin >> x;

        // Check for failed extraction
        if (!std::cin)
        {
            std::cin.clear(); // put us back into 'normal' mode
            ignoreLine(); // remove the bad input
            std::cerr << "Oops, that input is invalid. Please try again.\n";
        }
        else
        {
            ignoreLine(); // remove any extraneous input
            return x;
        }
    }
}

double getOperator()
{
    while (true)
    {
        std::cout << "Enter one of the following: +, -, *, or /: ";
        char operation { };
        std::cin >> operation;
        ignoreLine(); // remove any extraneous input

        switch (operation)
        {
        case '+':
        case '-':
        case '*':
        case '/':
            return operation;
        default:
            std::cerr << "Oops, that input is invalid. Please try again. \n";
        }
    }
}

void printResult(double x, char operation, double y)
{
    switch (operation)
    {
    case '+':
        std::cout << x << " + " << y << " is " << x + y << '\n';
        break;
    case '-':
        std::cout << x << " - " << y << " is " << x - y << '\n';
        break;
    case '*':
        std::cout << x << " * " << y << " is " << x * y << '\n';
        break;
    case '/':
        std::cout << x << " / " << y << " is " << x / y << '\n';
        break;
    default:
        std::cerr << "Something went wrong: printResult() got an invalid operator.\n";
    }
}

int main()
{
    double x { getDouble() };
    double operation { getOperator() };
    double y { getDouble() };

    printResult(x, operation, y);

    return 0;
}
