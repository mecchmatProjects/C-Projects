#ifndef _FIGURE3D_H_
#define _FIGURE3D_H_


#include "point3d.h"
#include <utility>
#include <vector>

using std::vector;
using std::pair;
typedef pair<int, int> pii;

struct Figure3D {
    int num_points, num_edges;
    vector<Point3D> points;
    vector<pii> edges;
    Figure3D(): num_points(0), num_edges(0) {}
    Figure3D(vector<Point3D> points, vector<pii> edges):
        num_points(points.size()), num_edges(edges.size()),
        points(points), edges(edges) {}
    void turn3D(Angle3D a, Point3D p);
    void project(Point3D p);
    friend ostream& operator<<(ostream& os, const Figure3D& f);
    friend istream& operator>>(istream& is, Figure3D& f);
};

#endif
