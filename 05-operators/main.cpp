int main()
{
    return 0;
}

// 5.1 - Operator presedence
// Compound expresssion
// All operators are assigned a level of precedence. Operators with the highest level of
// precedence are evaluated first.
// But if operators are of the same presedence, the operator's associativity tells the
// compiler whether to evaluate the operators from left to right or from right to left
// Operators on presence level 5 have an associativity of left to right
// E.g. 3 * 4 / 2 = (3 * 4) / 2 = 6

// Presence level 1 is the highest presedence level; 17 is the lowest.

// Prec/Ass     Operator        Description
// ---          ---             ---
// 1 L->R       ::              Global scope (unary) - ::name
//              ::              Namespace scope (binary) - class_name::member_name
// 2 L->R       ()              Parenteses - (expression)
//              ()              Function call - function_name(params)
//              ()              Initialization - type name(expression)
//              {}              Uniform initialization (C++11) type name{expression}
//              type()          Functional cast - new_type(expresssion)
//              type{}          Functional cast (C++11) - new_type{expression}
//              []              Array subscript - pointer[expression]
//              .               Member access from object - object.member_name
//              ->              Member access from object ptr - object_pointer->member_name
//              ++              Post-increment - lvalue++
//              --              Post-decrement - lvalue--
//              typeid          Run-time type information - typeid(type) or typeid(expression)
//              const_cast      Cast away const - const_cast<type>(expression)
//              dynamic_cast    Run-time type-checked cast - dynamic_cast<type>(expression)
//            reinterpret_cast  Cast one type to another - reinterpret_cast<type>(expression)
//              static_cast     Compile-time type-checked cast - static-cast<type>(expression)
//              sizeof...       Get parameter pack size - sizeof..(expression)
//              noexcept        Compile-time exception check - noexcept(expression)
//              alignof         Get type alighment - alignof(Type)
// 3 R->L       +               Unary plus - +expression
//              -               Unary minus - -expression
//              ++              Pre-increment - ++lvalue
//              --              Pre-decrement - --lvalue
//              !               Logical NOT - !expression
//              ~               Bitwise NOT - +expression
//              (type)          C-style cast (new_type)expression
//              sizeof          Size in bytes - sizeof(type) or sizeof(expression)
//              co_await        Await asynchronous call - co_await expression
//              &               Address of - &lvalue
//              *               Dereference - *expression
//              new             Dynamic memory allocation - new type
//              new[]           Dynamic array allocation - new type[expression]
//              delete          Dynamic memory deletion - delete pointer
//              delete[]        Dynamic array deletion - delete[] pointer
// 4 L->R       ->*             Member pointer selector - object_pointer->*pointer_to_member
//              .*              Member object selector - object.*pointer_to_member
// 5 L->R       *               Multiplication - expression * expression
//              /               Division - expression / expression
//              %               Modulus - expression % expression
// 6 L->R       +               Addition - expression + expression
//              -               Subtraction - expression - expression
// 7 L->R       <<              Bitwise shift left - expression << expression
//              >>              Bitwise shift right - expression >> expression
// 8 L->R       <=>             Three-way comparison - expression <=> expression
// 9 L->R       <               Comparison less than - expression < expression
//              <=              Comparison less than or equals - expression <= expression
//              >               Comparison greater than - expression > expression
//              >=              Comparison greater than or equals - expression >= expression
// 10 L->R      ==              Equality - expression == expression
//              !=              Inequality - expression != expression
// 11 L->R      &               Bitwise AND - expression & expression
// 12 L->R      ^               Bitwise XOR - expression ^ expression
// 13 L->R      |               Bitwise OR - expression | expression
// 14 L->R      &&              Logical AND - expression && expression
// 15 L->R      ||              Logical OR - expression || expression
// 16 R->L      throw           Throw expression - throw expression
//              co_yield        Yield expression - co_yield expression
//              ?:              Conditional - expression ? expression : expression
//              =               Assignment - lvalue = expression
//              *=              Multiplication assignment - lvalue *= expression
//              /=              Division assignment - lvalue /= expression
//              %=              Modulus assignment - lvalue %= expression
//              +=              Addition assignment - lvalue += expression
//              -=              Subtraction assignment - lvalue -= expression
//              <<=             Bitwise shift left assignment - lvalue <<= expression
//              >>=             Bitwise shift right assignment - lvalue >>= expression
//              &=              Bitwise AND assignment - lvalue &= expression
//              |=              Bitwise OR assignment - lvalue |= expression
//              ^=              Bitwise XOR assignment - lvalue ^= expression
// 17 L->R      ,               Comma operator - expression, expression

// C++ doesn't include an operator to do exponentiaton

