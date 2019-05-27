//
// Created by Mariia on 30.04.2019.
//

#ifndef QUATERNION_PANKOVA_PROGECTIONS3D_H
#define QUATERNION_PANKOVA_PROGECTIONS3D_H

#include "../headers/common.h"
#include "../headers/Edge3D.h"
#include "../headers/Figure3D.h"
#include "../headers/Point3D.h"

Point3D *project_Point(Point3D *thisPoint, Edge3D *norm);//Returns pointer to projection of given point onto plane.

Edge3D *project_Edge(Edge3D *thisEdge, Edge3D *norm);//Returns pointer to projection of given edge onto plane.

Figure3D *project_Figure(Figure3D *thisFigure, Edge3D *norm);//Returns pointer to projection of given figure onto plane.

#endif //QUATERNION_PANKOVA_PROGECTIONS3D_H
