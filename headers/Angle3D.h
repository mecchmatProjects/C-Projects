//
// Created by Andrew Korzhuk on 29.04.2019.
//

#ifndef QUATERNION_KORZHUK_ANGLE3D_H
#define QUATERNION_KORZHUK_ANGLE3D_H

#include "../headers/common.h"
#include "../headers/Point3D.h"
#include "../headers/Edge3D.h"
#include "../headers/Figure3D.h"
#include "../headers/Quaternion.h"

typedef enum angleType{RADIAN, DEGREE} AngleType; /*<Enum of implemented degrees size.>*/

typedef struct angle3D {
    DType value; /*<Angle value in certain type>*/
    AngleType type;
} Angle3D;

Angle3D* makeAngle3D(DType value, AngleType type); /*<Returns a pointer to Angle3D with given values.>*/

void changeAngle3DType(Angle3D* this, AngleType newType); /*<Convert type of this angle to another.>*/

void rotatePoint(Point3D* point, Angle3D* angle, Edge3D* axle);
/*<Rotate given point around given axle by given angle.>*/

void rotateEdge(Edge3D *edge, Angle3D *angle, Edge3D *axle); /*<Rotate Edge around given axle by given angle.>*/

IType rotateFigure(Figure3D *figure, Angle3D *angle, Edge3D *axle); /*<Rotate Figure around given axle by given angle.>*/

#endif //QUATERNION_KORZHUK_ANGLE3D_H
