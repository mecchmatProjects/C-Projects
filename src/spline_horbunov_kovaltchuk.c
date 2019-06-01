/*
 * spline_horbunov_kovaltchuk.c
 * by Horbunov Daniel & Kovaltchuk Anastasiya
 * project: Splines #8
 * email #1: dangor66@gmail.com
 * email #2: nastasiaKovalchuk15@gmail.com
 */

#include "../headers/spline_horbunov_kovaltchuk.h"

#define MIN_NET_ELEMENTS 2
#define MIN_POWER 0

#include <assert.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
 * 0.1 Utility function in order to calculate powers of numbers
 */
static float power(float x, unsigned r) { if (!r) return 1; else return x * power(x, r - 1); }
/*
 * 0.2 Utility function in order to sort numeric array
 */
static void selection_sort(float *a, unsigned n) {
    unsigned i, j, k;
    float x;
    for (i = 0; i <= n - 2; i++) {
        j = i;
        for (k = i + 1; k <= n - 1; k++) if (a[k] <= a[j]) j = k;
        x = a[j];
        a[j] = a[i];
        a[i] = x;
    }
}
/*
 * 1.0 Function that is used to check if there are the same elements in the net
 * IN - Defect struct OUT - short 0 or 1
 */
static short check(Defect d) {
    short cnt;
    for (int i = 0; i < d.m; i++) {
        cnt = 0;

        for (int j = 0; j < d.m; j++) {
            if (d.net[i] == d.net[j]) {
                cnt++;
            }

            if (cnt > 1) return 0;
        }
    }
    return 1;
}

// UTILITY FUNCTIONS FOR STRUCTURE NAMED DEFECT

void free_polynomial(Polynomial *p)
{
    free(p->coefficients);
    p->coefficients = NULL;
}

// UTILITY FUNCTIONS FOR STRUCTURE NAMED DEFECT
static void copy_defect(Defect *to, Defect from)
{
    to->m = from.m;
    to->net = (float*)calloc(to->m, sizeof(float));
    for(unsigned i=0; i<to->m; i++) to->net[i] = from.net[i];
}

void free_defect(Defect *d)
{
    free(d->net);
    d->net = NULL;
}
/*
 * 2.0 Function that is used to check if given nets from different Defect structures are the same or not
 * IN - Defect structures OUT - short 0 or 1
 */
short is_same_defect_net(Defect d_0, Defect d_1) {
    if (d_0.m != d_1.m) return 0;
    else for (unsigned i = 0; i < d_0.m; i++) if (d_0.net[i] != d_1.net[i]) return 0;
    return 1;
}

// OPERATIONS WITH STRUCTURE NAMED POLYNOMIAL

/*
 * 3.0 Function that is used to calculate tha value of polynomial
 */
float calculate_polynomial(Polynomial x, float t) {
    float result = 0;
    for (unsigned i = 0; i < x.n; i++) { result += x.coefficients[i] * power(t, i); }
    return result;
}

/*
 * 4.0 Function that returns a polynomial made out of the sum of the given ones
 */
Polynomial add_polynomial(Polynomial x, Polynomial y) {
    Polynomial result;

    result.n = (x.n > y.n) ? x.n : y.n;
    result.coefficients = (float *) calloc(result.n, sizeof(float));

    for (unsigned i = 0; i < result.n; i++) { result.coefficients[i] = 0; }

    for (unsigned i = 0; i < x.n; i++) { result.coefficients[i] = x.coefficients[i]; }

    for (unsigned i = 0; i < y.n; i++) { result.coefficients[i] += y.coefficients[i]; }

    return result;
}
/*
 * 5.0 Function that returns a polynomial made out of the subtraction of the given ones
 */
