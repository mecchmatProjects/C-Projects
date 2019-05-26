//
// Created by Andrew Korzhuk on 29.04.2019.
//

#ifndef QUATERNION_KORZHUK_POINT3D_H
#define QUATERNION_KORZHUK_POINT3D_H

#include "common.h"

typedef enum coordSystemTag {
    /** Enum of implemented coordinate systems.
     *
     */
    CARTESIAN,
    SPHERICAL,
    CYLINDRICAL,
} CoordSystem;

typedef struct point3DTag{
    DType x; /* <also represents rho in cylindrical and r in spherical> */
    DType y; /* <represents theta in spherical and phi in cylindrical> */
    DType z; /* <represent phi in spherical> */
    CoordSystem coordSys;
} Point3D;

IType toSpherical(Point3D* thisPoint); /*<Change Point3D coord system to Spherical.>*/

IType toCylindrical(Point3D* thisPoint); /*<Change Point3D coord system to Cylindrical.>*/

IType toCartesian(Point3D* thisPoint); /*<Change Point3D coord system to Cartesian.>*/

IType pointMul(Point3D* thisPoint, IType multiplier);
/*<Multiplies all coordinates in Cartesian coordinate system by multiplier.>*/

IType changeSys(Point3D* thisPoint, CoordSystem castTo);
/*<Change coordinate system of thisPoint to value of castTo.>*/

Point3D* pointAdd(Point3D* thisPoint, Point3D* otherPoint); /*<Return sum of two points.>*/

ChType* reprPoint(Point3D*); /*<Return char* representation of thisPoint.>*/

Point3D* makePoint(DType x, DType y, DType z, CoordSystem coordSys);
/*<Returns a pointer to point3D with given coordinates.>*/

#endif //QUATERNION_KORZHUK_POINT3D_H
