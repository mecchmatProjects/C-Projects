/*
The MIT License (MIT)
Copyright (c) 2019 Horbunov Daniel (dangor66@gmail.com)
27.05.2019
This module is designed for equation solving to support basic math into the project.
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

/*
 * spline_horbunov_kovaltchuk.h
 * by Horbunov Daniel & Kovaltchuk Anastasiya
 * project: Splines #8
 * email #1: dangor66@gmail.com
 * email #2: nastasiaKovalchuk15@gmail.com
 */

#ifndef SPLINE_HORBUNOV_KOVALTCHUK_SPLINE_HORBUNOV_KOVALTCHUK_H
#define SPLINE_HORBUNOV_KOVALTCHUK_SPLINE_HORBUNOV_KOVALTCHUK_H

#include <stdio.h>

/*
 * 1.0 Defining Polynomial structure:
 * n - number of coefficients of polynomial
 * coefficients - array of real numbers
 */

typedef struct
{
    unsigned n;
    float *coefficients;
}
        Polynomial;

/*
 * 2.0 Defining Defect structure:
 * m - number of nodes of the net
 * net - array of real numbers
 */

typedef struct
{
    unsigned m;
    float *net;
}
        Defect;

/*
 * 3.0 Defining Spline structure:
 * n - number of coefficients for each polynomial
 * defect_struct - Defect structure ( 2.0 )
 * polynomial_array - array of Polynomial structures ( 1.0 )
 */

typedef struct
{
    unsigned n;
    Defect defect_struct;
    Polynomial *polynomial_array;
}
        Spline;

extern void free_polynomial(Polynomial *p);

extern void input_polynomial(Polynomial *p, unsigned len);

extern void free_defect(Defect *d);

extern void input_defect(Defect *d);

extern short is_same_defect_net(Defect d_0, Defect d_1);

extern float calculate_polynomial(Polynomial x, float t);

extern void un_add_spline(Spline *s_0, Spline s_1);

extern void un_sub_spline(Spline *s_0, Spline s_1);

extern void un_mul_spline_by_scalar(Spline *s_0, float c);

extern void un_div_spline_by_scalar(Spline *s_0, float c);

extern void un_mul_spline(Spline *s_0, Spline s_1);

extern Polynomial add_polynomial(Polynomial x, Polynomial y);

extern Polynomial sub_polynomial(Polynomial x, Polynomial y);

extern Polynomial mul_polynomial(Polynomial x, Polynomial y);

extern Polynomial mul_polynomial_by_scalar(Polynomial x, float c);

extern Polynomial div_polynomial_by_scalar(Polynomial x, float c);

extern Polynomial derivative_of_polynomial(Polynomial x);

extern Polynomial integral_of_polynomial(Polynomial x, float c);

extern float riemann_integral_of_polynomial(Polynomial x, float a, float b);

extern void input_spline(Spline *s);

extern void free_spline(Spline *s);

float calculate_spline(Spline s, float t);

extern Spline add_spline(Spline s_0, Spline s_1);

extern Spline sub_spline(Spline s_0, Spline s_1);

extern Spline mul_spline_by_scalar(Spline s_0, float c);

extern Spline div_spline_by_scalar(Spline s_0, float c);

extern Spline mul_spline(Spline s_0, Spline s_1);

extern Spline derivative_of_spline(Spline s);

extern Spline integral_of_spline(Spline s, float c);

extern float riemann_integral_of_spline(Spline s, float a, float b);

extern void output_polynomial(Polynomial poly, int type, int width, int precision);

extern void output_defect(Defect defect, int type, int width, int precision);

extern void output_spline(Spline spline, int type, int width, int precision);

extern Spline rand_spline(unsigned len, short mode);

extern void write_spline(Spline s, FILE *f);

extern void read_spline(Spline *s, FILE *f);

#endif