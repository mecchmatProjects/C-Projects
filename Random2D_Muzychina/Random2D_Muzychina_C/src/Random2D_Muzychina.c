/* File Random2D_Muzychina.c
Realization of Random2D functions (32) (C)
Done by Anna Muzychina (group comp. mat. 2)
Date 09.12.2020 */

#include "../headers/Random2D_Muzychina.h"


// Генератор чисел a, c, m, s0 удовлетворяющих условиям
void generate_numbers_Random2D(Random2D* self) {
    
    //m = INT_MAX;   \
    //c = 0;          > эталонные значения для генератора
    //a = 48271;     /

    NType k = 16 + rand() % 16;
    if (k == 31) {
        self->m = INT_MAX;
    } else { self->m = pow(2, k); }
    self->c = rand() % self->m;
    if (self->c % 2 == 0)
        self->c += 1;
    self->a = 4*(rand() % (self->m/4)) + 1;
    self->s0 = rand() % self->m;
    self->s_n = self->s0;
    
    //printf("m = %d, a = %d, c = %d, s0 = %d\n", self->m, self->a, self->c, self->s0);
}

// Следующий член последовательности s_n
NType next_s_n_Random2D(Random2D* self) {
    self->s_n = (self->a*self->s_n + self->c) % self->m;
    return self->s_n;
}

// Следующий член последовательности r_n
DType next_r_n_Random2D(Random2D* self) {
    self->r_n = (DType)(self->s_n + 1)/(self->m + 1);
    next_s_n_Random2D(self);
    return self->r_n;
}

// Сгенерировать целое число
IType generate_integer_Random2D(Random2D* self) {
    IType a = INT_MAX*(2*(0.5 - next_r_n_Random2D(self)));
    return a;
}

// Сгенерировать вещественное число
DType generate_real_Random2D(Random2D* self) {
    DType a = (DType)generate_integer_Random2D(self) - next_r_n_Random2D(self);
    return a;
}

// Сгенерировать вектор длины n
DType* generate_vector_Random2D(Random2D* self, NType n) {
    DType* v = (DType*) malloc(n * sizeof *v);
    for (IType i = 0; i < n; i++)
        v[i] = generate_real_Random2D(self);
    return v;
}

// Коэффициент корреляции двух векторов X и Y размерности n
DType correlationCoefficient(DType* X, DType* Y, NType n, FILE* fout) {
    DType sum_X = 0, sum_Y = 0, sum_XY = 0;
    DType squareSum_X = 0, squareSum_Y = 0;

    for (IType i = 0; i < n; i++) {
        sum_X = sum_X + X[i];
        sum_Y = sum_Y + Y[i];
        sum_XY = sum_XY + X[i] * Y[i];
        squareSum_X = squareSum_X + X[i] * X[i];
        squareSum_Y = squareSum_Y + Y[i] * Y[i];
    }

    DType corr = (DType)(n*sum_XY - sum_X*sum_Y)/sqrt((n*squareSum_X - sum_X*sum_X)*(n*squareSum_Y - sum_Y*sum_Y));
    printf("Correlation coefficient of %u-dimensional vectors = %.1lf\n", n, corr);
    if (fout)
        fprintf(fout, "Correlation coefficient of %u-dimensional vectors = %.1lf\n", n, corr);
    return corr;
}

// Объем n-мерной сферы методом Монте Карло
DType sphere_volume_Monte_Carlo_Random2D(Random2D* self, NType N, FILE* fout) {
    DType vol = 0;
    DType hit = 0;
    DType n_vol = pow(M_PI, N/2.0)/exp(lgamma(N/2.0 + 1.0));

    
    for (IType i = 0; i < 100000; i++) {
        DType r = 0;
        for (IType j = 0; j < N; j++) {
            DType x = 2*(next_r_n_Random2D(self) - 0.5);
            r += x*x;
        }
        if (sqrt(r) < 1)
            hit += 1;
    }
    
    vol = (pow(2, N)*hit)/100000;
    printf("Volume of a %u-sphere: %lf\n", N, vol);
    printf("Actual volume: %lf\n", n_vol);
    printf("Fractional error: %lf\n", fabs(n_vol - vol));
    if (fout) {
        fprintf(fout, "Volume of a %u-sphere: %lf\n", N, vol);
        fprintf(fout, "Actual volume: %lf\n", n_vol);
        fprintf(fout, "Fractional error: %lf\n", fabs(n_vol - vol));
    }
    return vol;
}

void print_integer_Random2D(FILE* fout, const char* text, int num) {
    printf(text, num);
    fprintf(fout, text, num);
}

void print_double_Random2D(FILE* fout, const char* text, double num) {
    printf(text, num);
    fprintf(fout, text, num);
}
