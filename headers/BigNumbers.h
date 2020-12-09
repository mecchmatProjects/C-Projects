#ifndef C_PROJECT_BIGNUMBERS_H
#define C_PROJECT_BIGNUMBERS_H

/*
#include "stdio.h"
#include <malloc.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
*/
#include "common.h"

/* Representation of big integer.
 * body - array of non-negative elements;
 * sign - +-1 - sign of number
 * intsAmount - amount of elements in body*/
typedef struct BigInteger{
    size_t intsAmount;
    SMALL_INT sign;
    ELEM_TYPE *body;
} BigInteger;


/* Convert digit to decimal system.
 * '0' - 0
 * '1' - 1
 * ...
 * '9' - 9
 * 'a' - 10
 * ...
 * 'z' - 36
 *
 * @param numb: symbol of digit
 * */
extern SMALL_INT convert2int(SYMBOL numb);


/* Binary raise to the power of integer number.
 *
 * @param a: number
 * @param n: power*/
extern INT  binPow(INT a, SMALL_INT n);


/* Create copy of BigInteger. */
extern BigInteger *copy(const BigInteger *a);


/* Parse BigInteger from an array of chars.
 *
 * @param number: array of chars that contains digits and small english letters allowed in
 *                given numerical system
 * @param size: size of array
 * @param base: base of numerical system the array of chars is represented in*/
extern BigInteger *fromOtherChars(const SYMBOL *number, SIZE size, SMALL_INT base);


/* Optimized parsing BigInteger from an array of chars in decimal case.
 * It is recommended to use this instead of fromOtherChars(number, size, 10)
 *
 * @param number: array of chars that contains only digits
 * @param size: size of array*/
extern BigInteger *fromChars(const SYMBOL *number, SIZE size);


/* Create BigInteger from standard c integer.*/
extern BigInteger *fromInt(ELEM_TYPE num);


/* Print BigInteger in stdout. */
extern void print(const BigInteger *a);

extern void fprint(FILE *file, const BigInteger *a);


extern BigInteger *readBigInt(FILE *input);


extern BigInteger *readAnyBigInt(SMALL_INT base, FILE *input);


extern BigInteger *inputBigInt();

extern BigInteger *inputAnyBigInt(SMALL_INT base);

/* Delete leading zero elements of BigInteger. */
extern void delRedundantZeros(BigInteger *a);


/* Compare absolute parts of two BigIntegers.
 *
 * @param a: first BigInteger
 * @param b: second BigInteger
 * return: 1 if |a| > |b|, 0 if |a| == |b| and -1 otherwise */
extern SMALL_INT absRelation(BigInteger *a, BigInteger *b);


/* Addition recursive function of comparing.
 * Calls if numbers have the same length
 *
 * @param a: first BigInteger
 * @param b: second BigInteger
 * @param last_index: index of elements that comparing at the moment
 * return: 1 if |a| > |b|, 0 if |a| == |b| and -1 otherwise */
extern SMALL_INT _absRelation(const BigInteger *a, const BigInteger *b, SIZE last_index);


/* Adding of two normalized BigIntegers (it means that each hasn't
 * leading zero elements and each element < 10^(ELEM_SIZE_NUM + 1)).
 *
 * Returns normalized BigInteger.*/
extern BigInteger *add(const BigInteger *a, const BigInteger *b);


/* Addition function for adding of non-negative BigIntegers (means that sign == 1).
 * Returns non-normalized BigInteger. */
extern BigInteger *_add(const BigInteger *a, const BigInteger *b);


/* Subtraction of two normalized BigIntegers (it means that each hasn't
 * leading zero elements and each element < 10^(ELEM_SIZE_NUM + 1)).
 *
 * Returns normalized BigInteger. */
extern BigInteger *sub(const BigInteger *a, const BigInteger *b);


/* Addition function for subtraction of non-negative BigIntegers (means that sign == 1).
 * Returns non-normalized BigInteger.*/
extern BigInteger *_sub(const BigInteger *a, const BigInteger *b);


/* Multiply two non-negative normalized (it means that each hasn't
 * leading zero elements and each element < 10^(ELEM_SIZE_NUM + 1) BigIntegers
 * using Karatsuba's algorithm.
 *
 * Returns normalized BigInteger.*/
extern BigInteger *karatsuba_mul(BigInteger *X, BigInteger *Y);;


/* Multiply two normalized (it means that each hasn't
 * leading zero elements and each element < 10^(ELEM_SIZE_NUM + 1) BigIntegers.
 *
 * Returns normalized BigInteger. */
extern BigInteger *mul(const BigInteger *X, const BigInteger *Y);


/* Divide two normalized (it means that each hasn't
 * leading zero elements and each element < 10^(ELEM_SIZE_NUM + 1) BigIntegers
 * using the improved long division (school method of numbers division).
 *
 * Returns normalized BigInteger.*/
extern BigInteger *divide(const BigInteger *X, const BigInteger *Y);


/* Extended Euclidean algorithm for BigIntegers.
 * Find the greatest common divisor of the two numbers (a and b) and solutions
 * of the Bezout equation ax + by = gcd(a, b).
 *
 * Returns the array of BigIntegers: x, y and gcd*/
extern BigInteger **xgcd(const BigInteger *a, const BigInteger *b);

/* Auxiliary function for xgcd. Finds the xgcd for a >= b*/
extern BigInteger **_xgcdHelper(BigInteger *a, BigInteger *b);


/* Euclidean algorithm for BigIntegers.
 * Find the greatest common divisor of two numbers.*/
extern BigInteger *gcd(const BigInteger *a, const BigInteger *b);


/* Find the least common multiplier using the gcd.*/
extern BigInteger *lcm(const BigInteger *a, const BigInteger *b);


/* Normalize BigInteger - delete leading zero elements and recompute
 * each of element be less than 10^(ELEM_SIZE_NUM + 1). */
extern void normalize(BigInteger *n);


/* Add leading zero elements to BigNumber in order to make the size of
 * BigNumber be equal to n if n is even and n+1 otherwise.*/
extern void extendBigInteger(BigInteger *x, SIZE n);


/* Multiply BigInteger on 10^(ELEM_SIZE_NUM)  (shift right each of element on the 1 index and
 * add the zero to begin) */
extern void shiftRight(BigInteger *number);


#endif //C_PROJECT_BIGNUMBERS_H
