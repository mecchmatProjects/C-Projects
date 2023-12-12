#include "Unit.h"
#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS
#include <math.h>

//відстань між двома точками в декартьовій системі координат
double distance_cartesian(union Point1 p1, union Point1 p2) {
    double dx = p1.cartesian.x - p2.cartesian.x;
    double dy = p1.cartesian.y - p2.cartesian.y;
    return sqrt(dx * dx + dy * dy);
}

//відстань між точками в полярній системі координат
double distance_polar(union Point1 p1, union Point1 p2) {
    double d = p1.polar.r * p1.polar.r + p2.polar.r * p2.polar.r;
    double rad1 = p1.polar.theta * 180.0 / M_PI;
    double rad2 = p2.polar.theta * 180.0 / M_PI;
    d -= 2 * p1.polar.r * p2.polar.r * cos(rad1 - rad2);
    return sqrt(d);
}

//перетворення гривень та копійок лише в копійки
int transform1(union Money m) {
    return m.hryvni.bills * 100 + m.hryvni.pennies;
}

//перетворення копійок в гривні та копійки
void transform2(union Money m) {
    int b;
    int p;
    b = m.pennie.pennies % 100;
    p = (m.pennie.pennies - b) / 100;
    printf("%d hryvni, %d copiyky", p, b);
}

//веедення вектору через 2 точки
double input1(union Vector* v) {
    printf("A(x,y,z)= ");
    scanf_s("%lf", &v->Point3.x1);
    scanf_s("%lf", &v->Point3.y1);
    scanf_s("%lf", &v->Point3.z1);

    printf("B(x,y,z)= ");
    scanf_s("%lf", &v->Point3.x2);
    scanf_s("%lf", &v->Point3.y2);
    scanf_s("%lf", &v->Point3.z2);

    return 0.;
}

//введення вектору через точку та вектор з неї
double input2(union Vector* v) {
    printf("A(x,y,z)= ");
    scanf_s("%lf", &v->Point_Vector.x);
    scanf_s("%lf", &v->Point_Vector.y);
    scanf_s("%lf", &v->Point_Vector.z);

    printf("AB(x,y,z)= ");
    scanf_s("%lf", &v->Point_Vector.xv);
    scanf_s("%lf", &v->Point_Vector.yv);
    scanf_s("%lf", &v->Point_Vector.zv);

    return 0.;
}

//перетворення двох точок у вектор та точку
void transform(union Vector p1, union Vector* p2) {
    double x_v = p1.Point3.x2 - p1.Point3.x1;
    double y_v = p1.Point3.y2 - p1.Point3.y1;
    double z_v = p1.Point3.z2 - p1.Point3.z1;

    p2->Point_Vector.x = p1.Point3.x1;
    p2->Point_Vector.y = p1.Point3.y1;
    p2->Point_Vector.z = p1.Point3.z1;

    p2->Point_Vector.xv = x_v;
    p2->Point_Vector.yv = y_v;
    p2->Point_Vector.zv = z_v;
}

//перевірка на коленарність двох векторів
bool colinear(union Vector v1, union Vector v2) {
    double mult, i, j, k;
    i = v1.Point_Vector.yv * v2.Point_Vector.zv - v1.Point_Vector.zv * v2.Point_Vector.yv;
    j = v1.Point_Vector.xv * v2.Point_Vector.zv - v1.Point_Vector.zv * v2.Point_Vector.xv;
    k = v1.Point_Vector.xv * v2.Point_Vector.yv - v1.Point_Vector.yv * v2.Point_Vector.xv;

    mult = j - j + k;
    return mult == 0;
}

//відстань між декартовими координатами у тривимірному просторі
double distance(union Point4 p1, union Point4 p2) {
    double dx = p1.cartesian.x - p2.cartesian.x;
    double dy = p1.cartesian.y - p2.cartesian.y;
    double dz = p1.cartesian.z_c - p2.cartesian.z_c;
    return sqrt(dx * dx + dy * dy + dz * dz);
}

//перетворення полярних координат у декартові
void convert1(union Point4 p1, union Point4* p2) {
    double rad = p1.polar.theta_p * 180.0 / M_PI;
    p2->cartesian.x = p1.polar.r_p * cos(rad);
    p2->cartesian.y = p1.polar.r_p * sin(rad);
    p2->cartesian.z_c = p1.polar.z_p;
}

