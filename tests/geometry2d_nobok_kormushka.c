#define _ERROR_INVALID_INPUT 1

#include "../headers/geometry2d_nobok_kormushka.h"

#include <stdlib.h>

void TestVectorOperations()
{
    Vector2D a, b;

    printf("Vector Operations:\n");

    console_input_vector2d_data(&a);
    stream_output_vector2d_data(stdout, a, 1, 1, 1);
    console_input_vector2d_data(&b);
    stream_output_vector2d_data(stdout, b, 1, 1, 1);

    printf("Arithmetic:\n");

    printf("a + b:\n");
    stream_output_vector2d_data(stdout, binary_sum_vectors(a, b), 1, 1, 1);

    printf("a - b:\n");
    stream_output_vector2d_data(stdout, binary_sub_vectors(a, b), 1, 1, 1);

    printf("[a , b] = %.4f\n", binary_mul_vectors(a, b));
    printf("<a , b> = %.4f\n", binary_mul_scalar_vectors(a, b));

    printf("||a|| = %.4f\n", norm_of_vector(a));
    printf("||b|| = %.4f\n", norm_of_vector(b));

    printf("a || b - ? => %i\n", collinear_vectors(a, b));
    printf("a ⊥ b - ? => %i\n", orthogonal_vectors(a, b));

    printf("Normed a - ? => %i\n", normed_vector(a));
    printf("Normed b - ? => %i\n", normed_vector(b));

    printf("Unary a = a + b:\n");
    unary_sum_vectors(&a, b);
    stream_output_vector2d_data(stdout, a, 1, 1, 1);

    printf("Unary a = a - b:\n");
    unary_sub_vectors(&a, b);
    stream_output_vector2d_data(stdout, a, 1, 1, 1);
}

void TestTriangleOperations()
{
    Point2D array[3];

    for(IType i=0; i<3; i++) console_input_point2d_data(array+i);

    Triangle2D t;

    t = triangle2D_from_points(array[0], array[1], array[2]);

    stream_output_triangle2d_data(stdout, t, 1, 1, 1);

    printf("TYPE:\n");
    console_output_type(t);

    printf("SIDES:\n");
    console_output_sides(t);

    printf("ANGLES:\n");

    printf("Rational:\n");
    console_output_angles(t, 0);

    printf("Degrees:\n");
    console_output_angles(t, 1);

    printf("Area:\n");
    printf("S = %.4f\n", calculate_area(t));

    Triangle2D q;

    q = triangle2D_from_points(
            point2D_standard(0, 0),
            point2D_standard(2, 0),
            point2D_standard(0, 3)
    );
    stream_output_triangle2d_data(stdout, q, 1, 1, 1);
    printf("Center for this triangle:\n");
    stream_output_point2d_data(stdout, center(q), 1, 1, 1);
}

void TestIntersectOperations()
{
    Line2D a, b;

    a = line2D_standard(-2, 1, 1);
    b = line2D_standard(3, 1, -1);

    Segment2D c;
    c = segment2D_standard(point2D_standard(0, 1), point2D_standard(1, -2));

    Segment2D d;
    d = segment2D_standard(point2D_standard(0, -1), point2D_standard(1, 1));

    Triangle2D t;

    t = triangle2D_from_points(
            point2D_standard(0, 0),
            point2D_standard(2, 0),
            point2D_standard(0, 3)
    );

    printf("LINE-LINE:\n");
    stream_output_point2d_data(stdout, get_intersect_line_line(a, b), 1, 1, 1);

    printf("LINE-SEGMENT:\n");
    stream_output_point2d_data(stdout, get_intersect_line_segment(a, c), 1, 1, 1);

    printf("SEGMENT-SEGMENT:\n");
    stream_output_point2d_data(stdout, get_intersect_segment_segment(c, d), 1, 1, 1);

    // !!!
    printf("LINE-TRIANGLE:\n");
    Point2D *result_1 = get_intersect_line_triangle(a, t);
    for(IType i=0; i<3; i++)
    {
        stream_output_point2d_data(stdout, result_1[i], 1, 1, 1);
    }
    printf("SEGMENT-TRIANGLE:\n");
    Point2D *result_2 = get_intersect_segment_triangle(d, t);
    for(IType i=0; i<3; i++)
    {
        stream_output_point2d_data(stdout, result_1[i], 1, 1, 1);
    }
    free(result_1); free(result_2);
}

