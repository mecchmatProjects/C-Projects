
/* TESTS
 * Realization of tests for matrix/vector structure functions
 * Done by Kostiukovych Stanislav, Statistics
 * Date 28.05.2019
 */

#include "src/Dmatrix.h"

void test_add_matrix(){
    matrix *A, *B, *C;
    int n =1, m=1;

    printf("Enter n: ");
    scanf("%d", &n);

    printf("Enter m: ");
    scanf("%d", &m);

    A = newMatrix(n, m);
    B = newMatrix(n, m);
    C= newMatrix(n,m);

    inputMatrixCoefficients(A, n, m);
    inputMatrixCoefficients(B, n, m);


    printf("Matrix A:");
    outputMatrix(A);

    printf("Matrix B:");
    outputMatrix(B);

    addMatrix(A, B, C);

    printf("Matrix of sum C:");
    outputMatrix(C);

    deleteMatrix(A);
    deleteMatrix(B);
    deleteMatrix(C);
}


void test_mul_matrix(){
    matrix *A, *B, *C;
    int n =1;

    printf("Enter n: ");
    scanf("%d", &n);

    A = newMatrix(n, n);
    B = newMatrix(n, n);
    C= newMatrix(n,n);

    inputMatrixCoefficients(A, n, n);
    inputMatrixCoefficients(B, n, n);


    printf("Matrix A:");
    outputMatrix(A);

    printf("Matrix B:");
    outputMatrix(B);

    mulMatrix(A, B, C);

    printf("Matrix of multiplying C:");
    outputMatrix(C);

    deleteMatrix(A);
    deleteMatrix(B);
    deleteMatrix(C);
}


void test_mul_matrix_vector(){
    matrix* mtx;
    vector* v, * ans;

    int n =1, m=1;

    printf("Enter n: ");
    scanf("%d", &n);

    printf("Enter m: ");
    scanf("%d", &m);

    mtx = newMatrix(n, m);
    inputMatrixCoefficients(mtx, n, m);

    v = newVector(n);
    inputVectorCoefficients(v, n);

    ans = newVector(n);

    mulMatrixVector(mtx, v, ans);


    printf("Matrix:");
    outputMatrix(mtx);

    printf("Vector:");
    outputVector(v);

    printf("Multiplication matrix and vector: ");
    outputVector(ans);

    deleteMatrix(mtx);
    deleteVector(v);
    deleteVector(ans);
}

void test_swap(){

    matrix *A;
    int n =1, m=1;
    int col_one =1 , col_two = 1;

    printf("Enter n: ");
    scanf("%d", &n);

    printf("Enter m: ");
    scanf("%d", &m);

    A = newMatrix(n, m);

    inputMatrixCoefficients(A, n, m);

    outputMatrix(A);

    printf("Enter colmn 1 to swap: ");
    scanf("%d", &col_one);

    printf("\nEnter colmn 2 to swap: ");
    scanf("%d", &col_two);

    if (swap_columns(A, col_one, col_two) ==0) {

        printf("\nWith swapping %d and %d columns: \n", col_one, col_two);
        outputMatrix(A);
    }
    else
        printf("Can't swap");

    deleteMatrix(A);
}

void test_determinant(){
    matrix *A;
    int n =1;

    printf("Enter n: ");
    scanf("%d", &n);

    A = newMatrix(n, n);
    inputMatrixCoefficients(A, n, n);

    outputMatrix(A);

    printf("\nDeterminant: ");
    printf("%lf", det(A));

    deleteMatrix(A);

}


int test_determinant_static(){
    matrix *A;
    int n =3;

    A = newMatrix(n, n);
    for (int i=1; i<=n; i++){
        for (int j=1; j<=n; j++)
            ELEM(A, i, j) = i*j/3 - 1;

    }

    if (det(A) ==-1){
        deleteMatrix(A);
        return 1;
    }

    deleteMatrix(A);

    return 0;
}

