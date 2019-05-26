#ifndef GEOMETRY3D_TRIANGLE_H
#define GEOMETRY3D_TRIANGLE_H

#include <math.h>
#include "segment.h"
#include "vector.h"
#include "plane.h"

struct triangle {
    point a, b, c;
};

Dtype triangle_perimeter(triangle t);
vector triangle_n_vector(triangle t);
Dtype triangle_area(triangle t);
plane triangle_plane(triangle t);

Strtype print_triangle(triangle s);

#endif //GEOMETRY3D_TRIANGLE_H
