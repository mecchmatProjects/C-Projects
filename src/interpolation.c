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

//================= LIBRARIES SECTION ==================

#include <malloc.h>
#include "interpolation.h"

//================ TASK FUNCTIONS SECTION ==============

// returns a and b as a 2-dimentional DVector
struct DVector Calculate(const struct Input_Data *inputData){
    // define result vector, which contains 2 coordinates
    // res.coordinates[0] - a
    // res.coordinates[1] - b
    // y = ax + b
    if (inputData->n <=0) {
        printf("Your dataset is empty, just like your head, dude.\n");
        struct DVector erroneous = {0, NULL};
        return erroneous;
    }

    struct DVector res = {2};
    res.coordinates = (floating_point *) calloc(2, sizeof(floating_point));

    // a
    floating_point a_numerator = 0;
    floating_point a_denominator = 0;
    floating_point buff;
    integer nn = inputData->n;
    for (integer i = 0; i < nn; ++i) {
        buff = nn * inputData->x->coordinates[i] - 1;
        a_numerator   += inputData->y->coordinates[i] * buff;
        a_denominator += inputData->x->coordinates[i] * buff;
    }
    res.coordinates[0] = a_numerator / a_denominator;

    // b
    floating_point b_numerator = 0;
    for (integer i = 0; i < nn; ++i) {
        b_numerator += inputData->y->coordinates[i];
        b_numerator -= inputData->x->coordinates[i] *
                       res.coordinates[0];
    }
    res.coordinates[1] = b_numerator / nn;

    return res;
}


struct DVector Interpolate(const struct Input_Data *inputData){
    // define result vector, which contains 2 coordinates
    // res.coordinates[0] - a
    // ....
    // res.coordinates[3] - d
    // y = ax^3+bx^2+cx+d

    if (inputData->n <= 0) {
        printf("Your dataset is empty, just like your head, dude.\n");
        struct DVector erroneous = {0, NULL};
        return erroneous;
    }

    floating_point **matrix = (floating_point **) malloc(sizeof(floating_point) * 16);
    for (int i = 0; i < 4; ++i) {
        matrix[i] = (floating_point *) malloc(sizeof(floating_point) * 4);
    }// matrix for finding a..d,
    // left side of linear system
    floating_point *vector = (floating_point *) malloc(sizeof(floating_point) * 4);
    for (integer i = 0; i < 4; ++i) {
        vector[0] = 0;
    }// vector-column in augmented matrix,
    // right side of linear system
    floating_point *sum_xn = (floating_point *) calloc(6, sizeof(floating_point));
    for (integer i = 0; i < 6; ++i) {
        sum_xn[i] = 0;
    }// sum of x^i from dataset, sum_xn[i] = sum of x^(i+1),
    // components of matrix on the left side of the linear system

    for (integer i = 0; i < inputData->n; ++i) {
        for (integer j = 0; j < 6; ++j) {
            sum_xn[j] += power(inputData->x->coordinates[i], j + 1);
        }

        for (integer j = 0; j < 4; ++j) {
            vector[j] += inputData->y->coordinates[i] *
                    power(inputData->x->coordinates[i], 3 - j);
        }
    }

    // define matrix for system
    // I really don't know how to that better
    matrix[0][0] = sum_xn[5];

    matrix[1][0] = sum_xn[4];
    matrix[0][1] = sum_xn[4];

    matrix[2][0] = sum_xn[3];
    matrix[1][1] = sum_xn[3];
    matrix[0][2] = sum_xn[3];

    matrix[3][0] = sum_xn[2];
    matrix[2][1] = sum_xn[2];
    matrix[1][2] = sum_xn[2];
    matrix[0][3] = sum_xn[2];

    matrix[3][1] = sum_xn[1];
    matrix[2][2] = sum_xn[1];
    matrix[1][3] = sum_xn[1];

    matrix[3][2] = sum_xn[0];
    matrix[2][3] = sum_xn[0];

    matrix[3][3] = inputData->n;

    // solve the system and get coefficients a..d
    struct DVector res = SolveLinSystem(matrix, vector, 4);

    free(vector);
    for (integer i = 0; i < 4; ++i) {
        free(matrix[i]);
    }
    free(matrix);

    return res;
}

floating_point power(floating_point x, integer n){
    floating_point res = 1;
    for (int i = 0; i < n; ++i) {
        res *= x;
    }

    return res;
}

floating_point fabs(floating_point x){
    if (x >= 0) {
        return x;
    } else {
        return -1 * x;
    }
}

struct DVector SolveLinSystem(floating_point** matrix,
                              floating_point *vector,
                              integer n){
    struct DVector res = {n};
    res.coordinates = (floating_point *) calloc(res.dim, sizeof(floating_point));

    Jacobi(res.dim, matrix, vector, res.coordinates);

    return res;
}

