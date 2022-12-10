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
