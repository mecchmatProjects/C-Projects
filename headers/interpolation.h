//
// Created by olga on 23.04.19.
//
// Olga Moskanova
// statistics, 2 year
//
// olyushkam@gmail.com
// https://github.com/gamble27
//
// this project can also be found here:
// https://github.com/gamble27/c_interpolation
//

#ifndef INTERPOLATION_MOSKANOVA_INTERPOLATION_H
#define INTERPOLATION_MOSKANOVA_INTERPOLATION_H

#define integer int
#define floating_point float
#define character char
#define file_t FILE*

#include <lzma.h> // get size_t thing

//================ STRUCTURES DEFINITION SECTION  ==============


struct DVector{
    size_t dim;
    floating_point *coordinates;
};
typedef struct DVector DVector;


struct Input_Data{
    int n; // length of arrays.
    // x is height (cm)
    // y is weight (kg)
    struct DVector *x, *y;
};
typedef struct Input_Data Input_Data;

//================ TASK FUNCTIONS SECTION ==============

// Calculates a,b and returns result as a DVector
// .coordinates[0] = a
// .coordinates[1] = b
struct DVector Calculate(const struct Input_Data *inputData);

// Interpolation for a non-linear (Cube) polynome
// result is still a vector (dim = 4)
// polynome(x) = (sum, i from 0 to 3) result[3-i]*x^i :]
struct DVector Interpolate(const struct Input_Data *inputData);

//================ INPUT SECTION ==============

integer input          (Input_Data *inputData);
integer inputTextFile  (char *file, Input_Data *inputData);

// input text file structure
// dim
//
// x1...xn separated by \n
//
// y1...yn separated by \n

//================ OUTPUT SECTION ==============

// int ones for exit code
void     output          (DVector *result);
integer  outputBinaryFile(char *file, DVector *result);
integer  outputTextFile  (char *file, DVector *result);

#endif //INTERPOLATION_MOSKANOVA_INTERPOLATION_H
