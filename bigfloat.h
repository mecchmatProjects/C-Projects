#ifndef BIG_FLOAT_H
#define BIG_FLOAT_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define PRECISION 100

typedef long long int lli;
typedef unsigned long long ull;

typedef struct bigfloat {  //structure to represent the BigFloat number
  char digits[PRECISION];  //numbers of the BigFloat number
  char decimal; //place of dot in the BigFloat number
  char negative; //sign of BigFloat number
} BigFloat;

BigFloat *create(char *);  //Create BigFloat number and return the pointer
void freeBigFloat(BigFloat *); //Destroy BigFloat number
void parse(BigFloat *, char *); //Parses in a string representing a floating point number
void print(BigFloat *); //Prints of the BigFloat to console
void add(BigFloat *, BigFloat *, BigFloat *); //Adds two BigFloats
void subtract(BigFloat *, BigFloat *, BigFloat *); //Subtract b number from a number and return a number
void multiply(BigFloat *, BigFloat *, BigFloat *); //Multiply two BigFloats
void make_negative(BigFloat *b); //Make the BigFloat negative
void divide(BigFloat *, BigFloat *, BigFloat *);  //Divide two BigFloats
char equals(BigFloat *, BigFloat *); //two BigFloats are equal?
char compare(BigFloat *, BigFloat *);  //Compares two BigFloats
void clear(BigFloat *);  //Clear the BigFloat number (the BigFloat number = 0)
void solve_y(BigFloat *a, BigFloat *b, BigFloat *c); //Solve any Linear Equation in One Variable (aY + b + c = 0)
lli quadratic_equation(BigFloat *, BigFloat *, BigFloat *); //Solve quadratic equation Ax**2+Bx+C
lli to_int(BigFloat *b); //convert the BigFloat number to int
void make_array(FILE*, char*, int); //create array from file
void read_from_file(char*); //read array from file
void write_to_file(BigFloat *); //Write the BigFloat to txt file

void standardizeDecimal(BigFloat *, BigFloat *); //shifts two BigFloats so that they have the same decimal point
void multiplyLine(BigFloat *, BigFloat *, int); //Multiply using line method
void zerosFirst(BigFloat *);  //Delete all trailing zeros in the BigFloat and all zeros are leading the BigFloat
void trailingZeros(BigFloat *); //Delete all leading zeros in the BigFloat and all zeros are trailing the BigFloat
void shiftDownBy(char *, int, int);  //Shifts a char array down by the specified shift
void shiftUpBy(char *, int, int);  //Shifts a char array up by the specified shift

#endif