void test_inverse(){
    matrix *A, *B;

    int n =1;

    printf("Enter n: ");
    scanf("%d", &n);


    A = newMatrix(n, n);
    inputMatrixCoefficients(A, n, n);

    outputMatrix(A);


    B = newMatrix(n,n);
    if (inverse(A, B) ==0) {
        printf("The inverse matrix is: ");
        inverse(A, B);
        outputMatrix(B);
    }
    else
        printf("can't inverse");

    deleteMatrix(A);
    deleteMatrix(B);
}

void test_solve() {
    matrix *A, *temp;
    vector *v;
    int n = 1;

    printf("Enter n: ");
    scanf("%d", &n);

    A = newMatrix(n, n);

    inputMatrixCoefficients(A, n, n);

    v = newVector(n);
    inputVectorCoefficients(v, n);

    temp = newMatrix(A->rows, A->cols + 1);

    combineMatrixVector(A, temp, v);
    printf("\nYour matrix: \n");
    outputMatrix(temp);


    if (solve(temp, v) == 0) {
        printf("\nAnswer:");
        solve(temp, v);
        outputVector(v);
    }

    else
        printf("\nCan't solve, error #%d", solve(temp, v));


    deleteMatrix(temp);
    deleteMatrix(A);
    deleteVector(v);
}

void test_input_string(){
    matrix *A;
    int n=0 ,m =0;

    printf("Enter n: ");
    scanf("%d", &n);

    printf("Enter m: ");
    scanf("%d", &m);

    A = newMatrix(n, m);
    inputMatrixString(A, n, m);
    outputMatrix(A);
    deleteMatrix(A);
}

void test_input_coefficients(){
    matrix *A;
    int n=0 ,m =0;

    printf("Enter n: ");
    scanf("%d", &n);

    printf("Enter m: ");
    scanf("%d", &m);

    A = newMatrix(n, m);
    inputMatrixCoefficients(A, n, m);
    outputMatrix(A);
    deleteMatrix(A);
}


void test_vector_text_file(){
    vector *a, *b;
    char* filename = "vector.txt";
    int size=0;
    int size_read=0, _=0; // second variable is useless

    printf("Enter size: ");
    scanf("%d", &size);

    a = newVector(size);
    // input vector
    inputVectorCoefficients(a, size);
    // write to txt file
    outputVectorTextFile(a, filename);
    // get size
    getSizeVectorTextFile(&size_read, filename);

    b = newVector(size_read);

    // read vector from txt
    inputVectorTextFile(b, size_read, filename);
    printf("Vector from text file is: ");
    outputVector(b);

    deleteVector(a);
    deleteVector(b);
}

void test_matrix_text_file(){
    matrix *A, *B;
    char* filename = "matrix.txt";
    int row=0 ,col =0;
    int row_read=0, col_read=0;

    printf("Enter rows: ");
    scanf("%d", &row);

    printf("Enter cols: ");
    scanf("%d", &col);

    A = newMatrix(row, col);
    // input matrix
    inputMatrixCoefficients(A, row, col);
    // write to txt file
    outputMatrixtoTextFile(A, filename);

    // get number of cols and rows
    getSizeMatrixTextFile(&row_read,&col_read, filename);
    B = newMatrix(row_read, col_read);

    // read matrix from txt
    inputMatrixTextFile(B,row_read, col_read, filename);
    printf("Matrix from text file is: ");
    outputMatrix(B);

    // clear memory
    deleteMatrix(B);
    deleteMatrix(A);
}

// do later
void test_vector_binary_file(){
    vector *a, *b;
    char* filename = "vector.dat";
    int size=0;

    printf("Enter size: ");
    scanf("%d", &size);

    a = newVector(size);
    // input matrix
    inputVectorCoefficients(a, size);

    outputVectorBinaryFile(a, filename);

    b = newVector(size);

    // read matrix from binary
    inputVectorBinaryFile(b,size,filename);
    outputVector(b);

    // clear memory
    deleteVector(b);
    deleteVector(a);
}



