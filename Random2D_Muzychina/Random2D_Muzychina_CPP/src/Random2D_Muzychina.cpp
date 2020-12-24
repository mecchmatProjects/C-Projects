/* File Random2D_Muzychina.cpp
Realization of Random2D class (32) (C++)
Done by Anna Muzychina (group comp. mat. 2)
Date 09.12.2020 */

#include "../headers/Random2D_Muzychina.h"


Random2D::Random2D() {
    generate_numbers_Random2D();
}

// Генератор чисел a, c, m, s0 удовлетворяющих условиям
void Random2D::generate_numbers_Random2D() {
    
    //m = INT_MAX;   \
    //c = 0;          > эталонные значения для генератора
    //a = 48271;     /

    NType k = 16 + rand() % 16;
    if (k == 31) {
        m = INT_MAX;
    } else { m = pow(2, k); }
    c = rand() % m;
    if (c % 2 == 0)
        c += 1;
    a = 4*(rand() % (m/4)) + 1;
    s0 = rand() % m;
    s_n = s0;
    
    //printf("m = %d, a = %d, c = %d, s0 = %d\n", m, a, c, s0);
}

// Следующий член последовательности s_n
NType Random2D::next_s_n_Random2D() {
    s_n = (a*s_n + c) % m;
    return s_n;
}

// Следующий член последовательности r_n
DType Random2D::next_r_n_Random2D() {
    r_n = (DType)(s_n + 1)/(m + 1);
    next_s_n_Random2D();
    return r_n;
}

// Сгенерировать целое число
IType Random2D::generate_integer_Random2D() {
    IType a = INT_MAX*(2*(0.5 - next_r_n_Random2D()));
    return a;
}

// Сгенерировать вещественное число
DType Random2D::generate_real_Random2D() {
    DType a = (DType)generate_integer_Random2D() - next_r_n_Random2D();
    return a;
}

// Сгенерировать вектор длины n (или длины 1000 если параметр n не указан)
vector<DType> Random2D::generate_vector_Random2D(NType n) {
    vector<DType> v;
    for (IType i = 0; i < n; i++)
        v.push_back(generate_real_Random2D());
    return v;
}

// Коэффициент корреляции двух векторов X и Y
DType Random2D::correlationCoefficient(vector<DType> X, vector<DType> Y, FILE* fout) {
    NType n = X.size();
    if (n != Y.size()) {
        cout << "Vectors have different dimensions" << endl;
        return 10;
    }
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
DType Random2D::sphere_volume_Monte_Carlo_Random2D(NType N, FILE* fout) {
    DType vol = 0;
    DType hit = 0;
    DType n_vol = pow(M_PI, N/2.0)/exp(lgamma(N/2.0 + 1.0));
    
    for (IType i = 0; i < 100000; i++) {
        DType r = 0;
        for (IType j = 0; j < N; j++) {
            DType x = 2*(next_r_n_Random2D() - 0.5);
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