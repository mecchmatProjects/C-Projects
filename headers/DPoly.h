/* DPoly.h - an implementation of a polynomial datatype and related operations
 *
 * Copyright (c) 2019 Smirnova Tatiana, Bykova Polina
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef DPOLY_H
#define DPOLY_H

#include <stdio.h>

/* Defines the coefficient datatype */
typedef double dtype;

/* A dense univariate polinomial -- the base structure of the module
 * The base structure of the module */
typedef struct dpoly {
    /* a pointer to the array of polynomial coefficients
     * (starting from 0-order) */
    dtype* coefficients;
    /* number of coefficients set in the `coefficients` array */
    int size;
} dpoly;

/**
 * Creates a polynomial, reserving place for `size` coefficients,
 * and setting them all to 0
 *
 * @param poly  A pointer to an unitialized `dpoly` struct to be
 *              initialized.
 *              (call `dpoly_destroy` on an initialized struct pointer
 *              before reuse)
 *
 *              Points to a valid `dpoly` struct containing a zero
 *              polynomial with space allocated for `size` coefficients
 *              after the call.
 *
 * @param size  A number of coefficients to be allocated.
 *              Should be >= 0.
 *
 * @result void
 */
extern void dpoly_zero(dpoly* poly, int size);

/**
 * Creates a random polynomial, with `size` coefficients,
 *
 * @param poly  A pointer to an unitialized `dpoly` struct to be
 *              initialized.
 *
 *              Points to a valid `dpoly` struct containing a random
 *              polynomial with `size` coefficients after the call
 *
 * @param size  A number of coefficients
 *
 * @result void
 */
extern void dpoly_generate(dpoly* poly, int size);

/**
 * Deallocates space used in the polynomial
 *
 * @param poly  A pointer to a valid `dpoly` struct
 *              to deallocate
 *
 *              After the call points to an unitialized `dpoly` struct
 *
 * @result void
 */
extern void dpoly_destroy(dpoly* poly);

/**
 * Copies the polynomial pointed by `poly` to an uninitialized struct
 * pointed by `dest`
 *
 * @param poly  A pointer to a valid `dpoly` struct
 *              to copy from
 *
 * @param dest  A pointer to an uninitialized `dpoly` struct
 *              to copy to
 *
 *              Points to a valid `dpoly` struct containing the same
 *              polynomial as `poly` after the call
 *
 * @result void
 */
extern void dpoly_copy(const dpoly* poly, dpoly* dest);

/* Input */

/**
 * Reads the polynomial written as a sum of monomial terms
 * from a string `str`
 *
 * For example "2 * x - 2.5 x + 1.4e2 * x^3 + 3"
 *
 * @param poly  A pointer to an uninitialized `dpoly` struct
 *              to read polynomial into
 *
 *              Points to a valid `dpoly` struct containing the read
 *              polinomial after the call
 *
 * @param str   A string describing the polynomial
 *
 * @result int  The number of monomial terms successfully read
 *              (for example if the string is "1 + 2 x + junk + x^16"
 *              the result should be 2 and the read polynomial will be
 *              "1 + 2 x"
 */
extern int dpoly_sinput(dpoly* poly, const char* str);

/**
 * Reads the polynomial written as a sum of terms from a file
 *
 * The polynomial should be written in one line.
 * The format is the same as for `dpoly_sinput`.
 *
 * @param poly  A pointer to an uninitialized `dpoly` struct
 *              to read polynomial into
 *
 *              Points to a valid `dpoly` struct containing the read
 *              polinomial after the call
 *
 * @param file  A descriptor for the file opened for input (in text mode)
 *
 * @result int  The number of monomial terms successfully read
 *              see `dpoly_sinput`
 */
extern int dpoly_finput(dpoly* poly, FILE* file);

/**
 * Reads the polynomial written as a sum of terms from
 * the standard input
 *
 * See `dpoly_finput` for more details.
 *
 * @param poly  A pointer to an uninitialized `dpoly` struct
 *              to read polynomial into
 *
 *              Points to a valid `dpoly` struct containing the read
 *              polinomial after the call
 *
 * @result int  The number of monomial terms successfully read
 *              see `dpoly_sinput`
 */
