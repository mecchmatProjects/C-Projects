#ifndef GEOMETRY3D_VECTOR_H
#define GEOMETRY3D_VECTOR_H

#include <math.h>
#include "common.h"

struct vector {
    Dtype x, y, z;
};

vector v_add(vector s1, vector s2);

vector v_sub(vector s1, vector s2);

Dtype v_multS(vector s1, vector s2);

vector v_mult(vector s1, vector s2);

Dtype vector_length(vector v);

vector v_scale(vector, Dtype);

int vector_equals(vector s1, vector s2);

void print_vector(vector, Strtype);

#endif //GEOMETRY3D_VECTOR_H
