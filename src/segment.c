#include "segment.h"
/*
 * длина отрезка
 */
Dtype segment_length(segment s) {
    return sqrt(pow(s.b.x - s.a.x, 2) + pow(s.b.y - s.a.y, 2) + pow(s.b.z - s.a.z, 2));
}

