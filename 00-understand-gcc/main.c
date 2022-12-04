#include <stdio.h>

int main(void) {
    printf("hello world\n");
}

/* GCC Compilation Steps:
 * 1) Preprocessing
 *      gcc -E -o main_exp.c main.c -> main_exp.c - strip comments, etc.
 * 2) Compilation
 *      gcc -S main_exp.c -> main_exp.s - Semantic analysis, etc. into assembly
 * 3) Assembly
 *      gcc -c main_exp.s -> main_exp.o - binary from the assembly
 * 4) Linking 
 *      gcc -o main main_exp.s -> main - link with other binaries and included libraries and create an executable
 * */
