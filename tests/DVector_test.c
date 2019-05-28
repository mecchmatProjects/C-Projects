#include "../src/DVector.c"

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
const char *path_to_inputfile = "/home/pandrii000/hdd/University/Coursework/DVector_DMatrix_Polukhin_and_Liaskovskiy/tests/DVector_test.txt";
const char *path_to_outputfile = "/home/pandrii000/hdd/University/Coursework/DVector_DMatrix_Polukhin_and_Liaskovskiy/tests/DVector_output.txt";

void test_add_DVector(ITYPE type, ITYPE width, ITYPE precision)
{
    printf("TEST add_DVector FUNCTION\n");
    DVector a, b, answer;
    ITYPE size_a, size_b;
    // read vector a
    scanf("%u", &size_a);
    a = generate_DVector(size_a);
    input_DVector(&a);
    // read vector b
    scanf("%u", &size_b);
    b = generate_DVector(size_b);
    input_DVector(&b);
    // testing
    answer = add_DVector(a, b);
    output_DVector(answer, type, width, precision);
}

void test_sub_DVector(ITYPE type, ITYPE width, ITYPE precision)
{
    printf("TEST sub_DVector FUNCTION\n");
    DVector a, b, answer;
    ITYPE size_a, size_b;
    // read vector a
    scanf("%u", &size_a);
    a = generate_DVector(size_a);
    input_DVector(&a);
    // read vector b
    scanf("%u", &size_b);
    b = generate_DVector(size_b);
    input_DVector(&b);
    // testing
    answer = sub_DVector(a, b);
    output_DVector(answer, type, width, precision);
}

void test_mult_DVector(ITYPE type, ITYPE width, ITYPE precision)
{
    printf("TEST mult_DVector FUNCTION\n");
    DVector a, b, answer;
    ITYPE size_a, size_b;
    // read vector a
    scanf("%u", &size_a);
    a = generate_DVector(size_a);
    input_DVector(&a);
    // read vector b
    scanf("%u", &size_b);
    b = generate_DVector(size_b);
    input_DVector(&b);
    // testing
    answer = mult_DVector(a, b);
    output_DVector(answer, type, width, precision);
}

void test_divide_DVector(ITYPE type, ITYPE width, ITYPE precision)
{
    printf("TEST divide_DVector FUNCTION\n");
    DVector a, b, answer;
    ITYPE size_a, size_b;
    // read vector a
    scanf("%u", &size_a);
    a = generate_DVector(size_a);
    input_DVector(&a);
    // read vector b
    scanf("%u", &size_b);
    b = generate_DVector(size_b);
    input_DVector(&b);
    // testing
    answer = divide_DVector(a, b);
    output_DVector(answer, type, width, precision);
}

void test_mod_DVector(ITYPE type, ITYPE width, ITYPE precision)
{
    printf("TEST mod_DVector FUNCTION\n");
    DVector a, b, answer;
    ITYPE size_a, size_b;
    // read vector a
    scanf("%u", &size_a);
    a = generate_DVector(size_a);
    input_DVector(&a);
    // read vector b
    scanf("%u", &size_b);
    b = generate_DVector(size_b);
    input_DVector(&b);
    // testing
    answer = mod_DVector(a, b);
    output_DVector(answer, type, width, precision);
}

void test_multConst_DVector(ITYPE type, ITYPE width, ITYPE precision)
{
    printf("TEST multConst_DVector FUNCTION\n");
    DVector a, answer;
    ITYPE size_a;
    DTYPE b;
    // read vector a
    scanf("%u", &size_a);
    a = generate_DVector(size_a);
    input_DVector(&a);
    // read DTYPE b
    scanf("%lf", &b);
    // testing
    answer = multConst_DVector(a, b);
    output_DVector(answer, type, width, precision);
}

