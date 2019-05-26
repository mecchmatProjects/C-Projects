#include "vector_test.h"

vector s1 = {-1, 2, -2};
vector s2 = {2, 1, -1};

int test_add() {
    vector res = {1, 3, -3};
    if (vector_equals(v_add(s1, s2), res)) return 1;
    return 0;
}

int test_sub() {
    vector res = {-3, 1, -1};
    if (vector_equals(v_sub(s1, s2), res)) return 1;
    return 0;
}

int test_mult() {
    vector res = {0, -5, -5};
    vector sv = v_mult(s1, s2);
    if (vector_equals(sv, res)) return 1;
    return 0;
}

int test_multS() {
    Dtype res = 2;
    Dtype st = v_multS(s1, s2);
    if (st == res) return 1;
    return 0;
}