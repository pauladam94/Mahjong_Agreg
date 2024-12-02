#include <stdbool.h>
#include <stdio.h>

void red() { printf("\033[1;31m"); }
void green() { printf("\033[1;32m"); }
void blue() {printf("\033[1;34m"); }
void purple() {printf("\033[1;35m"); }
void orange() { printf("\033[1;33m"); }
void reset() { printf("\033[0m"); }

void test(char *name, bool b) {
    if (b) {
        green();
        printf("[PASSED] %s\n", name);
        reset();
    } else {
        red();
        printf("[FAILED] %s\n", name);
        reset();
    }
}
