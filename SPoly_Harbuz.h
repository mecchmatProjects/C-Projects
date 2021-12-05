#pragma once
typedef struct SPoly {
    double *data;
    unsigned size;
} SPoly;
SPoly* create(unsigned size);
double get(SPoly* arr, int index);
double set(SPoly* arr, int index, double value);
void zeros(SPoly* arr);
void input(SPoly* arr);
void input_str(SPoly* arr);
void input_file(SPoly* arr,char name[]);
void print(SPoly* arr);
void print_file(SPoly* arr,char name[]);
void clearArr(SPoly* arr);
void freeArr(SPoly **arr);
void resizeArr(SPoly* arr, unsigned newSize);
SPoly* summary(SPoly* arr1,SPoly* arr2);
SPoly* subtraction(SPoly* arr1,SPoly* arr2);
SPoly* derivative(SPoly* arr);
double value_in_point(SPoly* arr,double x);
double derivative_value(SPoly* arr,double x);
SPoly* integration(SPoly* arr,double c);
double integration_value(SPoly* arr,double a,double b);
SPoly* multiply_num(SPoly* arr, double a);
SPoly* multiply(SPoly* arr1,SPoly* arr2);
SPoly* devide_num(SPoly* arr, double a);
SPoly* devide(SPoly* arr1,SPoly*arr2);
SPoly* devide_ost(SPoly* arr1,SPoly* arr2);
