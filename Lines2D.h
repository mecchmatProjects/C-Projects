#ifndef LINES2D_H_INCLUDED
#define LINES2D_H_INCLUDED
/* Base structure of point */

typedef struct Point2D {
    double x;
    double y
};
/* Structure of segment */
typedef struct Segment2D{
    struct Point2D pt1, pt2;
};

/* Structure of line */
typedef struct Line2D{
    double a;
    double b;
    double c;
};
/* Structure of Polyline */
typedef struct Polyline2D{
    int N;
    struct Point2D *Points;
};
/* Structure of Vector */
typedef struct Vector2D{
    double a;
    double b;
};
/* Structure of Polygone */
typedef struct Polygone2D{
    int N;
    struct Point2D *Points;
};

/* functions  */
struct Vector2D To_Vector(struct Point2D pt1, struct Point2D pt2);
struct Vector2D  add(struct Vector2D v1, struct Vector2D v2);
struct Vector2D mult(struct Vector2D v1, struct Vector2D v2);
double multS(struct Vector2D v1, struct Vector2D v2);
struct Point2D check_lines_pt(struct Line2D line_1, struct Line2D line_2);
struct Point2D check_line_seg_pt(struct Line2D line_1, struct Segment2D s2);
struct Point2D check_segments_pt(struct Segment2D s1, struct Segment2D s2);
double polygon_square(struct Polygone2D p);
double distance(struct Point2D point1, struct Point2D point2);
int check_convex(struct Polygone2D p);
struct Point2D check_polyline_self(struct Polyline2D lam);
#endif // LINES2D_H_INCLUDED
