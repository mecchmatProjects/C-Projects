typedef struct
{
	double x;
	double y;
} Point2D;

typedef struct
{
	Point2D a;
	Point2D b;
} Segment2D;

typedef struct
{
	Point2D a;
	Point2D b;
	Point2D c;
} Triangle2D;

typedef struct
{
	double a;
	double b;
	double c;
} Line2D;

Line2D bisectorA(Triangle2D* t);
Line2D bisectorB(Triangle2D* t);
Line2D bisectorC(Triangle2D* t);
Point2D center(Triangle2D* t);
