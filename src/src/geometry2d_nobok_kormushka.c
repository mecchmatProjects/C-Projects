#include "../headers/geometry2d_nobok_kormushka.h"

#define _INF (1./0.)

#define _NORMAL 0
#define _FULL 1
#define _EMPTY -1

#define _ACUTE_TRIANGLE 1
#define _OBTUSE_TRIANGLE 2
#define _RIGHT_TRIANGLE 0

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <malloc.h>

Point2D point2D_standard(float a, float b)
{
    Point2D r;
    r._x = a;
    r._y = b;
    if((r._x == _INF) && (r._y == _INF))
    {
        ((r._x * r._y) < 0) ?
        (r._type = _EMPTY) : (r._type = _FULL);
    } else r._type = _NORMAL;
    return r;
}

Line2D line2D_standard(Point2D a, Point2D b)
{
    Line2D r;
    r._list[0] = a;
    r._list[1] = b;
    return r;
}

Segment2D segment2D_standard(Point2D a, Point2D b)
{
    Segment2D r;
    r._list[0] = a;
    r._list[1] = b;
    return r;
}

Vector2D vector2D_standard(float a, float b)
{
    Vector2D r;
    r._x = a;
    r._y = b;
    return r;
}

Vector2D vector2D_from_points(Point2D a, Point2D b)
{
    Vector2D r;
    r._x = a._x - b._x;
    r._y = a._y - b._y;
    return r;
}

Vector2D vector2D_from_line(Line2D s)
{
    return vector2D_from_points(s._list[0], s._list[1]);
}

Vector2D vector2D_from_segment(Segment2D s)
{
    return vector2D_from_points(s._list[0], s._list[1]);
}

Vector2D binary_sum_vectors(Vector2D a, Vector2D b)
{
    return vector2D_standard(a._x + b._x, a._y + b._y);
}

Vector2D binary_sub_vectors(Vector2D a, Vector2D b)
{
    return vector2D_standard(a._x - b._x, a._y - b._y);
}

void unary_sum_vectors(Vector2D *a, Vector2D b)
{
    *a = binary_sum_vectors(*a, b);
}

void unary_sub_vectors(Vector2D *a, Vector2D b)
{
    *a = binary_sub_vectors(*a, b);
}

float binary_mul_vectors(Vector2D a, Vector2D b)
{
    return a._x * b._y  - a._y * b._x;
}

float binary_mul_scalar_vectors(Vector2D a, Vector2D b)
{
    return a._x * b._x + a._y * b._y;
}

float norm_of_vector(Vector2D v)
{
    return sqrt(v._x * v._x + v._y * v._y);
}

bool collinear_vectors(Vector2D a, Vector2D b)
{
    return (binary_mul_vectors(a, b)) ? 0 : 1;
}

bool orthogonal_vectors(Vector2D a, Vector2D b)
{
    return (binary_mul_scalar_vectors(a, b)) ? 0 : 1;
}

bool normed_vector(Vector2D v)
{
    return (norm_of_vector(v) == 1.) ? 1 : 0;
}

bool compare_segments(Segment2D a, Segment2D b)
{
    for(int i=0; i<2; i++)
    {
        if(a._list[i]._x != b._list[i]._x) return 0;
        if(a._list[i]._y != b._list[i]._y) return 0;
    }
    return 1;
}

short check_points_of_triangle(Triangle2D t)
{
    Segment2D s1, s2, s3;
    float a, b, c;
    float z;

    s1 = segment2D_standard(t._list[0], t._list[1]);
    s2 = segment2D_standard(t._list[1], t._list[2]);
    s3 = segment2D_standard(t._list[0], t._list[2]);

    assert(!compare_segments(s1, s2));
    assert(!compare_segments(s2, s3));
    assert(!compare_segments(s3, s1));

    a = norm_of_vector(vector2D_from_points(t._list[0], t._list[1]));
    b = norm_of_vector(vector2D_from_points(t._list[1], t._list[2]));
    c = norm_of_vector(vector2D_from_points(t._list[0], t._list[2]));

    if((a > b) && (a > c))
    {
        z = c;
        c = a;
        a = z;
    }

    else {
        if((b > c) && (b > a))
        {
            z = c;
            c = b;
            b = z;
        }
    }

    if(c > a + b) return -1;
    else
    {
        if((c * c) == ((a * a) + (b * b))) return _RIGHT_TRIANGLE;
        else
        {
            if((c * c) > ((a * a) + (b * b))) return _OBTUSE_TRIANGLE;
            else return _ACUTE_TRIANGLE;
        }
    }
}

