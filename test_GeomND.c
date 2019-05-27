#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include"GeomND.h"
#include"GeomND.c"
#define filename "Geom_output.txt"

void console_test() {
    PointND p1, p2, p3;
    PlaneND plane_random;
    srand(time(0));
    p1 = input_point();
    output_point(p1, 1, 8, 4);
    PlaneND plane;
    //plane = input_plane();
    VectorND v1, v2;
    //v1 = input_vector();
    v2 = generate_vector(6);
    output_vector(v2, 0, 5, 5);
    //outputBinaryFile_point("binfile", p1);
    p2 = generate_point(5);
    output_point(p2, 0, 5, 5);
    p3 = generate_point(3);
    output_point(p3, 1, 4, 4);
    plane_random = generate_plane(3);
    output_plane(plane_random, 0, 5, 5);
    int rez = outputBinaryFile_point(filename, p1);
    printf("rez = %d", rez);
    inputBinaryFile_point(filename, &p3);
    output_point(p3, FLOAT, 3, 3);

    SegmentND seg = generate_segment(3), ss;
    output_segment(seg, FLOAT, 3, 4);
    rez = outputBinaryFile_segment(filename, seg);
    printf("\nrez = %d", rez);
    inputBinaryFile_segment(filename, &ss);
    output_segment(ss, FLOAT, 3, 4);
}

int main()
{
    console_test();
}