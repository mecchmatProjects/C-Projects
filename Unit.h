#pragma once

#include <cmath>
#include <string>
#include <string.h>

//1 ������
// ���������� �������� �� ������� ��� Point1
union Point1 {
    struct {
        double x, y;
    } cartesian;
    struct {
        double r, theta;
    } polar;
};

//������� ��� ���������� ������ �� �������, �������� � ��������� �� ������� ������ ���������
double distance_cartesian(union Point1 p1, union Point1 p2);
double distance_polar(union Point1 p1, union Point1 p2);


//2 ������
// ���������� �������� �� ������� ��� Money
union Money {
    struct {
        int bills;
        int pennies;
    } hryvni;
    struct {
        int pennies;
    } pennie;
};

//������� ��� ������������ ������ � ������� ������ �� �������
int transform1(union Money m);
void transform2(union Money m);


//3 ������
// ���������� �������� �� ������� ��� Vector
union Vector {
    struct {
        double x1;
        double y1;
        double z1;
        double x2;
        double y2;
        double z2;
    } Point3;

    struct {
        double x;
        double y;
        double z;
        double xv;
        double yv;
        double zv;
    } Point_Vector;
};

//������� ��� �������� ������� �������
double input1(union Vector* v);
double input2(union Vector* v);
//������� ��� ������������ ���� ����� � ������ �� �����
void transform(union Vector p1, union Vector* p2);
//������� ��� �������� ����������� ����� �������
bool colinear(union Vector v1, union Vector v2);


//4 ������
// ���������� �������� �� ������� ��� Point4
union Point4 {
    struct {
        double x, y, z_c;
    } cartesian;

    struct {
        double r_p, theta_p, z_p;
    } polar;

    struct {
        double r_s, theta_s, psi;
    } spherical;
};

//������� ��� ���������� ������ �� �������, �������� � ��������� ������ ���������
double distance(union Point4 p1, union Point4 p2);
//������� ��� ������������ �����, �������� � ����� �������� ��������� � ��������
void convert1(union Point4 p1, union Point4* p2);
void convert2(union Point4 p1, union Point4* p2);


// 5 ������
// ���������� �������� �� ������� ��� Figure
union Figure {
    struct {
        unsigned r;
    } circle;

    struct {
        unsigned a;
    } square;

    struct {
        unsigned a, b, c;
    } triangle;

    struct {
        unsigned a, b;
    } rectangle;

    struct {
        unsigned a, b, c, d;
    } trapeze;
};

//������� ��� ���������� ��������� �����
double perimeter_circle(union Figure c);
double perimetr_square(union Figure s);
double perimetr_triangle(union Figure t);
double perimetr_restangle(union Figure r);
double perimetr_trapeze(union Figure tr);

//������� ��� ���������� ����� �����
double square_circle(union Figure c);
double square_square(union Figure s);
double square_triangle(union Figure t);
double square_restangle(union Figure r);
double square_trapeze(union Figure tr);

//6 ������
//����� ������������� �� ������������
#define INFINITY_STR "Infinity"
#define UNDEFINED_STR "Undefined"

//��'������� ��� �������� ���� ������
typedef enum { NUMBER_DOUBLE, NUMBER_INT, NUMBER_UNSIGNED, STRING } ValueType;

// ���������� �������� �� ������� ��� CustomType
typedef struct {
    ValueType type;
    union {
        double number_double;
        int number_int;
        unsigned int number_unsigned;
        char string[20];
    } value;
} CustomType;

//������� ���� ���� �������
CustomType addValues(CustomType a, CustomType b);

//������� ������ ���� �������
CustomType subtractValues(CustomType a, CustomType b);

//������� �������� ���� �����
CustomType multiplyValues(CustomType a, CustomType b);

//������� ������ ���� �����
CustomType divideValues(CustomType a, CustomType b);

//��������� ��������
void printValue(CustomType value);