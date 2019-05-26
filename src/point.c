#include <stdio.h>
#include <plane.h>
#include <line.h>
#include "point.h"

int point_equals(point p1, point p2) {
    if (p1.x == p2.x && p1.y == p2.y && p1.z == p2.z) return 1;
    return 0;
}
/*
 * точка пересечения линии с плоскостью
 */
point intersectPL(plane p1, line l1) {
    vector p0 = {0, 0, -p1.d / p1.c};
    vector n = {p1.a, p1.b, p1.c};
    Dtype mS_d_n = v_multS(l1.d, n); // scalar mult of vectors d and n
    Dtype mS_diff_n = v_multS(v_sub(p0, point_to_vector(l1.x)), n); // scalar mult of vectors (p0-x) and n
    if (mS_d_n == 0) {
        if (mS_diff_n == 0) return (point) {INF, -INF, 0}; // прямая, параллельная плоскости
        else return (point) {INF, INF, INF}; // прямая, лежащая на плоскости
    }
    Dtype d = mS_diff_n / mS_d_n;
    point res = vector_to_point(v_add(v_scale(l1.d, d), point_to_vector(l1.x)));
    return res;
}

vector point_to_vector(point p) {
    return (vector) {p.x, p.y, p.z};
}

point vector_to_point(vector p) {
    return (point) {p.x, p.y, p.z};
}

void print_point(point s, Strtype res) {
    sprintf(res, "Point(%e, %e, %e)", s.x, s.y, s.z);
}
