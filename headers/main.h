#ifndef GEOMETRY3D_MAIN_H
#define GEOMETRY3D_MAIN_H

#include <vector_test.h>
#include <triangle_test.h>
#include <stdio.h>
#include <stdlib.h>
#include <line_test.h>
#include <point_test.h>
#include <pyramid_test.h>

int test() {
    {
        printf("Vector:\n");
        int res1 = test_add();
        int res2 = test_sub();
        int res3 = test_mult();
        int res4 = test_multS();
        char *res_str = (char *) calloc(sizeof(char), 'a');
        print_line((line) {{1, 2, 3},
                           {3, 2, 1}}, res_str);
        printf("%s\n", res_str);
        printf("Test 1 (add): %d\n"
               "Test 2 (sub): %d\n"
               "Test 3 (mult): %d\n"
               "Test 4 (multS): %d\n", res1, res2, res3, res4);
    }
    {
        printf("Triangle:\n");
        int res1 = test_n_vector();
        int res2 = test_perimeter();
        int res3 = test_area();
        int res4 = test_triangle_plane();
        printf("Test 1 (n_vector): %d\n"
               "Test 2 (perimeter): %d\n"
               "Test 3 (area): %d\n"
               "Test 4 (triangle_plane): %d\n", res1, res2, res3, res4);
    }
    {
        printf("Line:\n");
        int res1 = test_intersect_planes();
        int res2 = test_intersect_plane_and_line();
        int res3 = test_intersect_plane_and_line_INF();
        printf("Test 1 (intersection of planes): %d\n"
               "Test 2 (line and plane intersection): %d\n"
               "Test 3 (parallel line and plane intersection): %d\n", res1, res2, res3);
    }
    {
        printf("Pyramid:\n");
        int res1 = test_volume();
        printf("Test 1 (Volume test): %d\n", res1);
    }
    return 0;
}

#endif //GEOMETRY3D_MAIN_H