int test_solve_text_file(){
    char* file_matrix = "../tests/test_solve.txt";
    char* answer = "../tests/test_solve_answer.txt";
    matrix* mtx;
    vector* ans, *true_ans;
    int col=1,row=1;

    // get size of matrix in text file
    getSizeMatrixTextFile(&row,&col, file_matrix);
    // create matrx/ vectors
    mtx = newMatrix(row, col);
    ans = newVector(row);
    true_ans = newVector(row);

    // input from text filematrix
    inputMatrixTextFile(mtx, row, col, file_matrix);

    // solve them
    solve(mtx, ans);

    // input true answer
    inputVectorTextFile(true_ans, row, answer);


    if (equalVectors(ans, true_ans))
        return 1;

    deleteVector(true_ans);
    deleteMatrix(mtx);
    deleteVector(ans);
    return 0;
}


int test_mul_text_file(){
    char* file_matrix1 = "../tests/test_mul_mtx1.txt";
    char* file_matrix2 = "../tests/test_mul_mtx2.txt";
    char* file_matrix_answ = "../tests/test_mul_ans.txt";
    int row=3, col=3;


    matrix *A, *B, *C, *C_true;
    A = newMatrix(row, col);
    B = newMatrix(row, col);
    C = newMatrix(row, col);
    C_true = newMatrix(row, col);

    inputMatrixTextFile(A, row,col, file_matrix1);
    inputMatrixTextFile(B, row,col, file_matrix2);
    inputMatrixTextFile(C_true, row, col, file_matrix_answ);

    if (mulMatrix(A, B, C) == 0){
        if (equalMatrix(C, C_true)){
            return 1;
        } else{
            outputMatrix(C);
            outputMatrix(C_true);
        }

    } else
        printf("Error #%d", mulMatrix(A, B, C));

    deleteMatrix(A);
    deleteMatrix(B);
    deleteMatrix(C);
    deleteMatrix(C_true);

    return 0;
}

int test_inverse_text_file(){
    char* file_matrix1 = "../tests/test_inv_mtx1.txt";
    char* file_matrix2 = "../tests/test_inv_ans.txt";
    int row=3, col=3;


    matrix *A, *A_inv, *A_true;
    A = newMatrix(row,col);
    A_inv = newMatrix(row, col);
    A_true = newMatrix(row, col);

    inputMatrixTextFile(A, row,col, file_matrix1);
    inputMatrixTextFile(A_true, row,col, file_matrix2);
    inverse(A, A_inv);

    if (equalMatrix(A_inv, A_true)) {
        return 1;
    }

    deleteMatrix(A);
    deleteMatrix(A_inv);
    deleteMatrix(A_true);

    return 0;
}

void passed_test(int c){
    if (c)
        printf("test passed\n");

    else
        printf("test failed\n");
}



void type_test(){
    printf("1 - using keyboard,\n"
           "2 - unit test\n"
           "0 - exit\n");

    int option = -1;

    while (option != 0){
        printf("\nEnter type of testing:\n");
        scanf("%d", &option);
        if (option == 1){

            printf("\nTest 1: Input matrix as string with spaces\n");
            test_input_string();

            printf("\nTest 2: Vector to text file\n");
            test_vector_text_file();

            printf("\nTest 3: Matrix to text file\n");
            test_matrix_text_file();

            printf("\nTest 4: Adding matrix\n");
            test_add_matrix();

            printf("\nTest 5: multiplying  matrix and vector\n");
            test_mul_matrix_vector();

            printf("\nTest 6: multiplying matrix\n");
            test_mul_matrix();

            printf("\nTest 7: Swap columns\n");
            test_swap();

            printf("\nTest 8: Determinant\n");
            test_determinant();

            printf("\nTest 9: Inverse\n");
            test_inverse();

            printf("\nTest 10: Solve\n");
            test_solve();


        }
        else if(option == 2) {
            printf("\nTest multiplying\n");
            passed_test(test_mul_text_file());
            printf("\nTest solve\n");
            passed_test(test_solve_text_file());
            printf("\nTest determinant\n");
            passed_test(test_determinant_static());
            printf("\nTest inverse\n");
            passed_test(test_inverse_text_file());

        }
    }
}


/*
 * Types error:
 * -1 no struct or file
 * -2 and -3 - error in dimension
 * -4 - can't solve because matrix is Linear dependent
 */


int main() {
    type_test();
}