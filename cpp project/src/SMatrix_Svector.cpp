#include "SMatrix_SVector.h"

void WriteMatrix(double** a, int n, int m, string s)
{
	int i, j;
	ofstream f(s);
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
			f << a[i][j] << " ";//запись в файл поэлементно
		f << endl;//новая строка
	}
	//Закрытие файла
	f.close();

}

double** clone(double** arr, int n)//дублирование матрицы, чтобы при будущих подсчётах не менять данную
{
	double** newArr = new double* [n];
	for (int row = 0; row < n; row++)
	{
		newArr[row] = new double[n];
		for (int col = 0; col < n; col++)
			newArr[row][col] = arr[row][col];
	}
	return newArr;
}

void scalar_multi(double** m, int n, double a) //умножение на скаляр с изменением матрицы(для функции нахождения обратной)
{
	for (int row = 0; row < n; row++)
		for (int col = 0; col < n; col++) {
			m[row][col] *= a;
		}
}

double** scalar_multiNxM(double** m, int n, int k, double a) { //умножение на скаляр без изменения матрицы путём дублирования
	double** newArr = clone(m, n);
	for (int row = 0; row < n; row++)
		for (int col = 0; col < k; col++) {
			newArr[row][col] *= a;
		}
	return newArr;
}

double** matrix_multi(double** A, double** B, int n) //умножение квадратных матриц
{
	double** result = new double* [n];
	for (int row = 0; row < n; row++) {
		result[row] = new double[n];
		for (int col = 0; col < n; col++) {
			result[row][col] = 0;
		}
	}

	for (int row = 0; row < n; row++) {
		for (int col = 0; col < n; col++) {
			for (int j = 0; j < n; j++) {
				result[row][col] += A[row][j] * B[j][col];
			}
		}
	}
	return result;
}

double** matrix_multiNxM(double** a, double** b, int n1, int m1, int n2, int m2) //умножение произвольных матриц
{

	double** res;
	int i, j;
	res = new double* [n1];
	for (i = 0; i < m2; i++)
	{
		res[i] = new double[m2];
	}

	for (i = 0; i < n1; i++)
	{
		for (j = 0; j < m2; j++)
		{
			res[i][j] = 0;
			for (int k = 0; k < m1; k++)
				res[i][j] += a[i][k] * b[k][j];
		}
	}
	return res;
}

void clear(double** arr, int n) //отчистка
{
	for (int i = 0; i < n; i++)
		delete[] arr[i];
	delete[] arr;
}

void sumA(double** A, double** B, int n) //сумма матриц с изменением матрицы А (для функции нахождения обратной матрицы)
{
	for (int row = 0; row < n; row++)
		for (int col = 0; col < n; col++)
			A[row][col] += B[row][col];
}

double** sum(double** A, double** B, int n) //сумма матриц без изменения матрицы А
{
	double** newArr = clone(A, n);
	for (int row = 0; row < n; row++)
		for (int col = 0; col < n; col++)
			newArr[row][col] += B[row][col];
	return newArr;
}

double** dif(double** A, double** B, int n) //разница матриц без изменения матрицы А
{
	double** newArr = clone(A, n);
	for (int row = 0; row < n; row++)
		for (int col = 0; col < n; col++)
			newArr[row][col] -= B[row][col];
	return newArr;
}

void show(double** matrix, int n, int m, string s,string b) // вывод матрицы в консоль, в .txt и .bin файлы
{
	for (int row = 0; row < n; row++) {
		for (int col = 0; col < m; col++)
			printf("%lf\t", matrix[row][col]);
		printf("\n");
	}
	WriteMatrix(matrix, n, m, s);
	WriteMatrix(matrix, n, m, b);
	printf("\n");
}

double det(double** matrix, int n) //нахождение определителя матрицы
{
	double** B = clone(matrix, n);
	for (int step = 0; step < n - 1; step++)
		for (int row = step + 1; row < n; row++)
		{
			double coeff = -B[row][step] / B[step][step];
			for (int col = step; col < n; col++)
				B[row][col] += B[step][col] * coeff;
		}
	double Det = 1;
	for (int i = 0; i < n; i++)
		Det *= B[i][i];
	clear(B, n);
	return Det;
}

