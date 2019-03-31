/***
The MIT License (MIT)
Copyright (c) 2014 Viktor Borodin (borodin@mail.univ.kiev.ua)
21.06.2014

 * Realization of basic geometric primitives  
 * sets of points, lines, segnents

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
***/
#ifndef __BASEGEOM__
#define __BASEGEOM__

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define N 100 /* number of points */
#define DIM 2 /* number of dimensions */

typedef ptype double /* but int possible!!!!!! */;

typedef ntype unsigned int;

/* FIXME: later double type macroses */

#define EQ_EPS 0.000001;

//#define  PD_EQL(a,b)          fabs(a-b) < _eps_dbl_err ;

/* Basic types definitions */

typedef struct DPoint_
{
	union  //classical and vector represent
	{
		struct
		{
			ptype x;
			ptype y;
		};
		ptype ptr[2];
	};
} DPoint;


typedef struct DLine_
{
	ptype a;
	ptype b;
	ptype c;
} DLine;


typedef union mat2_
{
	struct 
	{
		ptype a;
		ptype b;
		ptype c;
		ptype d;
	};
	ptype arr[4];
} mat2;



typedef struct DTriangle_
{
	DPoint a;
	DPoint b;
	DPoint c;
} DTriangle;

/* !!!!!!!! Please make ARect to the DRect form !!!!! */
typedef struct DRect_  // by 2 points(downleft and right top)
{
	DPoint DownLef;
	DPoint UpRight;
} DRect;

typedef struct ARect_ //? by position of the center and sizes 
{
	DPoint pos;
	DPoint size;
} ARect;


typedef struct DCircle_
{
	DPoint pos;
	ptype r;
} DCircle;



typedef struct DSegm_
{
	DPoint a;
	DPoint b;
} DSegm;


/* ?????Maybe dont need this form here?????? */
typedef struct DMyLine_
{
	ptype k;
	ptype r;
} DMyLine;

typedef struct DRay_
{
	ptype a;
	ptype b;
	DPoint centr;
} DRay;


/* Constructors  */
/* !!!!!! Correct it in the way of Nikolai !!!!!!!!!!!*/
DPoint setPoint (const ptype x,const ptype y)
{
	DPoint pnt;
	pnt.x =x;
	pnt.y=y;
	return pnt;
}

DSegm setSegm (const ptype x, const ptype y,const ptype x1, const ptype y1)
{
	DPoint pnt;
	DSegm c;
	pnt.x =x;
	pnt.y=y;
	c.a=pnt;
	pnt.x =x1;
	pnt.y=y1;
	c.b=pnt;
	return c;
}

DSegm setSegmPnts (const DPoint x,const DPoint x1)
{
	
	DSegm c;
	c.a=x;
	c.b=x1;
	return c;
}

/* !!!!!! Do not do it in the way of Nikolai - correct his code !!!!!!!!!!!*/
DRect setRect (const ptype x, const ptype y,const ptype x1, const ptype y1)
{
	DPoint pnt;
	DRect c;
	pnt.x =x;
	pnt.y=y;
	c.DownLeft=pnt;
	pnt.x =x1;
	pnt.y=y1;
	c.UpRight=pnt;
	return c;
}

DRect setRectPnts (const DPoint p,const DPoint p1)
{
	
	Drect c;
	c.DownLeft.x=(p.x>p1.x)?p1.x:p.x;
	c.UpRight.x=(p.x>p1.x)?p.x:p1.x;
	c.DownLeft.y=(p.y>p1.y)?p1.x:p.x;
	c.UpRight.y=(p.y>p1.y)?p.y:p1.y;
	return c;
}

DLine setLine(const ptype a, const ptype b, const ptype c)
{
	DLine l;
	l.a=a;
	l.b=b;
	l.c=c;
	return l;
}

ntype setMyLine(const ptype a, const ptype b, const ptype c, DMyLine *l)
{
	DMyLine l;
	double alpha;
	if(a||b) 
		{
			alpha= sqrt(a*a+b*b));
			l->r = c / alpha;
			l->k = sin(a/alpha);
			return 0;
		}
	return 1;
}

DRay setRay(const ptype a, const ptype b, const ptype c, const ptype d)
{
	DRay l;
	l.centr.x=a;
	l.centr=b;
	l.a=c;
	l.b=d;
	return l;
}

DRay setRayP(const DPoint p, const double c, const double d)
{
	DRay l;
	l.centr=p;
	l.a=c;
	l.b=d;
	return l;
}

/* Showing up */

void showPoint(const DPoint p)
{
	printf("P=(%e,%e)",p.x,p.y);
}

void showSegm(const DSegm p)
{
	printf("V=");
	showPoint(p.a);
	printf("-");
	showPoint(p.b);
}

void showRect(const DRect p)
{
	printf("R=");
	showPoint(p.DownLeft);
	printf("-");
	showPoint(p.UpRight);
}

/* Functions for segment -   */
/*!!!!! - merge it with Nikolai code  - You can do it your way instead of My or Nikolai */
DPoint pntAdd(DPoint p1, DPoint p2)
{ 
	DPoint z;
	z.x = p1.x+p2.x; 
	z.y = p1.y+p2.y;
	return z;
}
/*!!!!! - merge it with Nikolai code  - You can do it your way instead of My or Nikolai */
DPoint pntSub(DPoint p1, DPoint p2)
{ 
	DPoint z;
	z.x = p1.x-p2.x; 
	z.y = p1.y-p2.y;
	return z;
}
/*!!!!! - merge it with Nikolai code  - You can do it your way instead of My or Nikolai */
double pntMult(DPoint p1, DPoint p2)
{
	return (p1.x-p2.x)*(p1.y-p2.y); 
}


/*!!!!! - merge it with Nikolai code  - You can do it your way instead of My or Nikolai */
double segmLength(const DSegm p)
{
	return (p.a.x-p.b.x)*(p.a.x - p.b.x) + (p.a.y - p.b.y)*(p.a.y - p.b.y);
}

double segmMult(const DSegm x, const DSegm b);

DSegm segmAdd(const DSegm s, const DPoint p);

DSegm segmMin(const DSegm s, const DPoint p);

int segmIntersect(const DSegm x, const DSegm y, DPoint* p);

/* ....*/


double angleLine(const DLine l);

double freeLine(const DLine l);

int linePoints(const DPoint p1, const DPoint p2, DLine* l);

DLine linePerpX(const DLine l, const double x);

DLine linePerpY(const DLine l, const double y);


DRay rayLineX(const DLine l, const double x);

DRay rayLineY(const DLine l, const double y);


/*!!!!! - merge it with Nikolai code  - You can do it your way instead of My or Nikolai */
int lineIntersect(const DLine l1, const DLine l2, DPoint* p);

double linePointdist(const DLine l, const DPoint p);

DLine lineAdd(const DLine l1, const DLine l2);

int lineSegmIntersect(const DLine l,const DSegm s, DPoint* p);

 


#endif /* __BASEGEOM__ end */