void test_divideConst_DVector(ITYPE type, ITYPE width, ITYPE precision)
{
    printf("TEST divideConst_DVector FUNCTION\n");
    DVector a, answer;
    ITYPE size_a;
    DTYPE b;
    // read vector a
    scanf("%u", &size_a);
    a = generate_DVector(size_a);
    input_DVector(&a);
    // read DTYPE b
    scanf("%lf", &b);
    // testing
    answer = divideConst_DVector(a, b);
    output_DVector(answer, type, width, precision);
}

void test_modConst_DVector(ITYPE type, ITYPE width, ITYPE precision)
{
    printf("TEST modConst_DVector FUNCTION\n");
    DVector a, answer;
    ITYPE size_a;
    DTYPE b;
    // read vector a
    scanf("%u", &size_a);
    a = generate_DVector(size_a);
    input_DVector(&a);
    // read DTYPE b
    scanf("%lf", &b);
    // testing
    answer = modConst_DVector(a, b);
    output_DVector(answer, type, width, precision);
}

void test_unadd_DVector(ITYPE type, ITYPE width, ITYPE precision)
{
    printf("TEST unadd_DVector FUNCTION\n");
    DVector a, b;
    ITYPE size_a, size_b;
    // read vector a
    scanf("%u", &size_a);
    a = generate_DVector(size_a);
    input_DVector(&a);
    // read vector b
    scanf("%u", &size_b);
    b = generate_DVector(size_b);
    input_DVector(&b);
    // testing
    if(unadd_DVector(&a, b))
        output_DVector(a, type, width, precision);
}

void test_unsub_DVector(ITYPE type, ITYPE width, ITYPE precision)
{
    printf("TEST unsub_DVector FUNCTION\n");
    DVector a, b;
    ITYPE size_a, size_b;
    // read vector a
    scanf("%u", &size_a);
    a = generate_DVector(size_a);
    input_DVector(&a);
    // read vector b
    scanf("%u", &size_b);
    b = generate_DVector(size_b);
    input_DVector(&b);
    // testing
    if(unsub_DVector(&a, b))
        output_DVector(a, type, width, precision);
}

void test_unmult_DVector(ITYPE type, ITYPE width, ITYPE precision)
{
    printf("TEST unmult_DVector FUNCTION\n");
    DVector a, b;
    ITYPE size_a, size_b;
    // read vector a
    scanf("%u", &size_a);
    a = generate_DVector(size_a);
    input_DVector(&a);
    // read vector b
    scanf("%u", &size_b);
    b = generate_DVector(size_b);
    input_DVector(&b);
    // testing
    if(unmult_DVector(&a, b))
        output_DVector(a, type, width, precision);
}

void test_undivide_DVector(ITYPE type, ITYPE width, ITYPE precision)
{
    printf("TEST undivide_DVector FUNCTION\n");
    DVector a, b;
    ITYPE size_a, size_b;
    // read vector a
    scanf("%u", &size_a);
    a = generate_DVector(size_a);
    input_DVector(&a);
    // read vector b
    scanf("%u", &size_b);
    b = generate_DVector(size_b);
    input_DVector(&b);
    // testing
    if(undivide_DVector(&a, b))
        output_DVector(a, type, width, precision);
}

void test_unmod_DVector(ITYPE type, ITYPE width, ITYPE precision)
{
    printf("TEST unmod_DVector FUNCTION\n");
    DVector a, b;
    ITYPE size_a, size_b;
    // read vector a
    scanf("%u", &size_a);
    a = generate_DVector(size_a);
    input_DVector(&a);
    // read vector b
    scanf("%u", &size_b);
    b = generate_DVector(size_b);
    input_DVector(&b);
    // testing
    if(unmod_DVector(&a, b))
        output_DVector(a, type, width, precision);
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

    test_sub_DVector(0, 7, 2);

    if (input_type == INPUT_FROM_FILE)
        fclose(stdin);

    if (ouput_type == OUTPUT_IN_FILE)
        fclose(stdout);
}
