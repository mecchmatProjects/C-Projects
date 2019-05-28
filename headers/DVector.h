#define DVector_H
#pragma once

#include "common.h"

typedef struct DVectorTag
{
    UTYPE size;
    DTYPE *mas;

} DVector;

/**
 * @brief Add values in DVector x and DVector y, by the indices
 * 
 * @param x DVector
 * @param y DVector
 * @return DVector 
 */
extern DVector add_DVector(DVector x, DVector y);

/**
 * @brief Substitute values in DVector x and DVector y, by the indices
 * 
 * @param x DVector
 * @param y DVector
 * @return DVector 
 */
extern DVector sub_DVector(DVector x, DVector y);

/**
 * @brief Multiply values in DVector x and DVector y, by the indices
 * 
 * @param x DVector
 * @param y DVector
 * @return DVector 
 */
extern DVector mult_DVector(DVector x, DVector y);

/**
 * @brief Multiply every value in DVector x with DTYPE y 
 * 
 * @param x DVector
 * @param y DTYPE
 * @return DVector 
 */
extern DVector multConst_DVector(DVector x, DTYPE y);

/**
 * @brief Divide values in DVector x and DVector y, by the indices
 * 
 * @param x DVector
 * @param y DVector
 * @return DVector 
 */
extern DVector divide_DVector(DVector x, DVector y);

/**
 * @brief Divide every value in DVector x with DTYPE y 
 * 
 * @param x DVector
 * @param y DTYPE
 * @return DVector 
 */
extern DVector divideConst_DVector(DVector x, DTYPE y);

/**
 * @brief Do modulo division for values in DVector x and DVector y, by the indices
 * 
 * @param x DVector
 * @param y DVector
 * @return DVector 
 */
extern DVector mod_DVector(DVector x, DVector y);

/**
 * @brief Do modulo division for every value in DVector x with DTYPE y 
 * 
 * @param x DVector
 * @param y DTYPE
 * @return DVector 
 */
extern DVector modConst_DVector(DVector x, DTYPE y);

/**
 * @brief Change every value in DVector x by adding value in DVector y with the same index
 * 
 * @param x pointer to DVector
 * @param y Dvector
 * @return 0 if operation can not be executed, else 1
 */
extern ITYPE unadd_DVector(DVector *x, const DVector y);

/**
 * @brief Change every value in DVector x by substitute value in DVector y with the same index
 * 
 * @param x pointer to DVector
 * @param y Dvector
 * @return 0 if operation can not be executed, else 1
 */
extern ITYPE unsub_DVector(DVector *x, const DVector y);

/**
 * @brief Change every value in DVector x by multiply value in DVector y with the same index
 * 
 * @param x pointer to DVector
 * @param y Dvector
 * @return 0 if operation can not be executed, else 1
 */
extern ITYPE unmult_DVector(DVector *x, const DVector y);

/**
 * @brief Change every value in DVector x by division value in DVector y with the same index
 * 
 * @param x pointer to DVector
 * @param y Dvector
 * @return 0 if operation can not be executed, else 1
 */
extern ITYPE undivide_DVector(DVector *x, const DVector y);

/**
 * @brief Change every value in DVector x by modulo division value in DVector y with the same index
 * 
 * @param x pointer to DVector
 * @param y Dvector
 * @return 0 if operation can not be executed, else 1
 */
extern ITYPE unmod_DVector(DVector *x, const DVector y);

/**
 * @brief Fill given DVector x with input values 
 * 
 * @param x pointer to DVector x
 * @return size of x
 */
extern ITYPE input_DVector(DVector *x);

/**
 * @brief Write values of DVector x in the current output stream with given type, width and precision
 * 
 * @param x DVector
 * @param type 0 - common representation, 1 - exponential representation of values
 * @param width minimum amount of chars, that every value fill
 * @param precision level of exactness in the values 
 * @return size of x 
 */
extern ITYPE output_DVector(DVector x, ITYPE type, ITYPE width, ITYPE precision);

/**
 * @brief Fill given DVector x with values in the binary file 
 * 
 * @param file name of the file
 * @param x pointer to DVector x
 * @return size of x
 */
extern ITYPE inputBinaryFile_DVector(char *file, DVector *x);

/**
 * @brief Write values of DVector x in the binary file 
 * 
 * @param File path to the file
 * @param x DVector
 * @return size of x 
 */
extern ITYPE outputBinaryFile_DVector(char *File, DVector x);

/**
 * @brief Fill given DVector x with values in the text file 
 * 
 * @param file path to the file
 * @param x pointer to DVector x
 * @return size of x
 */
extern ITYPE inputTextFile_DVector(char *file, DVector *x);

/**
 * @brief Write values of DVector x in the text file with given type, width and precision 
 * 
 * @param File path to the file
 * @param x DVector
 * @param type 0 - common representation, 1 - exponential representation of values
 * @param width minimum amount of chars, that every value fill
 * @param precision level of exactness in the values 
 * @return size of x 
 */
extern ITYPE outputTextFile_DVector(char *File, DVector x, ITYPE type, ITYPE width, ITYPE precision);

/**
 * @brief Generate DVector with size n
 * 
 * @param n size of DVector
 * @return DVector 
 */
extern DVector generate_DVector(UTYPE n);