Polynomial sub_polynomial(Polynomial x, Polynomial y) {
    Polynomial result;

    result.n = (x.n > y.n) ? x.n : y.n;
    result.coefficients = (float *) calloc(result.n, sizeof(float));

    for (unsigned i = 0; i < result.n; i++) { result.coefficients[i] = 0; }

    for (unsigned i = 0; i < x.n; i++) { result.coefficients[i] = x.coefficients[i]; }

    for (unsigned i = 0; i < y.n; i++) { result.coefficients[i] -= y.coefficients[i]; }

    return result;
}
/*
 * 6.0 Function that returns a polynomial made out of the multiplication of the given ones
 */
Polynomial mul_polynomial(Polynomial x, Polynomial y) {
    Polynomial result;

    result.n = (x.n + y.n) - 1;
    result.coefficients = (float *) calloc(result.n, sizeof(float));

    for (unsigned i = 0; i < result.n; i++) { result.coefficients[i] = 0; }

    for (unsigned i = 0; i < x.n; i++) {
        for (unsigned j = 0; j < y.n; j++) { result.coefficients[i + j] += x.coefficients[i] * y.coefficients[j]; }
    }

    return result;
}
/*
 * 7.0 Multiplication by scalar value
 */
Polynomial mul_polynomial_by_scalar(Polynomial x, float c) {
    Polynomial result;

    result.coefficients = (float *) calloc(result.n = x.n, sizeof(float));

    for (unsigned i = 0; i < result.n; i++) { result.coefficients[i] = x.coefficients[i] * c; }

    return result;
}
/*
 * 8.0 Division by scalar value
 */
Polynomial div_polynomial_by_scalar(Polynomial x, float c) {
    Polynomial result;

    result.coefficients = (float *) calloc(result.n = x.n, sizeof(float));

    for (unsigned i = 0; i < result.n; i++) { result.coefficients[i] = x.coefficients[i] / c; }

    return result;
}

/*
 * 9.0 Find the derivative of given polynomial
 */
Polynomial derivative_of_polynomial(Polynomial x) {
    Polynomial result;

    result.coefficients = (float *) calloc(result.n = x.n - 1, sizeof(float));

    for (unsigned i = 0; i < result.n; i++) { result.coefficients[i] = x.coefficients[i + 1] * (i + 1); }

    return result;
}

/*
 * 10.0 Find the integral of given polynomial
 */
Polynomial integral_of_polynomial(Polynomial x, float c) {
    Polynomial result;

    result.coefficients = (float *) calloc(result.n = x.n + 1, sizeof(float));

    for (unsigned i = 1; i < result.n; i++) { result.coefficients[i] = x.coefficients[i-1] / (i); }

    result.coefficients[0] = c;

    return result;
}

/*
 * 9.0 Calculate riemann integral of given polynomial
 */
float riemann_integral_of_polynomial(Polynomial x, float a, float b) {
    Polynomial y = integral_of_polynomial(x, 0);

    float result = calculate_polynomial(y, b) - calculate_polynomial(y, a);

    free_polynomial(&y);

    return result;
}

// OPERATIONS WITH STRUCTURE NAMED SPLINE

/*
 * 10.0 Used in order to free space from Spline structure.
 * First of all: abusing free() function on each polynomial from polynomial_array
 * Then free(net) from defect_struct
 */
void free_spline(Spline *s) {
    for (unsigned i = 0; i < s->defect_struct.m-1; i++)
    {
        free_polynomial(&s->polynomial_array[i]);
    }
    free(s->polynomial_array);
    s->polynomial_array = NULL;
    free_defect(&s->defect_struct);
}
/*
 * 11.0 Calculate the value of Spline
 * First of all, checking whether given dot belongs to given net or not
 * Finally, calculating the value using some polynomial from array
 */
float calculate_spline(Spline s, float t) {
    for (unsigned i = 0; i < s.defect_struct.m - 1; i++) {
        if ((s.defect_struct.net[i] <= t) && (t <= s.defect_struct.net[i + 1]))
            return calculate_polynomial(s.polynomial_array[i], t);
    }
    return 0;
}

