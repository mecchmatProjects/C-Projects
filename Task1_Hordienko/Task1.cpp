//директиви препроцессора
#include<iostream>
#include<cstdlib>
#include<windows.h>
#include<fstream>
#include <math.h>
#include<iomanip>
#include <stdlib.h>
#include <time.h>
//підключення заголовочного файлу
#include"Task1.h"

//використання простору стандартних імен
using namespace std;

//===================================================================================================================

Task1::Task1(double n) { x = n; } //конструктор з параметрами

Task1::Task1() : Task1(0) {}  //конструктор за замовчуванням

Task1::~Task1() { //деструктор класу, не може приймати параметри та завжди є єдиним в класі
	//cout << "Destructor called for Task1 " << x << endl;
}

//===================================================================================================================


//реалізація стандратної операції додавання для 2 екземплярів класу задачі
Task1 add_Task1(Task1 x, Task1 y) {
	Task1 res = x.x + y.x;
	return res;
}

//реалізація стандратної операції віднімання для 2 екземплярів класу задачі
Task1 sub_Task1(Task1 x, Task1 y) {
	Task1 res;
	if(x.x >= y.x) res = x.x - y.x;
	else res = y.x - x.x;
	return res;
}

//реалізація стандратної операції множення для 2 екземплярів класу задачі
Task1 mul_Task1(Task1 x, Task1 y) {
	Task1 res = x.x * y.x;
	return res;
}

//реалізація стандратної операції множення для екземпляру класу задачі та скаляру
Task1 dmul_Task1(Task1 x, double y) {
	Task1 res = x.x * y;
	return res;
}

//реалізація стандратної операції ділення для 2 екземплярів класу задачі
Task1 div_Task1(Task1 x, Task1 y) {
	Task1 res = x.x / y.x;
	return res;
}

//реалізація стандратної операції ділення для екземпляру класу задачі та скаляру
Task1 ddiv_Task1(Task1 x, double y) {
	Task1 res = x.x / y;
	return res;
}

//реалізація стандратної операції взяття по модулю для 2 екземплярів класу задачі
Task1 mod_Task1(Task1 x, Task1 y) {
	Task1 res = fmod(x.x , y.x);
	return res;
}

//реалізація стандратної операції взяття по модулю для екземпляру класу задачі та скаляру
Task1 dmod_Task1(Task1 x, double y) {
	Task1 res = fmod(x.x , y);
	return res;
}


//===================================================================================================================

//реалізація стандартної унарної операції додавання вказівника на екземпляр класу задачі та константою
double unadd_Task1(Task1* x, const Task1 y) {
	double res = (*(x)).x + y.x;
	return res;
}

//реалізація стандартної унарної операції віднімання вказівника на екземпляр класу задачі та константою
double unsub_Task1(Task1* x, const Task1 y) {
	double res;
	if((*(x)).x >= y.x) res = (*(x)).x - y.x;
	else res = y.x - (*(x)).x;
	return res;
}

//реалізація стандартної унарної операції множення вказівника на екземпляр класу задачі та константою
double unmul_Task1(Task1* x, const Task1 y) {
	double res = (*(x)).x * y.x;
	return res;
}

//реалізація стандартної унарної операції ділення вказівника на екземпляр класу задачі та константою
double undiv_Task1(Task1* x, const Task1 y) {
	double res = (*(x)).x / y.x;
	return res;
}

//реалізація стандартної унарної операції взяття по модулю вказівника на екземпляр класу задачі та константою
double unmod_Task1(Task1* x, const Task1 y) {
	double res = fmod(((*(x)).x) , (y.x));
	return res;
}


//===================================================================================================================

//функція вводу екземляру класу з клавіатури
int input_Task1(Task1* x) {
	double a;
	
	try {
		cout << "Please, enter x: ";
		cin >> a;
		*(x) = Task1(a);
		return 1;
	}
	catch (string) {
		cin.clear();
		cin.sync();
		cout << "********************************************************************************" << endl << "<<<VALUE IS ABSENT>>>" << endl;
		return 0;
	}
}

//функція виводу екземляру класу на консоль з заданими параметрами
void output_Task1(Task1 x, int type, int width, int precision) {
	double y = x.x;
	/*int a = int(y); //обрізаємо число до коми за к-тю знаків width
	a = a / pow(10, width);
	a = a * pow(10, width);
	y = y - a;*/

	//вивід в нормальній формі з к-тю знаків після коми precision
	if (type) {
		cout << fixed << "The value in normal form\n";
		cout.precision(precision);
		cout << y << endl;
	}
	//вивід в експоненцільній формі з к-тю знаків після коми precision
	else {
		cout.setf(ios::scientific);
		cout << fixed << "The value in exponential form\n";
		cout.precision(precision);
		cout << y << endl;
	}
}


//функція вводу екземляру класу з бінарного файлу
int inputBinaryFile_Task1(Task1* x) {
	ifstream fin("Task1.dat");
	double a;

	try {
		fin >> a;
		*(x) = Task1(a);
		fin.close();
		return 1;
	}
	catch (string) {
		fin.clear();
		fin.sync();
		fin.close();
		cout << "********************************************************************************" << endl << "<<<VALUE IS ABSENT>>>" << endl;
		return 0;
	}

}

//функція виводу екземляру класу в бінарний файл з заданими параметрами
void outputBinaryFile_Task1(Task1 x, int type, int width, int precision) {
	ofstream fout("output.dat");
	double y = x.x;
	/*int a = int(y); //обрізаємо число до коми за к-тю знаків width
	a = a / pow(10, width);
	a = a * pow(10, width);
	y = y - a;*/

	//вивід в нормальній формі з к-тю знаків після коми precision
	if (type) {
		fout << fixed << "The value in normal form\n";
		fout.precision(precision);
		fout << y << endl;
	}
	//вивід в експоненцільній формі з к-тю знаків після коми precision
	else {
		fout.setf(ios::scientific);
		fout << fixed << "The value in exponential form\n";
		fout.setf(ios::scientific);
		fout.precision(precision);
		fout << y << endl;
	}
	fout.close();
}


//функція вводу екземляру класу з текстового файлу
int inputTextFile_Task1(Task1* x) {
	ifstream fin("Task1.txt");
	double a;

	try {
		fin >> a;
		*(x) = Task1(a);
		fin.close();
		return 1;
	}
	catch (string) {
		fin.clear();
		fin.sync();
		fin.close();
		cout << "********************************************************************************" << endl << "<<<VALUE IS ABSENT>>>" << endl;
		return 0;
	}

}

//функція виводу екземляру класу в текстовий файл з заданими параметрами
void outputTextFile_Task1(Task1 x, int type, int width, int precision) {
	ofstream fout("output.txt");
	double y = x.x;
	/*int a = int(y); //обрізаємо число до коми за к-тю знаків width
	a = a / pow(10, width);
	a = a * pow(10, width);
	y = y - a;*/

	//вивід в нормальній формі з к-тю знаків після коми precision
	if (type) {
		fout << fixed << "The value in normal form\n";
		fout.precision(precision);
		fout << y << endl;
	}
	//вивід в експоненцільній формі з к-тю знаків після коми precision
	else {
		fout.setf(ios::scientific);
		fout << fixed << "The value in exponential form\n";
		fout.precision(precision);
		fout << y << endl;
	}
	fout.close();
}
// Генерація випадкового екземпляру класу Task1 розмірності n
Task1 generate_Task1(int n) {
	srand(time(0));
	double a = rand() / 100000.0;
	a = a * pow(10, n);
	double b = rand() / 100000.0;
	a += b;
	Task1 x(a);
	return x;
}
