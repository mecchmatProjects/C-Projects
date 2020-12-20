#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <math.h>
#define _CRT_SECURE_NO_WARNINGS
#define TRUE 1
#define FALSE 0
#ifndef MAIN_C_DATA_COMPARISON_FALENDYSH_H
#define MAIN_C_DATA_COMPARISON_FALENDYSH_H
struct res  //Первая структура для методов dist и corr
{
    size_t n;
    int* R1;
    int* R2;
};

struct res1  //Вторая структура для матрицы путаницы
{
    size_t n;
    int* R1;
    int* R2;
};

struct res2  //Третья структура для методов распределения
{
    size_t n;
    double* R1;
    double* R2;
    double* R1clone1;
    double* R2clone1;
    double* R1clone2;
    double* R2clone2;
};

struct res create();
struct res1 create1();
struct res2 create2();
struct res data_from_txt();
struct res1 data_from_txt1();
struct res2 data_from_txt2();
int dist(struct res Arrays);
int corr(struct res Arrays);
void TP(struct res1 Arrays1, FILE* file);
void TN(struct res1 Arrays1, FILE* file);
void FP(struct res1 Arrays1, FILE* file);
void FN(struct res1 Arrays1, FILE* file);
int TPR(struct res1 Arrays1);
int FPR(struct res1 Arrays1);
int ACC(struct res1 Arrays1);
int PPV(struct res1 Arrays1);
int NPV(struct res1 Arrays1);
int FNR(struct res1 Arrays1);
int FDR(struct res1 Arrays1);
int FOR(struct res1 Arrays1);
int F1(struct res1 Arrays1);
double func_distr(struct res2 Arrays2);
double func_loss(struct res2 Arrays2);
double dist_f(struct res2 Arrays2);
double loss(struct res2 Arrays2);
void dist_f_loss(struct res2 Arrays2, FILE* file);

#endif //MAIN_C_DATA_COMPARISON_FALENDYSH_H