/*
 * 12.0 Arithmetic for Splines, basically, the same as for Polynomial ones.
 * Excluding those iterations and net-checking functions.
 */
Spline add_spline(Spline s_0, Spline s_1) {
    if (!is_same_defect_net(s_0.defect_struct, s_1.defect_struct)) exit(1);

    Spline result;

    copy_defect(&result.defect_struct, s_0.defect_struct);
    result.n = s_0.n;

    result.polynomial_array = (Polynomial *) calloc(result.defect_struct.m, sizeof(Polynomial));

    for (unsigned i = 0; i < result.defect_struct.m - 1; i++) {
        result.polynomial_array[i] =
                add_polynomial(s_0.polynomial_array[i], s_1.polynomial_array[i]);
    }
    return result;
}
/*
 * 13.0 -> 12.0
 */
Spline sub_spline(Spline s_0, Spline s_1) {
    if (!is_same_defect_net(s_0.defect_struct, s_1.defect_struct)) exit(1);

    Spline result;

    copy_defect(&result.defect_struct, s_0.defect_struct);
    result.n = s_0.n;

    result.polynomial_array = (Polynomial *) calloc(result.defect_struct.m, sizeof(Polynomial));

    for (unsigned i = 0; i < result.defect_struct.m - 1; i++) {
        result.polynomial_array[i] =
                sub_polynomial(s_0.polynomial_array[i], s_1.polynomial_array[i]);
    }

    return result;
}
/*
 * 14.0 -> 12.0
 */
Spline mul_spline_by_scalar(Spline s_0, float c) {
    Spline result;

    copy_defect(&result.defect_struct, s_0.defect_struct);
    result.n = s_0.n;

    result.polynomial_array = (Polynomial *) calloc(result.defect_struct.m, sizeof(Polynomial));

    for (unsigned i = 0; i < result.defect_struct.m - 1; i++) {
        result.polynomial_array[i] =
                mul_polynomial_by_scalar(s_0.polynomial_array[i], c);
    }

    return result;
}
/*
 * 15.0 -> 12.0
 */
Spline div_spline_by_scalar(Spline s_0, float c) {
    assert(c);

    Spline result;

    copy_defect(&result.defect_struct, s_0.defect_struct);
    result.n = s_0.n;

    result.polynomial_array = (Polynomial *) calloc(result.defect_struct.m, sizeof(Polynomial));

    for (unsigned i = 0; i < result.defect_struct.m - 1; i++) {
        result.polynomial_array[i] =
                div_polynomial_by_scalar(s_0.polynomial_array[i], c);
    }

    return result;
}
/*
 * 16.0 -> 12.0
 */
Spline mul_spline(Spline s_0, Spline s_1)
{
    if (!is_same_defect_net(s_0.defect_struct, s_1.defect_struct)) exit(1);

    Spline result;

    copy_defect(&result.defect_struct, s_0.defect_struct);
    result.n = s_0.n * s_1.n - 1;

    result.polynomial_array = (Polynomial *) calloc(result.defect_struct.m, sizeof(Polynomial));

    for (unsigned i = 0; i < result.defect_struct.m - 1; i++) {
        result.polynomial_array[i] =
                mul_polynomial(s_0.polynomial_array[i], s_1.polynomial_array[i]);
    }

    return result;
}
/*
 * 17.0 Unary arithmetic for Splines. Also, see 12.0
 */
void un_add_spline(Spline *s_0, Spline s_1) {
    if (!is_same_defect_net(s_0->defect_struct, s_1.defect_struct)) exit(1);

    Spline result;

    copy_defect(&result.defect_struct, s_0->defect_struct);
    result.n = s_0->n;

    result.polynomial_array = (Polynomial *) calloc(result.defect_struct.m, sizeof(Polynomial));

    for (unsigned i = 0; i < result.defect_struct.m - 1; i++) {
        result.polynomial_array[i] =
                add_polynomial(s_0->polynomial_array[i], s_1.polynomial_array[i]);
    }

    free_spline(s_0);

    *s_0 = result;
}

