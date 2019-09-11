/*
 * rational_sulyma_horbunov_trukhan.c
 * by Sulyma Mariia, Ernest Trukhan
 * project: Rational #4
 * email: marysulyma@gmail.com,quiz290600@gmail.com
 */

#define _POSITIVE_TYPE 0
#define _NEGATIVE_TYPE 1
#define _NORMAL 0
#define _INFINITE 1

#include "../headers/rational_sulyma_horbunov_trukhan.h"

#include <assert.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <time.h>
#include <math.h>

// !!! INFO !!!
// For easier comprehension of things that are happening here,
// read comments in rational_sulyma_horbunov.h first

/*
 * Releasing memory, used for elements of dynamic array of given structure (1)
 */
void free_FractionArray(FractionArray f)
{
    free(f.array);
}

/*
 * Same as (1)
 */
void free_ChainFraction(ChainFraction f)
{
    free(f.components);
}

/*
 * Extra function: returns absolute value of long int type number
 */
static NType _int_abs(IType x)
{
    return (x < 0) ? -x : x;
}

/*
 * Extra function: returns absolute value of double type number
 */
static DType _float_abs(DType x)
{
    return (x < 0) ? -x : x;
}

/*
 * Extra function: calculates power of the given number
 */
static DType _power(DType x, NType n)
{
    if(!n) return 1;
    return _power(x, n-1) * x;
}

/*
 * Extra function: returns whole part of double type number
 * Behaves like floor() from <math.h>
 */
static NType _whole_part(DType x)
{
    return _int_abs((IType)x);
}

/*
 * Extra function: returns greatest number divisor
 * of positive integers a, b
 */
static IType _gcd(IType a, IType b)
{
    IType q=1;
    for(IType i=a; i>0; i--)
    {
        if (!(a%i) && !(b%i))
        {
            q = i;
            break;
        }
    }
    return q;
}

/*
 * Extra function:
 * Calculate accuracy.
 * Don't know why that was implemented, but anyway
 */
static DType _get_epsilon(DType x, DType y)
{
    return _float_abs(x - y)/x;
}

/*
 * Extra function:
 * Defining whether given fraction is positive or negative one
 * Based on nominator and denominator values comparison
 */
static void _define_sign(Fraction *f)
{
    ((f->nominator * f->denominator) >= 0) ? (f->sign = _POSITIVE_TYPE) : (f->sign = _NEGATIVE_TYPE);
    f->nominator = _int_abs(f->nominator); f->denominator = _int_abs(f->denominator);
}

/*
 * Extra function:
 * Defining whether given fraction is normal one or not
 * Based on denominator value check
 */
static void _define_type(Fraction *f)
{
    (f->denominator) ? (f->type = _NORMAL) : (f->type = _INFINITE);
}

/*
 * Basic function for initialising values of Fraction structure
 * Steps:
 * - Assign given values to Fraction.nominator and Fraction.denominator
 * - Define sign of given fraction
 * - Define the type of fraction
 * - Reducing nominator and denominator values using gcd function
 */
Fraction fraction(IType a, IType b)
{
    Fraction out;

    out.nominator = a; out.denominator = b;

    _define_sign(&out);

    _define_type(&out);

    if(out.type == _NORMAL)
    {
        IType red = _gcd(out.nominator, out.denominator);
        while (red != 1)
        {
            out.nominator /= red;
            out.denominator /= red;
            red = _gcd(out.nominator, out.denominator);
        }
    }

    return out;
}

/*
 * Returns a positive-defined fraction
 * Steps:
 * - 'Seeding' random number generator
 * - Abusing rand() function
 * - Making random fraction
 */
Fraction generate_random_fraction()
{
    IType s_time;
    long l_time;

    l_time = time(NULL);
    s_time = (NType)l_time/2;

    srand(s_time);

    return fraction(rand() % 100, rand() % 100);
}

/*
 * Used for transforming integer value
 * into fraction structure
 */
Fraction int_to_fraction(IType x)
{
    return fraction(x, 1);
}

