#ifndef GEOMETRY3D_LINE_H
#define GEOMETRY3D_LINE_H

#include "common.h"
#include "vector.h"
#include "point.h"

struct line {
    vector d; // line direction
    point x; // line point
};

/*
 * возвращает линию пересечения двух плоскостей
 */
line intersectP(plane p1, plane p2);

int line_equals(line, line);

void print_line(line s, Strtype);

#endif //GEOMETRY3D_LINE_H
