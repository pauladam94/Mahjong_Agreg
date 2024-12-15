#ifndef PATTERNS_H
#define PATTERNS_H
#include "pattern.h"

void patterns_pp(FILE *file, vec(Pattern *) const patterns);
vec(Pattern *) patterns_first_group_pattern(Pattern *pat);
void patterns_free(vec(Pattern *) * patterns);

#endif // PATTERNS_H
