//
// Created by Mariia on 30.04.2019.
//

#ifndef QUATERNION_PANKOVA_EDGE3D_H
#define QUATERNION_PANKOVA_EDGE3D_H

#include "common.h"
#include "Point3D.h"
#include "Quaternion.h"

typedef struct edge3D{
    Point3D* point_A; //Begin of a vector
    Point3D* point_B; //End of a vector
    CoordSystem coord_system;
} Edge3D; //edges are implemented as vectors

Edge3D* make_Edge(Point3D *pointA, Point3D *pointB); //Return pointer to new Edge3D with given points as begin and end of an edge.

void change_sys_Edge(Edge3D *thisEdge, CoordSystem newSys); //Change coordinate system of thisEdge.

Quaternion* get_Unit_Quaternion(Edge3D *thisEdge); //Returns Unit Quaternion generated from vector of thisEdge.

ChType *_repr_Edge3D(Edge3D *thisEdge); //Return char* representation of thisEdge.

void free_Edge(Edge3D *thisEdge); //Free allocated memory for pointA and pointB and memory for thisEdge.

#endif //QUATERNION_PANKOVA_EDGE3D_H
