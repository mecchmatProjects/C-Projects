/*
The MIT License (MIT)

Copyright (c) 2019 Valentina Pryhodiuk (shevacharmeleon@gmail.com)
19.05.2019
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

/*** File  TrigPoly.h
Declaration of functions TrigPoly (Task 7)
Done by Valentina Pryhodiuk (group statistic 2.2)
Email: shevacharmeleon@gmail.com
Date 19.05.2019 ***/

//headers
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/* Base structure of TrigPoly
    I used # ifndef, to prevent
    errors caused by multiple declarations*/
# ifndef _TRIGPOLY_
# define _TRIGPOLY_
typedef double Dtype;
#define SI sizeof(Dtype)

    typedef struct{
        size_t n; //size of polynome
        Dtype alpha;// starting real number – angle
        Dtype * a;// coefficients of sin
        Dtype * b;// coefficients of cos
    }TrigPoly;
# endif

/* functions for my polynome */

//standart operations
extern TrigPoly add(TrigPoly p1, TrigPoly p2); //+
extern TrigPoly sub(TrigPoly p1, TrigPoly p2); //+
extern TrigPoly mul(TrigPoly p1, TrigPoly p2); //+
extern TrigPoly mul_const(TrigPoly p, Dtype C); //+
extern int div_(TrigPoly p, TrigPoly p1); //+
extern TrigPoly div_const(TrigPoly p, Dtype C); //+
extern Dtype mod(TrigPoly p, TrigPoly p1);//+
extern Dtype value(TrigPoly p); //+
extern TrigPoly derivative(TrigPoly p);
extern TrigPoly integral(TrigPoly p, Dtype C);
extern Dtype integrate(TrigPoly p, Dtype a, Dtype b);

//unary operations
extern int unadd(TrigPoly * p1, const TrigPoly p2); //+
extern int unsub(TrigPoly * p1, const TrigPoly p2); //+
extern int unmul(TrigPoly * p1, const TrigPoly p2); //+

// input/output functions
extern void output(TrigPoly poly, int type, int width, int precision); //+
extern int outputBinaryFile(char * filename, TrigPoly p); //+
extern int outputTextFile(char* File, TrigPoly x, int type, int width, int precision); //+
extern void coolOutput(TrigPoly poly, int type, int width, int precision); //+
extern int inputBinaryFile(char * filename, TrigPoly * p); //+
extern int inputTextFile(char * filename, TrigPoly * x); //+

//generation and destroy
extern TrigPoly generate(int n); //+
extern int inputStringOfCoef(TrigPoly * x, char * str); //+
extern int inputAsTable(TrigPoly * x);
extern int destroy(TrigPoly * x); //+

// extra functions, which were used to implement previous
extern Dtype setAlpha();
extern Dtype doubleFromFile(FILE* f1);
extern Dtype doubleFromStr(char * str);
extern int spaceCounter(FILE* f);

