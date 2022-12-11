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



// O.4 - Converting between binary and decimal
// Decimal: 5623 = (5 * 1000) + (6 * 100 ) + (2 * 10  ) + (3 * 1   )
//                 (10^(4-1))   (10^(3-1))   (10^(2-1))   (10^(1-1))
//                 (digit 4 )   (digit 3 )   (digit 2 )   (digit 1 )

// Converting binary to decimal
// Binary:  0101'1110 ->
// (0 * 128) + (1 * 64 ) + (0 * 32) + (1 * 16) + (1 * 8) + (1 * 4) + (1 * 2) + (0 * 1  )
// (2^(8-1))   (2^(7-1))     ..................................                (2^(1-1))
// (bit 8  )   (bit 7  )     ..................................                (bit 1  )
// Decimal -> 94

// Method 1 for converting decimal to binary
// Decimal: 148 ->
// 148 / 2 = 74 remainder 0
// 74  / 2 = 37 remainder 0
// 37  / 2 = 18 remainder 1
// 18  / 2 = 9  remainder 0
// 9   / 2 = 4  remainder 1
// 4   / 2 = 2  remainder 0
// 2   / 2 = 1  remainder 0
// 1   / 2 = 0  remainder 1
// Binary -> 10010100

// Method 2 for converting decimal to binary
// Decimal: 148 ->
// Is 148 >= 128? Yes, so the 128 bit = 1; 148 - 128 = 20, which means we need to find bits worth 20 more
// Is 20  >= 64?  No, so the 64 bit = 0
// Is 20  >= 32?  No, so the 32 bit = 0
// Is 20  >= 16?  Yes, so the 16 bit = 1; 20 - 16 = 4
// Is 4   >= 8?   No, so the 8 bit = 0
// Is 4   >= 4?   Yes, so the 4 bit must be 1; 4-4, which means all the rest of the bits must be 0
// Binary -> 10010100
// This was only unsigned integers

// Signed numbers and two's complement:
// Signed integers are typically stored using a method known as two's complement
// The leftmost (most significant) bit is used as the sign bit; 0 - positive; 1 - negative
// Postive signed numbers are represented in binary just like positive unsigned numbers
// (with the sign bit set to 0)
// Negative signed numbers are represented in binary as the bitwise inverse of the positive
// number, plus 1

// E.g.
// -5 -> 1111'1011
// 5 -> 0000'0101
// Invert all bits -> 1111'1010
// Add 1 -> 1111'1011
// -75 -> 1011'0100
// Why do we add 1? Consider 0, if a negative value was simply represented as the inverse
// of the positive number, 0 would have to representations: 0000'0000 (positive zero) and
// 1111'1111 (negative zero). By adding 1, 1111'1111 intentionally overflows and becomes
// 0000'0000
// This prevents 0 from having two representations, and simplifies some of the internal
// logic needed to do arithmetic with negative numbers

// Converting binary (two's complelemnt) to decimal
// First look at the sign bit:
// If the sign bit is 0, just convert the number as shown for unsigned numbers above
// If the sign bit is 1, then we invert the bits, add 1, then convert to decimal, then make
// the decimal number negative.
// E.g.
// 1001'1110 -> -98
// Sign bit is 1 -> Invert -> 0110'0001
// Add 1 -> 0110'0010 -> 98 in decimal

// Two's complement now guaranteed as of C++20

// Floating point numbers are more complicated: https://tfinley.net/csarch-notes/2000/floating
// TODO ^

// Math just works:
// E.g.:
//  0110'0100       100
// +               +
//  1001'1110       -98
//  ---------       ---
//  0000'0010       2
