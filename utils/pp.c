#include <stdio.h>
#include <stdarg.h>

void fppf(FILE *file, const char *str, ...) {
    // initializing list pointer 
    va_list ptr; 
    va_start(ptr, str);
    int a = va_arg(ptr, int);
}