//перетворення циліндричних координат у декартові
void convert2(union Point4 p1, union Point4* p2) {
    double rad1 = p1.spherical.theta_s * 180.0 / M_PI;
    double rad2 = p1.spherical.psi * 180.0 / M_PI;
    p2->cartesian.x = p1.spherical.r_s * cos(rad1) * sin(rad2);
    p2->cartesian.y = p1.spherical.r_s * sin(rad1) * cos(rad2);
    p2->cartesian.z_c = p1.spherical.r_s * sin(rad2);
}

//периметр круга
double perimeter_circle(union Figure c) {
    return 2 * M_PI * c.circle.r;
}

//периметр квадрата
double perimetr_square(union Figure s) {
    return 4 * s.square.a;
}

//периметр трикутника
double perimetr_triangle(union Figure t) {
    return t.triangle.a + t.triangle.b + t.triangle.c;
}

//периметр прямокутника
double perimetr_restangle(union Figure r) {
    return 2 * (r.rectangle.a + r.rectangle.b);
}

//периметр трапеції
double perimetr_trapeze(union Figure tr) {
    return tr.trapeze.a + tr.trapeze.b + tr.trapeze.c + tr.trapeze.d;
}

//площа круга
double square_circle(union Figure c) {
    return M_PI * c.circle.r * c.circle.r;
}

//площа квадрата
double square_square(union Figure s) {
    return s.square.a * s.square.a;
}

//площа трикутника
double square_triangle(union Figure t) {
    double p = perimetr_triangle(t) / 2;
    double a = p - t.triangle.a;
    double b = p - t.triangle.b;
    double c = p - t.triangle.c;
    return sqrt(p * a * b * c);
}

//площа прямокутника
double square_restangle(union Figure r) {
    return r.rectangle.a * r.rectangle.b;
}

//площа трапеції
double square_trapeze(union Figure tr) {
    unsigned a = tr.trapeze.a;
    unsigned b = tr.trapeze.b;
    unsigned c = tr.trapeze.c;
    unsigned d = tr.trapeze.d;

    return ((b + a) * sqrt((b - a + c + d) * (a - b + c - d) * (a - b - c + d))) / (4 * (b - a));
}

//функція додавання двох чисел
CustomType addValues(CustomType a, CustomType b) {
    CustomType result;

    if (a.type == STRING || b.type == STRING) {
        strcpy_s(result.value.string, INFINITY_STR);
    }
    else if (a.type == NUMBER_DOUBLE && b.type == NUMBER_DOUBLE) {
        result.type = NUMBER_DOUBLE;
        result.value.number_double = a.value.number_double + b.value.number_double;
    }
    else if (a.type == NUMBER_DOUBLE && b.type != NUMBER_DOUBLE) {
        result.type = NUMBER_DOUBLE;
        result.value.number_double = a.value.number_double + (double)b.value.number_int;
    }
    else if (a.type != NUMBER_DOUBLE && b.type == NUMBER_DOUBLE) {
        result.type = NUMBER_DOUBLE;
        result.value.number_double = (double)a.value.number_int + b.value.number_double;
    }
    else if (a.type == NUMBER_INT && b.type == NUMBER_INT) {
        result.type = NUMBER_INT;
        result.value.number_int = a.value.number_int + b.value.number_int;
    }
    else if (a.type == NUMBER_UNSIGNED && b.type == NUMBER_UNSIGNED) {
        result.type = NUMBER_UNSIGNED;
        result.value.number_unsigned = a.value.number_unsigned + b.value.number_unsigned;
    }

    return result;
}

//функція віднімання двох чисел
CustomType subtractValues(CustomType a, CustomType b) {
    CustomType result;
    result.type = STRING; // Default to string type

    if (a.type == STRING || b.type == STRING) {
        strcpy_s(result.value.string, INFINITY_STR);
    }
    else if (a.type == NUMBER_DOUBLE && b.type == NUMBER_DOUBLE) {
        result.type = NUMBER_DOUBLE;
        result.value.number_double = a.value.number_double - b.value.number_double;
    }
    else if (a.type == NUMBER_DOUBLE && b.type != NUMBER_DOUBLE) {
        result.type = NUMBER_DOUBLE;
        result.value.number_double = a.value.number_double - (double)b.value.number_int;
    }
    else if (a.type != NUMBER_DOUBLE && b.type == NUMBER_DOUBLE) {
        result.type = NUMBER_DOUBLE;
        result.value.number_double = (double)a.value.number_int - b.value.number_double;
    }
    else if (a.type == NUMBER_INT && b.type == NUMBER_INT) {
        result.type = NUMBER_INT;
        result.value.number_int = a.value.number_int - b.value.number_int;
    }
    else if (a.type == NUMBER_UNSIGNED && b.type == NUMBER_UNSIGNED) {
        result.type = NUMBER_UNSIGNED;
        result.value.number_unsigned = a.value.number_unsigned - b.value.number_unsigned;
    }

    return result;
}

