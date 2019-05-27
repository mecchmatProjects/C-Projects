//
// Created by Mariia on 30.04.2019.
//

#include "../headers/Angle3D.h"

Angle3D* make_Angle3D(DType value, AngleType type){
    /**Returns a pointer to Angle3D with given values.
     *
     * Preferably use this function instead of malloc or calloc, in order to get get right initialization of fields.
     *
     */
    Angle3D* newAngle = malloc(sizeof(Angle3D));
    newAngle->type = type;
    if (type == DEGREE){
        newAngle->value = fmod(value, 360);
    }
    else if (type == RADIAN){
        newAngle->value = fmod(value, 2*M_PI);
    }
    return newAngle;
}

void change_type_Angle3D(Angle3D *this, AngleType newType) {
    /** Convert type of this angle to newType.
     *
     * Available types are:
     * 1) RADIAN
     * 2) DEGREE
     *
     */
    if (newType==RADIAN && this->type==DEGREE){
        this->value = this->value/180*M_PI;
        this->type = newType;
    }
    else if (newType==DEGREE && this->type==RADIAN) {
        this->value = this->value*180/M_PI;
        this->type = newType;
    }
}

void rotate_Point(Point3D *point, Angle3D *angle, Edge3D *axle) {
    /** Rotate given point around given axle by given angle.
     *
     * Rotation is made by Quaternions.
     *
     */
    Angle3D thisAngle = *angle;
    if (angle->type!=RADIAN){
        change_type_Angle3D(&thisAngle, RADIAN);
    }

    Point3D thisPoint = *point;
    if (point->coord_system!=CARTESIAN){
        change_system(&thisPoint, CARTESIAN);
    }

    Edge3D thisAxle = *axle;
    if (axle->coord_system!=CARTESIAN){
        change_sys_Edge(&thisAxle, CARTESIAN);
    }

    Quaternion* u = get_normed_Quaternion(get_Unit_Quaternion(&thisAxle));
    Quaternion* v = make_Quaternion(0, thisPoint.x, thisPoint.y, thisPoint.z);
    DType angleMultiplier = sin(thisAngle.value/2);
    Quaternion* q = make_Quaternion(cos(thisAngle.value / 2),
                                    u->i * angleMultiplier, u->j * angleMultiplier, u->k * angleMultiplier);
    Quaternion* rez = mulQuaternion(mulQuaternion(q,v), invert_Quaternion(q));

    Point3D* newPoint = make_Point(rez->i, rez->j, rez->k, CARTESIAN);
    change_system(newPoint, point->coord_system);
    *point = *newPoint;
}

void rotate_Edge(Edge3D *edge, Angle3D *angle, Edge3D *axle) {
    /** Rotate Edge around given axle by given angle.
     *
     * Rotation is made by rotating each point in Edge.
     *
     */
    rotate_Point(edge->point_A, angle, axle);
    rotate_Point(edge->point_B, angle, axle);
}

void rotate_Figure(Figure3D *figure, Angle3D *angle, Edge3D *axle) {
    /** Rotate Figure around given axle by given angle.
     *
     * Rotation is made by rotating each point and edge in Figure.
     *
     */
    for (int i=0; i<figure->points->size; i++){
        rotate_Point(figure->points->data[i], angle, axle);
    }
    for (int i=0; i<figure->edges->size; i++){
        rotate_Edge(figure->edges->data[i], angle, axle);
    }
}
