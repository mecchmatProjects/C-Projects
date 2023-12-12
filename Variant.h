#pragma once
#include <variant>
#include <cmath>
#include <optional>
#include <iostream>
#include <variant>

//1 задача
// Визначення структур та функцій для Point1
struct Point1 {
    union {
        struct {
            double x, y;
        } cartesian;
        struct {
            double r, theta;
        } polar;
    };
};

//функції для обчислення відстані між точками, заданими в декартовій та полярній системі координат
double distance_cartesian(const Point1& p1, const Point1& p2);
double distance_polar(const Point1& p1, const Point1& p2);


//2 задача
// Визначення структур та функцій для Money
struct Money {
    union {
        struct {
            int bills;
            int pennies;
        } hryvni;
        struct {
            int pennies;
        } pennie;
    };
};

//функції для перетворення копійок в паперові купюри та навпаки
int transform1(const Money& m);
void transform2(const Money& m);

//3 задача
// Визначення структур та функцій для Vector
struct Vector {
    union {
        struct {
            double x1, y1, z1;
            double x2, y2, z2;
        } Point3;

        struct {
            double x, y, z;
            double xv, yv, zv;
        } Point_Vector;
    };
};

//функції для введення значенб векторів
double input1(Vector& v);
double input2(Vector& v);
//функція для перетворення двох точок у вектор та точку
void transform(Vector p1, Vector& p2);
//функція для перевірки колінеарності трьох векторів
bool colinear(const Vector& v1, const Vector& v2);


//4 задача
// Визначення структур та функцій для Point4
struct Point4 {
    union {
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
};

//функція для обчислення відстані між точками, заданими в декартовій системі координат
double distance(const Point4& p1, const Point4& p2);
//функції для перетворення точок, заданими в інших системах координат в декартові
void convert1(const Point4& p1, Point4& p2);
void convert2(const Point4& p1, Point4& p2);


// 5 задача
// Визначення структур та функцій для Figure
struct Figure {
    union {
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
};

//функції для обчислення периметру фігур
double perimeter_circle(const Figure& c);
double perimetr_square(const Figure& s);
double perimetr_triangle(const Figure& t);
double perimetr_restangle(const Figure& r);
double perimetr_trapeze(const Figure& tr);

//функції для обчислення площі фігур
double square_circle(const Figure& c);
double square_square(const Figure& s);
double square_triangle(const Figure& t);
double square_restangle(const Figure& r);
double square_trapeze(const Figure& tr);


//6 задача
enum ValueType { NUMBER_DOUBLE, NUMBER_INT, NUMBER_UNSIGNED };

//Визначення структур та функцій для Figure
struct CustomType {
    ValueType type;
    std::variant<double, int, unsigned> value;
};

//функції арифметичних дій для двох значень
CustomType addValues(const CustomType& a, const CustomType& b);
CustomType subtractValues(const CustomType& a, const CustomType& b);
CustomType multiplyValues(const CustomType& a, const CustomType& b);
CustomType divideValues(const CustomType& a, const CustomType& b);
//функція виводу значення
void printValue(const CustomType& value);