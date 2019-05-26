#ifndef GEOMETRY3D_PLANE_H
#define GEOMETRY3D_PLANE_H

#include "common.h"

struct plane {
    Dtype a, b, c, d;
};

int plane_equals(plane p1, plane p2);

Strtype print_plane(plane s);

#endif //GEOMETRY3D_PLANE_H
