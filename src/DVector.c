#pragma once

#include "../headers/DVector.h"

DVector generate_DVector(UTYPE n)
{
    DVector newvector;
    newvector.size = n;
    newvector.mas = (DTYPE *)malloc(sizeof(DTYPE) * n);
    return newvector;
}

ITYPE input_DVector(DVector *x)
{
    for (UTYPE _i = 0; _i < x->size; ++_i)
    {
        scanf("%lf", &(x->mas[_i]));
    }
    return x->size;
}

ITYPE output_DVector(DVector x, ITYPE type, ITYPE width, ITYPE precision)
{
    if (type == 0)
    {
        for (UTYPE _i = 0; _i < x.size; ++_i)
            printf("%*.*lf ", width, precision, x.mas[_i]);
    }
    else
    {
        for (UTYPE _i = 0; _i < x.size; ++_i)
            printf("%*.*e ", width, precision, x.mas[_i]);
    }
    return x.size;
}

ITYPE inputBinaryFile_DVector(char *file, DVector *x)
{
    FILE *read_ptr;
    if ((read_ptr = fopen(file, "rb")) == NULL)
    {
        fprintf(stderr, "Read error!\n");
        return 0;
    }
    printf("%p\n", read_ptr);
    fread(x->mas, sizeof(DTYPE), x->size, read_ptr);
    fclose(read_ptr);
    return x->size;
}

ITYPE outputBinaryFile_DVector(char *file, DVector x)
{
    FILE *write_ptr;
    if ((write_ptr = fopen(file, "wb")) == NULL)
    {
        fprintf(stderr, "Write error!\n");
        return 0;
    }
    fwrite(x.mas, sizeof(DTYPE), x.size, write_ptr);
    fclose(write_ptr);
    return x.size;
}

ITYPE inputTextFile_DVector(char *file, DVector *x)
{
    FILE *read_ptr;
    if ((read_ptr = fopen(file, "r")) == NULL)
    {
        fprintf(stderr, "Read error!\n");
        return 0;
    }

    for (UTYPE _i = 0; _i < x->size; ++_i)
        fscanf(read_ptr, "%lf", &(x->mas[_i]));
    fclose(read_ptr);
    return x->size;
}

ITYPE outputTextFile_DVector(char *file, DVector x, int type, int width, int precision)
{
    FILE *write_ptr;
    if ((write_ptr = fopen(file, "w")) == NULL)
    {
        fprintf(stderr, "Write error!\n");
        return 0;
    }
    if (type == 0)
    {
        for (UTYPE _i = 0; _i < x.size; ++_i)
            fprintf(write_ptr, "%*.*lf ", width, precision, x.mas[_i]);
    }
    else
    {
        for (UTYPE _i = 0; _i < x.size; ++_i)
            fprintf(write_ptr, "%*.*e ", width, precision, x.mas[_i]);
    }
    fprintf(write_ptr, "\n");
    printf("Done!");
    fclose(write_ptr);
    return x.size;
}

DVector add_DVector(DVector x, DVector y)
{
    if (x.size != y.size)
        return generate_DVector(0);

    for (UTYPE i = 0; i < x.size; i++)
        x.mas[i] += y.mas[i];

    return x;
}

DVector sub_DVector(DVector x, DVector y)
{
    if (x.size != y.size)
        return generate_DVector(0);

    for (UTYPE i = 0; i < x.size; i++)
        x.mas[i] -= y.mas[i];

    return x;
}

DVector mult_DVector(DVector x, DVector y)
{
    if (x.size != y.size)
        return generate_DVector(0);

    for (UTYPE i = 0; i < x.size; i++)
        x.mas[i] *= y.mas[i];

    return x;
}

DVector multConst_DVector(DVector x, DTYPE y)
{
    for (UTYPE i = 0; i < x.size; i++)
        x.mas[i] *= y;

    return x;
}

DVector divide_DVector(DVector x, DVector y)
{
    if (x.size != y.size)
        return generate_DVector(0);

    for (UTYPE i = 0; i < x.size; i++)
    {
        if (y.mas[i] == 0)
            return generate_DVector(0);

        x.mas[i] /= y.mas[i];
    }

    return x;
}

DVector divideConst_DVector(DVector x, DTYPE y)
{
    if (y == 0)
        return generate_DVector(0);

    for (UTYPE i = 0; i < x.size; i++)
    {
        x.mas[i] /= y;
    }

    return x;
}

DVector mod_DVector(DVector x, DVector y)
{
    if (x.size != y.size)
        return generate_DVector(0);

    for (UTYPE i = 0; i < x.size; i++)
    {
        if (y.mas[i] == 0)
            return generate_DVector(0);

        while (x.mas[i] - y.mas[i] >= 0)
        {
            x.mas[i] -= y.mas[i];
        }
    }

    return x;
}

DVector modConst_DVector(DVector x, DTYPE y)
{
    if (y == 0)
        return generate_DVector(0);

    for (UTYPE i = 0; i < x.size; i++)
    {
        while (x.mas[i] - y >= 0)
        {
            x.mas[i] -= y;
        }
    }

    return x;
}

ITYPE unadd_DVector(DVector *x, const DVector y)
{
    if (x->size != y.size)
        return 0;

    for (UTYPE i = 0; i < x->size; i++)
        x->mas[i] += y.mas[i];

    return 1;
}

ITYPE unsub_DVector(DVector *x, const DVector y)
{
    if (x->size != y.size)
        return 0;

    for (UTYPE i = 0; i < x->size; i++)
        x->mas[i] -= y.mas[i];

    return 1;
}

ITYPE unmult_DVector(DVector *x, const DVector y)
{
    if (x->size != y.size)
        return 0;

    for (UTYPE i = 0; i < x->size; i++)
        x->mas[i] *= y.mas[i];

    return 1;
}

ITYPE undivide_DVector(DVector *x, const DVector y)
{
    if (x->size != y.size)
        return 0;

    for (UTYPE i = 0; i < x->size; i++)
        if (y.mas[i] == 0)
            return 0;

    for (UTYPE i = 0; i < x->size; i++)
        x->mas[i] /= y.mas[i];

    return 1;
}

ITYPE unmod_DVector(DVector *x, const DVector y)
{
    if (x->size != y.size)
        return 0;

    for (UTYPE i = 0; i < x->size; i++)
        if (y.mas[i] == 0)
            return 0;

    for (UTYPE i = 0; i < x->size; i++)
        while (x->mas[i] - y.mas[i] >= 0)
        {
            x->mas[i] -= y.mas[i];
        }
    return 1;
}
