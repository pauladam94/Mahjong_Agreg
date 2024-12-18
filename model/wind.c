#include "wind.h"

void wind_pp(FILE *file, Wind wind) {
    switch (wind) {
    case EAST:
        fprintf(file, "EAST");
    case SOUTH:
        fprintf(file, "SOUTH");
    case WEST:
        fprintf(file, "WEST");
    case NORTH:
        fprintf(file, "NORTH");
    }
}
