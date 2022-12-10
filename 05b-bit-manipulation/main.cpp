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

// O.2 - Bitwise operators
// Operator         Symbol      Form        Operation
// left shift       <<          x << y      all bits in x shifted left y bits
// right shift      >>          x >> y      all bits in x shifted right y bits
// bitwise NOT      ~           ~x          all bits in x flipped
// bitwise AND      &           x & y       each bit in x AND each bit in y
// bitwise OR       |           x | y       each bit in x OR each bit in y
// bitwise XOR      ^           x ^ y       each bit in x XOR each bit in y
// The bitwise operators are defined for integral types and std::bitset. Use bitset because
// it's easier to print the output in binary.
// Best practice: to avoid surprises, use the bitwise operators with unsigned operands or
// std::bitset

// Bitwise left shift (<<) and bitwise right shift (>>) operators
// Bits that are shifted off the end of the number are lost
// e.g. 0011 << 1 is 0110; 0011 << 3 is 1000
// e.g. 1100 >> 1 is 0110; 1100 >> 3 is 0001

// std::cout has overloaded operator << so it does console output instead of bit shifting.
// Same for >>
// Parentesization is required:
// std::cout << x << 1 << '\n'; // not the same as
// std::cout << (x << 1) << '\n';

// Bitwise NOT: ~0100 is 1011

// Bitwise OR: 0101 | 0110 is 0111

// Bitwise AND: 0101 & 0110 is 0100

// Bitwise XOR: 0110 ^ 0011 is 0101

// Bitwise assignment operators: <<=, >>=, |=, &=, ^=



// O.3 - Bit manipulation with bitwise operators and bit masks
// Let's take a look at how bitwise operators are more commonly used

// Bit masks
// A bit mask blocks the bitwise operators from touching bits we don't want modified, and
// allows access to the ones we do want modified.

// C++14 supports binary literals; pre C++14, would need to use hex literals
// Or shift them into place.

// See bit-masks.cpp

// std::bitset supports the full set of bitwise operators, so can still use masks.
// Unlike std::bitset functions, masks allow to modify multiple bits at once.

// A best practice is to give bit masks useful names as a way to document the meaning of
// the bit flags. E.g. mask1 -> isHungry

// When is it useful?
// 8 booleans would normally take 8 bytes. But the above example would use 9 bytes
// (8 bytes to define the bit masks, and 1 byte for the flag variable)
// But this is useful if there are many identical flag variables.
// E.g. 8 flags for 100 entities: 8 bytes for the masks and 100 bytes for 100 entity flag
// sets = 108 bytes total; instead of 800 bytes total for 8 bools for each of the 100
// entities

// Another case: if you had a function that could take any combination of 32 different
// paremeters. Would be very long function call with individual bools
// E.g. void some_function(std::bitset<32> options);
// some_function(option10 | option32);
// OpenGL opted to use bit flag parameters instead of many consecutive bool parameters
// glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the color and the depth buffer
// In gl2.h:
// #define GL_DEPTH_BUFFER_BIT      0x00000100
// #define GL_STENCIL_BUFFER_BIT    0x00000400
// #define GL_COLOR_BUFFER_BIT      0x00004000

// Bit masks involving multiple bits
// For color display devices, the amount of R, G and B for a given pixel is represented
// by an 8-bit unsigned integer. When assigning color values to a pixel, in addition to
// those 3, a 4th value called is often used. Alpha - how transparent the color is.
// masks    0xFF000000 - red bits - 32 bits
//          0x00FF0000 - green bits
//          ...
// Isolate red value and right shift into the lower 8 bits, then cast to uint8_t:
// std::uint8_t red { static_cast<std::uint8_t>((pixel * red_bits) >> 24) };
