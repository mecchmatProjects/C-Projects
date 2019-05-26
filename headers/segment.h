#ifndef GEOMETRY3D_SEGMENT_H
#define GEOMETRY3D_SEGMENT_H

#include "point.h"
#include <math.h>

struct segment {
    point a, b;
};

Dtype segment_length(segment s);

Strtype print_segment(segment s);

#endif //GEOMETRY3D_SEGMENT_H
