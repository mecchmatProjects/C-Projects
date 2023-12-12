#include "Unit.h"
#include <iostream>
#include <time.h>

int main() {
	//дізнаємось поточний час
	clock_t start_time = clock();
	//1 завдання
	printf("task 1\n");
	union Point1 p1, p2;
	//запишемо алгоритм для обох видів координат
	printf("Input the first point in Cartesian coordinates (x, y): ");
	scanf_s("%lf %lf", &p1.cartesian.x, &p1.cartesian.y);
	printf("Input the second point in Cartesian coordinates (x, y): ");
	scanf_s("%lf %lf", &p2.cartesian.x, &p2.cartesian.y);
	printf("The distance between the two points is: %lf\n", distance_cartesian(p1, p2));

	printf("Input the first point in Polar coordinates (r, theta): ");
	scanf_s("%lf %lf", &p1.polar.r, &p1.polar.theta);
	printf("Input the second point in Polar coordinates (r, theta): ");
	scanf_s("%lf %lf", &p2.polar.r, &p2.polar.theta);
	printf("The distance between the two points is: %lf", distance_polar(p1, p2));

	//2 завдання
	printf("\ntask 2\n");
	int n;
	//вибираємо тип вводу
	printf("input type of money(1-bills and pennies, 2-only pennies): ");
	scanf_s("%d", &n);


	//для кожного типу напишемо окремий алгоритм
	union Money m;
	if (n == 1) {
		printf("input hryvni and copiyky: ");
		scanf_s("%d %d", &m.hryvni.bills, &m.hryvni.pennies);
		printf("transform form: ");
		printf("%d copiyok", transform1(m));
	}

	if (n == 2) {
		printf("input copiyky: ");
		scanf_s("%d", &m.pennie.pennies);
		printf("transform form: ");
		transform2(m);
	}

	//3 завдання
	printf("\ntask 3\n");
	union Vector v1, v_01;
	int n1;
	//вибір методу введення
	printf("choose input of 1 vector(1-2 points, 2-point and vector): ");
	scanf_s("%d", &n1);
	printf("input first vector(x, y, z):\n ");
	v1 = { 0, 0, 0, 0, 0, 0 };
	if (n1 == 1) {
		input1(&v1);
		transform(v1, &v_01);//перетворення для легшого обчислення
	}
	else if (n1 == 2) {
		input2(&v1);
		v_01 = v1;
	}


	union Vector v2, v_02;
	int n2;
	printf("choose input of 2 vector(1 -2 points, 2 -point and vector): ");
	scanf_s("%d", &n2);
	printf("input second vector(x, y, z):\n");
	v2 = { 0, 0, 0, 0, 0, 0 };
	if (n2 == 1) {
		input1(&v2);
		transform(v2, &v_02);//перетворення для легшого обчислення
	}
	else if (n2 == 2) {
		input2(&v2);
		v_02 = v2;
	}

	union Vector v3, v_03;
	int n3;
	printf("choose input of 3 vector(1 -2 points, 2 -point and vector): ");
	scanf_s("%d", &n3);
	printf("input third vector:\n");
	v3 = { 0, 0, 0, 0, 0, 0 };
	if (n3 == 1) {
		input1(&v3);
		transform(v3, &v_03);//перетворення для легшого обчислення
	}
	else if (n3 == 2) {
		input2(&v3);
		v_03 = v3;
	}

	//перевірка колінеарності
	if (colinear(v_01, v_02) || colinear(v_01, v_03) || colinear(v_02, v_03) == true) {
		printf("all vectors are collinear with each other");
	}
	else {
		printf("vectors are not colinear");
	}

	//4 завдання
	printf("\ntask 4\n");
	double d;
	union Point4 p3, p4;

	//виберемо систему координат
	printf("enter 1 if you are interested in Cartesian coordinates, 2 for polar, 3 for spherical: ");
	int n0;
	scanf_s("%d", &n0);

	if (n0 == 1) {//обчислення для декартових координат
		printf("input first point(x,y,z): ");
		scanf_s("%lf %lf %lf", &p3.cartesian.x, &p3.cartesian.y, &p3.cartesian.z_c);
		printf("input second point(x,y,z): ");
		scanf_s("%lf %lf %lf", &p4.cartesian.x, &p4.cartesian.y, &p4.cartesian.z_c);
		d = distance(p3, p4);
	}

	if (n0 == 2) {//обчислення для полярних координат
		union Point4 p_1, p_2;
		printf("input first point(r,theta,z): ");
		scanf_s("%lf %lf %lf", &p3.polar.r_p, &p3.polar.theta_p, &p3.polar.z_p);
		printf("input second point(r,theta,z): ");
		scanf_s("%lf %lf %lf", &p4.polar.r_p, &p4.polar.theta_p, &p4.polar.z_p);
		convert1(p3, &p_1);
		convert1(p4, &p_2);
		d = distance(p_1, p_2);
	}

	if (n0 == 3) {//обчислення для сферичних координат
		union Point4 p_1, p_2;
		printf("input first point(r,theta,psi): ");
		scanf_s("%lf %lf %lf", &p3.spherical.r_s, &p3.spherical.theta_s, &p3.spherical.psi);
		printf("input second point(r,theta,z): ");
		scanf_s("%lf %lf %lf", &p4.spherical.r_s, &p4.spherical.theta_s, &p4.spherical.psi);
		convert2(p3, &p_1);
		convert2(p4, &p_2);
		d = distance(p_1, p_2);
	}
	printf("%lf", d);

	//5 завдання
	union Figure c, s, r, t, tr;

	//дані про круг
	printf("input radius of circle: ");
	scanf_s("%lf", &c.circle.r);

	//дані про квадрат
	printf("input sideof square: ");
	scanf_s("%lf", &s.square.a);

	//дані про прямокутник
	printf("input sideof restangle: ");
	scanf_s("%lf %lf", &r.rectangle.a, &r.rectangle.b);

	//дані про трикутник
	printf("input sideof triangle: ");
	scanf_s("%lf %lf %lf", &t.triangle.a, &t.triangle.b, &t.triangle.c);

	//дані про трапецію
	printf("input sideof trapeze: ");
	scanf_s("%lf %lf %lf %lf", &t.trapeze.a, &t.trapeze.b, &t.trapeze.c, &t.trapeze.d);

	//виводимо площі та периметри фігур
	printf("P (circle) = %lf", perimeter_circle(c));
	printf("S (circle) = %lf", square_circle(c));
	printf("P (square) = %lf", perimetr_square(s));
	printf("S (square) = %lf", square_square(s));
	printf("P (restangle) = %lf", perimetr_restangle(r));
	printf("S (restangle) = %lf", square_restangle(r));
	printf("P (triangle) = %lf", perimetr_triangle(t));
	printf("S (triangle) = %lf", square_triangle(t));
	printf("P (trapeze) = %lf", perimetr_trapeze(tr));
	printf("S (restangle) = %lf", square_trapeze(tr));


	//6 завдання
	printf("\ntask 6\n");
	CustomType a, b, result;

	//вводимо значення
	char type1[20];
	printf("input type of first number: ");
	scanf_s("%20s", type1, (unsigned)sizeof(type1));
	if (strcmp(type1, "int") == 0) {
		a.type = NUMBER_INT;
		int a0;
		printf("input first number: ");
		scanf_s("%d", &a0);
		a.value.number_int = a0;
	}
	if (strcmp(type1, "double") == 0) {
		a.type = NUMBER_DOUBLE;
		double a0;
		printf("input first number: ");
		scanf_s("%lf", &a0);
		a.value.number_double = a0;
	}
	if (strcmp(type1, "unsigned") == 0) {
		a.type = NUMBER_UNSIGNED;
		unsigned a0;
		printf("input first number: ");
		scanf_s("%u", &a0);
		a.value.number_unsigned = a0;
	}

	char type2[20];
	printf("input type of second number: ");
	scanf_s("%20s", type2, (unsigned)sizeof(type2));
	if (strcmp(type2, "int") == 0) {
		b.type = NUMBER_INT;
		int b0;
		scanf_s("%d", &b0);
		b.value.number_int = b0;
	}
	if (strcmp(type2, "double") == 0) {
		b.type = NUMBER_DOUBLE;
		double b0;
		scanf_s("%lf", &b0);
		b.value.number_double = b0;
	}
	if (strcmp(type2, "unsigned") == 0) {
		b.type = NUMBER_UNSIGNED;
		unsigned b0;
		scanf_s("%u", &b0);
		b.value.number_unsigned = b0;
	}

	//виводимо введені значення
	printf("a = ");
	printValue(a);
	printf("b = ");
	printValue(b);

	//додаємо
	result = addValues(a, b);
	printf("a + b = ");
	printValue(result);

	//віднімаємо
	result = subtractValues(a, b);
	printf("a - b = ");
	printValue(result);

	//множимо
	result = multiplyValues(a, b);
	printf("a * b = ");
	printValue(result);

	// ділимо
	result = divideValues(a, b);
	printf("a / b = ");
	printValue(result);

	//дізнаємось час після виконання функцій
	clock_t end_time = clock();

	//дізнаємось час виконання функцій
	double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

	printf("the function was executed %lf seconds", elapsed_time);

	return 0;
}