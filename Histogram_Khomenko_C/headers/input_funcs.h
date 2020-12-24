#ifndef __input_funcs__
#define __input_funcs__

#include "../headers/common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
читає з консолі рядок довільної довжини(до знаку  '\n') та повертає його
*/
char* input_str();

/*
якщо мається на увазі ввід не с файлу(с консолі) filename = "not_file", 
в іншому випадку  filename рівний назві файлу в купі з розширенням файлу (".txt", ".dat")
*/
DType* input_float_number(IType* n, char filename[]);

#endif /* __input_funcs__ end */