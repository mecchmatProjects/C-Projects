#include <stdlib.h>
#include <stdio.h>
#include "../headers/interpolation_tyshchenko.h"

DVector Calculate(const struct Input_Data *inputData){
    if (inputData->n <=0) {
        printf("Your dataset is empty.\n");
        struct DVector erroneous = {0, NULL};
        return erroneous;
    }

    struct DVector res = {2};
    res.coordinates = (DType *) calloc(2, sizeof(DType));

    DType a_numerator = 0;
    DType a_denominator = 0;
    DType buff;
    IType nn = inputData->n;
    for (IType i = 0; i < nn; ++i) {
        buff = nn * inputData->x->coordinates[i] - 1;
        a_numerator   += inputData->y->coordinates[i] * buff;
        a_denominator += inputData->x->coordinates[i] * buff;
    }
    res.coordinates[0] = a_numerator / a_denominator;

    DType b_numerator = 0;
    for (IType i = 0; i < nn; ++i) {
        b_numerator += inputData->y->coordinates[i];
        b_numerator -= inputData->x->coordinates[i] * res.coordinates[0];
    }
    res.coordinates[1] = b_numerator / nn;

    return res;
}


DVector Interpolate(const struct Input_Data *inputData){
    if (inputData->n <= 0) {
        printf("Your dataset is empty.\n");
        struct DVector erroneous = {0, NULL};
        return erroneous;
    }

    DType **matrix = (DType **) malloc(sizeof(DType) * 16);
    for (int i = 0; i < 4; ++i) {
        matrix[i] = (DType *) malloc(sizeof(DType) * 4);
    }

    DType *vector = (DType *) malloc(sizeof(DType) * 4);
    for (IType i = 0; i < 4; ++i) {
        vector[0] = 0;
    }

    DType *sum_xn = (DType *) calloc(6, sizeof(DType));
    for (IType i = 0; i < 6; ++i) {
        sum_xn[i] = 0;
    }

    for (IType i = 0; i < inputData->n; ++i) {
        for (IType j = 0; j < 6; ++j) {
            sum_xn[j] += power(inputData->x->coordinates[i], j + 1);
        }

        for (IType j = 0; j < 4; ++j) {
            vector[j] += inputData->y->coordinates[i] * power(inputData->x->coordinates[i], 3 - j);
        }
    }

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


    struct DVector res = SolveLinSystem(matrix, vector, 4);

    free(vector);
    for (IType i = 0; i < 4; ++i) {
        free(matrix[i]);
    }
    free(matrix);

    return res;
}

DType power(DType x, IType n){
    DType res = 1;
    for (int i = 0; i < n; ++i) {
        res *= x;
    }

    return res;
}

DType fabs(DType x){
    if (x >= 0) {
        return x;
    } else {
        return -1 * x;
    }
}

DVector SolveLinSystem(DType** matrix,
                              DType *vector,
                              IType n){
    struct DVector res = {n};
    res.coordinates = (DType *) calloc(res.dim, sizeof(DType));
    for(int i=0; i<res.dim; i++)
        printf("%lf\n", res.coordinates[i]);
    Jacobi(res.dim, matrix, vector, res.coordinates);

    return res;
}

void Jacobi (IType n, DType** matrix, DType* f, DType* result)
{
    const DType eps = 0.1;

    DType *TempX = (DType *) calloc(n, sizeof(DType));
    DType norm;
    do {
        for (IType i = 0; i < n; i++) {
            TempX[i] = f[i];
            for (IType g = 0; g < n; g++) {
                if (i != g)
                    TempX[i] -= matrix[i][g] * result[g];
            }
            TempX[i] /= matrix[i][i];
        }
        norm = fabs(result[0] - TempX[0]);
        for (int h = 0; h < n - 1; h++) {
            if (fabs(result[h] - TempX[h]) > norm){
                // printf("%lf\n", norm);
                norm = fabs(result[h] - TempX[h]);
            }
            result[h] = TempX[h];
        }
        
    } while (norm > eps);
    free(TempX);
}

IType input(Input_Data *inputData){
    printf("How many (x,y) pairs will be there?\n");
    printf("Please note:\n");
    printf("x is height (cm)\n");
    printf("y is weight (kg)\n");
    scanf("%i", &inputData->n);
    if (inputData->n <= 0) {
        printf("dataset length must be greater than 0\n");
        return 1;
    }
    if (inputData->x == NULL | inputData->y == NULL) {
        printf("you have not provided any containers for dataset in your program");
        printf("\nSegmentation fault\n");
        return 1;
    }

    inputData->x->dim = inputData->n;
    inputData->y->dim = inputData->n;
    inputData->x->coordinates = (DType *) calloc(inputData->x->dim, sizeof(DType));
    inputData->y->coordinates = (DType *) calloc(inputData->y->dim, sizeof(DType));
    for (IType i = 0; i < inputData->n; ++i) {
        printf("x[%i]=", i+1);
        scanf("%lf", &inputData->x->coordinates[i]);

        printf("y[%i]=", i+1);
        scanf("%lf", &inputData->y->coordinates[i]);
    }

    return 0;
}

IType inputTextFile(char *file, Input_Data *inputData) {
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
    inputData->x->coordinates = (DType *) calloc(inputData->x->dim, sizeof(DType));
    inputData->y->coordinates = (DType *) calloc(inputData->y->dim, sizeof(DType));

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

void output(DVector *result) {
    printf("y=");
    for (IType i = 0; i < result->dim - 2; ++i) {
        printf("%.2fx^%i+",
               result->coordinates[i],
               (IType) result->dim - i - 1);
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
    fwrite(result, sizeof(DType), result->dim, fout);
    fclose(fout);

    return 0;
}

int outputTextFile(char *file, DVector *result){
    file_t fout = fopen(file, "w");
    if (!fout) {
        printf("error opening text file\n");
        return 1;
    }

    fseek(fout, 0, SEEK_END);

    fprintf(fout, "y=");
    for (IType i = 0; i < result->dim - 2; ++i) {
        fprintf(fout, "%.2fx^%i+", result->coordinates[i], (IType) result->dim - i - 1);
    }
    fprintf(fout, "%.2fx+", result->coordinates[result->dim - 2]);
    fprintf(fout, "%.2f\n", result->coordinates[result->dim - 1]);

    fclose(fout);

    return 0;
}