#pragma once

#include "../headers/DMatrix.h"

DMatrix generate_DMatrix(UTYPE n, UTYPE m)
{
	DMatrix newmatrix;
	newmatrix.rows = m;
	newmatrix.columns = n;
	newmatrix.mas = (DTYPE **)malloc(sizeof(DTYPE *) * m);
	for (UTYPE _m = 0; _m < m; ++_m)
	{
		newmatrix.mas[_m] = (DTYPE *)malloc(sizeof(DTYPE) * n);
	}
	return newmatrix;
}

ITYPE input_DMatrix(DMatrix *x)
{
	for (UTYPE _n = 0; _n < x->rows; ++_n)
	{
		for (UTYPE _m = 0; _m < x->columns; ++_m)
		{
			scanf("%lf", &(x->mas[_n][_m]));
		}
	}
	return x->columns * x->rows;
}

ITYPE output_DMatrix(DMatrix x, ITYPE type, ITYPE width, ITYPE precision)
{
	if (type == 0)
	{
		for (UTYPE _n = 0; _n < x.rows; ++_n)
		{
			for (UTYPE _m = 0; _m < x.columns; ++_m)
			{
				printf("%*.*lf ", width, precision, x.mas[_n][_m]);
			}
			printf("\n");
		}
	}
	else
	{
		for (UTYPE _n = 0; _n < x.rows; ++_n)
		{
			for (UTYPE _m = 0; _m < x.columns; ++_m)
			{
				printf("%*.*e ", width, precision, x.mas[_n][_m]);
			}
			printf("\n");
		}
	}
	return x.rows * x.columns;
}

ITYPE inputBinaryFile_DMatrix(char *file, DMatrix *x)
{
	FILE *read_ptr;
	if ((read_ptr = fopen(file, "rb")) == NULL)
	{
		fprintf(stderr, "Read error!\n");
		return 0;
	}
	for (UTYPE _i = 0; _i < x->rows; _i++)
	{
		fread(x->mas[_i], sizeof(DTYPE), x->columns, read_ptr);
	}
	fclose(read_ptr);
	return x->rows * x->columns;
}

ITYPE outputBinaryFile_DMatrix(char *file, DMatrix x)
{
	FILE *write_ptr;
	if ((write_ptr = fopen(file, "wb")) == NULL)
	{
		fprintf(stderr, "Write error!\n");
		return 0;
	}
	for (UTYPE _i = 0; _i < x.rows; _i++)
	{
		fwrite(x.mas[_i], sizeof(DTYPE), x.columns, write_ptr);
	}
	fclose(write_ptr);
	return x.rows * x.columns;
}

ITYPE inputTextFile_DMatrix(char *file, DMatrix *x)
{
	FILE *read_ptr;
	if ((read_ptr = fopen(file, "r")) == NULL)
	{
		fprintf(stderr, "Read error!\n");
		return 0;
	}
	for (UTYPE _i = 0; _i < x->rows; _i++)
	{
		for (UTYPE _j = 0; _j < x->columns; _j++)
		{
			fscanf(read_ptr, "%lf", &(x->mas[_i][_j]));
		}
	}
	fclose(read_ptr);
	return x->rows * x->columns;
}

ITYPE outputTextFile_DMatrix(char *file, DMatrix x, ITYPE type, ITYPE width, ITYPE precision)
{
	FILE *write_ptr;
	if ((write_ptr = fopen(file, "w")) == NULL)
	{
		fprintf(stderr, "Write error!\n");
		return 0;
	}
	if (type == 0)
	{
		for (UTYPE _i = 0; _i < x.rows; ++_i)
			for (UTYPE _j = 0; _j < x.columns; _j++)
				fprintf(write_ptr, "%*.*lf ", width, precision, x.mas[_i][_j]);
	}
	else
	{
		for (UTYPE _i = 0; _i < x.rows; ++_i)
			for (UTYPE _j = 0; _j < x.columns; _j++)
				fprintf(write_ptr, "%*.*e ", width, precision, x.mas[_i][_j]);
	}
	fprintf(write_ptr, "\n");
	printf("Done!");
	fclose(write_ptr);
	return x.rows * x.columns;
}