extern int dpoly_input(dpoly* poly);

/**
 * Reads the polynomial written as a list of coefficients
 * (starting from 0) from the string `str`
 *
 * For example "3 4.5 0 1.2e-3 1" should be read as
 * "3 + 4.5 x + 0.0012 x^3 + x^4"
 *
 * @param poly  A pointer to an uninitialized `dpoly` struct
 *              to read polynomial into
 *
 *              Points to a valid `dpoly` struct containing the read
 *              polinomial after the call
 *
 * @param str   A string containing the coefficients of the polynomial
 *
 * @result int  The number of coefficients successfully read
 *              (for example if the string is "1 2.0 3.14help 42"
 *              the result should be 3 and the read polynomial will be
 *              "1 + 2 x + 3.14 x^2"
 */
extern int dpoly_sread_text(dpoly* poly, const char* str);

/**
 * Reads the polynomial written as a list of coefficients
 * (starting from 0) from the file
 *
 * The polynomial coefficients should be written in one line
 * The format is the same as for `dpoly_sread_text`
 *
 * @param poly  A pointer to an uninitialized `dpoly` struct
 *              to read polynomial into
 *
 *              Points to a valid `dpoly` struct containing the read
 *              polinomial after the call
 *
 * @param file  A descriptor for the file opened for input
 *              (in text mode)
 *
 * @result int  The number of coefficients successfully read
 *              see `dpoly_sread_text`
 */
extern int dpoly_fread_text(dpoly* poly, FILE* file);

/**
 * Reads the polynomial written as a list of coefficients
 * (starting from 0) from the standard input
 *
 * See `dpoly_fread_text` for more details.
 *
 * @param poly  A pointer to an uninitialized `dpoly` struct
 *              to read polynomial into
 *
 *              Points to a valid `dpoly` struct containing the read
 *              polinomial after the call
 *
 * @result int  The number of coefficients successfully read
 */
extern int dpoly_read_text(dpoly* poly);

/**
 * Reads the polynomial from the binary file
 *
 * Format:
 * int size -- number of coefficients
 * array of `size` doubles -- coefficients starting form 0
 *
 * The binary format is not meant to be portable between
 * different architectures (uses native integer size and endianness)
 *
 * @param poly  A pointer to an uninitialized `dpoly` struct
 *              to read polynomial into
 *
 *              Points to a valid `dpoly` struct containing the read
 *              polinomial after the call
 *
 * @param file  A descriptor for the file opened for input
 *              (in binary mode)
 *
 * @result int  The number of coefficients successfully read
 */
extern int dpoly_fread_binary(dpoly* poly, FILE* file);

/* Output */

/**
 * Outputs the polynomial as a sum of monomial terms to a result string
 *
 * @param poly      A pointer to a valid `dpoly` struct containing
 *                  the polinomial to output
 *
 * @result char*    The string representing the polynomial
 *                  (should be manually `free`d after use)
 */
extern char* dpoly_sprint(const dpoly* poly);

/**
 * Outputs the polynomial as a sum of monomial terms to a file
 *
 * @param poly  A pointer to a valid `dpoly` struct containing
 *              the polinomial to output
 *
 * @param file  A descriptor for the file opened for output
 *              (in text mode)
 *
 * @result void
 */
extern void dpoly_fprint(const dpoly* poly, FILE* file);

/**
 * Outputs the polynomial as a sum of monomial terms to
 * the standard output
 *
 * @param poly  A pointer to a valid `dpoly` struct containing
 *              the polinomial to output
 *
 * @result void
 */
extern void dpoly_print(const dpoly* poly);


/**
 * Outputs the polynomial as a space-separated list of coefficients
 * starting from 0 to a result string
 *
 * @param poly      A pointer to a valid `dpoly` struct containing
 *                  the polinomial to output
 *
 * @result char*    The string containing the list of coefficients
 *                  (should be manually `free`d after use)
 */
