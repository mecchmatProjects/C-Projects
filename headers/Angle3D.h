//
// Created by Mariia on 30.04.2019.
//

#ifndef QUATERNION_PANKOVA_ANGLE3D_H
#define QUATERNION_PANKOVA_ANGLE3D_H

#include "../headers/common.h"
#include "../headers/Point3D.h"
#include "../headers/Edge3D.h"
#include "../headers/Figure3D.h"
#include "../headers/Quaternion.h"

typedef enum{
    RADIAN,
    DEGREE
} AngleType; //Enum of implemented angles size

typedef struct angle3D{
    DType value; //Angle size in certain type
    AngleType type;
} Angle3D;

Angle3D* make_Angle3D(DType value, AngleType type); //Returns a pointer to Angle3D with given values.

void change_type_Angle3D(Angle3D *this, AngleType newType); //Convert type of this angle to another.

void rotate_Point(Point3D *point, Angle3D *angle, Edge3D *axle); //Rotate given point around given axle by given angle.

void rotate_Edge(Edge3D *edge, Angle3D *angle, Edge3D *axle); //Rotate Edge around given axle by given angle.

void rotate_Figure(Figure3D *figure, Angle3D *angle, Edge3D *axle); //Rotate Figure around given axle by given angle.

#endif //QUATERNION_PANKOVA_ANGLE3D_H
