/* File Random2D_Muzychina.h
Realization of Random2D class (32) (C++)
Done by Anna Muzychina (group comp. mat. 2)
Date 09.12.2020 */

#ifndef __RANDOM2D_CPP__
#define __RANDOM2D_CPP__

#include <cmath>
#include <ctime>
#include <vector>
#include <string>
#include <fstream>
#include <climits>
#include <iostream>
#include "../headers/common.h"

using namespace std;


class Random2D {

    NType a, c, m, s0, s_n;
    DType r_n;

public:

    Random2D();

    void generate_numbers_Random2D();

    NType next_s_n_Random2D();

    DType next_r_n_Random2D();

    IType generate_integer_Random2D();

    DType generate_real_Random2D();

    vector<DType> generate_vector_Random2D(NType n=1000);

    DType correlationCoefficient(vector<DType> X, vector<DType> Y, FILE* fout=0);

    DType sphere_volume_Monte_Carlo_Random2D(NType N=3, FILE* fout=0);

    template<typename T>
    void print_Random2D(FILE* fout, const char* text, T num) {
        printf(text, num);
        fprintf(fout, text, num);
    }
};

#endif