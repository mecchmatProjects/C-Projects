//
// Created by Mariia on 30.04.2019.
//

#include "../headers/Edge3D.h"

Edge3D *make_Edge(Point3D *pointA, Point3D *pointB) {
    /** Return pointer to new Edge3D with given points as begin and end of an edge.
     *
     * Preferably use this function instead of malloc or calloc, in order to get get right initialization of fields.
     *
     */
    Edge3D* newEdge = malloc(sizeof(Edge3D));
    change_system(pointB, pointA->coord_system);
    newEdge->point_A = pointA;
    newEdge->point_B = pointB;
    newEdge->coord_system = pointA->coord_system;
    return newEdge;
}

void change_sys_Edge(Edge3D *thisEdge, CoordSystem newSys) {
    /** Change coordinate system of thisEdge.
     *
     * Available coordinate systems are:
     *  1) CARTESIAN
     *  2) CYLINDRICAL
     *  3) SPHERICAL
     * Coordinate system of used points also changed.
     */
    change_system(thisEdge->point_A, newSys);
    change_system(thisEdge->point_B, newSys);
}

Quaternion *get_Unit_Quaternion(Edge3D *thisEdge) {
    /** Returns Unit Quaternion generated from vector of thisEdge.
     *
     * Unit Quaternion of vector(a, b, c) is Quaternion(0, a, b, c).
     *
     */
    Quaternion* newQuaternion = malloc(sizeof(Quaternion));
    newQuaternion->a = 0;
    newQuaternion->i = thisEdge->point_B->x-thisEdge->point_A->x;
    newQuaternion->j = thisEdge->point_B->y-thisEdge->point_A->y;
    newQuaternion->k = thisEdge->point_B->z-thisEdge->point_A->z;
    return newQuaternion;
}

ChType *_repr_Edge3D(Edge3D *thisEdge) {
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
    sprintf(repr, "Edge 3D:{\n A= %s\n B= %s\n}", _repr_Point(thisEdge->point_A), _repr_Point(thisEdge->point_B));
    return repr;
}

void free_Edge(Edge3D *thisEdge) {
    /** Free allocated memory for pointA and pointB and memory for thisEdge.
     *
     */
    free(thisEdge->point_A);
    free(thisEdge->point_B);
    free(thisEdge);
}

