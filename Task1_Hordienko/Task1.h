#pragma once

//створення класу для даної задачі
class Task1
{
	//опис відкритих полей та методів
	public:

		double x;   //поле х даного класу

		Task1(double n);   //конструктор з параметрами
		Task1();   //конструктор за замовчуванням
		~Task1(); //деструктор класу, не може приймати параметри та завжди є єдиним в класі
			
};

//===================================================================================================================

//заголовки стандартних операцій 
Task1 add_Task1(Task1 x, Task1 y);
Task1 sub_Task1(Task1 x, Task1 y);
Task1 mul_Task1(Task1 x, Task1 y);
Task1 dmul_Task1(Task1 x, double y);
Task1 div_Task1(Task1 x, Task1 y);
Task1 ddiv_Task1(Task1 x, double y);
Task1 mod_Task1(Task1 x, Task1 y);
Task1 dmod_Task1(Task1 x, double y);


//===================================================================================================================


//заголовки стандартних унарних операцій
double unadd_Task1(Task1* x, const Task1 y);
double unsub_Task1(Task1* x, const Task1 y);
double unmul_Task1(Task1* x, const Task1 y);
double undiv_Task1(Task1* x, const Task1 y);
double unmod_Task1(Task1* x, const Task1 y);

//===================================================================================================================



//оперції введення/виведення для екземплярів класу
int input_Task1(Task1* x); //функція вводу екземляру класу з клавіатури
void output_Task1(Task1 x, int type, int width, int precision);  //функція виводу екземляру класу на консоль з заданими параметрами
//де type=1 - вивід числа в нормальній формі, type=0 - експоненцільній, width - к-ть цифр до коми, precision - к-ть цифр після коми

int inputBinaryFile_Task1(Task1* x);  //функція вводу екземляру класу з бінарного файлу
void outputBinaryFile_Task1(Task1 x, int type, int width, int precision); //функція виводу екземляру класу в бінарний файл з заданими параметрами

int inputTextFile_Task1(Task1* x); //функція вводу екземляру класу з текстового файлу
void outputTextFile_Task1(Task1 x, int type, int width, int precision); //функція виводу екземляру класу в текстовий файл з заданими параметрами


Task1 generate_Task1(int n); // Генерація випадкового екземпляру класу Task1 розмірності n