extern char* dpoly_swrite_text(const dpoly* poly);

/**
 * Outputs the polynomial as a space-separated list of coefficients
 * starting from 0 to a file
 *
 * @param poly  A pointer to a valid `dpoly` struct containing
 *              the polinomial to output
 *
 * @param file  A descriptor for the file opened for output
 *              (in text mode)
 *
 * @result void
 */
extern void dpoly_fwrite_text(const dpoly* poly, FILE* file);

/**
 * Outputs the polynomial as a space-separated list of coefficients
 * starting from 0 to the standard output
 *
 * @param poly  A pointer to a valid `dpoly` struct containing
 *              the polinomial to output
 *
 * @result void
 */
extern void dpoly_write_text(const dpoly* poly);

/**
 * Writes the polynomial to the binary file
 * See `dpoly_fread_binary`
 *
 * @param poly  A (non-null) pointer to an uninitialized `dpoly` struct
 *              to read polynomial into
 *
 * @param file  A descriptor for the file opened for output
 *              (in binary mode)
 *
 * @result void
 */
extern void dpoly_fwrite_binary(const dpoly* poly, FILE* file);

/* Calculations */

/**
 * Calculates the value of a polynomial at a given point `x`
 *
 * @param poly  A pointer to a valid `dpoly` struct
 *              containing the polynomial 'f' to calculate
 *
 * @param x     The point 'x' at which the polynomial value is
 *              calculated
 *
 * @result dtype The calculated value 'f(x)'
 */
extern dtype dpoly_value_at(const dpoly* poly, dtype x);

/**
 * Calculates the sum of the two polynomials
 *
 * @param lhs   A pointer to a valid `dpoly` struct
 *              containing polynomial 'L'
 *
 * @param rhs   A pointer to a valid `dpoly` struct
 *              containing polynomial 'R'
 *
 * @param res   A pointer to an uninitialized `dpoly` struct
 *              to write the sum into
 *
 *              Points to a valid `dpoly` struct containing the sum
 *              'L + R' after the call
 *
 * @result void
 */
extern void dpoly_add(const dpoly* lhs, const dpoly* rhs, dpoly* res);

/**
 * Calculates the product of the two polynomials
 *
 * @param lhs   A pointer to a valid `dpoly` struct
 *              containing polynomial 'L'
 *
 * @param rhs   A pointer to a valid `dpoly` struct
 *              containing polynomial 'R'
 *
 * @param res   A pointer to an uninitialized `dpoly` struct
 *              to write the product into
 *
 *              Points to a valid `dpoly` struct containing the sum
 *              'L * R' after the call
 *
 * @result void
 */
extern void dpoly_mul(const dpoly* lhs, const dpoly* rhs, dpoly* res);

/**
 * Calculates the quotient of the two polynomials
 *
 * L / R = Q means
 * Q is the unique polynomial such that L = Q * R + M,
 * where the degree of M is strictly less than the degree of R
 *
 * @param lhs   A pointer to a valid `dpoly` struct
 *              containing polynomial 'L'
 *
 * @param rhs   A pointer to a valid `dpoly` struct
 *              containing polynomial 'R'
 *
 * @param res   A pointer to an uninitialized `dpoly` struct
 *              to write the quotient into
 *
 *              Points to a valid `dpoly` struct containing the
 *              'L / R' after the call
 *
 * @result void
 */
extern void dpoly_div(const dpoly* lhs, const dpoly* rhs, dpoly* res);

/**
 * Calculates the remainder from the division of the two polynomials
 *
 * L % R = M means
 * there exists a unique polynomial Q such that L = Q * R + M,
 * and the degree of M is strictly less than the degree of R
 *
 * @param lhs   A pointer to a valid `dpoly` struct
 *              containing polynomial 'L'
 *
 * @param rhs   A pointer to a valid `dpoly` struct
 *              containing polynomial 'R'
 *
 * @param res   A pointer to an uninitialized `dpoly` struct
 *              to write the remainder into
 *
 *              Points to a valid `dpoly` struct containing the
 *              'L % R' after the call
 *
 * @result void
 */
