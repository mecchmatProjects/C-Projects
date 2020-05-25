#ifndef _POINT3D_H_
#define _POINT3D_H_

#include "quaternion.h"
#include <tuple>

typedef std::tuple<double, double, double> Angle3D;

struct Point3D {
    double x, y, z;
    Point3D from_spherical() const;
    Point3D from_cylinder() const;
    Point3D to_spherical() const;
    Point3D to_cylinder() const;
    Point3D operator+(Point3D p2) const;
    Point3D operator*(double a) const;
    bool operator==(Point3D p2) const;
    Point3D turn3D(Quaternion q) const;
    Point3D turn3D(Angle3D a, Point3D p) const;
    Point3D project(Point3D normal) const;
    friend ostream& operator<<(ostream& os, Point3D p);
    friend istream& operator>>(istream& is, Point3D& p);
};


#endif
