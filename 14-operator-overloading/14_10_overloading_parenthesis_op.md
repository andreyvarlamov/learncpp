# 14.10 - Overloading the parenthesis operator

```c++
#include <cassert>
#include <iostream>

class Matrix
{
private:
    double m_data[4][4]{};

public:
    double& operator()(int row, int col);
    double operator()(int row, int col) const;
    void operator()();
};

double& Matrix::operator()(int row, int col)
{
    assert(col >= 0 && col < 4);
    assert(row >= 0 && row < 4);

    return m_data[row][col];
}

double Matrix::operator()(int row, int col) const
{
    assert(col >= 0 && col < 4);
    assert(row >= 0 && row < 4);

    return m_data[row][col];
}

void Matrix::operator()()
{
    // reset
    for (int row { 0 }; row < 4; ++row)
    {
        for (int col { 0 }; col < 4; ++col)
        {
            m_data[row][col] = 0.0;
        }
    }
}

int main()
{
    Matrix matrix { };
    matrix(1, 2) = 4.5;
    matrix();
    std::cout << matrix(1, 2) << '\n'; // 0

    return 0;
}
```

Strongly discouraged to use this for unconventional purposes

### Functors
**Function object**

```c++
#include <iostream>

class Accumulator
{
private:
    int m_counter { 0 };

public:
    int operator()(int i) { return (m_counter += i); }
};

int main()
{
    Accumulator acc { };
    std::cout << acc(10) << '\n';
    std::cout << acc(20) << '\n';

    return 0;
}
```

With functors (compared to a function with a static variable), we can instantiate many
separate functor objects.
