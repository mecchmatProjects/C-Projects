//директиви препроцессора
#include<iostream>
#include<cstdlib>
#include<windows.h>
#include<fstream>
#include<iomanip>
//підключення заголовочного файлу
#include "Task1.h"

//використання простору стандартних імен
using namespace std;

//===================================================================================================================

int main() {

	Sleep(1000);
	cout << "Hordienko Ivan\n\n";

	Task1* x = new Task1();
	Task1* y = new Task1();
	Task1 res(10), x1(20);
	int a, n;

	while (true) {
		cout << "Please choose method of entering data:\n";
		cout << "1 - Keyboard\n";
		cout << "2 - Binary file\n";
		cout << "3 - Text file\n";
		cout << "4 - Random generated\n";
		cout << "other - exit\n\n";
		cin >> a;

		switch (a) {
		case 1: {
			input_Task1(x);
			input_Task1(y);

			break;
		}
		case 2: {
			inputBinaryFile_Task1(x);
			inputBinaryFile_Task1(y);

			break;
		}
		case 3: {
			inputTextFile_Task1(x);
			inputTextFile_Task1(y);
			break;
		}
		case 4: {
			cout << "Please, enter n: ";
			cin >> n;
			x1 = generate_Task1(n);
			x = &x1;

			cout << "Please, enter n: ";
			cin >> n;
			x1 = generate_Task1(n);
			y = &x1;

		}
		default:
			cout << "The program ends its work\n\n";
			return 0;
			break;

		}




		cout << "Please choose method of writing data:\n";
		cout << "1 - Console\n";
		cout << "2 - Binary file\n";
		cout << "3 - Text file\n";
		cout << "other - exit\n\n";
		cin >> a;

		switch (a) {
		case 1: {

			res = (add_Task1(*x, *y));
			output_Task1(res, 1, 1234, 12);
			res = sub_Task1(*x, *y);
			output_Task1(res, 0, 1234, 12);
			res = (mul_Task1(*x, *y));
			output_Task1(res, 1, 1234, 12);
			res = (div_Task1(*x, *y));
			output_Task1(res, 0, 1234, 12);
			res = (mod_Task1(*x, *y));
			output_Task1(res, 1, 1234, 12);

			break;
		}
		case 2: {
			res = (add_Task1(*x, *y));
			outputBinaryFile_Task1(res, 1, 1234, 12);
			res = (sub_Task1(*x, *y));
			outputBinaryFile_Task1(res, 0, 1234, 12);
			res = (mul_Task1(*x, *y));
			outputBinaryFile_Task1(res, 0, 1234, 12);
			res = (div_Task1(*x, *y));
			outputBinaryFile_Task1(res, 1, 1234, 12);
			res = (mod_Task1(*x, *y));
			outputBinaryFile_Task1(res, 1, 1234, 12);

			break;
		}
		case 3: {
			res = (add_Task1(*x, *y));
			outputTextFile_Task1(res, 1, 1234, 12);
			res = (sub_Task1(*x, *y));
			outputTextFile_Task1(res, 0, 1234, 12);
			res = (mul_Task1(*x, *y));
			outputTextFile_Task1(res, 0, 1234, 12);
			res = (div_Task1(*x, *y));
			outputTextFile_Task1(res, 1, 1234, 12);
			res = (mod_Task1(*x, *y));
			outputTextFile_Task1(res, 1, 1234, 12);

			break;
		}
		
		default:
			cout << "The program ends its work\n\n";
			return 0;
			break;

		}

	}

}