Triangle2D triangle2D_from_points(Point2D a, Point2D b, Point2D c)
{
    Triangle2D r;

    r._list[0] = a;
    r._list[1] = b;
    r._list[2] = c;

    r._type = check_points_of_triangle(r);

    assert(r._type != -1);

    return r;
}

float calc_angle_in_radians(float a, float b, float c)
{
    return acos((b * b + c * c - a * a)/(2 * b *c));
}

float convert_to_degrees(float r)
{
    return r * (180/M_PI);
}

float convert_to_radians(float r)
{
    return r * (M_PI/180);
}

float *get_sides(Triangle2D t)
{
    float *array;
    array = (float*)calloc(3, sizeof(float));

    array[0] = norm_of_vector(vector2D_from_points(t._list[0], t._list[1]));
    array[1] = norm_of_vector(vector2D_from_points(t._list[1], t._list[2]));
    array[2] = norm_of_vector(vector2D_from_points(t._list[0], t._list[2]));

    return array;
}

float *get_angles(Triangle2D t)
{
    float *array;
    array = (float*)calloc(3, sizeof(float));

    float a = norm_of_vector(vector2D_from_points(t._list[0], t._list[1]));
    float b = norm_of_vector(vector2D_from_points(t._list[1], t._list[2]));
    float c = norm_of_vector(vector2D_from_points(t._list[0], t._list[2]));

    array[0] = calc_angle_in_radians(a, b, c);
    array[1] = calc_angle_in_radians(b, c, a);
    array[2] = calc_angle_in_radians(c, a, b);

    return array;
}

float calculate_area(Triangle2D t)
{
    float a = norm_of_vector(vector2D_from_points(t._list[0], t._list[1]));
    float b = norm_of_vector(vector2D_from_points(t._list[1], t._list[2]));
    float c = norm_of_vector(vector2D_from_points(t._list[0], t._list[2]));

    float p = (a + b + c)/2.;
    return sqrt(p * (p - a) * (p - b) * (p - c));
}

void console_output_sides(Triangle2D t)
{
    float *a = get_sides(t);
    for (int i = 0; i < 3; ++i)
    {
        printf("%.4f\t", a[i]);
    }
    printf("\n");
    free(a);
}

void console_output_angles(Triangle2D t, bool radian_form)
{
    float *a = get_angles(t);
    for (int i = 0; i < 3; ++i)
    {
        printf("%.4f\t", radian_form ? a[i] : convert_to_degrees(a[i]));
    }
    printf("\n");
    free(a);
}

bool intersect_line_line(Line2D p, Line2D q)
{
    assert(!collinear_vectors(vector2D_from_line(p), vector2D_from_line(q)));
}

bool intersect_line_segment(Line2D p, Segment2D q)
{
    assert(!collinear_vectors(vector2D_from_line(p), vector2D_from_segment(q)));
}

bool intersect_segment_segment(Segment2D p, Segment2D q)
{
    assert(!collinear_vectors(vector2D_from_segment(p), vector2D_from_segment(q)));
}

bool intersect_line_triangle(Line2D p, Triangle2D t)
{}

bool intersect_segment_triangle(Segment2D p, Triangle2D t)
{}

Point2D get_intersect_line_line(Line2D p, Line2D q)
{}

Point2D get_intersect_line_segment(Line2D p, Segment2D q)
{}

Point2D get_intersect_segment_segment(Segment2D p, Segment2D q)
{}

Point2D *get_intersect_line_triangle(Line2D p, Triangle2D t)
{}

Point2D *get_intersect_segment_triangle(Segment2D p, Triangle2D t)
{}

void stream_output_point2d_data(FILE *f, Point2D p, int type, int width, int precision)
{
    assert(f != NULL);
    fprintf(f, "POINT2D\n");
    fprintf(f, "%i %f %f\n", p._type, p._x, p._y);
}

void stream_output_line2d_data(FILE *f, Line2D l, int type, int width, int precision)
{
    assert(f != NULL);
    fprintf(f, "LINE2D\n");
    for(int i=0; i<2; i++)
    {
        stream_output_point2d_data(f, l._list[i], type, width, precision);
    }
};

void stream_output_segment2d_data(FILE *f, Segment2D s, int type, int width, int precision)
{
    assert(f != NULL);
    fprintf(f, "SEGMENT2D\n");
    for(int i=0; i<2; i++)
    {
        stream_output_point2d_data(f, s._list[i], type, width, precision);
    }
}

