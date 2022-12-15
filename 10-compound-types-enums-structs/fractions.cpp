// 10.8 - Quiz - Question 2

#include <iostream>

struct Fraction
{
    int numerator { };
    int denominator { };
};

Fraction readFraction()
{
    std::cout << "Enter a value for the numerator: ";
    int numerator { };
    std::cin >> numerator;

    std::cout << "Enter a value for the denominator: ";
    int denominator { };
    std::cin >> denominator;

    return Fraction { numerator, denominator };
}

Fraction multiplyFractions(Fraction& f1, Fraction& f2)
{
    int numerator { f1.numerator * f2.numerator };
    int denominator { f1.denominator * f2.denominator };

    return Fraction { numerator, denominator };
}

int main()
{
    Fraction f1 = readFraction();
    Fraction f2 = readFraction();

    Fraction result = multiplyFractions(f1, f2);

    std::cout << "Your fractions multiplied together: "
        << result.numerator << "/" << result.denominator << '\n';

    return 0;
}
