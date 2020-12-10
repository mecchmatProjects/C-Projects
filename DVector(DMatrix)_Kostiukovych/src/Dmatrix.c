/* structure
 * Realization of matrix/vector structure functions
 * Done by Kostiukovych Stanislav, Statistics
 * Date 28.05.2019
 */


#include "Dmatrix.h"


/* Creates a vector with all values 0.
 * Returns NULL if size <= 0  and otherwise a
 * pointer to the new vector.
 */

vector * newVector(int num) {
    if (num <= 0) return NULL;

    // allocate a vector structure
    vector* v = (vector *)malloc(sizeof(vector));

    // set size
    v->n = num;

    // allocate a double array of size
    v->data = (double *) malloc(num*sizeof(double));
    // set all data to 0
    for (int i = 0; i < num; i++)
        v->data[i] = 0.0;
    return v;
}



/* Deletes a vector.  Returns 0 if successful and -1 if v
 * is NULL.
 */
int deleteVector(vector * v) {
    if (!v) return -1;
    free(v->data);
    free(v);
    return 0;
}


/* Creates a ``rows by cols'' matrix with all values 0.
 * Returns NULL if rows <= 0 or cols <= 0 and otherwise a
 * pointer to the new matrix.
 */

matrix * newMatrix(int rows, int cols) {
    if (rows <= 0 || cols <= 0) return NULL;

    // allocate a matrix structure
    matrix * m = (matrix *) malloc(sizeof(matrix));

    // set dimensions
    m->rows = rows;
    m->cols = cols;

    // allocate a double array of length rows * cols
    m->data = (double *) malloc(rows*cols*sizeof(double));
    // set all data to 0
    int i;
    for (i = 0; i < rows*cols; i++)
        m->data[i] = 0.0;
    return m;
}

matrix * copyMatrix(matrix * mtx) {
    if (!mtx) return NULL;

    // create a new matrix to hold the copy
    matrix * cp = newMatrix(mtx->rows, mtx->cols);

    for (int row = 1; row <= mtx->rows; row++)
        for (int col = 1; col <= mtx->cols; col++)
            ELEM(cp, col, row) = ELEM(mtx, col, row);

    return cp;
}


/* Deletes a matrix.  Returns 0 if successful and -1 if mtx
 * is NULL.
 */
int deleteMatrix(matrix * mtx) {
    if (!mtx) return -1;
    free(mtx->data);
    free(mtx);
    return 0;
}


// Input vector in terminal by coefficients

int inputVectorCoefficients(vector *vec, int size){
    if(!vec) return -1;
    int i=0;
    double num=0;
    for (i = 0; i < size; i++) {
        printf("Vector[%i]: ", i + 1);
        scanf("%lf", &num);
        vec->data[i] = num;
    }
    return 0;
}
// Input vector in terminal as string with whitespaces

int inputVectorString(vector *vec, int size) {
    if (!vec) return -1;
    double num = 0;
    printf("Enter vector as str:\n");
    for (int i = 0; i < size; i++) {
        scanf("%lf", &num);
        vec->data[i] = num;
    }
    return 0;
}

int inputVectorTextFile(vector* vec, int size, char*filename){
    FILE *inputFile = fopen(filename, "r");
    if (!inputFile)
        return -1;

    fseek(inputFile, 0, SEEK_SET);
    for(int i=0;i<size;i++)
    {
        fscanf(inputFile,"%lf",&vec->data[i]);
    }

    fclose(inputFile);
    return 0;
}


int inputVectorBinaryFile(vector* vec, int size, char*filename){
    FILE *f = fopen(filename, "w");

    if (!f)
        return -1;

    double templ =-1 ;

    for (int i =0; i < size ;i++){
        fread(&templ, sizeof(double), 1, f);
        printf("%lf ", templ);
    }

    fclose(f);
    return 0;
}


int outputVector(vector *vec){
    if (!vec)
        return -1;
    printf("\n");
    for (int i =0; i < vec->n; i++){
        printf("| %lf ", vec->data[i]);
    }
    printf("|\n");
    return 0;
}

int outputVectorTextFile(vector *vec, char *filename){
    FILE *f = fopen(filename, "w");

    if (!f)
        return -1;

    for (int i =0; i < vec->n ;i++){
        fprintf(f, "%lf\t", vec->data[i]);
    }

    fclose(f);
    return 0;
}

int outputVectorBinaryFile(vector *vec, char *filename){
    FILE *f = fopen(filename, "w");

    if (!f)
        return -1;

    for (int i=0; i < vec->n; i++){
        fwrite(&vec->data[i], sizeof(double), 1, f);
    }

    fclose(f);
    return 0;
}


