#include "error.h"
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>

void red() { printf("\033[1;31m"); }
void green() { printf("\033[1;32m"); }
void blue() { printf("\033[1;34m"); }
void purple() { printf("\033[1;35m"); }
void orange() { printf("\033[1;33m"); }
void reset() { printf("\033[0m"); }

void test(bool b, char *name, ...) {
    va_list args; // To handle the variable argument list

    va_start(args, name);
    if (b) {
        green();
        printf("[PASSED] ");
        vprintf(name, args); // Use vprintf to print the formatted string
        printf("\n");
        reset();
    } else {
        red();
        printf("[FAILED] ");
        vprintf(name, args); // Use vprintf to print the formatted string
        printf("\n");
        reset();
    }
    va_end(args);
}
