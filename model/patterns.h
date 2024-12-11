#ifndef PATTERNS_H
#define PATTERNS_H
#include "pattern.h"

typedef struct Patterns Patterns;

void patterns_pp(FILE* file, const vec(Pattern *)patterns);
void patterns_add_first_group_pattern(vec(Pattern *)patterns, Pattern *pat);

void patterns_free(Patterns* free);

#endif // PATTERNS_H
