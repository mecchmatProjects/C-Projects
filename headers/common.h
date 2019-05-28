/***
The MIT License (MIT)
Copyright (c) 2014 Viktor Borodin (borodin@mail.univ.kiev.ua)
21.06.2014

 * Basic types definitions and functions

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
***/
#ifndef __COMMON__
#define __COMMON__

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>

#include <string.h>

typedef double DTYPE ; /* Double real type for application */

typedef int ITYPE;    /* Integer type for application */

typedef size_t UTYPE; /* Unsigned type for application */

//TODO: v.b.: correct it with limits and float
#define EQ_EPS 0.000001 // epsilon : precision of arithmetics

#define MAX(a, b)       (a)>(b)?(a):(b)
#define MIN(a, b)       (a)<(b)?(a):(b)

#define PD_EQL(a, b)   fabs((a)-(b)) < EQ_EPS


/* Basic types definitions */

/*void* memzero(void* ptr, size_t n)
{
	memset(ptr, 0, n);
}*/

#endif 

/* __COMMON__ end */
