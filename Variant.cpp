#include "Variant.h"
#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS
#include <math.h>

//відстань між двома точками в декартьовій системі координат
double distance_cartesian(const Point1& p1, const Point1& p2) {
    double dx = p1.cartesian.x - p2.cartesian.x;
    double dy = p1.cartesian.y - p2.cartesian.y;
    return std::sqrt(dx * dx + dy * dy);
}

//відстань між точками в полярній системі координат
double distance_polar(const Point1& p1, const Point1& p2) {
    double d = p1.polar.r * p1.polar.r + p2.polar.r * p2.polar.r;
    double rad1 = p1.polar.theta * 180.0 / M_PI;
    double rad2 = p2.polar.theta * 180.0 / M_PI;
    d -= 2 * p1.polar.r * p2.polar.r * std::cos(rad1 - rad2);
    return std::sqrt(d);
}

//перетворення гривень та копійок лише в копійки
int transform1(const Money& m) {
    return m.hryvni.bills * 100 + m.hryvni.pennies;
}

//перетворення копійок в гривні та копійки
void transform2(const Money& m) {
    int b = m.pennie.pennies % 100;
    int p = (m.pennie.pennies - b) / 100;
    std::cout << p << " hryvni, " << b << " copiyky";
}

//веедення вектору через 2 точки
double input1(Vector& v) {
    std::cout << "A(x,y,z)= ";
    std::cin >> v.Point3.x1 >> v.Point3.y1 >> v.Point3.z1;

    std::cout << "B(x,y,z)= ";
    std::cin >> v.Point3.x2 >> v.Point3.y2 >> v.Point3.z2;

    return 0.0;
}

//введення вектору через точку та вектор з неї
double input2(Vector& v) {
    std::cout << "A(x,y,z)= ";
    std::cin >> v.Point_Vector.x >> v.Point_Vector.y >> v.Point_Vector.z;

    std::cout << "AB(x,y,z)= ";
    std::cin >> v.Point_Vector.xv >> v.Point_Vector.yv >> v.Point_Vector.zv;

    return 0.0;
}

//перетворення двох точок у вектор та точку
void transform(Vector p1, Vector& p2) {
    double x_v = p1.Point3.x2 - p1.Point3.x1;
    double y_v = p1.Point3.y2 - p1.Point3.y1;
    double z_v = p1.Point3.z2 - p1.Point3.z1;

    p2.Point_Vector.x = p1.Point3.x1;
    p2.Point_Vector.y = p1.Point3.y1;
    p2.Point_Vector.z = p1.Point3.z1;

    p2.Point_Vector.xv = x_v;
    p2.Point_Vector.yv = y_v;
    p2.Point_Vector.zv = z_v;
}

//перевірка на коленарність двох векторів
bool colinear(const Vector& v1, const Vector& v2) {
    double mult, i, j, k;
    i = v1.Point_Vector.yv * v2.Point_Vector.zv - v1.Point_Vector.zv * v2.Point_Vector.yv;
    j = v1.Point_Vector.xv * v2.Point_Vector.zv - v1.Point_Vector.zv * v2.Point_Vector.xv;
    k = v1.Point_Vector.xv * v2.Point_Vector.yv - v1.Point_Vector.yv * v2.Point_Vector.xv;

    mult = j - j + k;
    return mult == 0;
}

//відстань між декартовими координатами у тривимірному просторі
double distance(const Point4& p1, const Point4& p2) {
    double dx = p1.cartesian.x - p2.cartesian.x;
    double dy = p1.cartesian.y - p2.cartesian.y;
    double dz = p1.cartesian.z_c - p2.cartesian.z_c;
    return std::sqrt(dx * dx + dy * dy + dz * dz);
}

//перетворення полярних координат у декартові
void convert1(const Point4& p1, Point4& p2) {
    double rad = p1.polar.theta_p * 180.0 / M_PI;
    p2.cartesian.x = p1.polar.r_p * std::cos(rad);
    p2.cartesian.y = p1.polar.r_p * std::sin(rad);
    p2.cartesian.z_c = p1.polar.z_p;
}

//перетворення циліндричних координат у декартові
void convert2(const Point4& p1, Point4& p2) {
    double rad1 = p1.spherical.theta_s * 180.0 / M_PI;
    double rad2 = p1.spherical.psi * 180.0 / M_PI;
    p2.cartesian.x = p1.spherical.r_s * std::cos(rad1) * std::sin(rad2);
    p2.cartesian.y = p1.spherical.r_s * std::sin(rad1) * std::cos(rad2);
    p2.cartesian.z_c = p1.spherical.r_s * std::sin(rad2);
}

