#include "align.h"

float align_rotation(Align align) {
    switch (align) {
    case DOWN:
        return 0.;
    case RIGHT:
        return -90.;
    case UP:
        return 180.;
    case LEFT:
        return 90.;
    }
}
