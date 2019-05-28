/*
 * spline_tests_horbunov_kovaltchuk.c
 * by Horbunov Daniel & Kovaltchuk Anastasiya
 * project: Splines #8
 * email: dangor66@gmail.com
 */

#include "../headers/spline_horbunov_kovaltchuk.h"
//#include "../src/spline_horbunov_kovaltchuk.c"

#include <stdio.h>

void Test_No_1_rand_spline()
{
    printf("Test No 1:\n");

    Spline s;
    s = rand_spline(3, 1);
    output_spline(s, 0, 2, 2);
    free_spline(s);

    Spline v;
    v = rand_spline(3, 0);
    output_spline(v, 0, 2, 2);
    free_spline(v);
}

void Test_No_2_output_spline_float()
{
    printf("Test No 2:\n");

    Spline s;
    s = rand_spline(4, 1);
    output_spline(s, 0, 4, 4);
    free_spline(s);
}

void Test_No_3_output_spline_shortest()
{
    printf("Test No 3:\n");

    Spline s;
    s = rand_spline(4, 1);
    output_spline(s, 1, 4, 4);
    free_spline(s);
}

void Test_No_4_output_spline_scientific()
{
    printf("Test No 4:\n");

    Spline s;
    s = rand_spline(4, 1);
    output_spline(s, 2, 4, 4);
    free_spline(s);
}

void Test_No_5_output_defect_float()
{
    printf("Test No 5:\n");

    Spline s;
    s = rand_spline(4, 1);
    output_defect(s.defect_struct, 0, 4, 4);
    free_spline(s);
}

void Test_No_6_output_defect_shortest()
{
    printf("Test No 6:\n");

    Spline s;
    s = rand_spline(4, 1);
    output_defect(s.defect_struct, 1, 4, 4);
    free_spline(s);
}

void Test_No_7_output_defect_scientific()
{
    printf("Test No 7:\n");

    Spline s;
    s = rand_spline(4, 1);
    output_defect(s.defect_struct, 2, 4, 4);
    free_spline(s);
}

void Test_No_8_output_defect_float()
{
    printf("Test No 8:\n");

    Spline s;
    s = rand_spline(4, 1);
    output_polynomial(s.polynomial_array[0], 0, 4, 4);
    free_spline(s);
}

void Test_No_9_output_defect_shortest()
{
    printf("Test No 9:\n");

    Spline s;
    s = rand_spline(4, 1);
    output_polynomial(s.polynomial_array[0], 1, 4, 4);
    free_spline(s);
}

void Test_No_10_output_defect_scientific()
{
    printf("Test No 10:\n");

    Spline s;
    s = rand_spline(4, 1);
    output_polynomial(s.polynomial_array[0], 2, 4, 4);
    free_spline(s);
}

void Test_No_11_binary_arithmetic_add()
{
    printf("Test No 11:\n");

    Spline s1, s2, s3;

    s1 = rand_spline(5, 1);
    s2 = rand_spline(3, 1);

    s3 = add_spline(s1, s2);

    output_spline(s3, 0, 2, 2);

    free_spline(s1);
    free_spline(s2);
    free_spline(s3);
}

void Test_No_12_binary_arithmetic_sub()
{
    printf("Test No 12:\n");

    Spline s1, s2, s3;

    s1 = rand_spline(5, 1);
    s2 = rand_spline(3, 1);

    s3 = sub_spline(s1, s2);

    output_spline(s3, 0, 2, 2);

    free_spline(s1);
    free_spline(s2);
    free_spline(s3);
}

void Test_No_13_binary_arithmetic_mul()
{
    printf("Test No 13:\n");

    Spline s1, s2, s3;

    s1 = rand_spline(5, 1);
    s2 = rand_spline(3, 1);

    s3 = mul_spline(s1, s2);

    output_spline(s3, 0, 2, 2);

    free_spline(s1);
    free_spline(s2);
    free_spline(s3);
}

void Test_No_14_binary_arithmetic_mul_scalar()
{
    printf("Test No 14:\n");

    Spline s1, s2;

    float c = 4;

    s1 = rand_spline(5, 1);

    s2 = mul_spline_by_scalar(s1, c);

    output_spline(s2, 0, 2, 2);

    free_spline(s1);
    free_spline(s2);
}

void Test_No_15_binary_arithmetic_div_scalar()
{
    printf("Test No 15:\n");

    Spline s1, s2;

    float c = 4;

    s1 = rand_spline(5, 1);

    s2 = div_spline_by_scalar(s1, c);

    output_spline(s2, 0, 2, 2);

    free_spline(s1);
    free_spline(s2);
}

void Test_No_16_spline_derivative()
{
    printf("Test No 16:\n");

    Spline s, d;

    s = rand_spline(5, 1);

    d = derivative_of_spline(s);

    output_spline(d, 0, 2, 2);

    free_spline(s);
    free_spline(d);
}

void Test_No_17_spline_integral()
{
    printf("Test No 17:\n");

    Spline s, i;

    float c = 4;

    s = rand_spline(5, 1);

    i = integral_of_spline(s, c);

    output_spline(i, 0, 2, 2);

    free_spline(s);
    free_spline(i);
}

void Test_No_18_spline_riemann()
{
    printf("Test No 18:\n");

    Spline s;

    float a = 1, b = 2.5, i;

    s = rand_spline(5, 1);

    i = riemann_integral_of_spline(s, a, b);

    printf("I = %f\n", i);

    free_spline(s);
}


void Test_No_19_write_spline_into_text_file()
{
    printf("Test No 19:\n");

    FILE *f;

    Spline s;

    s = rand_spline(6, 1);

    f = fopen("../file.txt", "w");

    write_spline(s, f);

    fclose(f);

    free_spline(s);
}

void Test_No_20_read_spline_from_text_file()
{
    printf("Test No 20:\n");

    FILE *f;

    Spline s;

    f = fopen("../file.txt", "r");

    read_spline(&s, f);

    fclose(f);

    output_spline(s, 0, 2, 2);

    free_spline(s);
}

int main()
{
    Spline s, s0;

    s = rand_spline(3, 1);
    s0 = rand_spline(5, 1);

    output_spline(s, 0, 3, 3);
    output_spline(s0, 0, 3, 3);

    output_spline(add_spline(s, s0), 0, 2, 2);

    free_spline(s);
    free_spline(s0);

    /*
    Test_No_1_rand_spline();
    Test_No_2_output_spline_float();
    Test_No_3_output_spline_shortest();
    Test_No_4_output_spline_scientific();
    Test_No_5_output_defect_float();
    Test_No_6_output_defect_shortest();
    Test_No_7_output_defect_scientific();
    Test_No_8_output_defect_float();
    Test_No_9_output_defect_shortest();
    Test_No_10_output_defect_scientific();
    Test_No_11_binary_arithmetic_add();
    Test_No_12_binary_arithmetic_sub();
    Test_No_13_binary_arithmetic_mul();
    Test_No_14_binary_arithmetic_mul_scalar();
    Test_No_15_binary_arithmetic_div_scalar();
    Test_No_16_spline_derivative();
    Test_No_17_spline_integral();
    Test_No_18_spline_riemann();
    Test_No_19_write_spline_into_text_file();
    Test_No_20_read_spline_from_text_file();
     */
}
