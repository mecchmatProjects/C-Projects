#include "triangle.h"

/*
 * высчитываем периметр триугольникa
 */

Dtype triangle_perimeter(triangle t) {
    segment a = {t.b, t.c};
    segment b = {t.a, t.c};
    segment c = {t.a, t.b};
    Dtype a_length = segment_length(a);
    Dtype b_length = segment_length(b);
    Dtype c_length = segment_length(c);
    return (a_length + b_length + c_length);
}
/*ищем вектор-нормали (векторное произведение двух векторов плоскости треугольника)*/

vector triangle_n_vector(triangle t) {
    vector v1 = {t.b.x - t.a.x, t.b.y - t.a.y, t.b.z - t.a.z};
    vector v2 = {t.c.x - t.a.x, t.c.y - t.a.y, t.c.z - t.a.z};
    return v_mult(v1, v2);
}
/*
 * высчитываем площадь триугольникa
 * так как для вычисления вектора нормали нами использовалось векторное произвeдение двух сторон треугольника,
 * мы можем использовать его длину для определения площади
 */
Dtype triangle_area(triangle t) {
    return vector_length(triangle_n_vector(t))/2;
}
/*
 * задаем плоскость,в которой находится триугольник
 */
plane triangle_plane(triangle t) {
    vector n = triangle_n_vector(t);
    vector d = {t.a.x, t.a.y, t.a.z};
    plane res = {n.x, n.y, n.z, -v_multS(n, d)};
    return res;
}