int setElement(matrix * mtx, int row, int col, double val)
{
    if (!mtx) return -1;
    if (row <= 0 || row > mtx->rows ||
        col <= 0 || col > mtx->cols)
        return -2;

    ELEM(mtx, row, col) = val;
    return 0;
}

int inputMatrixString(matrix* A, int n, int m){
    if (!A)
        return -1;

    double num = 0;

    printf("Enter the elements of matrix: \n");
    for (int i=1; i<=n; i++){
        for (int j=1; j<=m; j++) {
            scanf("%lf", &num);
            setElement(A, i, j, num);
        }
    }
    return 0;
}

int inputMatrixCoefficients(matrix* A,int  n,int m){
    if (!A)
        return -1;

    double num=0;

    printf("Enter the elements of matrix: \n");
    for (int i=1; i<=n; i++){
        for (int j=1; j<=m; j++){
            printf("Matrix[%i][%i]: ", i, j);
            scanf("%lf", &num);
            setElement(A, i, j, num);
        }
    }
    return 0;
}


int getSizeMatrixTextFile(int *row, int *col, char* filename){
    FILE *inputFile = fopen(filename, "r");
    int c=0, all=0, temprow=0, tempcol=0;

    if (!inputFile)
        return -1;
    fseek(inputFile, 0, SEEK_SET);

    while ((c = getc(inputFile)) != EOF)
    {
        if (c == '\t')
            all++;
        if (c == '\n') {
            temprow++;

        }
    }
    *row = temprow;
    tempcol = all/temprow;
    *col = tempcol;

    fclose(inputFile);
    return 0;
}

int getSizeVectorTextFile(int* size_read,char* filename){
    FILE *inputFile = fopen(filename, "r");
    int all=0, c=0;
    if (!inputFile)
        return -1;
    fseek(inputFile, 0, SEEK_SET);

    while ((c = getc(inputFile)) != EOF)
    {
        if (c == '\t')
            all++;
    }

    *size_read = all;

    fclose(inputFile);
    return 0;
};


int inputMatrixTextFile(matrix *mtx, int row, int col, char* filename){

    FILE *inputFile = fopen(filename, "r");
    if (!inputFile)
        return -1;

    fseek(inputFile, 0, SEEK_SET);
    for(int i=1;i<=row;i++)
    {
        for(int j=1;j<=col;j++)
            fscanf(inputFile,"%lf",&ELEM(mtx, i, j));
    }

    fclose(inputFile);
    return 0;
}

int inputMatrixBinaryFile(matrix *mtx, int row, int col, char* filename){

    FILE *infile;
    // Open filename for reading
    infile = fopen(filename, "r");
    if (!infile)
        return -1;


    // read file contents till end of file
    fread(&mtx, sizeof(matrix), 1, infile);

    // close file
    fclose (infile);printf("\n");
    return 0;

}



/* Prints the matrix to stdout.  Returns 0 if successful
 * and -1 if mtx is NULL.
 */
int outputMatrix(matrix * mtx) {
    if (!mtx) return -1;

    int row, col;
    printf("\n");
    for (row = 1; row <= mtx->rows; row++) {
        printf("|");
        for (col = 1; col <= mtx->cols; col++) {

            // not printing minus zero
            if (ELEM(mtx, row, col) == 0) {
                ELEM(mtx, row, col) = 0;
            }

            printf("% 6.2f ", ELEM(mtx, row, col));
            printf("|");
        }
        // separate rows by newlines
        printf("\n");
    }
    printf("\n");
    return 0;
}


int outputMatrixtoTextFile(matrix* mtx, char *filename){
    FILE *f = fopen(filename, "w");

    if (!f)
        return -1;

    for (int i =1; i<= mtx->rows;i++){
        for (int j =1; j<= mtx->cols;j++){
            fprintf(f, "%lf\t", ELEM(mtx, i ,j));
        }
        fprintf(f, "\n");
    }
    fclose(f);
    return 0;
}


int outputMatrixBinaryFile(matrix *mtx, char* filename){
    FILE *outfile;

    // open file for writing
    outfile = fopen (filename, "w");
    if (!outfile)
        return -1;

    // write struct to file
    fwrite (&mtx, sizeof(matrix), 1, outfile);

    // close file
    fclose (outfile);
    return 0;
}


// FUNCS TO WORK WITH MATRIX/VECTOR


int equalVectors(vector *v1, vector *v2){
    if (v1->n != v2->n) return 0;
    for (int i =0; i < v1->n; i++){
        if (v1->data[i] != v2->data[i])
            return 0;
    }
    return 1;
}


