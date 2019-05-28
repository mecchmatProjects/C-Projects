#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include"GeomND.h"
#include"GeomND.c"
#define filename "Geom_output_ooops.dat"
#define filename_txt "Geom_output_geoma_is_great.txt"

void test_console()
{
    PointND point1, point2, point3, point4;
    SegmentND s1, s2, s3, s4;
    PyramidND pyr1, pyr2, pyr3, pyr4;
    VectorND v1, v2, v3, v4;
    LineND l1, l2, l3, l4;
    PlaneND plane1, plane2, plane3, plane4;
    AngleND a1, a2, a3, a4;

    point1 = input_point();
    s1 = input_segment();
    pyr1 = input_pyramid();
    v1 = input_vector();
    l1 = input_line();
    plane1 = input_plane();
    a1 = input_angle();
}

void test_text_file()
{
    int rezt=0;

    PointND point1, point2, point3, point4;
    SegmentND s1, s2, s3, s4;
    PyramidND pyr1, pyr2, pyr3, pyr4;
    VectorND v1, v2, v3, v4;
    LineND l1, l2, l3, l4;
    PlaneND plane1, plane2, plane3, plane4;
    AngleND a1, a2, a3, a4;

    point1 = generate_point(4);
    s1 = generate_segment(4);
    pyr1 = generate_pyramid(4);
    v1 = generate_vector(23);
    l1 = generate_line(12);
    plane1 = generate_plane(7);
    a1 = generate_angle(3);

    rezt+=outputTextFile_point(filename_txt, point1, SHORTEST, 7, 3);
    rezt+=outputTextFile_segment(filename_txt, s1, SHORTEST, 9, 8);
    rezt+=outputTextFile_pyramid(filename_txt, pyr1, SCIENTIFIC, 5, 5);
    rezt+=outputTextFile_vector(filename_txt, v1, FLOAT, 6, 4);
    rezt+=outputTextFile_line(filename_txt, l1, FLOAT, 6, 4);
    rezt+=outputTextFile_plane(filename_txt, plane1, FLOAT, 6, 4);
    rezt+=outputTextFile_angle(filename_txt, a1, FLOAT, 6, 4);

    rezt+=inputTextFile_point(filename_txt, &point1);
    rezt+=inputTextFile_segment(filename_txt, &s1);
    rezt+=inputTextFile_pyramid(filename_txt, &pyr1);
    rezt+=inputTextFile_vector(filename_txt, &v1);
    rezt+=inputTextFile_line(filename_txt, &l1);
    rezt+=inputTextFile_plane(filename_txt, &plane1);
    rezt+=inputTextFile_angle(filename_txt, &a1);
    printf("\ntext file test. rez = %d", rezt);

}

void test_binary_file()
{
    int rez=0;
    PointND point1b, point2b, point3b, point4b;
    SegmentND s1b, s2b, s3b, s4b;
    PyramidND pyr1b, pyr2b, pyr3b, pyr4b;
    VectorND v1b, v2b, v3b, v4b;
    LineND l1b, l2b, l3b, l4b;
    PlaneND plane1b, plane2b, plane3b, plane4b;
    AngleND a1b, a2b, a3b, a4b;

    point1b = generate_point(4);
    s1b = generate_segment(4);
    pyr1b = generate_pyramid(4);
    v1b = generate_vector(23);
    l1b = generate_line(12);
    plane1b = generate_plane(7);
    a1b = generate_angle(3);

    rez+=outputBinaryFile_point(filename, point1b);
    rez+=outputBinaryFile_segment(filename, s1b);
    rez+=outputBinaryFile_pyramid(filename, pyr1b);
    rez+=outputBinaryFile_vector(filename, v1b);
    rez+=outputBinaryFile_line(filename, l1b);
    rez+=outputBinaryFile_plane(filename, plane1b);
    rez+=outputBinaryFile_angle(filename, a1b);

    rez+=inputBinaryFile_point(filename, &point1b);
    rez+=inputBinaryFile_segment(filename, &s1b);
    rez+=inputBinaryFile_pyramid(filename, &pyr1b);
    rez+=inputBinaryFile_vector(filename, &v1b);
    rez+=inputBinaryFile_line(filename, &l1b);
    rez+=inputBinaryFile_plane(filename, &plane1b);
    rez+=inputBinaryFile_angle(filename, &a1b);

    printf("binary file test. rez = %d\n", rez);
}

int main()
{
    int test;
    printf("choose a test: \n 1 - console;\n 2 - text file; \n 3 - binary file\n");
    scanf("%d", &test);
    if (test%3==0)
    {
        test_binary_file();
    }
    else if (test%3==1)
    {
        test_console();
    }
    else
    {
        test_text_file();
    }
}