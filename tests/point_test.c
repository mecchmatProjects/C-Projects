#include "plane.h"
#include "line.h"
#include "point_test.h"

int test_intersect_plane_and_line() {
    plane test_plane1 = {3, 4, -2, 5};
    line test_line1 = {.d={4, 3, 6}, .x={1, 5, 2}};

    point w = {-7, -1, -10};
    point res = intersectPL(test_plane1, test_line1);
    return point_equals(res, w);
}

int test_intersect_plane_and_line_INF() {
    plane test_plane1 = {3, 4, -2, 5};
    line test_line1 = {.d={0, 1, 2}, .x={0, -0.5, 1.5}};

    point w = {INF, -INF, 0};
    point res = intersectPL(test_plane1, test_line1);
    return point_equals(res, w);
}
