// 11.x Quiz - Q2

#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

struct Student {
    std::string name { };
    int grade { };
};

bool greatest_grade(Student a, Student b)
{
    return (a.grade > b.grade);
}

int main()
{
    std::cout << "STUDENT GRADE SORTER" << '\n';
    std::cout << "How many students would you like to enter? ";

    int count { };
    std::cin >> count;

    assert(count > 0 && "Invalid student count");

    std::vector<Student> students ( static_cast<size_t>(count) );

    for (auto& student : students)
    {
        std::string name { };
        int grade { };

        std::cout << "Enter student's name: ";
        std::getline(std::cin >> std::ws, name);

        std::cout << "Enter student's grade: ";
        std::cin >> grade;

        student = { name, grade };
    }

    std::sort(students.begin(), students.end(), greatest_grade);

    for (auto& student : students)
    {
        std::cout << student.name << " got a grade of " << student.grade << '\n';
    }
}