/*
 * Calculate float value of fraction,
 * dividing nominator by denominator
 */
DType to_float(Fraction r)
{
    return (r.sign ? -1 : 1) * r.nominator/(r.denominator * 1.);
}

/*
 * lines 201 - 313 : Basic arithmetic described for fractions
 */
Fraction binary_add(Fraction a, Fraction b)
{
    return fraction((a.sign ? -1 : 1) * a.nominator * b.denominator +
    (b.sign ? -1 : 1) * b.nominator * a.denominator, a.denominator * b.denominator);
}

Fraction binary_sub(Fraction a, Fraction b)
{
    return fraction((a.sign ? -1 : 1) * a.nominator * b.denominator -
    (b.sign ? -1 : 1) * b.nominator * a.denominator, a.denominator * b.denominator);
}

Fraction binary_mul(Fraction a, Fraction b)
{
    return fraction((a.sign ? -1 : 1) * a.nominator * (b.sign ? -1 : 1) * b.nominator,
            a.denominator * b.denominator);
}

Fraction binary_div(Fraction a, Fraction b)
{
    return fraction((a.sign ? -1 : 1) * a.nominator * b.denominator,
                    a.denominator * (b.sign ? -1 : 1) * b.nominator);
}

void unary_add(Fraction *a, Fraction b)
{
    *a = fraction((a->sign ? -1 : 1) * a->nominator * b.denominator +
                    (b.sign ? -1 : 1) * b.nominator * a->denominator, a->denominator * b.denominator);
}

void unary_sub(Fraction *a, Fraction b)
{
    *a = fraction((a->sign ? -1 : 1) * a->nominator * b.denominator -
                    (b.sign ? -1 : 1) * b.nominator * a->denominator, a->denominator * b.denominator);
}

void unary_mul(Fraction *a, Fraction b)
{
    *a = fraction((a->sign ? -1 : 1) * a->nominator * (b.sign ? -1 : 1) * b.nominator,
                    a->denominator * b.denominator);
}

void unary_div(Fraction *a, Fraction b)
{
    *a = fraction((a->sign ? -1 : 1) * a->nominator * b.denominator,
                    a->denominator * (b.sign ? -1 : 1) * b.nominator);
}

Fraction scalar_binary_add(Fraction a, IType c)
{
    Fraction b = int_to_fraction(c);

    return fraction((a.sign ? -1 : 1) * a.nominator * b.denominator +
                    (b.sign ? -1 : 1) * b.nominator * a.denominator, a.denominator * b.denominator);
}

Fraction scalar_binary_sub(Fraction a, IType c)
{
    Fraction b = int_to_fraction(c);

    return fraction((a.sign ? -1 : 1) * a.nominator * b.denominator -
                    (b.sign ? -1 : 1) * b.nominator * a.denominator, a.denominator * b.denominator);
}

Fraction scalar_binary_mul(Fraction a, IType c)
{
    Fraction b = int_to_fraction(c);

    return fraction((a.sign ? -1 : 1) * a.nominator * (b.sign ? -1 : 1) * b.nominator,
                    a.denominator * b.denominator);
}

Fraction scalar_binary_div(Fraction a, IType c)
{
    Fraction b = int_to_fraction(c);

    return fraction((a.sign ? -1 : 1) * a.nominator * b.denominator,
                    a.denominator * (b.sign ? -1 : 1) * b.nominator);
}

void scalar_unary_add(Fraction *a, IType c)
{
    Fraction b = int_to_fraction(c);

    *a = fraction((a->sign ? -1 : 1) * a->nominator * b.denominator +
                    (b.sign ? -1 : 1) * b.nominator * a->denominator, a->denominator * b.denominator);
}

void scalar_unary_sub(Fraction *a, IType c)
{
    Fraction b = int_to_fraction(c);

    *a = fraction((a->sign ? -1 : 1) * a->nominator * b.denominator -
                    (b.sign ? -1 : 1) * b.nominator * a->denominator, a->denominator * b.denominator);
}

