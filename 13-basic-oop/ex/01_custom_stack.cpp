#include <cassert>
#include <iostream>

constexpr int CAPACITY = 10;

class Stack
{
    int m_array[CAPACITY] { };
    int m_size { };

public:
    void print()
    {
        std::cout << "( ";

        for (int i { 0 }; i < m_size; ++i)
        {
            std::cout << m_array[i] << ' ';
        }

        std::cout << ")\n";
    }

    bool push(int value)
    {
        if (m_size < CAPACITY)
        {
            m_array[m_size] = value;
            ++m_size;

            return true;
        }
        else
        {
            return false;
        }
    }

    int pop()
    {
        assert(m_size > 0 && "Stack is empty");

        --m_size;

        return m_array[m_size];
    }

    void reset()
    {
        m_size = 0;
    }
};

int main()
{
    Stack stack;
    stack.print();

    stack.push(5);
    stack.push(3);
    stack.push(8);
    stack.print();

    stack.pop();
    stack.print();

    stack.pop();
    stack.pop();

    stack.print();

    stack.push(5);
    stack.push(3);
    stack.push(8);
    stack.print();

    stack.reset();
    stack.print();
//  stack.pop();

    std::cout << "Will try to push 15 values (capacity: " << CAPACITY << ")...\n";
    for (int i { 0 }; i < 15; ++i)
    {
        std::cout << "Push success: " << stack.push(i) << '\n';
    }

    stack.print();

    return 0;
}
