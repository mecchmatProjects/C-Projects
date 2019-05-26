#include "plane.h"
/*
 * сравнение плоскостей
 */  
int plane_equals(plane p1, plane p2) {
    if (p1.a == p2.a &&
        p1.b == p2.b &&
        p1.c == p2.c &&
        p1.d == p2.d)
        return 1;
    return 0;
}