//периметр круга
double perimeter_circle(const Figure& c) {
    return 2 * M_PI * c.circle.r;
}

//периметр квадрата
double perimetr_square(const Figure& s) {
    return 4 * s.square.a;
}

//периметр трикутника
double perimetr_triangle(const Figure& t) {
    return t.triangle.a + t.triangle.b + t.triangle.c;
}

//периметр прямокутника
double perimetr_restangle(const Figure& r) {
    return 2 * (r.rectangle.a + r.rectangle.b);
}

//периметр трапеції
double perimetr_trapeze(const Figure& tr) {
    return tr.trapeze.a + tr.trapeze.b + tr.trapeze.c + tr.trapeze.d;
}

//площа круга
double square_circle(const Figure& c) {
    return M_PI * c.circle.r * c.circle.r;
}

//площа квадрата
double square_square(const Figure& s) {
    return s.square.a * s.square.a;
}

//площа трикутника
double square_triangle(const Figure& t) {
    double p = perimetr_triangle(t) / 2;
    double a = p - t.triangle.a;
    double b = p - t.triangle.b;
    double c = p - t.triangle.c;
    return std::sqrt(p * a * b * c);
}

//площа прямокутника
double square_restangle(const Figure& r) {
    return r.rectangle.a * r.rectangle.b;
}

//площа трапеції
double square_trapeze(const Figure& tr) {
    unsigned a = tr.trapeze.a;
    unsigned b = tr.trapeze.b;
    unsigned c = tr.trapeze.c;
    unsigned d = tr.trapeze.d;
    return ((b + a) * std::sqrt((b - a + c + d) * (a - b + c - d) * (a - b - c + d))) / (4 * (b - a));
}

//функція додавання
CustomType addValues(const CustomType& a, const CustomType& b) {
    CustomType result;
    result.type = a.type; // присвоєння типу

    //додавання
    if (a.type == NUMBER_DOUBLE) {
        result.value = std::get<double>(a.value) + std::get<double>(b.value);
    }
    else if (a.type == NUMBER_INT) {
        result.value = std::get<int>(a.value) + std::get<int>(b.value);
    }
    else if (a.type == NUMBER_UNSIGNED) {
        result.value = std::get<unsigned>(a.value) + std::get<unsigned>(b.value);
    }

    return result;
}

//функція віднімання
CustomType subtractValues(const CustomType& a, const CustomType& b) {
    CustomType result;
    result.type = a.type; // присвоєння типу

    //віднімання
    if (a.type == NUMBER_DOUBLE) {
        result.value = std::get<double>(a.value) - std::get<double>(b.value);
    }
    else if (a.type == NUMBER_INT) {
        result.value = std::get<int>(a.value) - std::get<int>(b.value);
    }
    else if (a.type == NUMBER_UNSIGNED) {
        result.value = std::get<unsigned>(a.value) - std::get<unsigned>(b.value);
    }

    return result;
}

//функція множення
CustomType multiplyValues(const CustomType& a, const CustomType& b) {
    CustomType result;
    result.type = a.type; //присвоєння типу

    //множення
    if (a.type == NUMBER_DOUBLE) {
        result.value = std::get<double>(a.value) * std::get<double>(b.value);
    }
    else if (a.type == NUMBER_INT) {
        result.value = std::get<int>(a.value) * std::get<int>(b.value);
    }
    else if (a.type == NUMBER_UNSIGNED) {
        result.value = std::get<unsigned>(a.value) * std::get<unsigned>(b.value);
    }

    return result;
}

CustomType divideValues(const CustomType& a, const CustomType& b) {
    CustomType result;
    result.type = a.type; //присвоєння типу

    //ділення
    if (a.type == NUMBER_DOUBLE) {
        result.value = std::get<double>(a.value) / std::get<double>(b.value);
    }
    else if (a.type == NUMBER_INT) {
        result.value = std::get<int>(a.value) / std::get<int>(b.value);
    }
    else if (a.type == NUMBER_UNSIGNED) {
        result.value = std::get<unsigned>(a.value) / std::get<unsigned>(b.value);
    }

    return result;
}

void printValue(const CustomType& value) {
    //виведемо значення, приймаючи до уваги їх тип
    if (value.type == NUMBER_DOUBLE) {
        std::cout << std::get<double>(value.value) << std::endl;
    }
    else if (value.type == NUMBER_INT) {
        std::cout << std::get<int>(value.value) << std::endl;
    }
    else if (value.type == NUMBER_UNSIGNED) {
        std::cout << std::get<unsigned>(value.value) << std::endl;
    }
}