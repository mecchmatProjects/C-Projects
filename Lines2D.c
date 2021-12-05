/* File  Lines2D_test.c
Realization of  Lines2D structure functions
Done by Platonov Denis and Oleksenko Vladisval  (group Statistic)
Email: ... & vlad.oleksenko99@gmail.com
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "common.h"
#include "Lines2d.h"

struct Vector2D To_Vector(struct Point2D pt1, struct Point2D pt2)
{
    struct Vector2D v;
    v.a=pt2.x-pt1.x;
    v.b=pt2.y-pt1.y;
    return v;
}

struct Vector2D  add(struct Vector2D v1, struct Vector2D v2)
{
    struct Vector2D result;
    result.a=v1.a+v2.a;
    result.b=v1.b+v2.b;
    return result;
}

struct Vector2D mult(struct Vector2D v1, struct Vector2D v2)
{
    struct Vector2D result;
    result.a = v1.a*v2.b;
    result.b = v1.b*v2.a;
    return result;
}

double multS(struct Vector2D v1, struct Vector2D v2)
{
    double result;
    result = v1.a*v2.a+v1.b*v2.b;
    return result;
}

struct Point2D check_lines_pt(struct Line2D line_1, struct Line2D line_2)
{
    struct Point2D result;
    result.x=(line_1.c*line_2.b-line_2.c*line_1.b)/(line_2.a*line_1.b-line_1.a*line_2.b);
    result.y=(-line_1.c-line_1.a*result.x)/line_1.b;
    return result;
}

struct Point2D check_line_seg_pt(struct Line2D line_1, struct Segment2D s2)
{
    struct Point2D result;
    struct Line2D line_s2;
    line_s2.a=s2.pt2.y-s2.pt1.y;
    line_s2.b=s2.pt1.x-s2.pt2.x;
    line_s2.c=s2.pt2.x*s2.pt1.y-s2.pt1.x*s2.pt2.y;
    result=check_lines_pt(line_1, line_s2);
    if (s2.pt1.x<=s2.pt2.x)
    {
        if (s2.pt1.x<=result.x<=s2.pt2.x)
        {
            return result;
        }
    }
    if (s2.pt2.x<=s2.pt1.x)
    {
        if (s2.pt2.x<=result.x<=s2.pt1.x)
        {
            return result;
        }
    }
}

struct Point2D check_segments_pt(struct Segment2D s1, struct Segment2D s2)
{
    struct Point2D result;
    struct Line2D line_s1;
    struct Line2D line_s2;
    line_s1.a=s1.pt2.y-s1.pt1.y;
    line_s1.b=s1.pt1.x-s1.pt2.x;
    line_s1.c=s1.pt2.x*s1.pt1.y-s1.pt1.x*s1.pt2.y;
    line_s2.a=s2.pt2.y-s2.pt1.y;
    line_s2.b=s2.pt1.x-s2.pt2.x;
    line_s2.c=s2.pt2.x*s2.pt1.y-s2.pt1.x*s2.pt2.y;
    result=check_lines_pt(line_s1, line_s2);
    if (s1.pt1.x<=s1.pt2.x)
    {
        if (s1.pt1.x<=result.x<=s1.pt2.x)
        {
            return result;
        }
    }
    if (s1.pt2.x<=s1.pt1.x)
    {
        if (s1.pt2.x<=result.x<=s1.pt1.x)
        {
            return result;
        }
    }
}

double polygon_square(struct Polygone2D p)
{
    double sum=0, x2, y2;
    struct Point2D *list = p.Points;
    double x1 = list[0].x;
    double y1 = list[0].y;
    x2=0;
    y2=0;
    for (int i=1; i<p.N; i++)
    {
        x2 = list[i].x;
        y2 = list[i].y;
        sum=sum+(x1+x2)*(y2-y1);
        x1=x2;
        y1=y2;
    }
    sum=sum+(list[0].x+x2)*(list[0].y-y2);
    return ( fabs(sum) / 2);
}

double distance(struct Point2D point1, struct Point2D point2)
{
    return (sqrt((point2.x-point1.x)*(point2.x-point1.x)+(point2.y-point1.y)*(point2.y-point1.y)));
}

int check_convex(struct Polygone2D p)
{
    struct Point2D *list = p.Points;
    int f=1;
    for (int i=-2; i<p.N-1; i++)
    {
        double a=distance(list[i], list[i+1]);
        double b=distance(list[i+1], list[i+2]);
        double c=distance(list[i], list[i+2]);
        if (a*a+b*b>c*c)
            f=0;
    }
    return f;
}

struct Point2D check_polyline_self(struct Polyline2D lam)
{
    int f=1;
    struct Point2D *list = lam.Points;
    for (int i=0; i<lam.N;i++)
    {
        for (int j=0; j<lam.N;j++)
        {
            struct Point2D res;
            struct Segment2D s_1;
            s_1.pt1=list[i];
            s_1.pt2=list[i+1];
            if ((i!=j) && ((i+1)!=j) && (i!=(j+1)))
            {
                struct Segment2D s_2;
                s_2.pt1=list[j];
                s_2.pt2=list[j+1];
                res = check_segments_pt(s_1,s_2);
                return res;
            }

        }
    }
}

