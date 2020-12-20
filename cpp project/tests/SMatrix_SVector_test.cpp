#include "../src/SMatrix_SVector.h"

int main()
{
	Matrix A;
	Matrix B;
	Vector V;
	ofstream f();
	int n = 0, m = 0;
	int n1 = 0, m1 = 0;
	int rn = 0, rm = 0;
	int l = 0;
	double detm;
	string d = "matr1.txt";
	string d1 = "matr2.txt";
	double** matrixA = new double* [1024];
	double** matrixB = new double* [1024];
	double** matrixC = new double* [1024];
	double** vector = new double* [1024];
	cout << "Write or Read matrixes? 1/2"<< endl;
	int wrm;
	cin >> wrm;
	while (true) {
		if ((wrm == 1) or (wrm == 2)) {
			break;
		}
		else {
			cout << "Enter Valid" << endl;
			cin >> wrm;
		};
	}
	switch (wrm)
	{
	case 1:
		EnterMatrix(n, m, matrixA, A);
		EnterMatrix(n1, m1, matrixB, B);
		break;
	case 2:
		matrixA = ReadMatrix(d, matrixA, n, m);
		matrixB = ReadMatrix(d1, matrixB, n1, m1);
		break;
	}
	int moe;
	double scalar;
	string sc = "matrixscalar.txt"; string scbin = "matrixscalar.bin";
	string mm = "matrixmulti.txt"; string mmbin = "matrixmulti.bin";
	string ms = "matrixsum.txt"; string msbin = "matrixsum.bin";
	string md = "matrixdif.txt"; string mdbin = "matrixdif.bin";
	string de = "matrixdet.txt"; string debin = "matrixdet.bin";
	string mr = "matrixreverse.txt"; string mrbin = "matrixreverse.bin";
	string mt = "matrixtranspose.txt"; string mtbin = "matrixtranspose.bin";
	string mv = "matrixvector.txt"; string mvbin = "matrixvector.bin";
	while (true)
	{
		cout << "Matrix Operators : " << endl << "1.Scalar Multiply" << endl << "2.Matrix Muliply" << endl << "3.Summ" << endl << "4.Diff" << endl << "5.Determinant of A" << endl << "6.Reverse A" << endl << "7.Transpose A" << endl << "8.VectorMulti" << endl << "9.Exit" << endl << endl;
		cin >> moe;
		while (true) {
			if ((moe == 1) or (moe == 2) or (moe == 3) or (moe == 4) or (moe == 5) or (moe == 6) or (moe == 7) or (moe == 8) or (moe == 9)) {
				break;
			}
			else {
				cout << "Enter Valid" << endl;
				cin >> moe;
			};
		}
		switch (moe)
		{
		case 1:
			cout << "Enter Scalar" << endl;
			cin >> scalar;
			matrixC = scalar_multiNxM(matrixA, n, m, scalar);
			show(matrixC, n, m, sc, scbin);
			break;
		case 2:
			if (n == m1) {
				cout << "A * B" << endl;
				matrixC = matrix_multiNxM(matrixA, matrixB, n, m, n1, m1);
				show(matrixC, n, m1, mm, mmbin);
				break;
			}
			else cout << "Wrong size" << endl;
		case 3:
			if (n == n1 and m == m1){
				cout << "A + B" << endl;
				matrixC = sum(matrixA, matrixB, n);
				show(matrixC, n, n, ms, msbin);
			}
			else cout << "Wrong Size" << endl;
			break;
		case 4:
			if (n == n1 and m == m1) {
				cout << "A + B" << endl;
				matrixC = dif(matrixA, matrixB, n);
				show(matrixC, n, n, md, mdbin);
			}
			else cout << "Wrong Size" << endl;
			break;
		case 5:
			if (n == m) {
				ofstream f(de);
				ofstream fbin(debin);
				cout << "Det(A)" << endl;
				detm = det(matrixA, n);
				cout << endl << detm << endl;
				f << detm;
				fbin << detm;
			}
			else cout << "Wrong size" << endl;
			break;
		case 6:
			if (n == m) {
				cout << "A^(-1)" << endl;
				matrixC = reverse(matrixA, n);
				show(matrixC, n, n, mr, mrbin);
			}
			else cout << "Wrong Size" << endl;
			break;
		case 7:
			cout << "Transpose A" << endl;
			matrixC = transpose(matrixA, n, m);
			show(matrixC, m, n, mt, mtbin);
			break;
		case 8:
			cout << "A*(Vector)" << endl;
			EnterVector(l, vector, V);
			if (l == n) {
				matrixC = matrix_multiNxM(matrixA, vector, n, m, 1, l);
				show(matrixC, n, 1, mv, mvbin);
			}
			else cout << "Wrong Size" << endl;
			break;
		case 9:
			exit(0);
		}
	}
	return 0;
}