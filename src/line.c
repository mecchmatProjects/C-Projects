#include <stdio.h>
#include <stdlib.h>
#include <plane.h>
#include "line.h"
/*
*пересение плоскостей,что представляет собой прямую линию
*/
line intersectP(plane p1, plane p2) {
    //let x=0
    Dtype det = p1.b * p2.c - p2.b * p1.c;
    Dtype det_y = -p1.d * p2.c + p2.d * p1.c;
    Dtype det_z = -p1.b * p2.d + p2.b * p1.d;
    vector n1 = {p1.a, p1.b, p1.c};
    vector n2 = {p2.a, p2.b, p2.c};
    line res = {.x = {0, det_y / det, det_z / det}, .d = v_mult(n1, n2)};
    return res;
}

int line_equals(line l1, line l2) {
    if (vector_equals(l1.d, l2.d) && point_equals(l1.x, l2.x)) return 1;
    return 0;
}

void print_line(line s, Strtype res) {
    Strtype point = (Strtype) calloc(sizeof(char), 'a');
    print_point(s.x, point);
    Strtype vector = (Strtype) calloc(sizeof(char), 'a');
    print_vector(s.d, vector);
    sprintf(res, "Line(%s, %s)", point, vector);
}