void TestTextOperations()
{
    FILE *test_stream;

    printf("POINT2D FILE OPERATIONS:\n");

    Point2D p, q;

    p = point2D_standard(1, 2);

    test_stream = fopen("../test_point2d_write.txt", "w");
    stream_output_point2d_data(test_stream, p, 1, 1, 1);
    fclose(test_stream);

    test_stream = fopen("../test_point2d_write.txt", "r");
    stream_input_point2d_data(test_stream, &q);
    fclose(test_stream);

    stream_output_point2d_data(stdout, q, 1, 1, 1);

    printf("LINE2D FILE OPERATIONS:\n");

    Line2D l, t;

    l = line2D_from_points(point2D_standard(0, 1), point2D_standard(1, 0));

    test_stream = fopen("../test_line2d_write.txt", "w");
    stream_output_line2d_data(test_stream, l, 1, 1, 1);
    fclose(test_stream);

    test_stream = fopen("../test_line2d_write.txt", "r");
    stream_input_line2d_data(test_stream, &t);
    fclose(test_stream);

    stream_output_line2d_data(stdout, t, 1, 1, 1);

    printf("SEGMENT2D FILE OPERATIONS:\n");

    Segment2D v, w;

    v = segment2D_standard(point2D_standard(0, 1), point2D_standard(1, 0));

    test_stream = fopen("../test_segment2d_write.txt", "w");
    stream_output_segment2d_data(test_stream, v, 1, 1, 1);
    fclose(test_stream);

    test_stream = fopen("../test_segment2d_write.txt", "r");
    stream_input_segment2d_data(test_stream, &w);
    fclose(test_stream);

    stream_output_segment2d_data(stdout, w, 1, 1, 1);

    printf("VECTOR2D FILE OPERATIONS:\n");

    Vector2D i, j;

    i = vector2D_standard(4, 6);

    test_stream = fopen("../test_vector2d_write.txt", "w");
    stream_output_vector2d_data(test_stream, i, 1, 1, 1);
    fclose(test_stream);

    test_stream = fopen("../test_vector2d_write.txt", "r");
    stream_input_vector2d_data(test_stream, &j);
    fclose(test_stream);

    stream_output_vector2d_data(stdout, j, 1, 1, 1);

    printf("TRIANGLE2D FILE OPERATIONS:\n");

    Triangle2D f, g;

    f = triangle2D_from_points(
            point2D_standard(0, 0),
            point2D_standard(1, 0),
            point2D_standard(0, 1)
            );

    test_stream = fopen("../test_triangle2d_write.txt", "w");
    stream_output_triangle2d_data(test_stream, f, 1, 1, 1);
    fclose(test_stream);

    test_stream = fopen("../test_triangle2d_write.txt", "r");
    stream_input_triangle2d_data(test_stream, &g);
    fclose(test_stream);

    stream_output_triangle2d_data(stdout, g, 1, 1, 1);

    printf("CIRCLE2D FILE OPERATIONS:\n");

    Circle2D h, y;

    h.center = point2D_standard(0, 0);

    h.radius = 1.5;

    test_stream = fopen("../test_circle2d_write.txt", "w");
    stream_output_circle2d_data(test_stream, h, 1, 1, 1);
    fclose(test_stream);

    test_stream = fopen("../test_circle2d_write.txt", "r");
    stream_input_circle2d_data(test_stream, &y);
    fclose(test_stream);

    stream_output_circle2d_data(stdout, y, 1, 1, 1);
}

IType main()
{
    short m;
    printf("Enter your mode:\n"
           "1 - Test basic vector operations\n"
           "2 - Test basic triangle operations\n"
           "3 - Test intersection functions\n"
           "4 - Test operations with text files\n");
    scanf("%hi", &m);

    switch (m)
    {
        case 1:
        {
            TestVectorOperations();
            break;
        }
        case 2:
        {
            TestTriangleOperations();
            break;
        }
        case 3:
        {
            TestIntersectOperations();
            break;
        }
        case 4:
        {
            TestTextOperations();
            break;
        }
        default:
        {
            printf("Invalid input.\n");
            exit(_ERROR_INVALID_INPUT);
        }
    }
}