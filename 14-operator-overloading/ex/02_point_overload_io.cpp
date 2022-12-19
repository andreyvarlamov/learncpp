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

    friend std::ostream& operator<<(std::ostream& out, const Point& point);
    friend std::istream& operator>>(std::istream& in, Point& point);
};

std::ostream& operator<<(std::ostream& out, const Point& point)
{
    out << "Point(" << point.m_x << ", " << point.m_y << ", " << point.m_z << ')';

    return out;
}

std::istream& operator>>(std::istream& in, Point& point)
{
    in >> point.m_x;
    in >> point.m_y;
    in >> point.m_z;

    return in;
}

int main()
{
    std::cout << "Enter a point: ";

    Point point;
    std::cin >> point;

    std::cout << "You entered: " << point << '\n';

    return 0;
}