extern void dpoly_mod(const dpoly* lhs, const dpoly* rhs, dpoly* res);

/**
 * Calculates the both the quatient and the remainder from
 * the division of the two polynomials
 *
 * See `dpoly_div` and `dpoly_mod`
 *
 * @param lhs   A pointer to a valid `dpoly` struct
 *              containing polynomial 'L'
 *
 * @param rhs   A pointer to a valid `dpoly` struct
 *              containing polynomial 'R'
 *
 * @param div   A pointer to an uninitialized `dpoly` struct
 *              to write the quotient into
 *
 *              Points to a valid `dpoly` struct containing the
 *              'L / R' after the call
 *
 * @param mod   A pointer to an uninitialized `dpoly` struct
 *              to write the remainder into
 *
 *              Points to a valid `dpoly` struct containing the
 *              'L % R' after the call
 *
 * @result void
 */
extern void dpoly_divmod(const dpoly* lhs, const dpoly* rhs,
                         dpoly* div, dpoly* mod);

/**
 * Calculates the sum of the two polynomials and assigns the result to
 * the first one
 *
 * @param lhs   A pointer to a valid `dpoly` struct
 *              containing polynomial 'L'
 *
 *              Points to a valid `dpoly` struct containing the sum
 *              'L + R' after the call
 *
 * @param rhs   A pointer to a valid `dpoly` struct
 *              containing polynomial 'R'
 *
 * @result void
 */
extern void dpoly_add_assign(dpoly* lhs, const dpoly* rhs);

/**
 * Calculates the product of the two polynomials and assigns the result
 * to the first one
 *
 * @param lhs   A pointer to a valid `dpoly` struct
 *              containing polynomial 'L'
 *
 *              Points to a valid `dpoly` struct containing the product
 *              'L * R' after the call
 *
 * @param rhs   A pointer to a valid `dpoly` struct
 *              containing polynomial 'R'
 *
 * @result void
 */
extern void dpoly_mul_assign(dpoly* lhs, const dpoly* rhs);

/**
 * Calculates the quotient of the two polynomials and assigns the result
 * to the first one
 *
 * See `dpoly_div`
 *
 * @param lhs   A pointer to a valid `dpoly` struct
 *              containing polynomial 'L'
 *
 *              Points to a valid `dpoly` struct containing
 *              the quotient 'L / R' after the call
 *
 * @param rhs   A pointer to a valid `dpoly` struct
 *              containing polynomial 'R'
 *
 * @result void
 */
extern void dpoly_div_assign(dpoly* lhs, const dpoly* rhs);

/**
 * Calculates the remainder of the division of the two polynomials
 * and assigns the result to the first one
 *
 * @param lhs   A pointer to a valid `dpoly` struct
 *              containing polynomial 'L'
 *
 *              Points to a valid `dpoly` struct containing
 *              the remainder 'L % R' after the call
 *
 * @param rhs   A pointer to a valid `dpoly` struct
 *              containing polynomial 'R'
 *
 * @result void
 */
extern void dpoly_mod_assign(dpoly* lhs, const dpoly* rhs);

/**
 * Calculates the sum of the two polynomials modulo the third one
 *
 * @param lhs       A pointer to a valid `dpoly` struct
 *                  containing polynomial 'L'
 *
 * @param rhs       A pointer to a valid `dpoly` struct
 *                  containing polynomial 'R'
 *
 * @param modulo    A pointer to a valid `dpoly` struct
 *                  containing polynomial 'M'
 *
 * @param res       A pointer to an uninitialized `dpoly` struct
 *                  to write the sum into
 *
 *                  Points to a valid `dpoly` struct containing the sum
 *                  '(L + R) % M' after the call
 *
 * @result void
 */
extern void dpoly_modulo_add(
    const dpoly* lhs, const dpoly* rhs, const dpoly* modulo,
    dpoly* res);

