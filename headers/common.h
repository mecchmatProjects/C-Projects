#ifndef __COMMON__
#define __COMMON__

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>

#include <string.h>

typedef double DType; /* Double real type for application */

typedef int IType;    /* Integer type for application */

typedef unsigned NType; /* Unsigned type for application */

//TODO: v.b.: correct it with limits and float
#define EQ_EPS 0.000001 // epsilon : precision of arithmetic

#define MAX(a,b)       (a)>(b)?(a):(b)
#define MIN(a,b)       (a)<(b)?(a):(b)

#define  PD_EQL(a,b)   fabs((a)-(b)) < EQ_EPS


/* Basic types definitions */

/* Point type as vector of two reals */
typedef struct DPoint_
{
    union  //classical and vector representation
    {
        struct
        {
            DType x;
            DType y;
        };
        DType ptr[2];
    };
} DPoint;


typedef struct DLine_
{
    DType x1;
    DType x2;
    DType dx;
} DLine;


// real function R^1 -> R^1
//typedef DType R1R_Func (DType);
typedef DType (*R1RFunc)(DType);



//void* memzero(void* ptr, size_t n)
//{
//    memset(ptr, 0, n);
//}

#endif /* __COMMON__ end */