// Parenthesization - () - operator with one of the highest presedence levels
// Best practice is to use parentheses to make it clear how a non-trivial expression
// should evaluate, even if they are technically unnecessary. With some exceptions:
// x = (y + z + w); // instead of this
// x = y + z + w; // it's okay to do this
// x = ((y || z) && w); // instead of this
// x = (y || z) && w; // this
// x = (y *= z); // expressions with multiple assignment still benefit from parenthesis

// The order of evaluation of operand expressions and function arguments is mostly unspecifed.
// E.g. this program will produce an ambiguous result.
//#include <iostream>
//
//int getValue()
//{
//    std::cout << "Enter an integer: ";
//
//    int x { };
//    std::cint >> x;
//    return x;
//}
//
//int main()
//{
//    std::cout << getValue() + (getValue() * getValue());
//    return 0;
//}
// The compiler may choose a different order to evaluate the operand expressions
// in the compound expression.

// 5.2 - Arithmetic operators
// Unary: plus and minus
// Unary minus - multiplied by -1
// Unary plus - returns the value of the operand

// Integer and floating point division
// Think of the division operator as having 2 different "modes".
// If either or both of the operands are floating point values, the division operator
// performs floating point division. Otherwise - integer division.

// int x { 7 };
// int y { 4 };
// static_cast<double>(x) / y; // 1.75

// Dividing by zero - crash

// 5.3 - Modulus and Exponentiation
// Modulus - "remainder operator"
// 7 % 4 = 3
// 2 % 5 = 2
// -6 % 4 = -2 // Always returns the sign of LHS
// 6 % -4 = 2

// Exponent
// C++ does not include an exponent operator
// To do exponents:
// #include <cmath>
// double x { std::pow(3.0, 4.0) };
// The parameters and return value of pow() are of type double
// Due to rounding errors in floating point numbers, the results of powe() may not be
// precise (even if you pass it integers or whole numbers).
// For integer exponentiation, best off using your own function
// See powint_ex.cpp
// Warning: in the vast majority of cases, integer exponentiation will overflow the
// integral type. This is likely why such a function wasn't included in the std library
// in the first place

// 5.4 - Increment/decrement operators, and side effects
// Operator                                 Symbol  Form    Operation
// Prefix increment (pre-increment)         ++      ++x     Increment x, then return x
// Prefix decrement (pre-decrement)         --      --x     Decrement x, then return x
// Postfix increment (post-increment)       ++      x++     Copy x, then increment x, then return the copy
// Postfix decrement (post-decrement)       --      x--     Copy x, then decrement x, then return the copy

// With postfix, the operand is copied, then the operand itself (not the copy) is decremented.
// Then, the copy (not the original) is evaluated
//#include <iostream>
//
//int main()
//{
//    int x { 5 };
//    int y = x++; // x is incremented to 6; copy of the original x is evaluated to the value 5;
//                 // and 5 is assigned to y
//
//    std::cout << x << ' ' << y << '\n'; // Output: 6 5
//    return 0;
//}
// The postfix version takes a lot more steps, and thus may not be as performant as the
// prefix version
// Best practice is to strongly favor the prefix version

// Side effects
// A function or expression is said to have a side effect if it does anything that persists
// beyond the life of the function or expression itself.
// x = 5; // even after the statement has finished executing x will still have the value of 5
// ++x // the value of x is altered even after the statement has finished evaluating
// std::cout << x; // The outputing of x also has the side effect of modifying the state of
// the console

// However they can lead to unexpected results
//# include <iostream>
//
//int add(int x, int y)
//{
//    return x + y;
//}
//
//int main()
//{
//    int x { 5 };
//    int value { add(x, ++x) }; // 5 + 5 or 6 + 6?
//                               // Depends on what order the compiler evaluates the function
//                               // arguments in
//
//    std::cout << value << '\n'; // value could be 11 or 12
//    return 0;
//}
// The C++ standard does not define the order in which function arguments are evaluated
// In the example above, this is only a problem because one of the arguments to function
// add() has a side effect.

// The C++ standard does that intentionally, so that compilers can do whatever is most
// natural (and thus most performant) for a given architecture.

// In general problems can be all avoided by ensuring that any variable that has a
// side-effect applied is used no more than once in a given statement.

// 5.5 - Comma and conditional operators
// x, y - Evaluate x then y, return the value of y
//#include <iostream>
//
//int main()
//{
//    int x { 1 };
//    int y { 2 };
//
//    std::cout << (++x, ++y) << '\n'; // increment x and y, evaluates to the right operand
//
//    return 0;
//}
// Because of low precedence, these 2 lines do different things
// z = (a, b); // Evaluate (a, b) first to get result of b, then assign that value to variable z
// z = a, b; // z gets assigned the value of a, and b is evaluated and discarded. "(z = a), b"

