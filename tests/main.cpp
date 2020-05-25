#include <bits/stdc++.h>
#include "quaternion.h"
#include "point3d.h"
#include "figure3d.h"

using namespace std;

void testQuaternion() {
    cerr << "QUATERNIONS:\n";
    Quaternion i = {0, 1, 0, 0};
    Quaternion j = {0, 0, 1, 0};
    Quaternion k = {0, 0, 0, 1};
    int passed = 0;
    int total_tests = 6;

    // test 1
    passed += (i*i == Quaternion(-1));
    // test 2
    passed += (i*j*k == Quaternion(-1));
    // test 3
    passed += (i+j-Quaternion(2)*k == Quaternion(0, 1, 1, -2));
    // test 4
    passed += (i*j == k);
    // test 5
    passed += (Quaternion(1)/i == Quaternion(-1)*i);
    // test 6
    passed += (Quaternion(24)/Quaternion(1, 2, 1, 0) == Quaternion(4, -8, -4, 0));

    cerr << "PASSED " << passed << " OUT OF " << total_tests << " TESTS\n";
}

void testPoint3D() {
    cerr << "POINT3D:\n";
    Point3D p1 = {1, 0, 0};
    Point3D p2 = {2, 2, 1};
    Point3D p3 = {3, 4, -5};
    int passed = 0;
    int total_tests = 6;

    // test 1
    passed += (p2.to_spherical() == Point3D{3, atan(1), acos(1.0/3)});
    // test 2
    passed += (p3.to_cylinder() == Point3D{5, asin(4.0/5), -5});
    // test 3
    passed += (p1 + p2 == Point3D{3, 2, 1});
    // test 4
    passed += (p2 * 2.0 == Point3D{4, 4, 2});
    // test 5
    passed += (Point3D{0, 0, 1} == p1.from_spherical());
    // test 6
    passed += (p3 == Point3D{5, asin(4.0/5), -5}.from_cylinder());

    cerr << "PASSED " << passed << " OUT OF " << total_tests << " TESTS\n";
}

void testFigure3D() {
    cerr << "FIGURE3D:\n";
    Point3D p1 = {0, 0, 0};
    Point3D p2 = {3, 4, 5};
    Point3D p3 = {1, 1, -1};
    int passed = 0;
    int total_tests = 6;
    Figure3D f1 = {
        {p1, p2, p3},
        {{0, 1}, {1, 2}, {0, 2}}
    };
    f1.project(Point3D{1, 1, 1});
    
    // test 1
    passed += (f1.points[0] == Point3D{0, 0, 0});
    // test 2
    passed += (f1.points[1] == Point3D{-1, 0, 1});
    // test 3
    passed += (f1.points[2] == Point3D{2.0/3, 2.0/3, -4.0/3});

    f1 = {
        {p1, p2, p3}, 
        {{0, 1}, {1, 2}, {0, 2}}
    };
    f1.turn3D({M_PI/2, -M_PI/2, M_PI}, {1, 2, 3});

    // test 4
    passed += (f1.points[0] == Point3D{-1, -1, 2});
    // test 5
    passed += (f1.points[1] == Point3D{3, 4, 5});
    // test 6
    passed += (f1.points[2] == Point3D{0, -2, 3});

    cerr << "PASSED " << passed << " OUT OF " << total_tests << " TESTS\n";
}

int main(int argc, char **argv) {
    testQuaternion();
    testPoint3D();
    testFigure3D();
    return 0;
}

