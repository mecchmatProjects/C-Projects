//
// Created by Andrew Korzhuk on 29.04.2019.
//

#include "../headers/Point3D.h"

IType toSpherical(Point3D* thisPoint){
    /** Change Point3D coord system to Spherical.
     *
     * If coord system is not defined returns SIGILL.
     * Returns zero in other case.
     */
    Point3D* newPoint = malloc(sizeof(Point3D));
    if (thisPoint->coordSys == SPHERICAL){ //from spherical to spherical

        *newPoint = *thisPoint;

    } else if (thisPoint->coordSys == CARTESIAN){ //from Cartesian to spherical

        newPoint->x = sqrt(pow(thisPoint->x,2)+

                pow(thisPoint->y,2)+pow(thisPoint->z,2));

        if (newPoint->x == 0){ //if point is in Cartesian origin

            newPoint->y = 0;
            newPoint->z = 0;

        } else if (thisPoint->x == 0){ //zero division

            newPoint->y = acos(thisPoint->z/newPoint->x);
            newPoint->z = 0;

        } else { // normal clause

            newPoint->y = acos(thisPoint->z/newPoint->x);
            newPoint->z = atan(thisPoint->y/thisPoint->x);
        }
    } else if (thisPoint->coordSys == CYLINDRICAL) {// from cylindrical to spherical

        newPoint->x = sqrt(pow(thisPoint->x,2)+pow(thisPoint->z,2));
        newPoint->z = thisPoint->y;

        if (thisPoint->z == 0){ // zero division clause
            newPoint->y = M_PI/2;
        } else {
            newPoint->y = atan(thisPoint->x/thisPoint->z);
        }
    } else {
        // thisPoint coordinate system is not defined
        return SIGILL;
    }
    newPoint->coordSys = SPHERICAL;
    *thisPoint = *newPoint;
    return 0;
};

IType toCartesian(Point3D* thisPoint){
    /** Change Point3D coord system to Cartesian.
     *
     * If coord system is not defined returns SIGILL.
     * Returns zero in other case.
     */
    Point3D* newPoint = malloc(sizeof(Point3D));
    if (thisPoint->coordSys == CARTESIAN){
        *newPoint = *thisPoint;

    } else if (thisPoint->coordSys == SPHERICAL) {
        newPoint->x = thisPoint->x*sin(thisPoint->y)*cos(thisPoint->z);
        newPoint->y = thisPoint->x*sin(thisPoint->y)*sin(thisPoint->z);
        newPoint->z = thisPoint->x*cos(thisPoint->y);

    } else if (thisPoint->coordSys == CYLINDRICAL) {
        newPoint->x = thisPoint->x*cos(thisPoint->y);
        newPoint->y = thisPoint->x*sin(thisPoint->y);
        newPoint->z = thisPoint->z;

    } else {
        return SIGILL;
    }
    newPoint->coordSys = CARTESIAN;
    *thisPoint = *newPoint;
    return 0;
};

IType toCylindrical(Point3D* thisPoint){
    /** Change Point3D coord system to Cylindrical.
     *
     * If coord system is not defined returns SIGILL.
     * Returns zero in other case.
     */
    Point3D* newPoint = malloc(sizeof(Point3D));
    if (thisPoint->coordSys == CARTESIAN){
        newPoint->x = sqrt(pow(thisPoint->x, 2)+pow(thisPoint->y, 2));
        newPoint->z = thisPoint->z;

        if (thisPoint->x == 0 ){
            newPoint->y = 0;

        } else {
            newPoint->y = atan(thisPoint->y/thisPoint->x);

        }
    } else if (thisPoint->coordSys == CYLINDRICAL) {
        *newPoint = *thisPoint;

    } else if (thisPoint->coordSys == SPHERICAL) {
        newPoint->x = thisPoint->x*sin(thisPoint->y);
        newPoint->y = thisPoint->z;
        newPoint->z = thisPoint->x*cos(thisPoint->y);

    } else {
        return SIGILL;
    }
    newPoint->coordSys = CYLINDRICAL;
    *thisPoint = *newPoint;
    return 0;
}