void scalar_unary_mul(Fraction *a, IType c)
{
    Fraction b = int_to_fraction(c);

    *a = fraction((a->sign ? -1 : 1) * a->nominator * (b.sign ? -1 : 1) * b.nominator,
                    a->denominator * b.denominator);
}

void scalar_unary_div(Fraction *a, IType c)
{
    Fraction b = int_to_fraction(c);

    *a = fraction((a->sign ? -1 : 1) * a->nominator * b.denominator,
                    a->denominator * (b.sign ? -1 : 1) * b.nominator);
}

IType binary_div_mod(Fraction r)
{
    if(r.type == _NORMAL) return r.nominator % r.denominator;
}

/*
 * lines 321 - 359 : Describing boolean functions for fractions
 */
bool eq_fractions(Fraction a, Fraction b)
{
    return to_float(a) == to_float(b);
}

bool neq_fractions(Fraction a, Fraction b)
{
    return to_float(a) != to_float(b);
}

bool g_fractions(Fraction a, Fraction b)
{
    return to_float(a) > to_float(b);
}

bool ge_fractions(Fraction a, Fraction b)
{
    return to_float(a) >= to_float(b);
}

bool l_fractions(Fraction a, Fraction b)
{
    return to_float(a) < to_float(b);
}

bool le_fractions(Fraction a, Fraction b)
{
    return to_float(a) <= to_float(b);
}

Fraction fr_max(Fraction a, Fraction b)
{
    return g_fractions(a, b) ? a : b;
}

Fraction fr_min(Fraction a, Fraction b)
{
    return l_fractions(a, b) ? a : b;
}

void stream_print_fraction(FILE *stream, Fraction f)
{
    assert(stream != NULL);

    fprintf(stream, "%c(%llu/%llu)\n", f.sign ? '-' : '+', f.nominator, f.denominator);
}

void stream_print_fractions(FILE *stream, FractionArray f)
{
    for(NType j=0; j<f.len; j++)
    {
        stream_print_fraction(stream, f.array[j]);
    }
}

/*
 * Basic function for reading fraction data from console
 */
Fraction console_read_fraction()
{
    IType a, b;

    printf("Nominator - ?\n");
    scanf("%lli", &a);

    printf("Denominator - ?\n");
    scanf("%lli", &b);

    return fraction(a, b);
}

/*
 * Basic function for reading fraction data from text file
 * (Actually works for stdin, but we're not going to use it for console input)
 */
Fraction stream_read_fraction(FILE *stream)
{
    assert(stream != NULL);

    char sign;

    IType n, d;

    fscanf(stream, "%c\(%lli/%lli)\n", &sign, &n, &d);

    return fraction(((sign == '-') ? -1 : 1) * n, d);
}

/*
 * Initialise FractionArray with given number of fractions and fraction structure objects
 */
void create(FractionArray *array, NType len, ...)
{
    array->len = len;

    array->array = (Fraction*)calloc(array->len, sizeof(Fraction));

    va_list fractions;

    va_start(fractions, len);

    for(NType j=0; j<array->len; j++)
    {
        array->array[j] = va_arg(fractions, Fraction);
    }

    va_end(fractions);
}

/*
 * Appending fractions to existing, initialised FractionArray object
 */
void insert(FractionArray *array, NType len, ...)
{
    array->len += len;

    array->array = (Fraction*)realloc(array->array, array->len * sizeof(Fraction));

    va_list fractions;

    va_start(fractions, len);

    for(NType j=(array->len-len); j<array->len; j++)
    {
        array->array[j] = va_arg(fractions, Fraction);
    }

    va_end(fractions);
}

/*
 * Get float type value by doing some primitive math
 * Yes, nothing special
 */
DType calculate_chain_fraction(ChainFraction r)
{
    DType result = 0;
    for(IType j=r.len-1; j>=0; j--)
    {
        result += r.components[j];
        if(j) result = 1/result;
    }
    return result;
}

