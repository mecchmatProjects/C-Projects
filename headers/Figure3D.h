//
// Created by Mariia on 30.04.2019.
//

#ifndef QUATERNION_PANKOVA_FIGURE3D_H
#define QUATERNION_PANKOVA_FIGURE3D_H

#include "common.h"
#include "Point3D.h"
#include "Edge3D.h"

typedef struct edge3DArray{
    /** Structure which is used to organize edge array.
     *
     * "data" is array of Edge3D* of size "size".
     *
     */
    Edge3D** data;
    IType size;
} Edge3DArray;

typedef struct point3DArray{
    /** Structure which is used to organize point array.
    *
    * "data" is array of Point3D* of size "size".
    *
    */
    Point3D** data;
    IType size;
} Point3DArray;

typedef struct figure3D{
    Edge3DArray* edges; //Array of used edges
    Point3DArray* points; //Array of used points
} Figure3D;

Figure3D* make_Figure(Edge3DArray *edges, Point3DArray *points); //Returns a pointer to Figure3D with given arrays of edges and points.

Edge3DArray* make_EdgeArray(IType size); //Returns a pointer to empty Edge3DArray with certain size.

Point3DArray* make_PointArray(IType size); //Returns a pointer to empty Point3DArray with certain size.

ChType *_repr_Figure(Figure3D *thisFigure); //Return char* representation of thisFigure.

void free_Figure(Figure3D *thisFigure); //Free allocated memory for Figure3D.

void free_Edge3DArray(Edge3DArray *thisArray); //Free allocated memory for Edge3DArray.

void free_Point3DArray(Point3DArray *thisArray); //Free allocated memory for Point3DArray.

#endif //QUATERNION_PANKOVA_FIGURE3D_H