void un_sub_spline(Spline *s_0, Spline s_1) {
    if (!is_same_defect_net(s_0->defect_struct, s_1.defect_struct)) exit(1);

    Spline result;

    copy_defect(&result.defect_struct, s_0->defect_struct);
    result.n = s_0->n;

    result.polynomial_array = (Polynomial *) calloc(result.defect_struct.m, sizeof(Polynomial));

    for (unsigned i = 0; i < result.defect_struct.m - 1; i++) {
        result.polynomial_array[i] =
                sub_polynomial(s_0->polynomial_array[i], s_1.polynomial_array[i]);
    }

    free_spline(s_0);

    *s_0 = result;
}

void un_mul_spline_by_scalar(Spline *s_0, float c) {
    Spline result;

    copy_defect(&result.defect_struct, s_0->defect_struct);
    result.n = s_0->n;

    result.polynomial_array = (Polynomial *) calloc(result.defect_struct.m, sizeof(Polynomial));

    for (unsigned i = 0; i < result.defect_struct.m - 1; i++) {
        result.polynomial_array[i] =
                mul_polynomial_by_scalar(s_0->polynomial_array[i], c);
    }

    free_spline(s_0);

    *s_0 = result;
}

void un_div_spline_by_scalar(Spline *s_0, float c) {
    assert(c);

    Spline result;

    copy_defect(&result.defect_struct, s_0->defect_struct);
    result.n = s_0->n;

    result.polynomial_array = (Polynomial *) calloc(result.defect_struct.m, sizeof(Polynomial));

    for (unsigned i = 0; i < result.defect_struct.m - 1; i++) {
        result.polynomial_array[i] =
                div_polynomial_by_scalar(s_0->polynomial_array[i], c);
    }

    free_spline(s_0);

    *s_0 = result;
}

void un_mul_spline(Spline *s_0, Spline s_1)
{
    if (!is_same_defect_net(s_0->defect_struct, s_1.defect_struct)) exit(1);

    Spline result;

    copy_defect(&result.defect_struct, s_0->defect_struct);
    result.n = s_0->n * s_1.n - 1;

    result.polynomial_array = (Polynomial *) calloc(result.defect_struct.m, sizeof(Polynomial));

    for (unsigned i = 0; i < result.defect_struct.m - 1; i++) {
        result.polynomial_array[i] =
                mul_polynomial(s_0->polynomial_array[i], s_1.polynomial_array[i]);
    }

    free_spline(s_0);

    *s_0 = result;
}
/*
 * 18.0 Like in 9.0, but with iterations
 */
Spline derivative_of_spline(Spline s) {
    Spline result;

    copy_defect(&result.defect_struct, s.defect_struct);
    result.n = s.n - 1;

    result.polynomial_array = (Polynomial *) calloc(result.defect_struct.m, sizeof(Polynomial));

    for (unsigned i = 0; i < result.defect_struct.m -1 ; i++) {
        result.polynomial_array[i] =
                derivative_of_polynomial(s.polynomial_array[i]);
    }

    return result;
}
/*
 * 18.0 Like in 10.0, but with iterations
 */
Spline integral_of_spline(Spline s, float c) {
    Spline result;

    copy_defect(&result.defect_struct, s.defect_struct);
    result.n = s.n + 1;

    result.polynomial_array = (Polynomial *) calloc(result.defect_struct.m, sizeof(Polynomial));

    for (unsigned i = 0; i < result.defect_struct.m; i++) {
        result.polynomial_array[i] =
                integral_of_polynomial(s.polynomial_array[i], c);
    }

    return result;
}
/*
 * 19.0 Dividing interval a,b into smaller parts, depends on the number of nodes,
 * that belong to the given interval
 */
