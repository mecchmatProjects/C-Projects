#include "quaternion.h"
#include <cmath>

static const double EPS = 1e-6;

Quaternion Quaternion::operator+(Quaternion q2) const {
    return {s + q2.s, x + q2.x, y + q2.y, z + q2.z};
}

Quaternion Quaternion::operator-(Quaternion q2) const {
    return {s - q2.s, x - q2.x, y - q2.y, z - q2.z};
}

Quaternion Quaternion::operator*(Quaternion q2) const {
    return {s * q2.s - x * q2.x - y * q2.y - z * q2.z,
            s * q2.x + q2.s * x + y * q2.z - q2.y * z,
            s * q2.y + q2.s * y + q2.x * z - x * q2.z,
            s * q2.z + q2.s * z + x * q2.y - q2.x * y};
}

Quaternion Quaternion::operator/(Quaternion q2) const {
    Quaternion invQ2;
    double norm2 = q2.s * q2.s + q2.x * q2.x + q2.y * q2.y + q2.z * q2.z;
    double invNorm2 = 1.0 / norm2;
    invQ2.s = q2.s * invNorm2;
    invQ2.x = -q2.x * invNorm2;
    invQ2.y = -q2.y * invNorm2;
    invQ2.z = -q2.z * invNorm2;
    return (*this * invQ2);
}

bool Quaternion::operator==(Quaternion q2) const {
    return fabs(x - q2.x) < EPS && 
           fabs(y - q2.y) < EPS && 
           fabs(z - q2.z) < EPS &&
           fabs(s - q2.s) < EPS;
}

ostream& operator<<(ostream& os, Quaternion q) {
    return os << q.s << " + " << q.x << "i + " 
              << q.y << "j + " << q.z << "k";
}

istream& operator>>(istream& is, Quaternion& q) {
    return is >> q.s >> q.x >> q.y >> q.z;
}
