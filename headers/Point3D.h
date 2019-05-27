//
// Created by Mariia on 30.04.2019.
//

#ifndef QUATERNION_PANKOVA_POINT3D_H
#define QUATERNION_PANKOVA_POINT3D_H

#include "common.h"

typedef enum coordSystemTag{
    CARTESIAN,
    SPHERICAL,
    CYLINDRICAL,
} CoordSystem;

typedef struct point3DTag{
    DType x; //rho in cylindrical and r in spherical
    DType y; //theta in spherical and phi in cylindrical
    DType z; //phi in spherical
    CoordSystem coord_system;
} Point3D;

Point3D* make_Point(DType x, DType y, DType z, CoordSystem coordSys); //Returns a pointer to point3D with given coordinates.

IType to_spherical(Point3D *thisPoint); //Change Point3D coord system to Spherical.

IType to_cylindrical(Point3D *thisPoint); //Change Point3D coord system to Cylindrical.

IType to_cartesian(Point3D *thisPoint); //Change Point3D coord system to Cartesian.

IType change_system(Point3D *thisPoint, CoordSystem castTo); //Change coordinate system of thisPoint to value of castTo.

IType pointMul(Point3D* thisPoint, IType multiplier); //Multiplies all coordinates in Cartesian coordinate system by multiplier.

Point3D* pointAdd(Point3D* thisPoint, Point3D* otherPoint); //Return sum of two points.

ChType* _repr_Point(Point3D *thisPoint); //Return char* representation of thisPoint.

#endif //QUATERNION_PANKOVA_POINT3D_H