double** reverse(double** matrix, int n) // Нахождение обратной матрицы
{ 
	double N1 = 0, Ninf = 0;
	double** A0 = clone(matrix, n);
	for (size_t row = 0; row < n; row++) {
		double colsum = 0, rowsum = 0;
		for (size_t col = 0; col < n; col++) {
			rowsum += fabs(A0[row][col]);
			colsum += fabs(A0[col][row]);
		}
		N1 = std::max(colsum, N1);
		Ninf = std::max(rowsum, Ninf);
	}
	for (size_t row = 0; row < n - 1; row++) {
		for (size_t col = row + 1; col < n; col++)
			std::swap(A0[col][row], A0[row][col]);
	}
	scalar_multi(A0, n, (1 / (N1 * Ninf)));
	double** E2 = new double* [n];
	for (int row = 0; row < n; row++)
	{
		E2[row] = new double[n];
		for (int col = 0; col < n; col++) {
			if (row == col)
				E2[row][col] = 2;
			else
				E2[row][col] = 0;
		}
	}
	double** inv = clone(A0, n);
	double EPS = 0.001;
	if (det(matrix, n) != 0) {
		while (fabs(det(matrix_multi(matrix, inv, n), n) - 1) >= EPS)
		{
			double** prev = clone(inv, n);
			inv = matrix_multi(matrix, prev, n);
			scalar_multi(inv, n, -1);
			sumA(inv, E2, n);
			inv = matrix_multi(prev, inv, n);
			clear(prev, n);
		}
		return inv;
	}
	else
		printf("Impossible\n");
	clear(matrix, n);
	clear(E2, n);
}

void EnterMatrix(int& n, int& m, double** matrix, Matrix Massive) //ввод матрицы через консоль
{
	int e = 0;
	int s = 0;
	int s1 = 1;
	cout << "Enter row: "; cin >> n;
	cout << "Enter col: "; cin >> m; cout << endl;
	cout << "Enter Matrix: " << endl;
	for (int row = 0; row < n; row++)
	{
		matrix[row] = new double[n];
		for (int col = 0; col < m; col++) {
			scanf("%lf", &matrix[row][col]);
			if (matrix[row][col] != 0) {
				Massive.point[s] = row;
				Massive.point[s1] = col;
				Massive.element[e] = matrix[row][col];
				e++;
				s = s + 2;
				s1 = s1 + 2;
			}
		}

	}
	cout << endl;
}

void EnterVector(int& m, double** matrix, Vector Massive) //ввод вектора через консоль
{
	int e = 0;
	int s = 0;
	int s1 = 1;
	int n = 1;
	cout << "Enter lenght: "; cin >> m; cout << endl;
	cout << "Enter Vector: " << endl;
	for (int row = 0; row < m; row++)
	{
		matrix[row] = new double[m];
		for (int col = 0; col < n; col++) {
			scanf("%lf", &matrix[row][col]);
			if (matrix[row][col] != 0) {
				Massive.point[s] = row;
				Massive.point[s1] = col;
				Massive.vector[e] = matrix[row][col];
				e++;
				s = s + 2;
				s1 = s1 + 2;
			}
		}

	}
	cout << endl;
}

double** transpose(double** matrix, int row, int col) //Транспонирование матрицы
{
	double** result;
	result = new double* [col];
	for (int i = 0; i < col; i++)
		result[i] = new double[row];

	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			result[j][i] = matrix[i][j];
	return result;

}

double** ReadMatrix(string d, double** x, int& n, int& m) //Чтение матрицы с файла
{
	ifstream in(d);
	if (in.is_open())
	{
		int count = 0;
		int temp;

		while (!in.eof())
		{
			in >> temp;
			count++;
		}
		in.seekg(0, ios::beg);
		in.clear();

		int count_space = 0;
		char symbol;
		while (!in.eof())
		{
			in.get(symbol);
			if (symbol == ' ') count_space++;
			if (symbol == '\n') break;
		}
		in.seekg(0, ios::beg);
		in.clear();
		n = count / (count_space + 1);
		m = count_space + 1;
		x = new double* [n];
		for (int i = 0; i < n; i++) x[i] = new double[m];
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++) {
				in >> x[i][j];
			}

		in.close();
	}
	else
	{
		cout << "File not found.";
	}
	return x;
}