float riemann_integral_of_spline(Spline s, float a, float b) {
    float result = 0;
    float buf = a;
    for(unsigned i=0; i<s.defect_struct.m - 1; i++)
    {
        if((a <= s.defect_struct.net[i]) && (s.defect_struct.net[i] <= b))
        {
            result += riemann_integral_of_polynomial(s.polynomial_array[i], buf, s.defect_struct.net[i]);
            buf = s.defect_struct.net[i];
        }

        if((s.defect_struct.net[i] < b) && (s.defect_struct.net[i+1] >= b))
        {
            result += riemann_integral_of_polynomial(s.polynomial_array[i], s.defect_struct.net[i], b);
        }
    }
    return result;
}

//I/O functions
/*
 * 20.0 - Output with given type, width and precision
 */
void output_polynomial(Polynomial poly, int type, int width, int precision) {
    if ((type < 0) || (type > 2)) type = 0;
    char modes[3][4] = {"f", "g", "e"};
    char out[96] = "%", buf[64];
    sprintf(buf, "%d.%d", width, precision);
    strcat(out, buf);
    strcat(out, modes[type]);
    for (int i = 0; i < poly.n; i++) {
        if(poly.coefficients[i])
        {
            printf("(");
            printf(out, poly.coefficients[i]);
            printf(")");

            printf(" * x^%i", i);

            if((i != poly.n - 1) && poly.coefficients[i+1])
                printf(" + ");
        }
    }
    printf("\n");
}

void output_defect(Defect defect, int type, int width, int precision) {
    if ((type < 0) || (type > 2)) type = 0;
    char modes[3][4] = {"f ", "g ", "e "};
    char out[96] = "%", buf[64];
    sprintf(buf, "%d.%d", width, precision);
    strcat(out, buf);
    strcat(out, modes[type]);
    printf("|| DEFECT OUTPUT ||\n");
    for (int i = 0; i < defect.m; i++) {
        printf(out, defect.net[i]);
    }
    printf("\n");
}

void output_spline(Spline spline, int type, int width, int precision) {
    if ((type < 0) || (type > 2)) type = 0;
    output_defect(spline.defect_struct, type, width, precision);
    printf("|| POLYNOMIAL SYSTEM OUTPUT ||\n");
    for (unsigned i = 0; i < spline.defect_struct.m-1; i++)
    {
        printf("P_%i = ", i);
        output_polynomial(spline.polynomial_array[i], type, width, precision);
    }
    printf("\n");
}

/*
 * 21.0 - Function to write spline data into text file.
 * Based on fprintf abuse and wizardry
 */
void write_spline(Spline s, FILE *f)
{
    assert(f != NULL);

    fprintf(f, "%u %u\n", s.defect_struct.m, s.n);

    for(unsigned i=0; i<s.defect_struct.m; i++)
    {
        fprintf(f, "%f ", s.defect_struct.net[i]);
    }
    fprintf(f, "\n");

    for(unsigned j=0; j<s.defect_struct.m-1; j++)
    {
        for(unsigned i=0; i<s.n; i++)
        {
            fprintf(f, "%f ", s.polynomial_array[j].coefficients[i]);
        }
        fprintf(f, "\n");
    }
}

/*
 * 22.0 - Function to read spline data from text file.
 * Based on fscanf unsafe exploit.
 * Also splitting c-string into parts by using strtok and some pointer extravaganza
 */
void read_spline(Spline *s, FILE *f)
{
    char *line = NULL;

    char *current;

    size_t len = 0;

    assert(f != NULL);

    fscanf(f, "%u %u\n", &s->defect_struct.m, &s->n);

    printf("%u %u\n", s->defect_struct.m, s->n);

    s->defect_struct.net = (float *) calloc(s->defect_struct.m, sizeof(float));

    s->polynomial_array = (Polynomial*)calloc(s->defect_struct.m-1, sizeof(Polynomial));

    getline(&line, &len, f);

    current = strtok(line, " ");
    for(unsigned i=0; i<s->defect_struct.m; i++)
    {
        s->defect_struct.net[i] = strtof(current, NULL);

        current = strtok(NULL, " ");
    }

    for(unsigned j=0; j<s->defect_struct.m-1; j++)
    {
        getline(&line, &len, f);

        s->polynomial_array[j].n = s->n;
        s->polynomial_array[j].coefficients = (float *) calloc(s->n, sizeof(float));

        current = strtok(line, " ");
        for(unsigned i=0; i<s->n; i++)
        {
            s->polynomial_array[j].coefficients[i] = strtof(current, NULL);

            current = strtok(NULL, " ");
        }
    }
}

