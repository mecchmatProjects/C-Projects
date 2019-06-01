//
// Created by olga on 10.05.19.
//

#include "interpolation.h"
#include <stdio.h>
#include <malloc.h>

int main(){

    struct Input_Data inp;
    inp.n = 2;
    struct DVector x1, y1;

    x1.dim = 2;
    x1.coordinates = calloc(x1.dim, sizeof(floating_point));
    x1.coordinates[0] = 0;
    x1.coordinates[1] = 1;

    y1.dim = 2;
    y1.coordinates = calloc(y1.dim, sizeof(floating_point));
    y1.coordinates[0] = 2;
    y1.coordinates[1] = 3;

    inp.x = &x1;
    inp.y = &y1;

    struct DVector v1;
    v1 = Calculate(&inp);
    printf("%zu", v1.dim);

    free(x1.coordinates);
    free(y1.coordinates);
    free(v1.coordinates);

    return 0;
}