DMatrix add_DMatrix(DMatrix x, DMatrix y)
{
	if (x.rows != y.rows || x.columns != y.columns)
		return generate_DMatrix(0, 0);

	for (UTYPE i = 0; i < x.rows; i++)
		for (UTYPE j = 0; j < x.columns; j++)
			x.mas[i][j] += y.mas[i][j];

	return x;
}

DMatrix sub_DMatrix(DMatrix x, DMatrix y)
{
	if (x.rows != y.rows || x.columns != y.columns)
		return generate_DMatrix(0, 0);

	for (UTYPE i = 0; i < x.rows; i++)
		for (UTYPE j = 0; j < x.columns; j++)
			x.mas[i][j] -= y.mas[i][j];

	return x;
}

DMatrix mult_DMatrix(DMatrix x, DMatrix y)
{
	if (x.rows != y.rows || x.columns != y.columns)
		return generate_DMatrix(0, 0);

	for (UTYPE i = 0; i < x.rows; i++)
		for (UTYPE j = 0; j < x.columns; j++)
			x.mas[i][j] *= y.mas[i][j];

	return x;
}

DMatrix multConst_DMatrix(DMatrix x, DTYPE y)
{
	for (UTYPE i = 0; i < x.rows; i++)
	{
		for (UTYPE j = 0; j < x.columns; j++)
		{
			x.mas[i][j] *= y;
		}
	}

	return x;
}

DMatrix divide_DMatrix(DMatrix x, DMatrix y)
{
	if (x.rows != y.rows || x.columns != y.columns)
		return generate_DMatrix(0, 0);

	for (UTYPE i = 0; i < x.rows; i++)
	{
		for (UTYPE j = 0; j < x.columns; j++)
		{
			if (y.mas[i][j] == 0)
				return generate_DMatrix(0, 0);

			x.mas[i][j] /= y.mas[i][j];
		}
	}

	return x;
}

DMatrix divideConst_DMatrix(DMatrix x, DTYPE y)
{
	if (y == 0)
		return generate_DMatrix(0, 0);

	for (UTYPE i = 0; i < x.rows; i++)
	{
		for (UTYPE j = 0; j < x.columns; j++)
		{
			x.mas[i][j] /= y;
		}
	}

	return x;
}

DMatrix mod_DMatrix(DMatrix x, DMatrix y)
{
	if (x.rows != y.rows || x.columns != y.columns)
		return generate_DMatrix(0, 0);

	for (UTYPE i = 0; i < x.rows; i++)
	{
		for (UTYPE j = 0; j < x.columns; j++)
		{
			if (y.mas[i][j] == 0)
				return generate_DMatrix(0, 0);

			while (x.mas[i][j] - y.mas[i][j] >= 0)
			{
				x.mas[i][j] -= y.mas[i][j];
			}
		}
	}

	return x;
}

DMatrix modConst_DMatrix(DMatrix x, DTYPE y)
{
	if (y == 0)
		return generate_DMatrix(0, 0);

	for (UTYPE i = 0; i < x.rows; i++)
	{
		for (UTYPE j = 0; j < x.columns; j++)
		{
			while (x.mas[i][j] - y >= 0)
			{
				x.mas[i][j] -= y;
			}
		}
	}

	return x;
}

ITYPE unadd_DMatrix(DMatrix *x, const DMatrix y)
{
	if (x->rows != y.rows || x->columns != y.columns)
		return 0;

	for (UTYPE i = 0; i < x->rows; i++)
	{
		for (UTYPE j = 0; j < x->columns; j++)
		{
			x->mas[i][j] += y.mas[i][j];
		}
	}

	return 1;
}

ITYPE unsub_DMatrix(DMatrix *x, const DMatrix y)
{
	if (x->rows != y.rows || x->columns != y.columns)
		return 0;

	for (UTYPE i = 0; i < x->rows; i++)
	{
		for (UTYPE j = 0; j < x->columns; j++)
		{
			x->mas[i][j] -= y.mas[i][j];
		}
	}

	return 1;
}

ITYPE unmult_DMatrix(DMatrix *x, const DMatrix y)
{
	if (x->rows != y.rows || x->columns != y.columns)
		return 0;

	for (UTYPE i = 0; i < x->rows; i++)
	{
		for (UTYPE j = 0; j < x->columns; j++)
		{
			x->mas[i][j] *= y.mas[i][j];
		}
	}

	return 1;
}