/*
 * 23.0 - For writing some data, given by user
 */
void input_polynomial(Polynomial *p, unsigned len) {

    p->n = len;

    p->coefficients = (float *) calloc(p->n, sizeof(float));

    for (unsigned i = 0; i < p->n; i++) {
        printf("p[%i] = ", i);
        scanf("%f", p->coefficients + i);
    }
}

/*
 * 24.0 mode is only used for tests
 * rand_spline makes a spline ( except not really ) with randomly generated polynomials
 */
Spline rand_spline(unsigned len, short mode)
{
    int stime;
    long ltime;

    // It is generally used to "seed" the random number generator.
    ltime = time (NULL);
    stime = (unsigned int)ltime/2;

    srand(stime);

    Spline r;

    r.n = len;

    if(!mode)
    {
        r.defect_struct.m = 2 + (int)(rand() / (RAND_MAX/(8 - 2)));
        r.defect_struct.net = (float*)calloc(r.defect_struct.m, sizeof(float));
        for(unsigned i=0; i<r.defect_struct.m; i++) r.defect_struct.net[i] = (float)rand() / ((float)RAND_MAX + 1.0);
        selection_sort(r.defect_struct.net, r.defect_struct.m);
    } else
        {
        r.defect_struct.m = 3;
        r.defect_struct.net = (float*)calloc(r.defect_struct.m, sizeof(float));
        for(unsigned i=0; i<r.defect_struct.m; i++) r.defect_struct.net[i] = i+1;
        }

    r.polynomial_array = (Polynomial*)calloc(r.defect_struct.m-1, sizeof(Polynomial));

    for(unsigned j=0; j<r.defect_struct.m-1; j++)
    {
        r.polynomial_array[j].n = r.n;
        r.polynomial_array[j].coefficients = (float *) calloc(r.n, sizeof(float));

        for(unsigned i=0; i<r.n; i++)
        {
            r.polynomial_array[j].coefficients[i] = (float)rand() / ((float)RAND_MAX + 1.0);
        }
    }

    return r;
}

/*
 * 25.0 - input the values of nodes of the net
 * First of all - input
 * Then - checking
 * Finally - sorting
 */
void input_defect(Defect *d) {
    printf("Enter the number of nodes:\t");
    scanf("%u", &d->m);

    assert(d->m >= MIN_NET_ELEMENTS);

    d->net = (float *) calloc(d->m, sizeof(float));

    for (unsigned i = 0; i < d->m; i++) {
        printf("node[%i] = ", i);
        scanf("%f", d->net + i);
    }

    if (!check(*d)) {
        printf("Same elements in your net, exiting...\n");
        free(d->net);
        exit(1);
    }

    selection_sort(d->net, d->m);
}

/*
 * 26.0 - input data for spline
 *  - Input data for defect structure
 *  - Input data for each polynomial from array
 */
void input_spline(Spline *s) {
    printf("Enter your len of each polynomial coefficients array:\n");
    scanf("%u", &(s->n));

    assert(s->n >= MIN_POWER);

    input_defect(&(s->defect_struct));

    printf("Inputs for each polynomial:\n");

    s->polynomial_array = (Polynomial*)calloc(s->defect_struct.m-1, sizeof(Polynomial));

    for(unsigned i=0; i<s->defect_struct.m-1; i++)
    {
        input_polynomial(&s->polynomial_array[i], s->n);
    }
}