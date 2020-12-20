#ifndef ABC
#define ABC
//Структура для методов dist() и corr().
struct res
{
    size_t n;
    int* R1;
    int* R2;
};
//Структруа для матрицы путаницы.
struct res1
{
    size_t n;
    bool* R1;
    bool* R2;
};
//Структура для методов распределения
struct res2
{
    size_t n;
    double* R1;
    double* R2;
    double* R1clone1;
    double* R2clone1;
    double* R1clone2;
    double* R2clone2;
};

res create();
res1 create1();
res2 create2();
res data_from_txt();
res1 data_from_txt1();
res2 data_from_txt2();
int dist(res Arrays);
int corr(res Arrays);
void TP(res1 Arrays1, FILE* file);
void TN(res1 Arrays1, FILE* file);
void FP(res1 Arrays1, FILE* file);
void FN(res1 Arrays1, FILE* file);
int TPR(res1 Arrays1);
int FPR(res1 Arrays1);
int ACC(res1 Arrays1);
int PPV(res1 Arrays1);
int NPV(res1 Arrays1);
int FNR(res1 Arrays1);
int FDR(res1 Arrays1);
int FOR(res1 Arrays1);
int F1(res1 Arrays1);
double func_distr(res2 Arrays2);
double func_loss(res2 Arrays2);
double dist_f(res2 Arrays2);
double loss(res2 Arrays2);
void distfloss(res2 Arrays2, FILE* file);

#endif