// Best practice: avoid using the comma operator, except within for loops.

// Comma as a separator
// In C++, the comma symbol is often used as a separator, and these uses do not invoke the
// comma operator.

// Conditional operator
// c ? x : y - if c is nonzero (true) then evaluate x, otherwise evaluate y
// "arithmetic if"

// Parenthesization of the conditional operator.
// Common convetntion to put the conditional part of the operation inside the parameters.
// The other operands evaluate as if they were parenthesized, so explicit parenthesization
// is not required for those.
// ?: has very low precedence, so if doing anything other than assigning the result to a
// variable, the whole ?: operator needs to be wrapped in parentheses.
// E.g.
// std::cout << (x > y) ? x : y << '\n'; // -> (std::cout << (x > y)) ? x : y << '\n';
// std::cout << ((x > y) ? x : y ) << '\n';

// The conditional operator evaluates as an expression
// So the conditional operator can be used in some places where if/else can not.
// E.g. when initializing a constant variable
// constexpr int classSize { inBigClassRoom ? 30 : 20 };
// No satisfactory if/else statement for this
// the only way if using if/else, would be to pull the check into a separate function

// The type of the expressions must match or be convertible

// Best practice is to only use the conditional operator for simple conditionals where
// you use the result and where it enhances readability

// 5.6 - Relational operators and floating point comparisons
// The ones that let you compare 2 values. There are 6: >, <, >=, <=, ==, !=

// Comparison of calculated floating point values can be problematic
// E.g.
// double d1 { 100.0 - 99.99 };
// double d2 { 10.0 - 9.99 };
// d1 is not necessarily equal to d2, because of rounding errors
// But sometimes comparison can be ok, if that level of precision is not needed
// (e.g. collision calculation)
// Equality operators with floating points are much more troublesome. Should be avoided.
// The only exception is when the comparison is between low-precision literals or const or constexpr variables

// Comparing floating point numbers
// The most common method involves using a function that looks to see if 2 numbers are
// almost the same. The "close enough" value is traditionally called epsilon.
// Epsilon is generally defines as a small positive number (e.g. 0.00000001, or 1e-8)

// New developers will try to write it like this:
//#include <cmath> // for std::abs()
//
//// epsilon is an absolute value
//bool approximatelyEqualAbs(double a, double, b, double apsEpsilon)
//{
//    // if the distance between a and b is less than absEpsilon, then a and b are "close enough"
//    return std::abs(a - b) <= absEpsilon;
//}
// While this function can work, it's not great. An epsilon of 0.00001 is good for inputs
// around 1.0, too big for inputs around 0.00000001, and too small for inputs like
// 10,000
// This means taht every time we call this function, we have to pick an epsilon that's
// appropriate for our inputs.
// See equal_float.cpp

// 5.7 - Logical operators
// Logical NOT operator has a very high level of presedence.
// !x > y is not !(x > y)
// (x=5; y=7); (!x) > y -> 0 > y -> false

// Short circuit evaluation: if the first operand evaluates to false, logical AND knows it
// must return false regardless of whether the second operand evaluates to true or false.
// It will return immediately without evaluating the second operand
// if (x == 1 && ++y == 2) { ... }

// Only the built-in versions of these operators perform short-circuit evaluation. If you
// overload these operators to make them work with your own types, those overloaded operators
// will not perform short-circuit evaluation.

// When mixing ANDs and ORs, the best practice is to explicitly parenthesize each operation
// to ensure they evaluate how you intend.

// De Morgan's law
// !(x && y) -> !x || !y
// !(x || y) -> !x && !y

// Truth table

// Where's the logical exclusive or (XOR) operator?
// C++ doesn't provide a logical XOR operator. And unlike logical OR and logical AND,
// logical XOR cannot be short circuit evaluated. Because of this making a logical XOR
// operator out of logical OR and logical AND operators is challenging.
// However, you can easily mimic logical XOR using the inequality operator.
// if (a != b) { ... } // a XOR b, assuming a and b are bools
// if (a != b != c != d) { ... } // a XOR b XOR c XOR d
// If you need a form of logical XOR that works with non-bool operands, you can static
// cast them to bool:
// if (static_cast<bool>(a) != static_cast<bool>(b) != static_cast<bool>(c)) { ... }

// Alternatively, C++ supports a set of keywords for the operators that use words instead
// of symbols.
// Operator     Alternate keyword
// &&           and
// ||           or
// !            not
// E.g.: not a and (b or c)
// Recommended to use symbolic names though.