/**
 * Calculates the sum of the two polynomials modulo the third one
 * and assigns it to the first one
 *
 * @param lhs       A pointer to a valid `dpoly` struct
 *                  containing polynomial 'L'
 *
 *                  Points to a valid `dpoly` struct containing the sum
 *                  '(L + R) % M' after the call
 *
 * @param rhs       A pointer to a valid `dpoly` struct
 *                  containing polynomial 'R'
 *
 * @param modulo    A pointer to a valid `dpoly` struct
 *                  containing polynomial 'M'
 *
 * @result void
 */
extern void dpoly_modulo_add_assign(
    dpoly* lhs, const dpoly* rhs, const dpoly* modulo);

/**
 * Calculates the product of the two polynomials modulo the third one
 *
 * @param lhs       A pointer to a valid `dpoly` struct
 *                  containing polynomial 'L'
 *
 * @param rhs       A pointer to a valid `dpoly` struct
 *                  containing polynomial 'R'
 *
 * @param modulo    A pointer to a valid `dpoly` struct
 *                  containing polynomial 'M'
 *
 * @param res       A pointer to an uninitialized `dpoly` struct
 *                  to write the product into
 *
 *                  Points to a valid `dpoly` struct containing the sum
 *                  '(L * R) % M' after the call
 *
 * @result void
 */
extern void dpoly_modulo_mul(
    const dpoly* lhs, const dpoly* rhs, const dpoly* modulo,
    dpoly* res);

/**
 * Calculates the product of the two polynomials modulo the third one
 * and assigns it to the first one
 *
 * @param lhs       A pointer to a valid `dpoly` struct
 *                  containing polynomial 'L'
 *
 *                  Points to a valid `dpoly` struct containing
 *                  the product '(L * R) % M' after the call
 *
 * @param rhs       A pointer to a valid `dpoly` struct
 *                  containing polynomial 'R'
 *
 * @param modulo    A pointer to a valid `dpoly` struct
 *                  containing polynomial 'M'
 *
 * @result void
 */
extern void dpoly_modulo_mul_assign(
    dpoly* lhs, const dpoly* rhs, const dpoly* modulo);

/**
 * Calculates the derivative of the polynomial
 *
 * @param poly  A pointer to a valid `dpoly` struct
 *              containing the polynomial 'f'
 *
 * @param res   A pointer to an unitialized `dpoly` struct
 *              to write the derivative into
 *
 *              Contains the derivative 'df(x)/dx' after the call
 *
 * @result void
 */
extern void dpoly_derivative(const dpoly* poly, dpoly* res);

/**
 * Calculates the value of the derivative of the polynomial at given
 * point
 *
 * @param poly      A pointer to a valid `dpoly` struct
 *                  containing the polynomial 'f'
 *
 * @param x0        A point 'x0' at which to calculate the derivative
 *
 * @result dtype    The value of the derivative at point 'x0':
 *                  'df(x)/dx|x=x0'
 */
extern dtype dpoly_derivative_at(const dpoly* poly, dtype x0);

/**
 * Calculates the indefinite integral of the polynomial
 *
 * @param poly  A pointer to a valid `dpoly` struct
 *              containing the polynomial 'f'
 *
 * @param res   A pointer to an unitialized `dpoly` struct
 *              to write the integral into
 *
 *              Contains the indefinite integral '\int f(x) dx'
 *              after the call
 *
 * @result void
 */
extern void dpoly_indefinite_integral(const dpoly* poly, dpoly* res);

/**
 * Calculates the definite integral of the polynomial
 *
 * @param poly          A pointer to a valid `dpoly` struct
 *                      containing the polynomial 'f'
 *
 * @param low_bound     The lower bound for the integration
 *
 * @param high_bound    The upper bound for the integration
 *
 * @result dtype        The value of the definite integral
 *                      '\int_{low_bound}^{high_bound} f(x) dx'
 */
extern dtype dpoly_definite_integral(
    const dpoly* poly, dtype low_bound, dtype high_bound);

// extern dtype dpoly_closest_zero(const dpoly* dpoly, dtype x);

#endif
