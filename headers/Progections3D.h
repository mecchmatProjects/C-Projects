//
// Created by Andrew Korzhuk on 15.05.2019.
//

#ifndef QUATERNION_KORZHUK_PROGECTIONS3D_H
#define QUATERNION_KORZHUK_PROGECTIONS3D_H

#include "../headers/common.h"
#include "../headers/Edge3D.h"
#include "../headers/Figure3D.h"
#include "../headers/Point3D.h"

Point3D *projectPoint(Point3D *thisPoint, Edge3D* norm);/*<Returns pointer to projection of given point onto plane.>*/

Edge3D *projectEdge(Edge3D *thisEdge, Edge3D* norm);/*<Returns pointer to projection of given edge onto plane.>*/

Figure3D *projectFigure(Figure3D *thisFigure, Edge3D* norm);
/*<Returns pointer to projection of given figure onto plane.>*/


#endif //QUATERNION_KORZHUK_PROGECTIONS3D_H
