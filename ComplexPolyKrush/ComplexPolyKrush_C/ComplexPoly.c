#include <stdio.h>
#include <stdlib.h>
#include "ComplexPoly.h"


complex * Init_coplex_Array(int * a)
{
    int n;
    printf("input deegree\n");
    scanf("%d", &n);
    printf("deegree of poly %d\n", n);
    *a = n;
    complex *array;
    array = (complex*)malloc((n + 1) * sizeof(complex));

    if (array == NULL) exit(1);
    else
    {
        for (int i = 0; i <= n; ++i)
        {
            printf("input coefs near X^%d\n", i);
            printf("input real>>\n ");
            scanf("%lf", &array[i].real);
            printf("input image>>\n ");
            scanf("%lf", &array[i].image);
        }
        return array;
    }
}
void ShowArray(complex arr[], int size_arr)
{
    for (int i = 0; i <= size_arr; i++)
        printf("(%g+(%g)I)*X^%d + ", arr[i].real, arr[i].image, i);
    printf("\n");
}
complex * add_arrays(complex iArr1[], complex iArr2[], int arr_size1, int arr_size2, int *a)
{
    complex * tmp = NULL;
    if (arr_size1 == arr_size2)
    {
        tmp = (complex*)malloc((arr_size1 + 1) * sizeof(complex));
        for (int i = 0; i <= arr_size1; ++i)
        {
            tmp[i] = plus(iArr1[i], iArr2[i]);
        }
        *a = arr_size1;
    }
    else if (arr_size1 > arr_size2)
    {
        tmp = (complex*)malloc((arr_size1 + 1) * sizeof(complex));
        for (int i = 0; i <= arr_size1; ++i)
        {
            if (arr_size1 >= i)
                tmp[i] = plus(iArr1[i], iArr2[i]);
            else
                tmp[i] = iArr1[i];
        }
        *a = arr_size1;
    }
    else if (arr_size1 < arr_size2)
    {
        tmp = (complex*)malloc((arr_size2 + 1) * sizeof(complex));
        for (int i = 0; i <= arr_size2; ++i)
        {
            if (arr_size2 >= i)
                tmp[i] = plus(iArr1[i], iArr2[i]);
            else
                tmp[i] = iArr2[i];
        }
        *a = arr_size2;
    }

    if (tmp == NULL)
        exit(1);
    else
        return  tmp;
}
complex * subtraction_arrays(complex iArr1[], complex iArr2[], int arr_size1, int arr_size2, int * a)
{
    complex * tmp = NULL;
    if (arr_size1 == arr_size2)
    {
        tmp = (complex*)malloc((arr_size1 + 1) * sizeof(complex));
        for (int i = 0; i <= arr_size1; ++i)
        {
            tmp[i] = minus(iArr1[i], iArr2[i]);
        }
        *a = arr_size1;
    }
    else if (arr_size1 > arr_size2)
    {
        tmp = (complex*)malloc((arr_size1 + 1) * sizeof(complex));
        for (int i = 0; i <= arr_size1; ++i)
        {
            if (arr_size1 >= i)
                tmp[i] = minus(iArr1[i], iArr2[i]);
            else
                tmp[i] = iArr1[i];
        }
        *a = arr_size1;
    }
    else if (arr_size1 < arr_size2)
    {
        tmp = (complex*)malloc((arr_size2 + 1) * sizeof(complex));
        for (int i = 0; i <= arr_size2; ++i)
        {
            if (arr_size2 >= i)
                tmp[i] = minus(iArr1[i], iArr2[i]);
            else
            {
                tmp[i].real = -iArr2[i].real;
                tmp[i].image = -iArr2[i].image;
            }
        }
        *a = arr_size2;
    }

    if (tmp == NULL)
        exit(1);
    else
        return  tmp;
}
complex value(complex iArr[], int n)
{
    printf("Now input coplex number\n");
    complex num;
    printf("real part>>\n");
    scanf("%lf", &num.real);
    printf("image part>>\n");
    scanf("%lf", &num.image);
    printf("(%g+(%g)I)", num.real, num.image);
    printf("\n");
    complex res, tmp = num;

    for (int i = 0; i <= n; ++i)
    {
        if (i == 0)
        {
            res = iArr[0];
        }
        else if (i == 1)
        {
            res = plus(res, multiply(num, iArr[i]));
        }
        else
        {
            for (int j = 0; j < i; ++j)
                tmp = multiply(tmp, num);
            res = plus(res, multiply(iArr[i], tmp));
        }
    }
    tmp.image = res.image;
    tmp.real = res.real;
    res.real = -tmp.image;
    res.image = -tmp.real;
    return res;
}
complex * generate(int * size)
{
    int n;
    printf("input deegree\n");
    scanf("%d", &n);
    printf("deegree of poly %d\n", n);
    *size = n;
    complex *array;
    array = (complex*)malloc((n + 1) * sizeof(complex));
    if (array == NULL) exit(1);
    else
    {
        for (int i = 0; i <= n; ++i)
        {
            array[i].real = rand() % 200 - 100;
            array[i].image = rand() % 200 - 100;
        }
        return array;
    }
}
complex * derivative(complex iArr[], int  sizr_arr, int *a)
{
    *a = sizr_arr - 1;
    complex *array;
    array = (complex*)malloc((sizr_arr) * sizeof(complex));
    for (int i = 0; i <= sizr_arr; ++i)
    {
        if (i != 0)
        {
            array[i-1].image = iArr[i].image*i;
            array[i-1].real = iArr[i].real*i;
        }
    }

    return array;
}
void write_into_file(complex iArr[], int sSize)
{
    FILE * file;
    file = fopen("res.txt", "w");
    if (file != NULL)
    {
        for (int i = 0; i < sSize; ++i)
            fprintf(file, "(%lf+%lf)*X^%s", iArr[i].real, iArr[i].image, i);
        fclose(file);
    }
    else
        printf("no\n");
}
