#ifndef PP_H
#define PP_H
#include <stdio.h>

// This functions calls fprintf on any s that don't contains `%a`
//
// If s contains `%a` then the arguments `fppf` are waiting for (in this order)
// - the pretty printer of type `void (FILE*, void*)`
// - the element to printer with this pretty printer of type `void *`
//
// This model have the purpose to replicate the one from Ocaml `Format.printf`
void fppf(FILE *file, const char *s, ...);

#endif
