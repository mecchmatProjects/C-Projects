#ifndef COMMON_H
#define COMMON_H

#include <float.h>

typedef double Dtype;
typedef char *Strtype;
typedef struct plane plane;
typedef struct pyramid pyramid;
typedef struct segment segment;
typedef struct point point;
typedef struct triangle triangle;
typedef struct vector vector;
typedef struct line line;
typedef enum area_index a_i;

#ifndef INF
#define INF DBL_MAX
#endif

int input();

void output();

int inputBinaryFile();

int outputBinaryFile();

int inputTextFile();

int outputTextFile();

#endif //COMMON_H
