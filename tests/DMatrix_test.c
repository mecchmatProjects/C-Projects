#include "../src/DMatrix.c"

enum INPUT_TYPE
{
    INPUT_FROM_CONSOLE,
    INPUT_FROM_FILE
};

enum OUTPUT_TYPE
{
    OUTPUT_IN_CONSOLE,
    OUTPUT_IN_FILE
};

const enum INPUT_TYPE input_type = INPUT_FROM_FILE;
const enum OUTPUT_TYPE ouput_type = OUTPUT_IN_FILE;
const char *path_to_inputfile = "/home/pandrii000/hdd/University/Coursework/DVector_DMatrix_Polukhin_and_Liaskovskiy/tests/DMatrix_test.txt";
const char *path_to_outputfile = "/home/pandrii000/hdd/University/Coursework/DVector_DMatrix_Polukhin_and_Liaskovskiy/tests/DMatrix_output.txt";

void test_add_DMatrix(ITYPE type, ITYPE width, ITYPE precision)
{
    printf("TEST add_DMatrix FUNCTION\n");
    DMatrix a, b, answer;
    ITYPE size_a_rows, size_a_columns;
    ITYPE size_b_rows, size_b_columns;
    // read matrix a
    scanf("%d %d", &size_a_rows, &size_a_columns);
    a = generate_DMatrix(size_a_rows, size_a_columns);
    input_DMatrix(&a);
    // read matrix b
    scanf("%d %d", &size_b_rows, &size_b_columns);
    b = generate_DMatrix(size_b_rows, size_b_columns);
    input_DMatrix(&b);
    // testing
    answer = add_DMatrix(a, b);
    output_DMatrix(answer, type, width, precision);
}

void test_sub_DMatrix(ITYPE type, ITYPE width, ITYPE precision)
{
    printf("TEST sub_DMatrix FUNCTION\n");
    DMatrix a, b, answer;
    ITYPE size_a_rows, size_a_columns;
    ITYPE size_b_rows, size_b_columns;
    // read matrix a
    scanf("%d %d", &size_a_rows, &size_a_columns);
    a = generate_DMatrix(size_a_rows, size_a_columns);
    input_DMatrix(&a);
    // read matrix b
    scanf("%d %d", &size_b_rows, &size_b_columns);
    b = generate_DMatrix(size_b_rows, size_b_columns);
    input_DMatrix(&b);
    // testing
    answer = sub_DMatrix(a, b);
    output_DMatrix(answer, type, width, precision);
}

void test_mult_DMatrix(ITYPE type, ITYPE width, ITYPE precision)
{
    printf("TEST mult_DMatrix FUNCTION\n");
    DMatrix a, b, answer;
    ITYPE size_a_rows, size_a_columns;
    ITYPE size_b_rows, size_b_columns;
    // read matrix a
    scanf("%d %d", &size_a_rows, &size_a_columns);
    a = generate_DMatrix(size_a_rows, size_a_columns);
    input_DMatrix(&a);
    // read matrix b
    scanf("%d %d", &size_b_rows, &size_b_columns);
    b = generate_DMatrix(size_b_rows, size_b_columns);
    input_DMatrix(&b);
    // testing
    answer = mult_DMatrix(a, b);
    output_DMatrix(answer, type, width, precision);
}

void test_divide_DMatrix(ITYPE type, ITYPE width, ITYPE precision)
{
    printf("TEST divide_DMatrix FUNCTION\n");
    DMatrix a, b, answer;
    ITYPE size_a_rows, size_a_columns;
    ITYPE size_b_rows, size_b_columns;
    // read matrix a
    scanf("%d %d", &size_a_rows, &size_a_columns);
    a = generate_DMatrix(size_a_rows, size_a_columns);
    input_DMatrix(&a);
    // read matrix b
    scanf("%d %d", &size_b_rows, &size_b_columns);
    b = generate_DMatrix(size_b_rows, size_b_columns);
    input_DMatrix(&b);
    // testing
    answer = divide_DMatrix(a, b);
    output_DMatrix(answer, type, width, precision);
}

void test_mod_DMatrix(ITYPE type, ITYPE width, ITYPE precision)
{
    printf("TEST mod_DMatrix FUNCTION\n");
    DMatrix a, b, answer;
    ITYPE size_a_rows, size_a_columns;
    ITYPE size_b_rows, size_b_columns;
    // read matrix a
    scanf("%d %d", &size_a_rows, &size_a_columns);
    a = generate_DMatrix(size_a_rows, size_a_columns);
    input_DMatrix(&a);
    // read matrix b
    scanf("%d %d", &size_b_rows, &size_b_columns);
    b = generate_DMatrix(size_b_rows, size_b_columns);
    input_DMatrix(&b);
    // testing
    answer = mod_DMatrix(a, b);
    output_DMatrix(answer, type, width, precision);
}

