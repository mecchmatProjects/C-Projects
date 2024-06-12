/* Headers
 * Realization headers for matrix/vector structure functions
 * Done by Kostiukovych Stanislav, Statistics
 * Date 28.05.2019
 */

#ifndef DVECTOR_DMATRIX_KOSTIUKOVYCH_DMATRIX_H
#define DVECTOR_DMATRIX_KOSTIUKOVYCH_DMATRIX_H
#endif //DVECTOR_DMATRIX_KOSTIUKOVYCH_DMATRIX_H

#include <stdio.h>
#include <malloc.h>
#include <math.h>


// structs
typedef struct {
    int rows;
    int cols;
    double* data;
} matrix;


typedef struct {
    int n;
    double* data;
} vector;

// funcs to work with memory

vector * newVector(int num);
int deleteVector(vector * v);
matrix * newMatrix(int rows, int cols);
matrix * copyMatrix(matrix * mtx);
int deleteMatrix(matrix * mtx);

// working with matrix elements

#define ELEM(mtx, row, col) mtx->data[(col-1) * mtx->rows + (row-1)]
int setElement(matrix * mtx, int row, int col, double val);


// funcs to input/output

// vector
int inputVectorCoefficients(vector *vec, int size);
int inputVectorString(vector *vec, int size);
int inputVectorTextFile(vector* vec, int size, char*filename);
int inputVectorBinaryFile(vector* vec, int size, char*filename);

int outputVector(vector *vec);
int outputVectorTextFile(vector *vec, char *filename);
int outputVectorBinaryFile(vector *vec, char *filename);

// matrix
int inputMatrixString(matrix* A, int row, int col);
int inputMatrixCoefficients(matrix* A,int  n,int m);
int inputMatrixTextFile(matrix *mtx, int row, int col, char* filename);
int inputMatrixBinaryFile(matrix *mtx, int row, int col, char* filename);

int outputMatrixtoTextFile(matrix* mtx, char *filename);
int outputMatrixBinaryFile(matrix *mtx, char* filename);
int outputMatrix(matrix * mtx);

int getSizeMatrixTextFile(int* row, int* col, char* filename);
int getSizeVectorTextFile(int* size_read, char* filename);


// operations with structs

int equalVectors(vector *v1, vector *v2);
int equalMatrix(matrix *mtx1, matrix *mtx2);
int mulVector(vector * v1, vector * v2, double *prod);
int mulVectorDigit(vector * v, double digit);

int addMatrix(matrix * mtx1, matrix * mtx2, matrix * sum);
int subMatrix(matrix * mtx1, matrix * mtx2, matrix * sum);
int mulMatrix(matrix * mtx1, matrix * mtx2, matrix * prod);
int mulMatrixVector(matrix *mtx, vector*vec, vector * res);
int mulMatrixDigit(matrix * mtx, double digit);
int transpose(matrix * in);
int swap_columns(matrix * in, int col1, int col2);
int swap_rows(matrix * in, int row1, int row2);
double det(matrix * in);
int GetMinor(matrix *src,matrix *dest, int row, int col);
int inverse(matrix *in, matrix *out);
int combineMatrixVector(matrix *mtx, matrix *temp, vector* ans);
int solve(matrix *mtx, vector*ans);