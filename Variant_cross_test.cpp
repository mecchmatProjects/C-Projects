#include "Variant.h"
#include <iostream>
#include <chrono>

int main() {
	//зафіксуємо поточний час
	auto start = std::chrono::high_resolution_clock::now();
	//1 завдання
	std::cout<<"task 1\n";
	Point1 p1, p2;
	//запишемо алгоритм для обох видів координат
	std::cout << "Input the first point in Cartesian coordinates (x, y): ";
	std::cin >> p1.cartesian.x >> p1.cartesian.y;
	std::cout << "Input the first point in Cartesian coordinates (x, y): ";
	std::cin >> p1.cartesian.x >> p1.cartesian.y;
	std::cout << "Input the second point in Cartesian coordinates (x, y): ";
	std::cin >> p2.cartesian.x >> p2.cartesian.y;
	std::cout << "The distance between the two points is: " << distance_cartesian(p1, p2) << "\n";

	std::cout << "Input the first point in Polar coordinates (r, theta): ";
	std::cin >> p1.polar.r >> p1.polar.theta;
	std::cout << "Input the second point in Polar coordinates (r, theta): ";
	std::cin >> p2.polar.r >> p2.polar.theta;
	std::cout << "The distance between the two points is: " << distance_polar(p1, p2);

	//2 завдання
	std::cout << "\ntask 2\n";
	int n;
	//вибираємо тип вводу
	std::cout << "input type of money(1-bills and pennies, 2-only pennies): ";
	std::cin >> n;


	//для кожного типу напишемо окремий алгоритм
	Money m;
	if (n == 1) {
		std::cout << "input hryvni and copiyky: ";
		std::cin >> m.hryvni.bills >> m.hryvni.pennies;
		std::cout << "transform form: ";
		std::cout << "copiyok" << transform1(m);
	}

	if (n == 2) {
		std::cout << "input copiyky: ";
		std::cin >> m.pennie.pennies;
		std::cout << "transform form: ";
		transform2(m);
	}

	//3 завдання
	std::cout << "\ntask 3\n";
	Vector v1, v_01;
	int n1;
	//вибір методу введення
	std::cout << "choose input of 1 vector(1-2 points, 2-point and vector): ";
	std::cin >> n1;
	std::cout << "input first vector(x, y, z):\n ";
	v1 = { 0, 0, 0, 0, 0, 0 };
	if (n1 == 1) {
		input1(v1);
		transform(v1, v_01);//перетворення для легшого обчислення
	}
	else if (n1 == 2) {
		input2(v1);
		v_01 = v1;
	}


	Vector v2, v_02;
	int n2;
	std::cout << "choose input of 2 vector(1 -2 points, 2 -point and vector): ";
	std::cin >> n2;
	std::cout << "input second vector(x, y, z):\n";
	v2 = { 0, 0, 0, 0, 0, 0 };
	if (n2 == 1) {
		input1(v2);
		transform(v2, v_02);//перетворення для легшого обчислення
	}
	else if (n2 == 2) {
		input2(v2);
		v_02 = v2;
	}

	Vector v3, v_03;
	int n3;
	std::cout << "choose input of 3 vector(1 -2 points, 2 -point and vector): ";
	std::cin >> n3;
	std::cout << "input third vector:\n";
	v3 = { 0, 0, 0, 0, 0, 0 };
	if (n3 == 1) {
		input1(v3);
		transform(v3, v_03);//перетворення для легшого обчислення
	}
	else if (n3 == 2) {
		input2(v3);
		v_03 = v3;
	}

	//перевірка колінеарності
	if (colinear(v_01, v_02) || colinear(v_01, v_03) || colinear(v_02, v_03) == true) {
		std::cout << "all vectors are collinear with each other";
	}
	else {
		std::cout << "vectors are not colinear";
	}

	//4 завдання
	std::cout << "\ntask 4\n";
	double d;
	Point4 p3, p4;

	//виберемо систему координат
	std::cout << "enter 1 if you are interested in Cartesian coordinates, 2 for polar, 3 for spherical: ";
	int n0;
	std::cin >> n0;

	if (n0 == 1) {//обчислення для декартових координат
		std::cout << "input first point(x,y,z): ";
		std::cin >> p3.cartesian.x >> p3.cartesian.y >> p3.cartesian.z_c;
		std::cout << "input second point(x,y,z): ";
		std::cin >> p4.cartesian.x >> p4.cartesian.y >> p4.cartesian.z_c;
		d = distance(p3, p4);
	}

	if (n0 == 2) {//обчислення для полярних координат
		Point4 p_1, p_2;
		std::cout << "input first point(r,theta,z): ";
		std::cin >> p3.polar.r_p >> p3.polar.theta_p >> p3.polar.z_p;
		std::cout << "input second point(r,theta,z): ";
		std::cin >> p4.polar.r_p >> p4.polar.theta_p >> p4.polar.z_p;
		convert1(p3, p_1);
		convert1(p4, p_2);
		d = distance(p_1, p_2);
	}

	if (n0 == 3) {//обчислення для сферичних координат
		Point4 p_1, p_2;
		std::cout << "input first point(r,theta,psi): ";
		std::cin >> p3.spherical.r_s >> p3.spherical.theta_s >> p3.spherical.psi;
		std::cout << "input second point(r,theta,z): ";
		std::cin >> p4.spherical.r_s >> p4.spherical.theta_s >> p4.spherical.psi;
		convert2(p3, p_1);
		convert2(p4, p_2);
		d = distance(p_1, p_2);
	}
	std::cout << d;

	//5 завдання
	Figure c, s, r, t, tr;

	//дані про круг
	std::cout << "input radius of circle: ";
	std::cin >> c.circle.r;

	//дані про квадрат
	std::cout << "input sideof square: ";
	std::cin >> s.square.a;

	//дані про прямокутник
	std::cout << "input sideof restangle: ";
	std::cin >> r.rectangle.a >> r.rectangle.b;

	//дані про трикутник
	std::cout << "input sideof triangle: ";
	std::cin >> t.triangle.a >> t.triangle.b>> t.triangle.c;

	//дані про трапецію
	std::cout << "input sideof trapeze: ";
	std::cin >> t.trapeze.a >> t.trapeze.b >> t.trapeze.c >> t.trapeze.d;

	//виводимо площі та периметри фігур
	std::cout << "P (circle) = " << perimeter_circle(c);
	std::cout << "S (circle) = " << square_circle(c);
	std::cout << "P (square) = " << perimetr_square(s);
	std::cout << "S (square) = " << square_square(s);
	std::cout << "P (restangle) = " << perimetr_restangle(r);
	std::cout << "S (restangle) = " << square_restangle(r);
	std::cout << "P (triangle) = " << perimetr_triangle(t);
	std::cout << "S (triangle) = " << square_triangle(t);
	std::cout << "P (trapeze) = " << perimetr_trapeze(tr);
	std::cout << "S (restangle) = " << square_trapeze(tr);

	//6 завдання
	CustomType a, b, result;

	//ввід першого значення
	std::string type1;
	std::cout << "input type of first number: ";
	std::cin >> type1;

	if (type1 == "int") {
		a.type = NUMBER_INT;
		int a0;
		std::cout << "input first number: ";
		std::cin >> a0;
		a.value = a0;
	}
	else if (type1 == "double") {
		a.type = NUMBER_DOUBLE;
		double a0;
		std::cout << "input first number: ";
		std::cin >> a0;
		a.value = a0;
	}
	else if (type1 == "unsigned") {
		a.type = NUMBER_UNSIGNED;
		unsigned a0;
		std::cout << "input first number: ";
		std::cin >> a0;
		a.value = a0;
	}

	//ввід другого значення
	std::string type2;
	std::cout << "input type of second number: ";
	std::cin >> type2;

	if (type2 == "int") {
		b.type = NUMBER_INT;
		int b0;
		std::cout << "input second number: ";
		std::cin >> b0;
		b.value = b0;
	}
	else if (type2 == "double") {
		b.type = NUMBER_DOUBLE;
		double b0;
		std::cout << "input second number: ";
		std::cin >> b0;
		b.value = b0;
	}
	else if (type2 == "unsigned") {
		b.type = NUMBER_UNSIGNED;
		unsigned b0;
		std::cout << "input second number: ";
		std::cin >> b0;
		b.value = b0;
	}

	//виведемо введені значення
	std::cout << "a = ";
	printValue(a);
	std::cout << "b = ";
	printValue(b);

	//сума
	result = addValues(a, b);
	std::cout << "a + b = ";
	printValue(result);

	//різниця
	result = subtractValues(a, b);
	std::cout << "a - b = ";
	printValue(result);

	//добуток
	result = multiplyValues(a, b);
	std::cout << "a * b = ";
	printValue(result);

	//частка
	result = divideValues(a, b);
	std::cout << "a / b = ";
	printValue(result);

	//знову зафксуємо поточний час
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> duration = end - start;

	// Виводимо час виконання
	std::cout << "the function was executed " << duration.count() << " seconds\n";

	return 0;
}