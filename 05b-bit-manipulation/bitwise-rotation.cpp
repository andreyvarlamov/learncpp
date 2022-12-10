
#include <bitset>
#include <iostream>

// "rotl" stands for "rotate left"
std::bitset<4> rotl(std::bitset<4> bits)
{
    // O.2 - Quiz - Question 2
    // Can use std::bitset::test() and std::bitset::set()
//    const bool leftbit { bits.test(3) };
//
//    bits <<= 1;
//
//    if (leftbit)
//    {
//        bits.set(0);
//    }
//
//    return bits;

    // Question 3
    // Can't use test and set
    // bits << 1 does the left shift
    // bits >> 3 handles the rotation of the leftmost bit
    return (bits << 1) | (bits >> 3);
}

int main()
{
    std::bitset<4> bits1 { 0b0001 };
    std::cout << rotl(bits1) << '\n';

    std::bitset<4> bits2 { 0b1001 };
    std::cout << rotl(bits2) << '\n';

    return 0;
}
