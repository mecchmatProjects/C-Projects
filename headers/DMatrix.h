#define DMatrix_H
#pragma once

#include "common.h"
#include "../src/DVector.c"

typedef struct DMatrixTag
{
	UTYPE rows;
	UTYPE columns;
	DTYPE **mas;
} DMatrix;

/**
 * @brief Add values in DMatrix x and DMatrix y, by the indices
 * 
 * @param x DMatrix
 * @param y DMatrix
 * @return DMatrix 
 */
extern DMatrix add_DMatrix(DMatrix x, DMatrix y);

/**
 * @brief Substitute values in DMatrix x and DMatrix y, by the indices
 * 
 * @param x DMatrix
 * @param y DMatrix
 * @return DMatrix 
 */
extern DMatrix sub_DMatrix(DMatrix x, DMatrix y);

/**
 * @brief Multiply values in DMatrix x and DMatrix y, by the indices
 * 
 * @param x DMatrix
 * @param y DMatrix
 * @return DMatrix 
 */
extern DMatrix mult_DMatrix(DMatrix x, DMatrix y);

/**
 * @brief Multiply every value in DMatrix x with DTYPE y 
 * 
 * @param x DMatrix
 * @param y DTYPE
 * @return DMatrix 
 */
extern DMatrix multConst_DMatrix(DMatrix x, DTYPE y);

/**
 * @brief Divide values in DMatrix x and DMatrix y, by the indices
 * 
 * @param x DMatrix
 * @param y DMatrix
 * @return DMatrix 
 */
extern DMatrix divide_DMatrix(DMatrix x, DMatrix y);

/**
 * @brief Divide every value in DMatrix x with DTYPE y 
 * 
 * @param x DMatrix
 * @param y DTYPE
 * @return DMatrix 
 */
extern DMatrix divideConst_DMatrix(DMatrix x, DTYPE y);

/**
 * @brief Do modulo division for values in DMatrix x and DMatrix y, by the indices
 * 
 * @param x DMatrix
 * @param y DMatrix
 * @return DMatrix 
 */
extern DMatrix mod_DMatrix(DMatrix x, DMatrix y);

/**
 * @brief Do modulo division for every value in DMatrix x with DTYPE y 
 * 
 * @param x DMatrix
 * @param y DTYPE
 * @return DMatrix 
 */
extern DMatrix modConst_DMatrix(DMatrix x, DTYPE y);

/**
 * @brief Change every value in DMatrix x by adding value in DMatrix y with the same index
 * 
 * @param x pointer to DMatrix
 * @param y DMatrix
 * @return 0 if operation can not be executed, else 1
 */
extern ITYPE unadd_DMatrix(DMatrix *x, const DMatrix y);

/**
 * @brief Change every value in DMatrix x by substitute value in DMatrix y with the same index
 * 
 * @param x pointer to DMatrix
 * @param y DMatrix
 * @return 0 if operation can not be executed, else 1
 */
extern ITYPE unsub_DMatrix(DMatrix *x, const DMatrix y);

/**
 * @brief Change every value in DMatrix x by multiply value in DMatrix y with the same index
 * 
 * @param x pointer to DMatrix
 * @param y DMatrix
 * @return 0 if operation can not be executed, else 1
 */
extern ITYPE unmult_DMatrix(DMatrix *x, const DMatrix y);

/**
 * @brief Change every value in DMatrix x by division value in DMatrix y with the same index
 * 
 * @param x pointer to DMatrix
 * @param y DMatrix
 * @return 0 if operation can not be executed, else 1
 */
extern ITYPE undivide_DMatrix(DMatrix *x, const DMatrix y);

/**
 * @brief Change every value in DMatrix x by modulo division value in DMatrix y with the same index
 * 
 * @param x pointer to DMatrix
 * @param y DMatrix
 * @return 0 if operation can not be executed, else 1
 */
extern ITYPE unmod_DMatrix(DMatrix *x, const DMatrix y);

/**
 * @brief Calculate determinant of x
 * 
 * @param x DMatrix
 * @return determinant
 */
extern DTYPE det_DMatrix(DMatrix x);

/**
 * @brief Calculate inverse matrix of x
 * 
 * @param x DMatrix
 * @return inverse DMatrix 
 */
extern DMatrix inverse_DMatrix(DMatrix x);

/**
 * @brief Multiply matrix on vector, by the algebra rule 
 * 
 * @param x DMatrix
 * @param y DVector
 * @return DVector 
 */
extern DVector solve_DMatrix(DMatrix x, DVector y);

/**
 * @brief Swap rows in matrix x 
 * 
 * @param x pointer to the matrix
 * @param i number of first row
 * @param j number of second row
 * @return is operation successfully finished
 */
extern ITYPE swap_row_DMatrix(DMatrix *x, UTYPE i, UTYPE j);

/**
 * @brief Swap columns in matrix x 
 * 
 * @param x pointer to the matrix
 * @param i number of first column
 * @param j number of second column
 * @return is operation successfully finished
 */
extern ITYPE swap_column_DMatrix(DMatrix *x, UTYPE i, UTYPE j);

/**
 * @brief Fill given DMatrix x with input values 
 * 
 * @param x pointer to DMatrix x
 * @return size of x
 */
extern ITYPE input_DMatrix(DMatrix *x);

/**
 * @brief Write values of DMatrix x in the current output stream with given type, width and precision
 * 
 * @param x DMatrix
 * @param type 0 - common representation, 1 - exponential representation of values
 * @param width minimum amount of chars, that every value fill
 * @param precision level of exactness in the values 
 * @return size of x 
 */
extern ITYPE output_DMatrix(DMatrix x, ITYPE type, ITYPE width, ITYPE precision);

/**
 * @brief Fill given DMatrix x with values in the binary file 
 * 
 * @param file name of the file
 * @param x pointer to DMatrix x
 * @return size of x
 */
extern ITYPE inputBinaryFile_DMatrix(char *file, DMatrix *x);

/**
 * @brief Write values of DMatrix x in the binary file 
 * 
 * @param File path to the file
 * @param x DMatrix
 * @return size of x 
 */
extern ITYPE outputBinaryFile_DMatrix(char *File, DMatrix x);

/**
 * @brief Fill given DMatrix x with values in the text file 
 * 
 * @param file path to the file
 * @param x pointer to DMatrix x
 * @return size of x
 */
extern ITYPE inputTextFile_DMatrix(char *file, DMatrix *x);

/**
 * @brief Write values of DMatrix x in the text file with given type, width and precision 
 * 
 * @param File path to the file
 * @param x DMatrix
 * @param type 0 - common representation, 1 - exponential representation of values
 * @param width minimum amount of chars, that every value fill
 * @param precision level of exactness in the values 
 * @return size of x 
 */
extern ITYPE outputTextFile_DMatrix(char *File, DMatrix x, ITYPE type, ITYPE width, ITYPE precision);

/**
 * @brief Generate DMatrix with size n*m
 * 
 * @param n number of rows
 * @param m number of columns
 * @return DMatrix 
 */
extern DMatrix generate_DMatrix(UTYPE n, UTYPE m);