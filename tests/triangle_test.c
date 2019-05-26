#include "triangle_test.h"

triangle test_triangle1 = {.a={2, 1, 3}, .b={4, 1, 2}, .c={6, 7, 3}};
triangle test_triangle2 = {.a={2, 1, 3}, .b={5, 1, 7}, .c={4, 2, 5}};

int test_n_vector() {
    vector res = triangle_n_vector(test_triangle1);
    vector w = {6, -4, 12};
    if (vector_equals(res, w)) return 1;
    return 0;
}

int test_perimeter() {
    Dtype res = triangle_perimeter(test_triangle2);
    if (res > 10 && res < 11) return 1;
    return 0;
}

int test_area() {
    Dtype res = triangle_area(test_triangle1);
    if (res == 7) return 1;
    return 0;
}

int test_triangle_plane() {
    plane res = triangle_plane(test_triangle1);
    plane w = {6, -4, 12, -44};
    return plane_equals(res, w);
}


