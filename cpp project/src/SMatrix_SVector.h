#include <iostream>
#include <conio.h>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

struct Matrix {
	int point[1024];
	double element[1024];
};

struct Vector {
	int point[1024];
	double vector[1024];
};
void WriteMatrix(double** a, int n, int m, string s);
double** clone(double** arr, int n);
void scalar_multi(double** m, int n, double a);
double** scalar_multiNxM(double** m, int n, int k, double a);
double** matrix_multi(double** A, double** B, int n);
double** matrix_multiNxM(double** a, double** b, int n1, int m1, int n2, int m2);
void clear(double** arr, int n);
void sumA(double** A, double** B, int n);
double** sum(double** A, double** B, int n);
double** dif(double** A, double** B, int n);
void show(double** matrix, int n, int m, string s,string b);
double det(double** matrix, int n);
double** reverse(double** matrix, int n);
void EnterMatrix(int& n, int& m, double** matrix, Matrix Massive);
void EnterVector(int& m, double** matrix, Vector Massive);
double** transpose(double** matrix, int row, int col);
double** ReadMatrix(string d, double** x, int& n, int& m);