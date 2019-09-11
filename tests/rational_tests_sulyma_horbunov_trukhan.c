/*
 * rational_tests_sulyma_horbunov_trukhan.c
 * by Sulyma Mariia, Ernest Trukhan
 * project: Rational #4
 * email: marysulyma@gmail.com, quiz290600@gmail.com
 */

#include "../headers/rational_sulyma_horbunov_trukhan.h"

#define ERR_INVALID_INPUT 1

#include <math.h>
#include <stdlib.h>

void TestsFractionNormal()
{
    Fraction a, b;

    a = console_read_fraction();

    b = console_read_fraction();

    printf("Init fractions:\n");

    stream_print_fraction(stdout, a);

    stream_print_fraction(stdout, b);

    printf("Boolean:\n");

    printf("a == b ? %i\n", eq_fractions(a, b));

    printf("a != b ? %i\n", neq_fractions(a, b));

    printf("a > b ? %i\n", g_fractions(a, b));

    printf("a >= b ? %i\n", ge_fractions(a, b));

    printf("a < b ? %i\n", l_fractions(a, b));

    printf("a <= b ? %i\n", le_fractions(a, b));

    printf("max(a, b) = ");
    stream_print_fraction(stdout, fr_max(a, b));

    printf("min(a, b) = ");
    stream_print_fraction(stdout, fr_min(a, b));

    printf("Arithmetic:\n");

    printf("Binary:\n");

    printf("a + b = ");
    stream_print_fraction(stdout, binary_add(a, b));

    printf("a - b = ");
    stream_print_fraction(stdout, binary_sub(a, b));

    printf("a * b = ");
    stream_print_fraction(stdout, binary_mul(a, b));

    printf("a / b = ");
    stream_print_fraction(stdout, binary_div(a, b));

    IType c;

    printf("c = ");
    scanf("%lli", &c);

    printf("%lli <-> ", c);
    stream_print_fraction(stdout, int_to_fraction(c));

    printf("a + %lli = ", c);
    stream_print_fraction(stdout, scalar_binary_add(a, c));

    printf("a - %lli = ", c);
    stream_print_fraction(stdout, scalar_binary_sub(a, c));

    printf("a * %lli = ", c);
    stream_print_fraction(stdout, scalar_binary_mul(a, c));

    printf("a / %lli = ", c);
    stream_print_fraction(stdout, scalar_binary_div(a, c));

    printf("div_mod(a) = %lli\ndiv_mod(b) = %lli\n", binary_div_mod(a), binary_div_mod(b));

    printf("Unary:\n");

    unary_add(&b, a);
    printf("b = b + a = ");
    stream_print_fraction(stdout, b);

    printf("b = b - a = ");
    unary_sub(&b, a);
    stream_print_fraction(stdout, b);

    printf("b = b * a = ");
    unary_mul(&b, a);
    stream_print_fraction(stdout, b);

    printf("b = b / a = ");
    unary_div(&b, a);
    stream_print_fraction(stdout, b);

    printf("a + %lli = ", c);
    scalar_unary_add(&a, c);
    stream_print_fraction(stdout, a);

    printf("a - %lli = ", c);
    scalar_unary_sub(&a, c);
    stream_print_fraction(stdout, a);

    printf("a * %lli = ", c);
    scalar_unary_mul(&a, c);
    stream_print_fraction(stdout, a);

    printf("a / %lli = ", c);
    scalar_unary_div(&a, c);
    stream_print_fraction(stdout, a);

    printf("Write into text file:\n");

    FILE *out;

    out = fopen("../file_output.txt", "w");

    FractionArray d;

    create(&d, 2, a, b);

    stream_print_fractions(stdout, d);

    printf("\n");

    insert(&d, 1, binary_mul(a, b));

    stream_print_fractions(stdout, d);

    stream_print_fractions(out, d);

    fclose(out);

    free_FractionArray(d);
    
    printf("Randomly generated fraction:\n");
    
    stream_print_fraction(stdout, generate_random_fraction());
}

void TestsFractionTextFiles()
{
    Fraction b;

    b = fraction(4, 6);

    FILE *in;

    in = fopen("../file_input.txt", "w");

    stream_print_fraction(in, b);

    fclose(in);

    in = fopen("../file_input.txt", "r");

    Fraction a;

    a = stream_read_fraction(in);

    stream_print_fraction(stdout, a);

    fclose(in);
}

void TestsChainFractionNormal()
{
    printf("M_PI = %.32f\n", M_PI);

    ChainFraction r[2];

    r[0] = create_N(M_PI, 4);

    r[1] = create_E(M_PI, 1e-7);

    for(NType j=0; j<2; j++)
    {
        printf("\n==========================\n");

        printf("ChainFraction #%lu\n", j);

        printf("get_value = %.32f\n", get_value(r[j]));

        printf("get_epsilon = %.32f\n", get_epsilon(r[j]));

        printf("Output as fraction:\n");

        stream_print_fraction(stdout, get_fraction(r[j]));

        printf("Diophantine approximation:\n");

        console_output_as_fraction(r[j]);

        printf("More detailed output for ChainFraction:\n");

        stream_output_chain_fraction(stdout, r[j]);

        printf("\n==========================\n");
    }

    printf("Finally, writing some data...\n");

    FILE *out;

    out = fopen("../file_output_chain.txt", "w");

    stream_output_chain_fraction(out, r[0]);

    fclose(out);

    printf("Done.\n");

    free_ChainFraction(r[0]); free_ChainFraction(r[1]);
}

void TestsChainFractionTextFiles()
{
    printf("Read ChainFraction structure data from text file:\n");

    FILE *in;

    in = fopen("../file_output_chain.txt", "r");

    ChainFraction a;

    stream_input_chain_fraction(in, &a);

    stream_output_chain_fraction(stdout, a);

    fclose(in);

    free_ChainFraction(a);
}

void TestGregory()
{
    printf("Calculating PI/4 using Gregory formula:\n");

    NType n;

    printf("N = ");

    scanf("%lu", &n);

    printf("PI/4 ≈ %.32f\n", gregory_formula(n));
}

int main()
{
    HType m;

    printf("Enter mode:\n"
           "1 - Basic operations with fractions\n"
           "2 - Interaction with text files. Fraction\n"
           "3 - ChainFraction implementation check\n"
           "4 - Interaction with text files. ChainFraction\n"
           "5 - fun\n");
    scanf("%hi", &m);

    switch(m)
    {
        case 1:
        {
            TestsFractionNormal();
            break;
        }
        case 2:
        {
            TestsFractionTextFiles();
            break;
        }
        case 3:
        {
            TestsChainFractionNormal();
            break;
        }
        case 4:
        {
            TestsChainFractionTextFiles();
            break;
        }
        case 5:
        {
            TestGregory();
            break;
        }
        default:
        {
            printf("Invalid value, exiting..\n");
            exit(ERR_INVALID_INPUT);
        }
    }
}
