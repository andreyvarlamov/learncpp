int main()
{
    return 0;
}

// 6.1 - Compound statements (blocks)
// A compound statement (also called a block, or block statement) is a group of zero or
// more statements that is treated by the compiler as if it were a single statement.
// Blocks begin with a {, and end with a }
// Blocks can be used anywhere a signle statement is allowed.
// Function body is a block.

// Blocks inside other blocks
// Although functions can't be nested inside other functions, blocks can be nested inside
// other blocks.
//int main()
//{ // outer block
//    // multiple statements
//    int value {};
//
//    { // inner/nested block
//        add(3, 4);
//    } // end inner/nested block
//
//    return 0;
//} // end outer block

// Using blocks to execute multiple statements conditionally.
// By default, an if statement executes a single statement if the condition evaluates to
// true. However, we can replace this single statement with a block of statements if we
// want multiple statements to execute when the condition evaluates to true.
// E.g.
//if (check_value)
//    do_thing();
// VVV
//if (check_value)
//{
//    do_thing_1();
//    do_thing_2();
//}

// Block nesting levels; (nesting depth)
// The C++ standard says that C++ compilers should support 256 levels of nesting --
// however, not all do (e.g. Visual Studio supports less).

// Best practice is to keep the nesting level of your functions to 3 or less
