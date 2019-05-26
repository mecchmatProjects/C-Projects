#include <stdio.h>
#include "vector.h"
/*
 * стандартная функция добавления векторов
 */

vector v_add(vector s1, vector s2) {
    vector res = {s1.x + s2.x, s1.y + s2.y, s1.z + s2.z};
    return res;
}
/*
 * вычитание векторов
 */
vector v_sub(vector s1, vector s2) {
    vector res = {s1.x - s2.x, s1.y - s2.y, s1.z - s2.z};
    return res;
}

Dtype v_multS(vector s1, vector s2) {
    return s1.x * s2.x +
           s1.y * s2.y +
           s1.z * s2.z;
}
/*
 * умножение векторов
 */
vector v_mult(vector s1, vector s2) {
    double matr[3][3] = {
            {s1.x, s1.y, s1.z},
            {s2.x, s2.y, s2.z}
    };
    vector s = {
            .x = matr[0][1] * matr[1][2] - matr[1][1] * matr[0][2],
            .y = -matr[0][0] * matr[1][2] + matr[1][0] * matr[0][2],
            .z = matr[0][0] * matr[1][1] - matr[1][0] * matr[0][1]
    };
    return s;
}
/*
 * длина вектора
 */
Dtype vector_length(vector v) {
    Dtype res = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    return res;
}

int vector_equals(vector s1, vector s2) {
    return s1.x == s2.x && s1.y == s2.y && s1.z == s2.z;
}
/*
 * скалярное произведение
 */
vector v_scale(vector v, Dtype l) {
    return (vector) {v.x * l, v.y * l, v.z * l};
}

void print_vector(vector s, Strtype res) {
    sprintf(res, "Vector(%e, %e, %e)", s.x, s.y, s.z);
}
