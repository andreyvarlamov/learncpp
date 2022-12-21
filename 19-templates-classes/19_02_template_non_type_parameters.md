# 19.2 - Template non-type parameters

Can be of following types:
* Integral type
* Enum type
* A pointer or reference to a class object
* A pointer or reference to a function
* A pointer or reference to a class member function
* `std::nullptr_t`
* A floating point type (since C++20)

Non-type parameter has to be constexpr. And will be replace at compile.

`std::array<int, 5>`
