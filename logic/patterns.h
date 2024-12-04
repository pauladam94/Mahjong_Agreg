#ifndef PATTERNS_H
#define PATTERNS_H
#include "pattern.h"

typedef struct Patterns Patterns;

Patterns *patterns_empty(void);
Pattern *patterns_pop(Patterns *patterns);
int patterns_size(const Patterns *patterns);

void patterns_pp(FILE* file, const Patterns *patterns);
void patterns_add_pattern(Patterns *patterns, Pattern *pat);
void patterns_add_first_group_pattern(Patterns *patterns, Pattern *pat);

void patterns_free(Patterns* free);

#endif // PATTERNS_H
