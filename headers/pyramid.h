#ifndef GEOMETRY3D_PYRAMID_H
#define GEOMETRY3D_PYRAMID_H

#include "point.h"

struct pyramid {
    point a, b, c, d;
};

enum area_index {
    ABD, ACD, BCD, ABC
};

Dtype pyr_volume(pyramid p);

Dtype pyr_area_side(pyramid p, a_i a);

Dtype pyr_full_area(pyramid p);

pyramid intersect_pyr_by_plane();

Strtype print_pyramid(pyramid s);

#endif //GEOMETRY3D_PYRAMID_H
