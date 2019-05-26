//
// Created by Andrew Korzhuk on 13.05.2019.
//

#include "../headers/Edge3D.h"

Edge3D *makeEdge(Point3D *pointA, Point3D *pointB) {
    /** Return pointer to new Edge3D with given points as begin and end of an edge.
     *
     * Preferably use this function instead of malloc or calloc, in order to get get right initialization of fields.
     *
     */
    Edge3D* newEdge = malloc(sizeof(Edge3D));
    changeSys(pointB, pointA->coordSys);
    newEdge->pointA = pointA;
    newEdge->pointB = pointB;
    newEdge->coordSys = pointA->coordSys;
    return newEdge;
}

void changeEdgeSys(Edge3D *thisEdge, CoordSystem newSys) {
    /** Change coordinate system of thisEdge.
     *
     * Available coordinate systems are:
     *  1) CARTESIAN
     *  2) CYLINDRICAL
     *  3) SPHERICAL
     * Coordinate system of used points also changed.
     */
    changeSys(thisEdge->pointA, newSys);
    changeSys(thisEdge->pointB, newSys);
}

Quaternion *getUnitQuaternion(Edge3D *thisEdge) {
    /** Returns Unit Quaternion generated from vector of thisEdge.
     *
     * Unit Quaternion of vector(a, b, c) is Quaternion(0, a, b, c).
     *
     */
    Quaternion* newQuaternion = malloc(sizeof(Quaternion));
    newQuaternion->a = 0;
    newQuaternion->i = thisEdge->pointB->x-thisEdge->pointA->x;
    newQuaternion->j = thisEdge->pointB->y-thisEdge->pointA->y;
    newQuaternion->k = thisEdge->pointB->z-thisEdge->pointA->z;
    return newQuaternion;
}

ChType *reprEdge3D(Edge3D *thisEdge) {
    /** Return char* representation of thisEdge.
     *
     * Use printf("%s",reprEdge(someEdge)) to print representation.
     * Example for Edge(P1,P2) where P1=(a1, b1, c1) and P2=(a2, b2, c2) in Cartesian coordinate system.
     * >>Edge 3D:{
     * >>A= Point3D Cartesian, x=a1, y=b1, z=c1
     * >>B= Point3D Cartesian, x=a2, y=b2, z=c2
     * >>}
     *
     */
    ChType *repr = malloc(sizeof(ChType)*250);
    sprintf(repr, "Edge 3D:{\n A= %s\n B= %s\n}",reprPoint(thisEdge->pointA),reprPoint(thisEdge->pointB));
    return repr;
}

void freeEdge(Edge3D* thisEdge) {
    /** Free allocated memory for pointA and pointB and memory for thisEdge.
     *
     */
    free(thisEdge->pointA);
    free(thisEdge->pointB);
    free(thisEdge);
}