int equalMatrix(matrix *mtx1, matrix *mtx2){
    if (!mtx1 || !mtx2) return 0;
    if (mtx1->rows != mtx2->rows ||
        mtx1->cols != mtx2->cols)
        return 0;
    int col, row;

    for (col = 1; col <= mtx1->cols; col++)
        for (row = 1; row <= mtx1->rows; row++)
            if(fabs(ELEM(mtx1, row, col) - ELEM(mtx2, row, col)) != 0.0
            && ELEM(mtx1, row, col) != ELEM(mtx2, row, col)
            &&fabs(ELEM(mtx1, row, col) - ELEM(mtx2, row, col)) > 0.1) {
                printf("%lf %lf\n",ELEM(mtx1, row, col) , ELEM(mtx2, row, col));
                return 0;
            }

    return 1;

}


int mulVector(vector * v1, vector * v2, double *prod){

    if (!v1 || !v2 || !prod) return -1;
    if (v1->n != v2->n) return -2;


    for (int i =0; i < v1->n; i++){
        *prod += v1->data[i]*v2->data[i];
    }
    return 0;
}


int mulVectorDigit(vector * v, double digit){
    if (!v) return -1;

    for (int i =0; i < v->n; i++) {
        v->data[i] *= digit;
    }

    return 0;
}



/* Writes the sum of matrices mtx1 and mtx2 into matrix
 * sum. Returns 0 if successful, -1 if any of the matrices
 * are NULL, and -2 if the dimensions of the matrices are
 * incompatible.
 */
int addMatrix(matrix * mtx1, matrix * mtx2, matrix * sum) {
    if (!mtx1 || !mtx2 || !sum) return -1;
    if (mtx1->rows != mtx2->rows ||
        mtx1->rows != sum->rows ||
        mtx1->cols != mtx2->cols ||
        mtx1->cols != sum->cols)
        return -2;

    int row, col;
    for (col = 1; col <= mtx1->cols; col++)
        for (row = 1; row <= mtx1->rows; row++)
            ELEM(sum, row, col) =
                    ELEM(mtx1, row, col) + ELEM(mtx2, row, col);
    return 0;
}

int subMatrix(matrix * mtx1, matrix * mtx2, matrix * sub) {
    if (!mtx1 || !mtx2 || !sub) return -1;
    if (mtx1->rows != mtx2->rows ||
        mtx1->rows != sub->rows ||
        mtx1->cols != mtx2->cols ||
        mtx1->cols != sub->cols)
        return -2;

    int row, col;
    for (col = 1; col <= mtx1->cols; col++)
        for (row = 1; row <= mtx1->rows; row++)
            ELEM(sub, row, col) =
                    ELEM(mtx1, row, col) - ELEM(mtx2, row, col);
    return 0;
}




/* Writes the product of matrices mtx1 and mtx2 into matrix
 * prod.  Returns 0 if successful, -1 if any of the
 * matrices are NULL, and -2 if the dimensions of the
 * matrices are incompatible.
 */
int mulMatrix(matrix * mtx1, matrix * mtx2, matrix * prod) {
    if (!mtx1 || !mtx2 || !prod) return -1;
    if (mtx1->cols != mtx2->rows ||
        mtx1->rows != prod->rows ||
        mtx2->cols != prod->cols)
        return -2;

    int k;
    for (int col = 1; col <= mtx2->cols; col++)
        for (int row = 1; row <= mtx1->rows; row++) {
            double val = 0.0;
            for (k = 1; k <= mtx1->cols; k++)
                val += ELEM(mtx1, row, k) * ELEM(mtx2, k, col);
            ELEM(prod, row, col) = val;
        }
    return 0;
}


int mulMatrixDigit(matrix * mtx, double digit){
    if (!mtx) return -1;

    for (int col = 1; col <= mtx->cols; col++)
        for (int row = 1; row <= mtx->rows; row++) {
            ELEM(mtx, row, col) *= digit;
        }

    return 0;
}


int mulMatrixVector(matrix *mtx, vector*vec, vector * res) {
    if(mtx->rows != vec->n || mtx->rows != res->n)
        return -1;
    for (int col = 1; col <= mtx->cols; col++)
        for (int row = 1; row <= mtx->rows; row++) {
            res->data[row - 1] += vec->data[col-1] * ELEM(mtx, row, col);
        }

    return 0;

}

void swap(double *a, double *b){
    double t;
    t  = *b;
    *b = *a;
    *a = t;
}

int transpose(matrix * in) {
    if (!in) return -1;
    for (int row = 1; row <= in->rows; row++) {
        for (int col = 1; col <= in->cols; col++) {
            if (row < col) {
                swap(&ELEM(in, col, row), &ELEM(in, row, col));
            }
        }
    }

    return 0;

}

int swap_columns(matrix * in, int col1, int col2){

    if (col1 > in->cols || col2 > in->cols)
        return -1;

    for (int row = 1; row <= in->rows; row++){
        swap(&ELEM(in, row, col1), &ELEM(in, row, col2));
    }

    return 0;
}