//функція множення двох чисел
CustomType multiplyValues(CustomType a, CustomType b) {
    CustomType result;
    result.type = STRING; // Default to string type

    if (a.type == STRING || b.type == STRING) {
        strcpy_s(result.value.string, INFINITY_STR);
    }
    else if (a.type == NUMBER_DOUBLE && b.type == NUMBER_DOUBLE) {
        result.type = NUMBER_DOUBLE;
        result.value.number_double = a.value.number_double * b.value.number_double;
    }
    else if (a.type == NUMBER_DOUBLE && b.type != NUMBER_DOUBLE) {
        result.type = NUMBER_DOUBLE;
        result.value.number_double = a.value.number_double * (double)b.value.number_int;
    }
    else if (a.type != NUMBER_DOUBLE && b.type == NUMBER_DOUBLE) {
        result.type = NUMBER_DOUBLE;
        result.value.number_double = (double)a.value.number_int * b.value.number_double;
    }
    else if (a.type == NUMBER_INT && b.type == NUMBER_INT) {
        result.type = NUMBER_INT;
        result.value.number_int = a.value.number_int * b.value.number_int;
    }
    else if (a.type == NUMBER_UNSIGNED && b.type == NUMBER_UNSIGNED) {
        result.type = NUMBER_UNSIGNED;
        result.value.number_unsigned = a.value.number_unsigned * b.value.number_unsigned;
    }

    return result;
}

//функція ділення двох чисел
CustomType divideValues(CustomType a, CustomType b) {
    CustomType result;
    result.type = STRING; // Default to string type

    if (a.type == STRING && b.type != STRING) {
        strcpy_s(result.value.string, INFINITY_STR);
    }
    else if (a.type != STRING && b.type == STRING) {
        result.type = NUMBER_DOUBLE;
        result.value.number_double = 0.0;
    }
    else if (a.type == NUMBER_DOUBLE && b.type == NUMBER_DOUBLE) {
        result.type = NUMBER_DOUBLE;
        result.value.number_double = a.value.number_double / b.value.number_double;
    }
    else if (a.type == NUMBER_DOUBLE && b.type != NUMBER_DOUBLE) {
        result.type = NUMBER_DOUBLE;
        result.value.number_double = a.value.number_double / (double)b.value.number_int;
    }
    else if (a.type != NUMBER_DOUBLE && b.type == NUMBER_DOUBLE) {
        result.type = NUMBER_DOUBLE;
        result.value.number_double = (double)a.value.number_int / b.value.number_double;
    }
    else if (a.type == NUMBER_INT && b.type == NUMBER_INT) {
        result.type = NUMBER_INT;
        result.value.number_int = a.value.number_int / b.value.number_int;
    }
    else if (a.type == NUMBER_UNSIGNED && b.type == NUMBER_UNSIGNED) {
        result.type = NUMBER_UNSIGNED;
        result.value.number_unsigned = a.value.number_unsigned / b.value.number_unsigned;
    }
    else if (b.type == NUMBER_DOUBLE && b.value.number_double == 0) {
        strcpy_s(result.value.string, INFINITY_STR);
    }
    else if (b.type == NUMBER_INT && b.value.number_int == 0) {
        strcpy_s(result.value.string, INFINITY_STR);
    }
    else if (b.type == NUMBER_UNSIGNED && b.value.number_unsigned == 0) {
        strcpy_s(result.value.string, INFINITY_STR);
    }

    return result;
}

//виведення значення
void printValue(CustomType value) {
    switch (value.type) {
    case NUMBER_DOUBLE:
        printf("%lf\n", value.value.number_double);
        break;
    case NUMBER_INT:
        printf("%d\n", value.value.number_int);
        break;
    case NUMBER_UNSIGNED:
        printf("%u\n", value.value.number_unsigned);
        break;
    case STRING:
        printf("%s\n", value.value.string);
        break;
    }
}