void test_multConst_DMatrix(ITYPE type, ITYPE width, ITYPE precision)
{
    printf("TEST multConst_DMatrix FUNCTION\n");
    DMatrix a, answer;
    ITYPE size_a_rows, size_a_columns;
    DTYPE b;
    // read matrix a
    scanf("%d %d", &size_a_rows, &size_a_columns);
    a = generate_DMatrix(size_a_rows, size_a_columns);
    input_DMatrix(&a);
    // read DTYPE b
    scanf("%lf", &b);
    // testing
    answer = multConst_DMatrix(a, b);
    output_DMatrix(answer, type, width, precision);
}

void test_divideConst_DMatrix(ITYPE type, ITYPE width, ITYPE precision)
{
    printf("TEST divideConst_DMatrix FUNCTION\n");
    DMatrix a, answer;
    ITYPE size_a_rows, size_a_columns;
    DTYPE b;
    // read matrix a
    scanf("%d %d", &size_a_rows, &size_a_columns);
    a = generate_DMatrix(size_a_rows, size_a_columns);
    input_DMatrix(&a);
    // read DTYPE b
    scanf("%lf", &b);
    // testing
    answer = divideConst_DMatrix(a, b);
    output_DMatrix(answer, type, width, precision);
}

void test_modConst_DMatrix(ITYPE type, ITYPE width, ITYPE precision)
{
    printf("TEST modConst_DMatrix FUNCTION\n");
    DMatrix a, answer;
    ITYPE size_a_rows, size_a_columns;
    DTYPE b;
    // read matrix a
    scanf("%d %d", &size_a_rows, &size_a_columns);
    a = generate_DMatrix(size_a_rows, size_a_columns);
    input_DMatrix(&a);
    // read DTYPE b
    scanf("%lf", &b);
    // testing
    answer = modConst_DMatrix(a, b);
    output_DMatrix(answer, type, width, precision);
}

void test_unadd_DMatrix(ITYPE type, ITYPE width, ITYPE precision)
{
    printf("TEST unadd_DMatrix FUNCTION\n");
    DMatrix a, b;
    ITYPE size_a_rows, size_a_columns;
    ITYPE size_b_rows, size_b_columns;
    // read matrix a
    scanf("%d %d", &size_a_rows, &size_a_columns);
    a = generate_DMatrix(size_a_rows, size_a_columns);
    input_DMatrix(&a);
    // read matrix b
    scanf("%d %d", &size_b_rows, &size_b_columns);
    b = generate_DMatrix(size_b_rows, size_b_columns);
    input_DMatrix(&b);
    // testing
    if (unadd_DMatrix(&a, b))
        output_DMatrix(a, type, width, precision);
}

void test_unsub_DMatrix(ITYPE type, ITYPE width, ITYPE precision)
{
    printf("TEST unsub_DMatrix FUNCTION\n");
    DMatrix a, b;
    ITYPE size_a_rows, size_a_columns;
    ITYPE size_b_rows, size_b_columns;
    // read matrix a
    scanf("%d %d", &size_a_rows, &size_a_columns);
    a = generate_DMatrix(size_a_rows, size_a_columns);
    input_DMatrix(&a);
    // read matrix b
    scanf("%d %d", &size_b_rows, &size_b_columns);
    b = generate_DMatrix(size_b_rows, size_b_columns);
    input_DMatrix(&b);
    // testing
    if (unsub_DMatrix(&a, b))
        output_DMatrix(a, type, width, precision);
}

void test_unmult_DMatrix(ITYPE type, ITYPE width, ITYPE precision)
{
    printf("TEST unmult_DMatrix FUNCTION\n");
    DMatrix a, b;
    ITYPE size_a_rows, size_a_columns;
    ITYPE size_b_rows, size_b_columns;
    // read matrix a
    scanf("%d %d", &size_a_rows, &size_a_columns);
    a = generate_DMatrix(size_a_rows, size_a_columns);
    input_DMatrix(&a);
    // read matrix b
    scanf("%d %d", &size_b_rows, &size_b_columns);
    b = generate_DMatrix(size_b_rows, size_b_columns);
    input_DMatrix(&b);
    // testing
    if (unmult_DMatrix(&a, b))
        output_DMatrix(a, type, width, precision);
}

void test_undivide_DMatrix(ITYPE type, ITYPE width, ITYPE precision)
{
    printf("TEST undivide_DMatrix FUNCTION\n");
    DMatrix a, b;
    ITYPE size_a_rows, size_a_columns;
    ITYPE size_b_rows, size_b_columns;
    // read matrix a
    scanf("%d %d", &size_a_rows, &size_a_columns);
    a = generate_DMatrix(size_a_rows, size_a_columns);
    input_DMatrix(&a);
    // read matrix b
    scanf("%d %d", &size_b_rows, &size_b_columns);
    b = generate_DMatrix(size_b_rows, size_b_columns);
    input_DMatrix(&b);
    // testing
    if (undivide_DMatrix(&a, b))
        output_DMatrix(a, type, width, precision);
}

