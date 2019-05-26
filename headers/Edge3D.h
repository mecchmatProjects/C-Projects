//
// Created by Andrew Korzhuk on 13.05.2019.
//

#ifndef QUATERNION_KORZHUK_EDGE3D_H
#define QUATERNION_KORZHUK_EDGE3D_H


#include "../headers/Point3D.h"
#include "../headers/Quaternion.h"

typedef struct edge3D{
    Point3D* pointA; /*<Represent begin in case of using this structure as vector>*/
    Point3D* pointB; /*<Represent end in case of using this structure as vector>*/
    CoordSystem coordSys;
} Edge3D;

Edge3D* makeEdge(Point3D* pointA, Point3D* pointB);
/*<Return pointer to new Edge3D with given points as begin and end of an edge.>*/

void changeEdgeSys(Edge3D* thisEdge, CoordSystem newSys); /*<Change coordinate system of thisEdge.>*/

Quaternion* getUnitQuaternion(Edge3D* thisEdge); /*<Returns Unit Quaternion generated from vector of thisEdge.>*/

ChType *reprEdge3D(Edge3D* thisEdge); /*<Return char* representation of thisEdge.>*/

void freeEdge(Edge3D* thisEdge); /*<Free allocated memory in edge>*/

#endif //QUATERNION_KORZHUK_EDGE3D_H
