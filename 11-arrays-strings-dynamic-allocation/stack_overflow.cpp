#include <iostream>

int main()
{
    int array[2094000]; // ~7.991 MB 

    // Seems the stack size is 8 MB using gcc 9 on linux
    // But doesn't seem to be consistent

    // Also I believe the stuff below is copied too and uses stack memory too
    std::cout << "Array size: " << sizeof(array) / 1024.0 / 1024.0 << " MB" << '\n';
}
