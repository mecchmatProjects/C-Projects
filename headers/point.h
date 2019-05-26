#ifndef GEOMETRY3D_POINT_H
#define GEOMETRY3D_POINT_H

#include "common.h"

struct point {
    Dtype x, y, z;
};

vector point_to_vector(point);

point vector_to_point(vector);

/*
 * возвращает точку пересечения плоскости с прямой
 */
point intersectPL(plane p1, line l1);

int point_equals(point, point);

void print_point(point, Strtype);

#endif //GEOMETRY3D_POINT_H
