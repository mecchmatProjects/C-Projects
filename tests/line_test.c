#include "line_test.h"

plane test_plane1 = {3, 4, -2, 5};
plane test_plane2 = {4, -3, 1, -3};

int test_intersect_planes() {
    line res = {.x = {0, -0.5, 1.5}, .d = {-2, -11, -25}};
    return line_equals(res, intersectP(test_plane1, test_plane2));
}
