# 14.6 - Overloading unary operators +, -, and !

```c++
#include <iostream>

class Point
{
private:
    double m_x { };
    double m_y { };
    double m_z { };

public:
    Point(double x = 0.0, double y = 0.0, double z = 0.0)
        : m_x { x }, m_y { y }, m_z { z }
    {
    }

    // Convert a Point into its negative equivalent
    Point operator-() const;

    // Return true if the point is set at the origin
    bool operator!() const;

    double getX() const { return m_x; }
    double getY() const { return m_y; }
    double getZ() const { return m_z; }
};

Point Point::operator-() const
{
    return { -m_x, -m_y, -m_z };
}

bool Point::operator!() const
{
    return (m_x == 0.0 && m_y == 0.0 && m_z == 0.0);
}

int main()
{
    Point point { };

    if (!point)
    {
        std::cout << "point is set at the origin.\n";
    }
    else
    {
        std::cout << "point is not set at the origin.\n";
    }

    return 0;
}
```
