#ifndef __another_funcs__
#define __another_funcs__

#include "../headers/common.h"

IType equal_strs(const char str1[], const char str2[]);

/*
видаляє елемент з динамічного массиву, змінюючи його розмір, який передається як параметр, 
та змінюючи кількість пам'яті, яка була виділина на массив, 
та повертає цей елемент
*/
DType exclude_from_mass(DType* mass, IType* n, IType idx);

#endif /* __another_funcs__ end */