#include <math.h>
#include "pyramid.h"
#include "pyramid_test.h"

int test_volume() {
    pyramid p = {{1, 2, 4},
                 {2, 3, 5},
                 {4, 1, 2},
                 {1, 3, 6}}; // V=0.5

    Dtype w = 0.5;
    Dtype res = pyr_volume(p);
    if (w == res) return 1;
    return 0;
}