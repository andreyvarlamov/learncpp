#include <algorithm>
#include <array>
#include <iostream>

struct Student
{
    std::string_view name { };
    int points { };
};

using Students = std::array<Student, 8>;

//int main(int argc, char* argv[])
int main()
{
    Students arr {
        {
            { "Albert", 3 },
            { "Ben", 5 },
            { "Christine", 2 },
            { "Dan", 8 },
            { "Enchilada", 4 },
            { "Francis", 1 },
            { "Greg", 3 },
            { "Hagrid", 5 },
        }
    };

    auto highestGrade {
        [](Student& a, Student& b)
        {
            return (a.points < b.points);
        }
    };

    const Student* bestStudent { std::max_element(arr.begin(), arr.end(), highestGrade) };

    std::cout << bestStudent->name << " is the best student" << '\n';
    return 0;
}

