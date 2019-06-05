/*
The MIT License (MIT)
Copyright (c) 2019 Oleksandra Karamushka (karamushka15.07@gmail.com)
01.06.2019
This module is designed for equation solving to support basic math into the project.
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#ifndef GEOMETRY2D_NOBOK_KORMUSHKA_GEOMETRY2D_NOBOK_KORMUSHKA_H
#define GEOMETRY2D_NOBOK_KORMUSHKA_GEOMETRY2D_NOBOK_KORMUSHKA_H

#include <stdbool.h>
#include <stdio.h>
#include "common.h"

typedef struct
{
    HType _type;
    DType _x;
    DType _y;
}
        Point2D;

typedef struct
{
    DType _a;
    DType _b;
    DType _c;
}
        Line2D;

typedef struct
{
    Point2D _list[2];
}
        Segment2D;

typedef struct
{
    DType _x;
    DType _y;
}
        Vector2D;

typedef struct
{
    Point2D _list[3];
    HType _type;
}
        Triangle2D;

typedef struct
{
    Point2D center;
    DType radius;
}
        Circle2D;

extern Point2D point2D_standard(DType a, DType b);

extern Line2D line2D_standard(DType a, DType b, DType c);

extern Line2D line2D_from_points(Point2D a, Point2D b);

extern Segment2D segment2D_standard(Point2D a, Point2D b);

extern Vector2D vector2D_standard(DType a, DType b);

extern Vector2D vector2D_from_points(Point2D a, Point2D b);

extern Vector2D vector2D_from_line(Line2D s);

extern Vector2D vector2D_from_segment(Segment2D s);

extern Vector2D binary_sum_vectors(Vector2D a, Vector2D b);

extern Vector2D binary_sub_vectors(Vector2D a, Vector2D b);

extern void unary_sum_vectors(Vector2D *a, Vector2D b);

extern void unary_sub_vectors(Vector2D *a, Vector2D b);

extern DType binary_mul_vectors(Vector2D a, Vector2D b);

extern DType binary_mul_scalar_vectors(Vector2D a, Vector2D b);

extern DType norm_of_vector(Vector2D v);

extern bool collinear_vectors(Vector2D a, Vector2D b);

extern bool orthogonal_vectors(Vector2D a, Vector2D b);

extern bool normed_vector(Vector2D v);

extern bool compare_segments(Segment2D a, Segment2D b);

extern HType check_points_of_triangle(Triangle2D t);

extern Triangle2D triangle2D_from_points(Point2D a, Point2D b, Point2D c);

extern DType calc_angle_in_radians(DType a, DType b, DType c);

extern DType convert_to_degrees(DType r);

extern DType convert_to_radians(DType r);

extern DType *get_sides(Triangle2D t);

extern DType *get_angles(Triangle2D t);

extern DType calculate_area(Triangle2D t);

extern void console_output_sides(Triangle2D t);

extern void console_output_angles(Triangle2D t, bool radian_form);

extern bool intersect_line_line(Line2D p, Line2D q);

extern bool intersect_line_segment(Line2D p, Segment2D q);

extern bool intersect_segment_segment(Segment2D p, Segment2D q);

extern bool intersect_line_triangle(Line2D p, Triangle2D t);

extern bool intersect_segment_triangle(Segment2D p, Triangle2D t);

extern Point2D get_intersect_line_line(Line2D p, Line2D q);

extern Point2D get_intersect_line_segment(Line2D p, Segment2D q);

extern Point2D get_intersect_segment_segment(Segment2D p, Segment2D q);

extern Point2D *get_intersect_line_triangle(Line2D p, Triangle2D t);

extern Point2D *get_intersect_segment_triangle(Segment2D p, Triangle2D t);

extern Segment2D get_median(Triangle2D t, NType i);

extern Point2D center(Triangle2D t);

extern Circle2D inner_tr(Triangle2D t);

extern Circle2D outer_tr(Triangle2D t);

extern void stream_output_point2d_data(FILE *f, Point2D p, IType type, IType width, IType precision);

extern void stream_output_line2d_data(FILE *f, Line2D l, IType type, IType width, IType precision);

extern void stream_output_segment2d_data(FILE *f, Segment2D s, IType type, IType width, IType precision);

extern void stream_output_vector2d_data(FILE *f, Vector2D v, IType type, IType width, IType precision);

extern void stream_output_triangle2d_data(FILE *f, Triangle2D t, IType type, IType width, IType precision);

extern void stream_output_circle2d_data(FILE *f, Circle2D c, IType type, IType width, IType precision);

extern void stream_input_point2d_data(FILE *f, Point2D *p);

extern void stream_input_line2d_data(FILE *f, Line2D *l);

extern void stream_input_segment2d_data(FILE *f, Segment2D *s);

extern void stream_input_vector2d_data(FILE *f, Vector2D *v);

extern void stream_input_triangle2d_data(FILE *f, Triangle2D *t);

extern void stream_input_circle2d_data(FILE *f, Circle2D *c);

extern void console_input_point2d_data(Point2D *p);

extern void console_input_line2d_data(Line2D *l);

extern void console_input_segment2d_data(Segment2D *s);

extern void console_input_vector2d_data(Vector2D *v);

extern void console_input_triangle2d_data(Triangle2D *t);

extern void console_input_circle2d_data(Circle2D *c);

extern void console_output_type(Triangle2D t);

#endif //GEOMETRY2D_NOBOK_KORMUSHKA_GEOMETRY2D_NOBOK_KORMUSHKA_H