/*
 * Create ChainFraction based on the init number of components
 */
ChainFraction create_N(DType x, NType n)
{
    ChainFraction r;

    r.x = x; r.len = n;

    r.components = (NType*)calloc(r.len, sizeof(NType));

    NType w; DType c;

    w = r.components[0] = _whole_part(x);

    c = x - w;

    for(NType j=1; j<r.len; j++)
    {
        w = _whole_part(1/c);
        r.components[j] = w;
        c = (1/c) - w;
    }

    r.eps = _get_epsilon(r.x, calculate_chain_fraction(r));

    return r;
}

/*
 * Create ChainFraction based on the init accuracy
 */
ChainFraction create_E(DType x, DType eps)
{
    ChainFraction r;

    r.x = x;
    r.eps = eps;
    r.len = 1;

    r.components = (NType *) calloc(r.len, sizeof(NType));

    NType w; DType c;

    w = r.components[0] = _whole_part(x);

    c = x - w;

    while (_float_abs(x - calculate_chain_fraction(r)) >= r.eps)
    {
        r.len++;
        r.components = (NType *) realloc(r.components, r.len * sizeof(NType));
        w = _whole_part(1 / c);
        r.components[r.len-1] = w;
        c = (1 / c) - w;
    }

    return r;
}

/*
 * Text file / console output of data from ChainFraction structure object
 */
void stream_output_chain_fraction(FILE *stream, ChainFraction r)
{
    assert(stream != NULL);

    fprintf(stream, "%.32f %.32f\n", r.x, r.eps);
    fprintf(stream, "%lu\n", r.len);
    for(NType j=0; j<r.len; j++)
    {
        fprintf(stream, "%lu ", r.components[j]);
    }
}

/*
 * Text file / console input of data from ChainFraction structure object
 */
void stream_input_chain_fraction(FILE *stream, ChainFraction *r)
{
    assert(stream != NULL);

    fscanf(stream, "%lf %lf\n", &r->x, &r->eps);
    fscanf(stream, "%li\n", &r->len);

    r->components = (NType*)calloc(r->len, sizeof(NType));

    for(NType j=0; j<r->len; j++)
    {
        fscanf(stream, "%li ", &r->components[j]);
    }
}

/*
 * Representation of ChainFraction structure data as chain fraction
 * F_V = A_0 + 1 / ( A_1 + 1 / ( ( ... ( A_N-1 + 1 / A_N ) ... ) ) )
 */
void console_output_as_fraction(ChainFraction r)
{
    fprintf(stdout, "%.4f ≈ ", r.x);
    NType cnt = 0;
    for(NType j=0; j<r.len; j++)
    {
        if(j)
        {
            fprintf(stdout, " + 1/(");
            cnt++;
        }
        fprintf(stdout, "%li", r.components[j]);
    }

    for(NType j=0; j<cnt; j++)
    {
        fprintf(stdout, ")");
    }
    fprintf(stdout, "\n");
}

/*
 * Return the ChainFraction.x value
 */
DType get_value(ChainFraction r)
{
    return r.x;
}

/*
 * Get current accuracy of ChainFraction structure object
 */
DType get_epsilon(ChainFraction r)
{
    return r.eps;
}

/*
 * Get fraction of ChainFraction structure object,
 * based on diophantine approximation algorithm
 */
Fraction get_fraction(ChainFraction r)
{
    Fraction result;

    result = int_to_fraction(r.components[r.len-1]);

    for(IType j=r.len-2; j>=0; j--)
    {
        result = binary_div(int_to_fraction(1), result);
        unary_add(&result, int_to_fraction(r.components[j]));
    }

    return result;
}

/*
 * Why not
 * Actually calculates approximate value of PI/4,
 * based on the number of components for the function below
 */
DType gregory_formula(NType N)
{
    DType result = 0;
    for(NType j=0; j<N; j++) result += to_float(fraction((IType)_power(-1, j), (2 * j) + 1));
    return result;
}
