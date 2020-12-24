#ifndef C_PROJECT_INTERPOLATION_H
#define C_PROJECT_INTERPOLATION_H

#include <glob.h>

#define IType int
#define DType double
#define character char
#define file_t FILE*

struct DVector{
    size_t dim;
    DType *coordinates;
};
typedef struct DVector DVector;


struct Input_Data{
    int n;
    struct DVector *x, *y;
};
typedef struct Input_Data Input_Data;

struct DVector Calculate(const struct Input_Data *inputData);

struct DVector Interpolate(const struct Input_Data *inputData);

DType power(DType x, IType n);
DType fabs(DType x);
void Jacobi(IType n, DType **matrix, DType *f, DType *result);
DVector SolveLinSystem(DType** matrix, DType *vector, IType n);

IType input(Input_Data *inputData);
IType inputTextFile(char *file, Input_Data *inputData);

void output (DVector *result);
IType outputBinaryFile(char *file, DVector *result);
IType outputTextFile(char *file, DVector *result);

#endif
