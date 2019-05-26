//
// Created by Andrew Korzhuk on 29.04.2019.
//

#include "../headers/Angle3D.h"

Angle3D *makeAngle3D(DType value, AngleType type) {
    /** Returns a pointer to Angle3D with given values.
     *
     * Preferably use this function instead of malloc or calloc, in order to get get right initialization of fields.
     */
    Angle3D* newAngle = malloc(sizeof(Angle3D));
    newAngle->type = type;
    if (type==RADIAN) {
        newAngle->value = fmod(value, 2*M_PI);
    } else if (type==DEGREE) {
        newAngle->value = fmod(value,360);
    }
    return newAngle;
}

void changeAngle3DType(Angle3D *this, AngleType newType) {
    /** Convert type of this angle to another.
     *
     * Available types are:
     * 1) RADIAN
     * 2) DEGREE
     *
     */
    if (newType==RADIAN && this->type==DEGREE){
        this->value = this->value/180*M_PI;
        this->type = newType;

    } else if (newType==DEGREE && this->type==RADIAN) {
        this->value = this->value*180/M_PI;
        this->type = newType;
    }
}

void rotatePoint(Point3D *point, Angle3D *angle, Edge3D *axle) {
    /** Rotate given point around given axle by given angle.
     *
     * Rotation is made by Quaternions.
     *
     */
    Angle3D thisAngle = *angle;
    if (angle->type!=RADIAN){
        changeAngle3DType(&thisAngle, RADIAN);
    }

    Point3D thisPoint = *point;
    if (point->coordSys!=CARTESIAN){
        changeSys(&thisPoint, CARTESIAN);
    }

    Edge3D thisAxle = *axle;
    if (axle->coordSys!=CARTESIAN){
        changeEdgeSys(&thisAxle, CARTESIAN);
    }

    Quaternion* u = getNormedQuaternion(getUnitQuaternion(&thisAxle));
    Quaternion* v = makeQuaternion(0, thisPoint.x, thisPoint.y, thisPoint.z);
    DType angleMultiplier = sin(thisAngle.value/2);
    Quaternion* q = makeQuaternion(cos(thisAngle.value/2),
            u->i*angleMultiplier, u->j*angleMultiplier, u->k*angleMultiplier);
    Quaternion* rez = mulQuaternion(mulQuaternion(q,v),invQuaternion(q));

    Point3D* newPoint = makePoint(rez->i, rez->j, rez->k, CARTESIAN);
    changeSys(newPoint, point->coordSys);
    *point = *newPoint;

    free(u);
    free(v);
    free(q);
    free(rez);
}

void rotateEdge(Edge3D *edge, Angle3D *angle, Edge3D *axle) {
    /** Rotate Edge around given axle by given angle.
     *
     * Rotation is made by rotating each point in Edge.
     *
     */
    rotatePoint(edge->pointA,angle,axle);
    rotatePoint(edge->pointB,angle,axle);
}

IType rotateFigure(Figure3D *figure, Angle3D *angle, Edge3D *axle) {
    /** Rotate Figure around given axle by given angle.
     *
     * Rotation is made by rotating each point and edge in Figure.
     *
     */

    for (int i=0; i<figure->points->size; i++){
        rotatePoint(figure->points->data[i], angle, axle);
    }

    for (int i=0; i<figure->edges->size; i++){
        rotateEdge(figure->edges->data[i], angle, axle);
    }


    return 0;
}

