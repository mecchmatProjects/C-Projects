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

class Project{
public:
    DVector x, y;
    Input_Data inputData;
    DVector ans_linear;
    DVector ans_cubic;
    Project(){
        inputData.n = 0;
        inputData.x = &x;
        inputData.y = &y;
        }
    

    struct DVector Calculate();

    struct DVector Interpolate();

    DType power(DType x, IType n);
    DType fabs(DType x);
    void Jacobi(IType n, DType **matrix,DType *f, DType *result);
    struct DVector SolveLinSystem(DType** matrix, DType *vector, IType n);

    IType input();
    IType inputTextFile(char *file);

    void output (DVector *result);
    IType outputBinaryFile(char *file, DVector *result);
    IType outputTextFile(char *file, DVector *result);
};
#endif
