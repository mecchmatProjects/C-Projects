#pragma once
#include <malloc.h>
#include <stdlib.h>
#include "Complex.c"

complex * Init_coplex_Array(int * a);
void ShowArray(complex arr[], int size_arr);
complex * add_arrays(complex iArr1[], complex iArr2[], int arr_size1, int arr_size2, int * a);
complex * subtraction_arrays(complex iArr1[], complex iArr2[], int arr_size1, int arr_size2, int * a);
complex value(complex iArr[], int n);
complex * generate(int * size);
complex * derivative(complex iArr[], int size_arr,int * a);


