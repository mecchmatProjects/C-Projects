#include "Complex.h"

complex plus(complex num1, complex num2)
{
    complex tmp;
    tmp.real = num1.real + num2.real;
    tmp.image = num1.image + num2.image;
    return tmp;
}
complex minus(complex num1, complex num2)
{
    complex tmp;
    tmp.real = num1.real - num2.real;
    tmp.image = num1.image - num2.image;
    return tmp;
}
complex multiply(complex num1, complex num2)
{
    complex tmp;
    tmp.real = num1.real*num2.real - num1.image*num2.image;
    tmp.image = num1.real*num2.image + num2.real*num1.image;
    return tmp;
}
complex division(complex num1, complex num2)
{
    complex tmp1, tmp2, tmp3,result;
    tmp1.real = num2.real;
    tmp1.image = -num2.image;
    tmp2 = multiply(num1, tmp1);
    tmp3 = multiply(num2, tmp1);
    result.real = tmp2.real / tmp3.real;
    result.image = tmp2.image / tmp3.real;
    return result;
}
