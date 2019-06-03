#define _POSITIVE_TYPE 0
#define _NEGATIVE_TYPE 1
#define _NORMAL 0
#define _INFINITE 1

#include "../headers/rational_sulyma_horbunov.h"

#include <assert.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <time.h>
#include <math.h>

void free_FractionArray(FractionArray f)
{
    free(f.array);
}

void free_ChainFraction(ChainFraction f)
{
    free(f.components);
}

static NType _int_abs(IType x)
{
    return (x < 0) ? -x : x;
}

static DType _float_abs(DType x)
{
    return (x < 0) ? -x : x;
}

static DType _power(DType x, NType n)
{
    if(!n) return 1;
    return _power(x, n-1) * x;
}

static NType _whole_part(DType x)
{
    return _int_abs((IType)x);
}

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

static DType _get_epsilon(DType x, DType y)
{
    return _float_abs(x - y)/x;
}

static void _define_sign(Fraction *f)
{
    ((f->nominator * f->denominator) >= 0) ? (f->sign = _POSITIVE_TYPE) : (f->sign = _NEGATIVE_TYPE);
    f->nominator = _int_abs(f->nominator); f->denominator = _int_abs(f->denominator);
}

static void _define_type(Fraction *f)
{
    (f->denominator) ? (f->type = _NORMAL) : (f->type = _INFINITE);
}

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

Fraction generate_random_fraction()
{
    IType s_time;
    long l_time;

    l_time = time(NULL);
    s_time = (NType)l_time/2;

    srand(s_time);

    return fraction(rand() % 100, rand() % 100);
}

Fraction int_to_fraction(IType x)
{
    return fraction(x, 1);
}

DType to_float(Fraction r)
{
    return (r.sign ? -1 : 1) * r.nominator/(r.denominator * 1.);
}

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

Fraction console_read_fraction()
{
    IType a, b;

    printf("Nominator - ?\n");
    scanf("%lli", &a);

    printf("Denominator - ?\n");
    scanf("%lli", &b);

    return fraction(a, b);
}

Fraction stream_read_fraction(FILE *stream)
{
    assert(stream != NULL);

    char sign;

    IType n, d;

    fscanf(stream, "%c\(%lli/%lli)\n", &sign, &n, &d);

    return fraction(((sign == '-') ? -1 : 1) * n, d);
}

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

DType get_value(ChainFraction r)
{
    return r.x;
}

DType get_epsilon(ChainFraction r)
{
    return r.eps;
}

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

DType gregory_formula(NType N)
{
    DType result = 0;
    for(NType j=0; j<N; j++) result += to_float(fraction((IType)_power(-1, j), (2 * j) + 1));
    return result;
}