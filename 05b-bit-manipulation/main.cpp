int main()
{
    return 0;
}

// O.1 - Bit flags and bit manipulation via std::bitset
// On modern computer architectures, the smallest addressable unit of memory is a byte.
// Since all objects need to have unique memory addresses, this means objects must be at
// least one byte in size. For booleans it's a bit wasteful.
// A boolean will use 1 bit and leave the other 7 unused.
// In some storage-intesnsive cases, it can be useful to "pack" 8 individual boolean
// values into a single byte for storage efficiency purposes.
// Bit manipulation.

// Bit flags.
// When individual bits of an object are used as Boolean values, the bits are called
// bit flags.
// To define a set of bit flags, we'll typically use an unsigned integer of the appropriate
// size (8 bits, 16 bits, 32 bits, etc... depending on how many flags we have),
// or std::bitset
// #include <bitset> // for std::bitset
// std::bitset<8> mybitset { }; // 8 bit bitset
// Bit manipulation is one of the few times when you should unambiguously use unsigned
// integers (or std::bitset)

// Bit numbering and bit positions
// Given a sequence of bits, we typically number the bits from right to left, starting
// with 0 (not 1). Each number denotes a bit position.

// Manipulating bits via std::biset
// std::bitset::test() - query whether a bit is a 0 or 1
// std::bitset::set() - turn a bit on
// std::bitset::reset() - turn a bit off
// std::bitset::flip() - toggle
//#include <bitset>
//#include <iostream>
//
//int main()
//{
//    std::bitset<8> bits { 0b0000'0101 };
//    bits.set(3);
//    bits.flip(4);
//    bits.reset(4);
//
//    std::cout << "All the bits: " << bits << '\n'; // All the bits: 00001101
//    std::cout << "Bit 3 has value: " << bits.test(3) << '\n'; // Bit 3 has value: 1
//    std::cout << "Bit 4 has value: " << bits.test(4) << '\n'; // Bit 4 has value: 0
//
//    return 0;
//}
