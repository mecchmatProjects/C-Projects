#include "point3d.h"
#include <cmath>

static const double EPS = 1e-6;

Point3D Point3D::to_spherical() const {
    double r = sqrt(x*x + y*y + z*z);
    double phi = atan(y/x);
    double theta = acos(z/r);
    return {r, phi, theta};
}

Point3D Point3D::from_spherical() const {
    double r = this->x;
    double phi = this->y;
    double theta = this->z;
    double x = r*sin(theta)*cos(phi);
    double y = r*sin(theta)*sin(phi);
    double z = r*cos(theta);
    return {x, y, z};
}

Point3D Point3D::from_cylinder() const {
    double rho = this->x;
    double phi = this->y;
    double x = rho*cos(phi);
    double y = rho*sin(phi);
    return {x, y, z};
}

Point3D Point3D::to_cylinder() const {
    double rho = sqrt(x*x + y*y);
    double phi = 0;
    if (x >= 0) phi = asin(y/rho);
    if (x < 0) phi = -asin(y/rho) + M_PI;
    return {rho, phi, z};
}

Point3D Point3D::operator+(Point3D p) const {
    return {x + p.x, y + p.y, z + p.z};
}

Point3D Point3D::operator*(double a) const {
    return {a*x, a*y, a*z};
}

Point3D Point3D::turn3D(Quaternion q) const {
    Quaternion v = {0, x, y, z};
    Quaternion q_inv = Quaternion(1)/q;
    Quaternion r = q*v*q_inv;
    return {r.x, r.y, r.z};
}

Point3D Point3D::turn3D(Angle3D a, Point3D p) const {
    Point3D result = (*this) + p*(-1);
    auto [ax, ay, az] = a;
    Quaternion qx = {cos(ax/2), sin(ax/2), 0, 0};
    Quaternion qy = {cos(ay/2), 0, sin(ay/2), 0};
    Quaternion qz = {cos(az/2), 0, 0, sin(az/2)};
    result = result.turn3D(qx).turn3D(qy).turn3D(qz);
    return result + p;
}

Point3D Point3D::project(Point3D normal) const {
    auto [a, b, c] = normal;
    double norm2 = (a*a + b*b + c*c);
    double x0 = -(b*(a*y - b*x) + c*(a*z - c*x))/norm2;
    double y0 = (a*a*y - a*b*x - b*c*z + c*c*y)/norm2;
    double z0 = (a*a*z - a*c*x + b*b*z - b*c*y)/norm2;
    return {x0, y0, z0};
}

bool Point3D::operator==(Point3D p) const {
    return fabs(x - p.x) < EPS && 
           fabs(y - p.y) < EPS && 
           fabs(z - p.z) < EPS;
}

ostream& operator<<(ostream& os, Point3D p) {
    return os << "x=" << p.x << " y=" << p.y << " z=" << p.z;
}

istream& operator>>(istream& is, Point3D& p) {
    return is >> p.x >> p.y >> p.z;
}
