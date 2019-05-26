//
// Created by Andrew Korzhuk on 15.05.2019.
//

#include "../headers/Progections3D.h"
#include "../headers/Point3D.h"
#include "../headers/Quaternion.h"


Point3D *projectPoint(Point3D *thisPoint, Edge3D* norm){
    /** Returns pointer to projection of given point onto plane.
     *
     * Plane is represented with normal vector "norm" and it's point A which is laying onto plane.
     *
     */
    Quaternion* normVector = getNormedQuaternion(getUnitQuaternion(norm));
    DType normScalar = normQuaternion(normVector);
    DType d = -(normVector->i*norm->pointA->x+normVector->j*norm->pointA->y+normVector->k*norm->pointA->z);
    DType t0 = (normVector->i*thisPoint->x+normVector->j*thisPoint->y+normVector->k*thisPoint->z+d)/normScalar;
    free(normVector);
    return makePoint(thisPoint->x-normVector->i*t0, thisPoint->y-normVector->j*t0, thisPoint->z-normVector->k*t0,
            CARTESIAN);
}

Edge3D *projectEdge(Edge3D *thisEdge, Edge3D *norm) {
    /** Returns pointer to projection of given edge onto plane.
     *
     * Plane representation is the same as in "projectPoint".
     *
     */
    return makeEdge(projectPoint(thisEdge->pointA, norm),projectPoint(thisEdge->pointB, norm));
}

Figure3D *projectFigure(Figure3D *thisFigure, Edge3D *norm) {
    /** Returns pointer to projection of given figure onto plane.
     *
     * Plane representation is the same as in "projectPoint".
     *
     */
    Point3DArray *newPointArray = initPointArray(thisFigure->points->size);
    Edge3DArray *newEdgeArray = initEdgeArray(thisFigure->edges->size);
    for (int i=0; i<thisFigure->points->size; i++){
        newPointArray->data[i] = projectPoint(thisFigure->points->data[i], norm);
    }
    for (int i=0; i<thisFigure->edges->size; i++){
        newEdgeArray->data[i] = projectEdge(thisFigure->edges->data[i], norm);
    }
    return makeFigure(newEdgeArray, newPointArray);
}
