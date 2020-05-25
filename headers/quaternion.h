#ifndef _QUATERNION_H_
#define _QUATERNION_H_

#include <iostream>

using std::ostream;
using std::istream;

struct Quaternion {
    double s, x, y, z;
    Quaternion(): s(0), x(0), y(0), z(0) {}
    Quaternion(double s): s(s), x(0), y(0), z(0) {}
    Quaternion(double s, double x, double y, double z):
        s(s), x(x), y(y), z(z) {}
    Quaternion operator+(Quaternion q2) const;
    Quaternion operator-(Quaternion q2) const;
    Quaternion operator*(Quaternion q2) const;
    Quaternion operator/(Quaternion q2) const;
    bool operator==(Quaternion q2) const;
    friend ostream& operator<<(ostream& os, Quaternion q);
    friend istream& operator>>(istream& is, Quaternion& q);
};

#endif