ChType* reprPoint(Point3D *thisPoint) {
    /** Return char* representation of thisPoint.
     *
     * Use printf("%s",reprPoint(somePoint)) to print representation
     * Example for point P1(a, b, c) in Cartesian coordinate system.
     * >> Point3D Cartesian, x=a, y=b, z=c
     */
    ChType *repr = malloc(sizeof(ChType)*59);
    if (thisPoint->coordSys == CARTESIAN){
        sprintf(repr, "Point3D Cartesian, x=%f, y=%f, z=%f", thisPoint->x, thisPoint->y, thisPoint->z);
    } else if (thisPoint->coordSys == CYLINDRICAL) {
        sprintf(repr, "Point3D Cylindrical, rho=%f, phi=%f, z=%f", thisPoint->x, thisPoint->y, thisPoint->z);
    } else if (thisPoint->coordSys == SPHERICAL) {
        sprintf(repr, "Point3D Spherical, r=%f, theta=%f, phi=%f", thisPoint->x, thisPoint->y, thisPoint->z);
    } else{
        sprintf(repr, "Undefined Point3D");
    }
    return repr;
}

IType pointMul(Point3D * thisPoint, int multiplier) {
    /** Multiplies all coordinates in Cartesian coordinate system by multiplier.
     *
     * thisPoint gets new coordinate values and save coordinate system.
     *
     */
    CoordSystem tmpCoordSys = thisPoint->coordSys;

    int errorCode = toCartesian(thisPoint);
    if (errorCode != 0){
        return errorCode;
    }
    thisPoint->x *= multiplier;
    thisPoint->y *= multiplier;
    thisPoint->z *= multiplier;

    if (tmpCoordSys == CARTESIAN){

        toCartesian(thisPoint);

    } else if (tmpCoordSys == CYLINDRICAL){

        toCylindrical(thisPoint);

    } else if (tmpCoordSys == SPHERICAL){

        toSpherical(thisPoint);

    } else {
        return SIGILL;
    }

    return 0;
}

Point3D *pointAdd(Point3D *thisPoint, Point3D *otherPoint) {
    /** Return sum of two points.
     *
     * Sum by coordinates.
     * Point "otherPoint" from different coordinate systems would be changed to coordinate system of "thisPoint".
     *
     */
    changeSys(otherPoint, thisPoint->coordSys);
    Point3D* newPoint = malloc(sizeof(Point3D));
    newPoint->x = thisPoint->x + otherPoint->x;
    newPoint->y = thisPoint->y + otherPoint->y;
    newPoint->z = thisPoint->z + otherPoint->z;
    newPoint->coordSys = thisPoint->coordSys;
    return newPoint;
}

IType changeSys(Point3D *thisPoint, CoordSystem castTo) {
    /** Change coordinate system of thisPoint to value of castTo.
     *
     * Available coordinate systems are:
     *  1) CARTESIAN
     *  2) CYLINDRICAL
     *  3) SPHERICAL
     *
     */
    if (castTo == CARTESIAN) {
        toCartesian(thisPoint);
    } else if (castTo == CYLINDRICAL) {
        toCylindrical(thisPoint);
    } else if (castTo == SPHERICAL){
        toSpherical(thisPoint);
    } else{
        return SIGILL;
    }
    return 0;
}

Point3D *makePoint(DType x, DType y, DType z, CoordSystem coordSys) {
    /** Returns a pointer to point3D with given coordinates.
     *
     * Preferably use this function instead of malloc or calloc, in order to get get right initialization of fields.
     */
    Point3D* newPoint = malloc(sizeof(Point3D));
    newPoint->x = x;
    newPoint->y = y;
    newPoint->z = z;
    newPoint->coordSys = coordSys;
    return newPoint;
};


