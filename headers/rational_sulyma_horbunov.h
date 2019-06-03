#ifndef RATIONAL_SULYMA_HORBUNOV_RATIONAL_SULYMA_HORBUNOV_H
#define RATIONAL_SULYMA_HORBUNOV_RATIONAL_SULYMA_HORBUNOV_H

#include <stdbool.h>
#include <stdio.h>
#include "common.h"

typedef struct
{
    bool type;
    bool sign;
    IType nominator;
    IType denominator;
}
        Fraction;

typedef struct
{
    NType len;
    Fraction *array;
}
        FractionArray;

typedef struct
{
    DType x;
    DType eps;
    NType *components;
    NType len;
}
        ChainFraction;

typedef struct
{
    NType len;
    ChainFraction *array;
}
        ChainFractionArray;

extern void free_FractionArray(FractionArray f);

extern void free_ChainFraction(ChainFraction f);

extern DType to_float(Fraction r);

extern Fraction fraction(IType a, IType b);

extern Fraction generate_random_fraction();

extern Fraction int_to_fraction(IType x);

extern Fraction binary_add(Fraction a, Fraction b);

extern Fraction binary_sub(Fraction a, Fraction b);

extern Fraction binary_mul(Fraction a, Fraction b);

extern Fraction binary_div(Fraction a, Fraction b);

extern void unary_add(Fraction *a, Fraction b);

extern void unary_sub(Fraction *a, Fraction b);

extern void unary_mul(Fraction *a, Fraction b);

extern void unary_div(Fraction *a, Fraction b);

extern Fraction scalar_binary_add(Fraction a, IType c);

extern Fraction scalar_binary_sub(Fraction a, IType c);

extern Fraction scalar_binary_mul(Fraction a, IType c);

extern Fraction scalar_binary_div(Fraction a, IType c);

extern void scalar_unary_add(Fraction *a, IType c);

extern void scalar_unary_sub(Fraction *a, IType c);

extern void scalar_unary_mul(Fraction *a, IType c);

extern void scalar_unary_div(Fraction *a, IType c);

extern IType binary_div_mod(Fraction r);

extern bool eq_fractions(Fraction a, Fraction b);

extern bool neq_fractions(Fraction a, Fraction b);

extern bool g_fractions(Fraction a, Fraction b);

extern bool ge_fractions(Fraction a, Fraction b);

extern bool l_fractions(Fraction a, Fraction b);

extern bool le_fractions(Fraction a, Fraction b);

extern Fraction fr_max(Fraction a, Fraction b);

extern Fraction fr_min(Fraction a, Fraction b);

extern void stream_print_fraction(FILE *stream, Fraction f);

extern void stream_print_fractions(FILE *stream, FractionArray f);

extern Fraction console_read_fraction();

extern FractionArray console_read_fractions();

extern Fraction stream_read_fraction(FILE *stream);

extern void create(FractionArray *array, NType len, ...);

extern void insert(FractionArray *array, NType len, ...);

extern DType calculate_chain_fraction(ChainFraction r);

extern ChainFraction create_N(DType x, NType n);

extern ChainFraction create_E(DType x, DType eps);

extern void stream_output_chain_fraction(FILE *stream, ChainFraction r);

extern void stream_input_chain_fraction(FILE *stream, ChainFraction *r);

extern void console_output_as_fraction(ChainFraction r);

extern DType get_value(ChainFraction r);

extern DType get_epsilon(ChainFraction r);

extern Fraction get_fraction(ChainFraction r);

extern DType gregory_formula(NType N);

#endif