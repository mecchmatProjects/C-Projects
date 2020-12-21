/* File Random2D_Muzychina.h
Realization of Random2D functions (32) (C)
Done by Anna Muzychina (group comp. mat. 2)
Date 09.12.2020 */

#ifndef __RANDOM2D_C__
#define __RANDOM2D_C__

#include <math.h>
#include <time.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include "../headers/common.h"


typedef struct Random2D {

    NType a, c, m, s0, s_n;
    DType r_n;

}Random2D;

void generate_numbers_Random2D(Random2D* self);

NType next_s_n_Random2D(Random2D* self);

DType next_r_n_Random2D(Random2D* self);

IType generate_integer_Random2D(Random2D* self);

DType generate_real_Random2D(Random2D* self);

DType* generate_vector_Random2D(Random2D* self, NType n);

DType correlationCoefficient(DType* X, DType* Y, NType n, FILE* fout);

DType sphere_volume_Monte_Carlo_Random2D(Random2D* self, NType N, FILE* fout);

void print_integer_Random2D(FILE* fout, const char* text, int num);

void print_double_Random2D(FILE* fout, const char* text, double num);

#endif
