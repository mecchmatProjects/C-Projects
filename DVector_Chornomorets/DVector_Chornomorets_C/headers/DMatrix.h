#ifndef CHORNOMORETS_DMATRIX_C
#define CHORNOMORETS_DMATRIX_C

/* Base structure of matrix of floats*/
typedef struct {
    Ntype n;
    Ntype m;
    Dtype *items;
}DMatrix;

#endif