void Jacobi (integer n, floating_point** matrix, floating_point* f, floating_point* result)
{
    // n = dim(matrix) = dim(f); matrix[n][n] - left side, f[n] - right side vector-column,
    // result[n] - answer

    const floating_point eps = 0.1; // accuracy

    floating_point *TempX = (floating_point *) calloc(n, sizeof(floating_point));
    floating_point norm; // норма, определяемая как наибольшая разность компонент столбца иксов соседних итераций.

    do {
        for (integer i = 0; i < n; i++) {
            TempX[i] = f[i];
            for (integer g = 0; g < n; g++) {
                if (i != g)
                    TempX[i] -= matrix[i][g] * result[g];
            }
            TempX[i] /= matrix[i][i];
        }
        norm = fabs(result[0] - TempX[0]);
        for (int h = 0; h < n; h++) {
            if (fabs(result[h] - TempX[h]) > norm)
                norm = fabs(result[h] - TempX[h]);
            result[h] = TempX[h];
        }
    } while (norm > eps);
    free(TempX);
}

//================ INPUT SECTION ==============

integer input(Input_Data *inputData){
    printf("How many (x,y) pairs will be there?\n");
    printf("Please note:\n");
    printf("x is height (cm)\n");
    printf("y is weight (kg)\n");
    scanf("%i", &inputData->n);
    if (inputData->n <= 0) {
        printf("dataset length must be greater than 0\n");
        return 1;
    }
    if (inputData->x == NULL
        | inputData->y == NULL) {
        printf("you have not provided any containers for dataset in your program");
        printf("\nSegmentation fault\n");
        return 1;
    }

    inputData->x->dim = inputData->n;
    inputData->y->dim = inputData->n;
    inputData->x->coordinates =
            (floating_point *)
            calloc(inputData->x->dim, sizeof(floating_point));
    inputData->y->coordinates =
            (floating_point *)
            calloc(inputData->y->dim, sizeof(floating_point));
    for (integer i = 0; i < inputData->n; ++i) {
        printf("x[%i]=", i+1);
        scanf("%lf", &inputData->x->coordinates[i]);

        printf("y[%i]=", i+1);
        scanf("%lf", &inputData->y->coordinates[i]);
    }

    return 0;
}

integer inputTextFile(char *file, Input_Data *inputData) {
    // input file structure
    // dim
    //
    // x1...xn separated by \n
    //
    // y1...yn separated by \n

    file_t input_file = fopen(file, "r");
    if (!input_file) {
        printf("error opening text file");
        return 1;
    }
    fseek(input_file, 0, SEEK_SET);
    fscanf(input_file, "%i", &inputData->n);

    if (inputData->n <= 0) {
        printf("dataset length must be greater than 0\n");
        return 1;
    }
    if (inputData->x == NULL
        | inputData->y == NULL) {
        printf("you have not provided any containers for dataset in your program");
        printf("\nSegmentation fault\n");
        return 1;
    }

    inputData->x->dim = inputData->n;
    inputData->y->dim = inputData->n;
    inputData->x->coordinates =
            (floating_point *)
                    calloc(inputData->x->dim, sizeof(floating_point));
    inputData->y->coordinates =
            (floating_point *)
                    calloc(inputData->y->dim, sizeof(floating_point));

    fseek(input_file, 1, SEEK_CUR);

    for (int i = 0; i < inputData->n; ++i) {
        fseek(input_file, 1, SEEK_CUR);
        fscanf(input_file, "%lf", &inputData->x->coordinates[i]);
    }

    fseek(input_file, 1, SEEK_CUR);

    for (int i = 0; i < inputData->n; ++i) {
        fseek(input_file, 1, SEEK_CUR);
        fscanf(input_file, "%lf", &inputData->y->coordinates[i]);
    }

    fclose(input_file);

    return 0;
}

//=============== OUTPUT SECTION ==============

void output(DVector *result) {
    printf("y=");
    for (integer i = 0; i < result->dim - 2; ++i) {
        printf("%.2fx^%i+",
               result->coordinates[i],
               (integer) result->dim - i - 1);
    }
    printf("%.2fx+", result->coordinates[result->dim - 2]);
    printf("%.2f\n", result->coordinates[result->dim - 1]);
}

int outputBinaryFile(char *file, DVector *result){
    file_t fout = fopen(file, "wb");
    if (!file) {
        printf("error opening binary file\n");
        return 1;
    }
    fseek(fout, 0, SEEK_END);
    fwrite(result, sizeof(floating_point), result->dim, fout);
    fclose(fout);

    return 0;
}

int outputTextFile(char *file, DVector *result){
    file_t fout = fopen(file, "a");
    if (!fout) {
        printf("error opening text file\n");
        return 1;
    }

    fseek(fout, 0, SEEK_END);

    fprintf(fout, "y=");
    for (integer i = 0; i < result->dim - 2; ++i) {
        fprintf(fout, "%.2fx^%i+",
               result->coordinates[i],
               (integer) result->dim - i - 1);
    }
    fprintf(fout, "%.2fx+", result->coordinates[result->dim - 2]);
    fprintf(fout, "%.2f\n", result->coordinates[result->dim - 1]);

    fclose(fout);

    return 0;
}