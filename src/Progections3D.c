//
// Created by Mariia on 15.05.2019.
//

#include "../headers/Progections3D.h"

Point3D *project_Point(Point3D *thisPoint, Edge3D *norm){
    /** Returns pointer to projection of given point onto plane.
     *
     * Plane is represented with normal vector "norm" and it's point A is laying onto plane.
     *
     */
    Quaternion* normVector = get_normed_Quaternion(get_Unit_Quaternion(norm));
    DType normScalar = get_norm_Quaternion(normVector);
    DType d = -(normVector->i*norm->point_A->x+normVector->j*norm->point_A->y+normVector->k*norm->point_A->z);
    DType t0 = (normVector->i*thisPoint->x+normVector->j*thisPoint->y+normVector->k*thisPoint->z+d)/normScalar;

    return make_Point(thisPoint->x - normVector->i * t0,
                      thisPoint->y - normVector->j * t0,
                      thisPoint->z - normVector->k * t0,
                      CARTESIAN);
}

Edge3D *project_Edge(Edge3D *thisEdge, Edge3D *norm) {
    /** Returns pointer to projection of given edge onto plane.
     *
     * Plane representation is the same as in "projectPoint".
     *
     */
    return make_Edge(project_Point(thisEdge->point_A, norm), project_Point(thisEdge->point_B, norm));
}

Figure3D *project_Figure(Figure3D *thisFigure, Edge3D *norm) {
    /** Returns pointer to projection of given figure onto plane.
     *
     * Plane representation is the same as in "projectPoint".
     *
     */
    Point3DArray *newPointArray = make_PointArray(thisFigure->points->size);
    Edge3DArray *newEdgeArray = make_EdgeArray(thisFigure->edges->size);
    for (int i=0; i<thisFigure->points->size; i++){
        newPointArray->data[i] = project_Point(thisFigure->points->data[i], norm);
    }
    for (int i=0; i<thisFigure->edges->size; i++){
        newEdgeArray->data[i] = project_Edge(thisFigure->edges->data[i], norm);
    }
    return make_Figure(newEdgeArray, newPointArray);
}
