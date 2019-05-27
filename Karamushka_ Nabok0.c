#include "types.h"
#include <math.h>

double length(Point2D P1, Point2D P2)
{
	Point2D P;
	P.x = P2.x - P1.x;
	P.y = P2.y - P1.y;
	return sqrt(pow(P.x, 2.0) + pow(P.y, 2.0));
}

Point2D add(Point2D P1,Point2D P2)
{
	 Point2D res;
	res.x = P1.x + P2.x;
	res.y = P1.y + P2.y;
	return res;
}

float mult(Point2D P1, Point2D P2)
{
	return P1.x * P2.x + P1.y * P2.y;
}

float multS(Point2D P1, Point2D P2)
{
	return P1.x * P2.y - P1.y * P2.x;
}

Point2D intersect(Segment2D S1, Segment2D S2)
{
	Point2D P = { 0, 0 };
	return P;
}

//Point2D intersect(Line2D L1, Segment2D S2)
//{
//
//
//}
//Point2D intersect(Line2D L1, Line2D L2)
//{
//
//}

double triangle_area(Point2D a, Point2D b, Point2D c)
{
	//length
	double lA, lB, lC;
	lA = length(a, b);
	lB = length(b, c);
	lC = length(c, a);

	double p = (lA + lB + lC) / 2;

	return sqrt(p * (p - lA) * (p - lB) * (p - lC));
}

double triangle_perimeter(Point2D a, Point2D b, Point2D c)
{
	//length
	double lA, lB, lC;
	lA = length(a, b);
	lB = length(b, c);
	lC = length(c, a);

	return lA + lB + lC;
}

double inscribed_circle_triangle_radius(Point2D a, Point2D b, Point2D c)
{
	//length
	double lA, lB, lC;
	lA = length(a, b);
	lB = length(b, c);
	lC = length(c, a);

	double p = triangle_perimeter(a, b, c) / 2;
	double area = triangle_area(a, b, c);

	return area / p;
}

double circumscribed_circle_triangle_radius(Point2D a, Point2D b, Point2D c)
{
	//length
	double lA, lB, lC;
	lA = length(a, b);
	lB = length(b, c);
	lC = length(c, a);

	if (triangle_validation(lA, lB, lC))
	{
		double p = (lA + lB + lC) / 2;
		double area = triangle_area(a, b, c);

		return (lA * lB * lC) / (4 * area);
	}
	else
	{
		printf("Wrong triangle");
	}
	return -1;
}

int triangle_validation(double a, double b, double c)
{
	if (a + b >= c && b + c >= a && a + c >= b)
		return 1;
	else
		return 0;
}

double angleA(double a, double b, double c) //opposite a
{
	return acos((pow(b, 2.0) + pow(c, 2.0) - pow(a, 2.0)) / (2.0 * b *c));
}

double angleB(double a, double b, double c) //opposite b
{
	return acos((pow(a, 2.0) + pow(c, 2.0) - pow(b, 2.0)) / (2.0 * a *c));
}

double angleC(double a, double b, double c) //opposite c
{
	return acos((pow(a, 2.0) + pow(b, 2.0) - pow(c, 2.0)) / (2.0 * a *b));
}

Line2D medianA(Triangle2D t)
{
	Line2D median;
	Point2D P1, P2;
	P1.x = (t.c.x + t.b.x) / 2;
	P1.y = (t.c.y + t.b.y) / 2;
	P2.x = t.a.x;
	P2.y = t.a.y;
	median.a = P1.y - P2.y;
	median.b = P2.x - P1.x;
	median.c = P1.x * P2.y - P2.x * P1.y;
	return median;
}

Line2D medianB(Triangle2D t)
{
	Line2D median;
	Point2D P1, P2;
	P1.x = (t.c.x + t.a.x) / 2;
	P1.y = (t.c.y + t.a.y) / 2;
	P2.x = t.b.x;
	P2.y = t.b.y;
	median.a = P1.y - P2.y;
	median.b = P2.x - P1.x;
	median.c = P1.x * P2.y - P2.x * P1.y;
	return median;
}

Line2D medianC(Triangle2D t)
{
	Line2D median;
	Point2D P1, P2;
	P1.x = (t.a.x + t.b.x) / 2;
	P1.y = (t.a.y + t.b.y) / 2;
	P2.x = t.c.x;
	P2.y = t.c.y;
	median.a = P1.y - P2.y;
	median.b = P2.x - P1.x;
	median.c = P1.x * P2.y - P2.x * P1.y;
	return median;
}

Line2D bisectorA(Triangle2D* t)
{
	Line2D bisector;
	Point2D P1, P2;
	float AB = length(t->a, t->b);
	float AC = length(t->a, t->c);
	P1.x = (AC * t->b.x + AB * t->c.x) / (AB + AC);
	P1.y = (AC * t->b.y + AB * t->c.y) / (AB + AC);
	P2.x = t->a.x;
	P2.y = t->a.y;
	bisector.a = P1.y - P2.y;
	bisector.b = P2.x - P1.x;
	bisector.c = P1.x * P2.y - P2.x * P1.y;
	return bisector;
}

Line2D bisectorB(Triangle2D* t)
{
	Line2D bisector;
	Point2D P1, P2;
	float BA = length(t->b, t->a);
	float BC = length(t->b, t->c);
	float ratio = BA / BC; // = AD / CD
	P1.x = (BC * t->a.x + BA * t->c.x) / (BA + BC);
	P1.y = (BC * t->a.y + BA * t->c.y) / (BA + BC);
	P2.x = t->b.x;
	P2.y = t->b.y;
	bisector.a = P1.y - P2.y;
	bisector.b = P2.x - P1.x;
	bisector.c = P1.x * P2.y - P2.x * P1.y;
	return bisector;
}

Line2D bisectorC(Triangle2D* t)
{
	Line2D bisector;
	Point2D P1, P2;
	float CA = length(t->c, t->a);
	float CB = length(t->c, t->b);
	float ratio = CA / CB; // = AD / BD
	P1.x = (CB * t->a.x + CA * t->b.x) / (CA + CB);
	P1.y = (CB * t->a.y + CA * t->b.y) / (CA + CB);
	P2.x = t->c.x;
	P2.y = t->c.y;
	bisector.a = P1.y - P2.y;
	bisector.b = P2.x - P1.x;
	bisector.c = P1.x * P2.y - P2.x * P1.y;
	return bisector;
}

Point2D center(Triangle2D* t)
{
	Point2D P;
	P.x = (t->a.x + t->b.x + t->c.x) / 3;
	P.y = (t->a.y + t->b.y + t->c.y) / 3;
	return P;
}