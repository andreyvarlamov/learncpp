#include <cstdint>
#include <iostream>
#include <bitset>

int main()
{
    [[maybe_unused]]
    constexpr std::uint8_t mask0 { 0b0000'0001 }; // bit 0
    [[maybe_unused]]
    constexpr std::uint8_t mask1 { 0b0000'0010 }; // bit 1
    [[maybe_unused]]
    constexpr std::uint8_t mask2 { 0b0000'0100 }; // bit 2
    [[maybe_unused]]
    constexpr std::uint8_t mask3 { 0b0000'1000 }; // bit 3
    [[maybe_unused]]
    constexpr std::uint8_t mask4 { 0b0001'0000 }; // bit 4
    [[maybe_unused]]
    constexpr std::uint8_t mask5 { 0b0010'0000 }; // bit 5
    [[maybe_unused]]
    constexpr std::uint8_t mask6 { 0b0100'0000 }; // bit 6
    [[maybe_unused]]
    constexpr std::uint8_t mask7 { 0b1000'0000 }; // bit 7

    std::uint8_t flags { 0b0000'0101 }; // 8 bits in size means room for 8 flags

    std::cout << "Flags = " << static_cast<std::bitset<8>>(flags) << "\n\n";

    // TESTING BITS
    // If bit 0 in flags is 1, when anded with mask0 -> 0b0000'0001 -> non-zero, so true
    // If bit 0 in flags is 0, when anded with mask0 -> 0b0000'0000 -> zero, so false
    std::cout << "Testing bits 0 and 1" << '\n';
    std::cout << "bit 0 is " << ((flags & mask0) ? "on\n" : "off\n");
    // If bit 1 in flags is 1, when anded with mask1 -> 0b0000'0010 -> non-zero, so true
    std::cout << "bit 1 is " << ((flags & mask1) ? "on\n" : "off\n\n");

    // SETTING BITS
    std::cout << "Setting bit 1" << '\n';
    // If bit 1 in flags is 1, it will be left as 1 (1 | 1 = 1)
    // If bit 1 in flags is 0, it will be set to 1 (0 | 1 = 1)
    flags |= mask1; // turn on bit 1
    std::cout << "Flags = " << static_cast<std::bitset<8>>(flags) << "\n\n";
    // Can also turn on multiple bits at the same time using Bitwise OR
    // flags |= (mask4 | mask5); // turn bits 4 and 5 at the same time

    // RESETTING BITS
    std::cout << "Resetting bit 2" << '\n';
    // If bit 2 in flags is 1, it will be set to 0 (1 & ~1)
    // If bit 2 in flags is 0, it will be left as 0 (0 & ~1)
    flags &= ~mask2; // turn off bit 1
    std::cout << "Flags = " << static_cast<std::bitset<8>>(flags) << "\n\n";
    // Can also turn off multiple bits at the same time
    // flags &= ~(mask4 | mask5);

    // FLIPPING BITS
    std::cout << "Flipping bit 3" << '\n';
    flags ^= mask3; // flip bit 3
    std::cout << "Flags = " << static_cast<std::bitset<8>>(flags) << "\n\n";
    std::cout << "Flipping bit 3 again" << '\n';
    flags ^= mask3; // flip bit 3
    std::cout << "Flags = " << static_cast<std::bitset<8>>(flags) << "\n";
    // Can also flip multiple bits at the same time
    // flags ^= (mask4 | mask5);

    return 0;
}
