#include "triangle.h"
#include "line.h"
#include "plane.h"
#include "vector.h"
#include "pyramid.h"
/*
 * Высчитываем обьем пирамиды умножением площади основы на треть высоты
 */
Dtype pyr_volume(pyramid p) {
    triangle abc_t = {p.a, p.b, p.c};
    plane abc_p = triangle_plane(abc_t);
    line h_l = {.x = p.d, .d = {abc_p.a, abc_p.b, abc_p.c}}; // прямая, проходящая через вершину D и основу
    point H = intersectPL(abc_p, h_l); // точка пересечения плоскости основы с прямой, проходящей через D
    vector h = v_sub(point_to_vector(p.d), point_to_vector(H));
    return pyr_area_side(p, ABC) * vector_length(h) / 3;
}
/*
 * ищем площать основы пирамиды
 */
Dtype pyr_area_side(pyramid p, a_i a) {
    triangle t;
    switch (a) {
        case ABC:
            t = (triangle) {p.a, p.b, p.c};
            break;
        case ABD:
            t = (triangle) {p.a, p.b, p.d};
            break;
        case ACD:
            t = (triangle) {p.a, p.c, p.d};
            break;
        case BCD:
            t = (triangle) {p.b, p.c, p.d};
    }
    return triangle_area(t);
}
/*
 * ищем полную поверхность пирамиды
 */
Dtype pyr_full_area(pyramid p) {
    Dtype s = pyr_area_side(p, ABC);
    s += pyr_area_side(p, ABD);
    s += pyr_area_side(p, ACD);
    s += pyr_area_side(p, BCD);
    return s;
}