ITYPE undivide_DMatrix(DMatrix *x, const DMatrix y)
{
	if (x->rows != y.rows || x->columns != y.columns)
		return 0;

	for (UTYPE i = 0; i < x->rows; i++)
	{
		for (UTYPE j = 0; j < x->columns; j++)
		{
			if (y.mas[i][j] == 0)
				return 0;

			x->mas[i][j] /= y.mas[i][j];
		}
	}

	return 1;
}

ITYPE unmod_DMatrix(DMatrix *x, const DMatrix y)
{
	if (x->rows != y.rows || x->columns != y.columns)
		return 0;

	for (UTYPE i = 0; i < x->rows; i++)
	{
		for (UTYPE j = 0; j < x->columns; j++)
		{
			if (y.mas[i][j] == 0)
				return 0;

			while (x->mas[i][j] - y.mas[i][j] >= 0)
				x->mas[i][j] -= y.mas[i][j];
		}
	}

	return 1;
}

DTYPE _det_DMatrix(DTYPE **mas, UTYPE n)
{
	DTYPE rezDet;
	ITYPE subJ, s;
	DTYPE **subT;
	if (n == 1)
		return mas[0][0];
	if (n == 2)
		return mas[0][0] * mas[1][1] - mas[0][1] * mas[1][0];
	subT = (DTYPE **)malloc((n - 1) * sizeof(DTYPE));
	rezDet = 0;
	s = 1;
	for (UTYPE _i = 0; _i < n; ++_i)
	{
		subJ = 0;
		for (UTYPE _j = 0; _j < n; ++_j)
			if (_i != _j)
				subT[subJ++] = mas[_j] + 1;
		rezDet = rezDet + s * mas[_i][0] * _det_DMatrix(subT, n - 1);
		s = -s;
	}
	free(subT);
	return rezDet;
}

DTYPE det_DMatrix(DMatrix x)
{
	if (x.columns == x.rows && x.columns > 0)
	{
		return _det_DMatrix(x.mas, x.rows);
	}
	else
	{
		return 0;
	}
}

DMatrix get_adjoint_DMatrix(DMatrix x)
{
	if (x.rows != x.columns)
		return generate_DMatrix(0, 0);

	UTYPE n = x.rows;
	DMatrix answer = generate_DMatrix(n, n);

	return answer;
}

DMatrix inverse_DMatrix(DMatrix x)
{
	if (x.rows != x.columns)
		return generate_DMatrix(0, 0);

	UTYPE n = x.rows;
	DMatrix answer = generate_DMatrix(n, n);

	DTYPE det = det_DMatrix(x);

	if (det == 0)
	{
		return generate_DMatrix(0, 0);
	}

	DMatrix adj = get_adjoint_DMatrix(x);

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			answer.mas[i][j] = adj.mas[i][j] / det;

	return answer;
}

DVector solve_DMatrix(DMatrix x, DVector y)
{
	if (x.columns != y.size)
		return generate_DVector(0);
	DVector rez = generate_DVector(x.rows);
	for (UTYPE _r = 0; _r < x.rows; ++_r)
	{
		DTYPE temp = 0;
		for (UTYPE _c = 0; _c < x.columns; ++_c)
		{
			temp += x.mas[_r][_c] * y.mas[_c];
		}
		rez.mas[_r] = temp;
	}
	return rez;
}

ITYPE swap_row_DMatrix(DMatrix *x, UTYPE i, UTYPE j)
{
	if (i < 0 || j < 0 || i >= x->rows || j >= x->rows)
		return 0;
	DTYPE *trow;
	trow = x->mas[i];
	x->mas[i] = x->mas[j];
	x->mas[j] = trow;
	return 1;
}

ITYPE swap_column_DMatrix(DMatrix *x, UTYPE i, UTYPE j)
{
	if (i < 0 || j < 0 || i >= x->columns || j >= x->columns)
		return 0;
	DTYPE temp;
	for (UTYPE _n = 0; _n < x->columns; ++_n)
	{
		temp = x->mas[_n][i];
		x->mas[_n][i] = x->mas[_n][j];
		x->mas[_n][j] = temp;
	}
	return 1;
}