#pragma once

#include <cmath>
#include <string>
#include <string.h>

//1 задача
// Визначення структур та функцій для Point1
union Point1 {
    struct {
        double x, y;
    } cartesian;
    struct {
        double r, theta;
    } polar;
};

//функції для обчислення відстані між точками, заданими в декартовій та полярній системі координат
double distance_cartesian(union Point1 p1, union Point1 p2);
double distance_polar(union Point1 p1, union Point1 p2);


//2 задача
// Визначення структур та функцій для Money
union Money {
    struct {
        int bills;
        int pennies;
    } hryvni;
    struct {
        int pennies;
    } pennie;
};

//функції для перетворення копійок в паперові купюри та навпаки
int transform1(union Money m);
void transform2(union Money m);


//3 задача
// Визначення структур та функцій для Vector
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

//функції для введення значенб векторів
double input1(union Vector* v);
double input2(union Vector* v);
//функція для перетворення двох точок у вектор та точку
void transform(union Vector p1, union Vector* p2);
//функція для перевірки колінеарності трьох векторів
bool colinear(union Vector v1, union Vector v2);


//4 задача
// Визначення структур та функцій для Point4
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

//функція для обчислення відстані між точками, заданими в декартовій системі координат
double distance(union Point4 p1, union Point4 p2);
//функції для перетворення точок, заданими в інших системах координат в декартові
void convert1(union Point4 p1, union Point4* p2);
void convert2(union Point4 p1, union Point4* p2);


// 5 задача
// Визначення структур та функцій для Figure
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

//функції для обчислення периметру фігур
double perimeter_circle(union Figure c);
double perimetr_square(union Figure s);
double perimetr_triangle(union Figure t);
double perimetr_restangle(union Figure r);
double perimetr_trapeze(union Figure tr);

//функції для обчислення площі фігур
double square_circle(union Figure c);
double square_square(union Figure s);
double square_triangle(union Figure t);
double square_restangle(union Figure r);
double square_trapeze(union Figure tr);

//6 задача
//рядки невизначеність та нескінченність
#define INFINITY_STR "Infinity"
#define UNDEFINED_STR "Undefined"

//об'єднання всіх можливих типів змінних
typedef enum { NUMBER_DOUBLE, NUMBER_INT, NUMBER_UNSIGNED, STRING } ValueType;

// Визначення структур та функцій для CustomType
typedef struct {
    ValueType type;
    union {
        double number_double;
        int number_int;
        unsigned int number_unsigned;
        char string[20];
    } value;
} CustomType;

//функція суми двох значень
CustomType addValues(CustomType a, CustomType b);

//функція різниці двох значень
CustomType subtractValues(CustomType a, CustomType b);

//функція множення двох чисел
CustomType multiplyValues(CustomType a, CustomType b);

//функція ділення двох чисел
CustomType divideValues(CustomType a, CustomType b);

//виведення значення
void printValue(CustomType value);