void test_unmod_DMatrix(ITYPE type, ITYPE width, ITYPE precision)
{
    printf("TEST unmod_DMatrix FUNCTION\n");
    DMatrix a, b;
    ITYPE size_a_rows, size_a_columns;
    ITYPE size_b_rows, size_b_columns;
    // read matrix a
    scanf("%d %d", &size_a_rows, &size_a_columns);
    a = generate_DMatrix(size_a_rows, size_a_columns);
    input_DMatrix(&a);
    // read matrix b
    scanf("%d %d", &size_b_rows, &size_b_columns);
    b = generate_DMatrix(size_b_rows, size_b_columns);
    input_DMatrix(&b);
    // testing
    if (unmod_DMatrix(&a, b))
        output_DMatrix(a, type, width, precision);
}


void test_det(ITYPE type, ITYPE width, ITYPE precision)
{
    printf("TEST det FUNCTION\n");
    DMatrix a;
    ITYPE size_a_rows, size_a_columns;
    // read matrix a
    scanf("%d %d", &size_a_rows, &size_a_columns);
    a = generate_DMatrix(size_a_rows, size_a_columns);
    input_DMatrix(&a);
    // testing
    DTYPE d = det_DMatrix(a);
    if (type == 0)
        printf("%*.*lf ", width, precision, d);
    else    
        printf("%*.*e ", width, precision, d);
}

void test_solve_DMatrix(ITYPE type, ITYPE width, ITYPE precision)
{
    printf("TEST solve_DMatrix FUNCTION\n");
    DMatrix a;
    DVector b;
    ITYPE size_a_rows, size_a_columns;
    ITYPE size_b;
    // read matrix a
    scanf("%d %d", &size_a_rows, &size_a_columns);
    a = generate_DMatrix(size_a_rows, size_a_columns);
    input_DMatrix(&a);
    // read vector b
    scanf("%d", &size_b);
    b = generate_DVector(size_b);
    input_DVector(&b);
    // testing
    DVector answer = solve_DMatrix(a, b);
    output_DVector(answer, type, width, precision);
}

void test_swap_row_DMatrix(ITYPE type, ITYPE width, ITYPE precision)
{
    printf("TEST swap_row_DMatrix FUNCTION\n");
    DMatrix a;
    ITYPE size_a_rows, size_a_columns, i, j;
    // read matrix a
    scanf("%d %d", &size_a_rows, &size_a_columns);
    a = generate_DMatrix(size_a_rows, size_a_columns);
    input_DMatrix(&a);
    // read i and j
    scanf("%d %d", &i, &j);
    // testing
    swap_row_DMatrix(&a, i, j);
    output_DMatrix(a, type, width, precision);
}

void test_swap_column_DMatrix(ITYPE type, ITYPE width, ITYPE precision)
{
    printf("TEST swap_column_DMatrix FUNCTION\n");
    DMatrix a;
    ITYPE size_a_rows, size_a_columns, i, j;
    // read matrix a
    scanf("%d %d", &size_a_rows, &size_a_columns);
    a = generate_DMatrix(size_a_rows, size_a_columns);
    input_DMatrix(&a);
    // read i and j
    scanf("%d %d", &i, &j);
    // testing
    swap_column_DMatrix(&a, i, j);
    output_DMatrix(a, type, width, precision);
}

void test_inverse_DMatrix(ITYPE type, ITYPE width, ITYPE precision)
{
    printf("TEST inverse_DMatrix FUNCTION\n");
    DMatrix a;
    ITYPE size_a_rows, size_a_columns;
    // read matrix a
    scanf("%d %d", &size_a_rows, &size_a_columns);
    a = generate_DMatrix(size_a_rows, size_a_columns);
    input_DMatrix(&a);
    // testing
    DMatrix inv_a = inverse_DMatrix(a);
    output_DMatrix(inv_a, type, width, precision);
}

int main()
{
    if (input_type == INPUT_FROM_FILE)
    {
        FILE *read_ptr = freopen(path_to_inputfile, "r", stdin);
        if (read_ptr == NULL)
        {
            printf("Read error!\n");
            return 0;
        }
    }

    if (ouput_type == OUTPUT_IN_FILE)
    {
        FILE *write_ptr = freopen(path_to_outputfile, "w", stdout);
        if (write_ptr == NULL)
        {
            printf("Write error!\n");
            return 0;
        }
    }

    test_add_DMatrix(0, 7, 2);

    if (input_type == INPUT_FROM_FILE)
        fclose(stdin);

    if (ouput_type == OUTPUT_IN_FILE)
        fclose(stdout);
}
