/*
 * spline_tests_horbunov_kovaltchuk.c
 * by Horbunov Daniel & Kovaltchuk Anastasiya
 * project: Splines #8
 * email #1: dangor66@gmail.com
 * email #2: nastasiaKovalchuk15@gmail.com
 */

#define ERR_INVALID_INPUT 1
#define ERR_SIGNAL 2

#include "../headers/spline_horbunov_kovaltchuk.h"

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void err_msg()
{
    printf("\n"
           "\t< MESSAGE >\t\n"
           "Unexpected error happened.\n"
           "Please contact with MilkyCousin\n"
           "or KovaltchukNastia.\n"
           "\t< MESSAGE >\t\n"
           "\n");
}

void signal_sigsegv(int signum)
{
    err_msg();
    signal(signum, SIG_DFL);
    exit(ERR_SIGNAL);
}

void output_splines(Spline s1, Spline s2, int mode, int w, int p)
{
    output_spline(s1, mode, w, p);
    output_spline(s2, mode, w, p);
}

void Tests(short output_mode, short mode)
{
    signal(SIGSEGV, signal_sigsegv);
    signal(SIGABRT, signal_sigsegv);

    // just don't kill me for that. compiler was arguing right there
    Spline spline_1={0,0}, spline_2={0,0};

    switch (mode)
    {
        case 1:
        {
            printf("Enter values for spline #1:\n");
            input_spline(&spline_1);

            printf("Enter values for spline #2:\n");
            input_spline(&spline_2);

            break;
        }
        case 2:
        {
            FILE *f_r_spline1, *f_r_spline2;

            f_r_spline1 = fopen("../from_spline_1.txt", "r");
            f_r_spline2 = fopen("../from_spline_2.txt", "r");

            read_spline(&spline_1, f_r_spline1);
            read_spline(&spline_2, f_r_spline2);

            fclose(f_r_spline1);
            fclose(f_r_spline2);

            break;
        }
        default:
        {
            spline_1 = rand_spline(6, 1);

            spline_2 = rand_spline(5, 1);
        }
    }

    printf("Init output values:\n");
    output_splines(spline_1, spline_2, output_mode, 4, 4);

    Spline derivative_1, derivative_2;

    derivative_1 = derivative_of_spline(spline_1);
    derivative_2 = derivative_of_spline(spline_2);

    printf("Derivative of splines:\n");

    output_splines(derivative_1, derivative_2, output_mode, 4, 4);

    Spline integral_1, integral_2;

    integral_1 = integral_of_spline(spline_1, 0);
    integral_2 = integral_of_spline(spline_2, 0);


    printf("Integral of splines, C = 0:\n");

    output_splines(integral_1, integral_2, output_mode, 4, 4);

    float i_value_1, i_value_2;

    i_value_1 = riemann_integral_of_spline(spline_1, 0, 1);
    i_value_2 = riemann_integral_of_spline(spline_2, 0, 1);

    printf("Integral[0, 1] of spline #1 is: %.4f\n", i_value_1);
    printf("Integral[0, 1] of spline #2 is: %.4f\n", i_value_2);

    float t, calc_1, calc_2;

    printf("Input value for calculation:\n");
    scanf("%f", &t);

    calc_1 = calculate_spline(spline_1, t);
    calc_2 = calculate_spline(spline_2, t);

    printf("S_1(%.4f) = %.4f\n", t, calc_1);
    printf("S_2(%.4f) = %.4f\n", t, calc_2);

    printf("\n");

    Spline sum_of_splines;

    sum_of_splines = add_spline(spline_1, spline_2);

    printf("Sum of splines:\n");
    output_spline(sum_of_splines, output_mode, 4, 4);

    Spline sub_of_splines;

    sub_of_splines = sub_spline(spline_1, spline_2);

    printf("Subtraction of splines:\n");
    output_spline(sub_of_splines, output_mode, 4, 4);

    Spline mul_of_splines;

    mul_of_splines = mul_spline(spline_1, spline_2);

    printf("Multiplication of splines:\n");
    output_spline(mul_of_splines, output_mode, 4, 4);

    float c;

    printf("Input scalar:\n");
    scanf("%f", &c);

    Spline spline_mul_by_scalar;

    spline_mul_by_scalar = mul_spline_by_scalar(spline_1, c);

    printf("Multiplication of spline #1 by scalar:\n");
    output_spline(spline_mul_by_scalar, output_mode, 4, 4);

    Spline spline_div_by_scalar;

    spline_div_by_scalar = div_spline_by_scalar(spline_2, c);

    printf("Division of spline #2 by scalar:\n");
    output_spline(spline_div_by_scalar, output_mode, 4, 4);

    printf("Unary arithmetic for spline #2:\n");

    printf("Sum:\n");
    un_add_spline(&spline_2, spline_1);
    output_spline(spline_2, output_mode, 4, 4);

    printf("Subtraction:\n");
    un_sub_spline(&spline_2, spline_1);
    output_spline(spline_2, output_mode, 4, 4);

    printf("Multiplication:\n");
    un_mul_spline(&spline_2, spline_1);
    output_spline(spline_2, output_mode, 4, 4);

    printf("Scalar multiplication and division by %.4f:\n", c);

    un_mul_spline_by_scalar(&spline_2, c);
    output_spline(spline_2, output_mode, 4, 4);

    un_div_spline_by_scalar(&spline_2, c);
    output_spline(spline_2, output_mode, 4, 4);

    printf("Finally, writing some data into text files..\n");

    FILE *f_w_spline1, *f_w_spline2;

    f_w_spline1 = fopen("../to_spline_1.txt", "w");
    f_w_spline2 = fopen("../to_spline_2.txt", "w");

    write_spline(spline_1, f_w_spline1);
    write_spline(spline_2, f_w_spline2);

    fclose(f_w_spline1);
    fclose(f_w_spline2);

    printf("Done.\n");

    free_spline(&spline_1);
    free_spline(&spline_2);
    free_spline(&sum_of_splines);
    free_spline(&sub_of_splines);
    free_spline(&mul_of_splines);
    free_spline(&spline_mul_by_scalar);
    free_spline(&spline_div_by_scalar);
    free_spline(&derivative_1);
    free_spline(&derivative_2);
    free_spline(&integral_1);
    free_spline(&integral_2);
}

int main()
{
    short m, out_m;

    printf("Choose mode:\n"
           "1 - read splines from console\n"
           "2 - read from txt files\n"
           "3 - generate random splines\n");

    scanf("%hi", &m);

    printf("Choose output mode:\n"
           "0 - normal float\n"
           "1 - short format\n"
           "2 - scientific format\n");

    scanf("%hi", &out_m);

    switch(m)
    {
        case 1:
        case 2:
        case 3:
        {
            Tests(out_m, m);
            break;
        }
        default:
        {
            printf("Invalid input.\nExiting..\n");
            exit(ERR_INVALID_INPUT);
        }
    }
}
