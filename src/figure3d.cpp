#include "figure3d.h"
#include <cmath>

void Figure3D::turn3D(Angle3D a, Point3D p) {
    for (auto& v : points) {
        v = v.turn3D(a, p);
    }
}

void Figure3D::project(Point3D normal) {
    for (auto& v : points) {
        v = v.project(normal);
    }
}

ostream& operator<<(ostream& os, const Figure3D& f) {
    os << "Points:\n";
    for (int i = 0; i < (int)f.points.size(); i++) {
        os << i << ": " << f.points[i] << '\n';
    }
    os << "Edges:\n";
    for (auto& e: f.edges) {
        os << e.first << " <-> " << e.second << '\n';
    }
    return os;
}

istream& operator>>(istream& is, Figure3D& f) {
    is >> f.num_points >> f.num_edges;
    f.points.resize(f.num_points);
    f.edges.resize(f.num_edges);
    for (int i = 0; i < f.num_points; i++) {
        is >> f.points[i];
    }
    for (int i = 0; i < f.num_edges; i++) {
        is >> f.edges[i].first >> f.edges[i].second;
    }
    return is;
}