int swap_rows(matrix * in, int row1, int row2){

    if (row1 > in->rows || row2 > in->rows)
        return -1;


    for (int col = 1; col <= in->cols; col++){
        swap(&ELEM(in, row1, col), &ELEM(in, row2, col));
    }

    return 0;

}

double det(matrix * temp) {

    matrix *in = copyMatrix(temp);

    double det = 1;
    int oper = 1;

    if (in->cols != in->rows)
        return 0.0;

    for (int i=1; i <= in->rows; i++) {
        for (int k = i+1; k<= in->cols; k++){
            if (fabs(ELEM(in, i, i)) < fabs(ELEM(in, k, i))){
                for (int j=1; j <= in->cols; j++) {
                    double templ = ELEM(in, i, j);
                    ELEM(in, i, j) = ELEM(in, k, j);
                    ELEM(in, k, j) = templ;
                    oper *= -1;
                }
            }
        }
    }

    for (int i=1; i <= in->rows; i++) {
        for (int j = i+1; j <= in->cols; j++) {
            if (ELEM(in, i, i) != 0){
                double koef = -ELEM(in, j, i) / ELEM(in, i, i);
                for (int k=i; k <= in->cols; k++) {
                    ELEM(in, j, k) += ELEM(in, i, k) * koef;


                    oper = ((i + j) % 2 == 0) ? 1 : -1;
                }
            }
        }
        det *= ELEM(in, i, i);
    }

    det *= oper;
    deleteMatrix(in);
    return det;
}

int GetMinor(matrix *src,matrix *dest, int row, int col){
    if (!src || !dest) return -1;

    // indicate which col and row is being copied to dest

    int colCount = 1,rowCount = 1;
    int i,j;

    for(i = 1; i <= src->rows; i++ ){
        if( i != row )
        {
            colCount = 1;
            for( j = 1; j <= src->cols; j++ )
            {
                // when j is not the element
                if( j != col )
                {
                    ELEM(dest, rowCount, colCount) = ELEM(src, i,j);
                    colCount++;
                }
            }
            rowCount++;
        }
    }
    return 0;
}

int inverse(matrix *in, matrix *out){

    if (det(in) == 0){
        return -1;
    }

    matrix *temp = newMatrix(in->rows-1, in->cols-1);


    int sign = 1;
    for (int i=1; i <= in->cols; i++){
        for (int j=1; j <= in->rows; j++){
            sign = ((i+j)%2==0)? 1: -1;
            GetMinor(in, temp, i, j);
            ELEM(out, i, j) = det(temp) * sign;

        }
    }
    deleteMatrix(temp);

    transpose(out);

    for (int i=1; i <= in->cols; i++){
        for (int j=1; j <= in->rows; j++) {
            ELEM(out, i, j) *= 1/det(in);
        }
    }
    return 0;
}

int combineMatrixVector(matrix *mtx, matrix *temp, vector* ans){
    if (!mtx || !temp || !ans) return -1;
    // combine it to one matrix temp
    for (int i=1; i<=mtx->rows; i++){
        for (int j=1; j<=mtx->cols; j++)
            ELEM(temp, i, j) = ELEM(mtx, i, j);
    }

    for (int i=1; i<=temp->rows; i++){
        ELEM(temp, i, temp->cols) = ans->data[i-1];
    }
    return 0;
}



// get 3 x 4 matrix and vector and solve
// writes solution in answer
int solve(matrix *mtx, vector*ans){

    if (!mtx || !ans)return -1;

    if (mtx->cols - mtx->rows!=1){
        return -2;
    }

    if (mtx->rows != ans->n){
        return -3;
    }


    for (int i=1; i <= mtx->rows; i++) {
        for (int j = i+1; j <= mtx->rows; j++) {
            double koef = -ELEM(mtx, j, i) / ELEM(mtx, i, i);
            for (int k=i; k <= mtx->cols; k++) {
                ELEM(mtx, j, k) += ELEM(mtx, i, k) * koef;
            }
        }
    }

    if (ELEM(mtx, mtx->rows, mtx->cols-1)==0)
        return -4;

    for (int i = mtx->rows ; i >= 1; i--) {
        for (int j = i - 1; j >= 1; j--) {
            double koef = -ELEM(mtx, j, i) / ELEM(mtx, i, i);
            for (int k = mtx->cols; k >= i; k--) {
                ELEM(mtx, j, k) += ELEM(mtx, i, k) * koef;
            }
        }
    }

    for (int i = 1; i <= mtx->rows; i++) {
        ans->data[i-1] = ELEM(mtx, i, mtx->cols) / ELEM(mtx, i, i);
    }

    deleteMatrix(mtx);
    return 0;
}
