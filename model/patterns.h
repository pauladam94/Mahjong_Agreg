#ifndef PATTERNS_H
#define PATTERNS_H
#include "pattern.h"

void patterns_pp(FILE *file, const vec(Pattern *) patterns);
void patterns_add_first_group_pattern(vec(Pattern *) patterns, Pattern *pat);

void patterns_free(vec(Pattern *) patterns);

#endif // PATTERNS_H
