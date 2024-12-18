#ifndef WIND_H
#define WIND_H
#include <stdio.h>

// This is ordered in the right order for a game
// The player that plays after the EAST is always the SOUTH
typedef enum Wind { EAST, SOUTH, WEST, NORTH } Wind;

void wind_pp(FILE *file, Wind wind);

#endif // WIND_H
