#pragma once

#include <stdio.h>

typedef struct
{
    double real;
    double image;
} complex;

complex plus(complex num1, complex num2);
complex minus(complex num1, complex num2);
complex multiply(complex num1, complex num2);
complex division(complex num1, complex num2);