void stream_output_vector2d_data(FILE *f, Vector2D v, int type, int width, int precision)
{
    assert(f != NULL);
    fprintf(f, "VECTOR2D\n");
    fprintf(f, "%f %f\n", v._x, v._y);
}

void stream_output_triangle2d_data(FILE *f, Triangle2D t, int type, int width, int precision)
{
    assert(f != NULL);
    fprintf(f, "TRIANGLE2D\n");
    fprintf(f, "%i\n", t._type);
    for(int i=0; i<3; i++)
    {
        stream_output_point2d_data(f, t._list[i], type, width, precision);
    }
}

void stream_output_circle2d_data(FILE *f, Circle2D c, int type, int width, int precision)
{
    assert(f != NULL);
    fprintf(f, "CIRCLE2D\n");
    fprintf(f, "%f\n", c.radius);
    stream_output_point2d_data(f, c.center, type, width, precision);
}

void stream_input_point2d_data(FILE *f, Point2D *p)
{
    assert(f != NULL);

    char *init_line = NULL;
    size_t len = 0;

    getline(&init_line, &len, f);

    assert(!strcmp(init_line, "POINT2D\n"));

    fscanf(f, "%hi %f %f\n",
           &p->_type, &p->_x, &p->_y);

    free(init_line);
}

void stream_input_line2d_data(FILE *f, Line2D *l)
{
    assert(f != NULL);

    char *init_line = NULL;
    size_t len = 0;

    getline(&init_line, &len, f);

    assert(!strcmp(init_line, "LINE2D\n"));

    for(int i=0; i<2; i++)
    {
        stream_input_point2d_data(f, &l->_list[i]);
    }

    free(init_line);
}

void stream_input_segment2d_data(FILE *f, Segment2D *s)
{
    assert(f != NULL);

    char *init_line = NULL;
    size_t len = 0;

    getline(&init_line, &len, f);

    assert(!strcmp(init_line, "SEGMENT2D\n"));

    for(int i=0; i<2; i++)
    {
        stream_input_point2d_data(f, &s->_list[i]);
    }

    free(init_line);
}

void stream_input_vector2d_data(FILE *f, Vector2D *v)
{
    assert(f != NULL);

    char *init_line = NULL;
    size_t len = 0;

    getline(&init_line, &len, f);

    assert(!strcmp(init_line, "VECTOR2D\n"));

    fscanf(f, "%f %f\n", &v->_x, &v->_y);

    free(init_line);
}

void stream_input_triangle2d_data(FILE *f, Triangle2D *t)
{
    assert(f != NULL);

    char *init_line = NULL;
    size_t len = 0;

    getline(&init_line, &len, f);

    assert(!strcmp(init_line, "TRIANGLE2D\n"));

    fscanf(f, "%hi\n", &t->_type);

    for(int i=0; i<3; i++)
    {
        stream_input_point2d_data(f, &t->_list[i]);
    }

    free(init_line);
}

void stream_input_circle2d_data(FILE *f, Circle2D *c)
{
    assert(f != NULL);

    char *init_line = NULL;
    size_t len = 0;

    getline(&init_line, &len, f);

    assert(!strcmp(init_line, "CIRCLE2D\n"));

    fscanf(f, "%f\n", &c->radius);

    stream_input_point2d_data(f, &c->center);

    free(init_line);
}

void console_input_point2d_data(Point2D *p)
{
    fscanf(stdin, "%hi %f %f\n",
           &p->_type, &p->_x, &p->_y);
}

void console_input_line2d_data(Line2D *l)
{
    for(int i=0; i<2; i++)
    {
        console_input_point2d_data(&l->_list[i]);
    }
}

void console_input_segment2d_data(Segment2D *s)
{
    for(int i=0; i<2; i++)
    {
        console_input_point2d_data(&s->_list[i]);
    }
}

void console_input_vector2d_data(Vector2D *v)
{
    fscanf(stdin, "%f %f\n",
            &v->_x, &v->_y);
}

void console_input_triangle2d_data(Triangle2D *t)
{
    Point2D array[3];
    for(int i=0; i<3; i++)
    {
        console_input_point2d_data(&array[i]);
    }
    *t = triangle2D_from_points(array[0], array[1], array[2]);
}

void console_input_circle2d_data(Circle2D *c)
{
    fscanf(stdin, "%f\n", &c->radius);

    console_input_point2d_data(&c->center);
}

void console_output_type(Triangle2D t)
{
    printf("%s triangle\n",
              (t._type == _RIGHT_TRIANGLE) ?
    "Right" : (t._type == _ACUTE_TRIANGLE) ?
    "Acute" : "Obtuse");
}
