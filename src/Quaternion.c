//
// Created by Andrew Korzhuk on 29.04.2019.
//

#include "../headers/Quaternion.h"

Quaternion* makeQuaternion(DType a, DType i, DType j, DType k) {
    /** Returns a pointer to Quaternion3D with given coordinates.
     *
     * Preferably use this function instead of malloc or calloc, in order to get get right initialization of fields.
     */
    Quaternion* newQuaternion = malloc(sizeof(Quaternion));
    newQuaternion->a = a;
    newQuaternion->i = i;
    newQuaternion->j = j;
    newQuaternion->k = k;
    return newQuaternion;
}

Quaternion *addQuaternion(Quaternion *this, Quaternion *other) {
    /** Returns sum of two Quaternions.
     *
     * Sum is by coordinates.
     *
     */
    Quaternion* newQuaternion = malloc(sizeof(Quaternion));
    newQuaternion->a = this->a+other->a;
    newQuaternion->i = this->i+other->i;
    newQuaternion->j = this->j+other->j;
    newQuaternion->k = this->k+other->k;
    return newQuaternion;
}

Quaternion *subQuaternion(Quaternion *this, Quaternion *other) {
    /** Returns subtraction result of two Quaternions.
     *
     * Subtraction is by coordinates.
     *
     */
    Quaternion* newQuaternion = malloc(sizeof(Quaternion));
    newQuaternion->a = this->a-other->a;
    newQuaternion->i = this->i-other->i;
    newQuaternion->j = this->j-other->j;
    newQuaternion->k = this->k-other->k;
    return newQuaternion;
}

Quaternion *mulQuaternion(Quaternion *this, Quaternion *other) {
    /** Returns multiplication result of two Quaternions.
     *
     * Used multiplication rules for Quaternions.
     *
     */
    Quaternion* newQuaternion = malloc(sizeof(Quaternion));
    newQuaternion->a = this->a*other->a-this->i*other->i-this->j*other->j-this->k*other->k;
    newQuaternion->i = this->a*other->i+this->i*other->a+this->j*other->k-this->k*other->j;
    newQuaternion->j = this->a*other->j+this->j*other->a+this->k*other->i-this->i*other->k;
    newQuaternion->k = this->a*other->k+this->k*other->a+this->i*other->j-this->j*other->i;
    return newQuaternion;
}

DType normQuaternion(Quaternion *this) {
    /** Return norm of quaternion.
     *
     */
    return sqrt(pow(this->a,2)+pow(this->i,2)+pow(this->j,2)+pow(this->k,2));
}

Quaternion *invQuaternion(Quaternion *this) {
    /** Returns pointer to inverted Quaternion.
     *
     */
    Quaternion* newQuaternion =conjQuaternion(this);
    DType sqNorm  = pow(normQuaternion(this),2);
    newQuaternion->a = this->a/sqNorm;
    newQuaternion->i = -this->i/sqNorm;
    newQuaternion->j = -this->j/sqNorm;
    newQuaternion->k = -this->k/sqNorm;
    return newQuaternion;
}

Quaternion *conjQuaternion(Quaternion *this) {
    /** Returns pointer to conjugate quaternion.
     *
     * All values except real, returned with opposite sign.
     *
     */
    Quaternion* newQuaternion = malloc(sizeof(Quaternion));
    newQuaternion->a = this->a;
    newQuaternion->i = -this->i;
    newQuaternion->j = -this->j;
    newQuaternion->k = -this->k;
    return newQuaternion;
}

Quaternion *divQuaternion(Quaternion *this, Quaternion *other) {
    /** Returns division result of two Quaternions.
     *
     * Division is implemented as multiplication by inverted.
     *
     */
    Quaternion* newQuaternion = invQuaternion(other);
    return mulQuaternion(this, newQuaternion);
}

Quaternion *getNormedQuaternion(Quaternion *this) {
    /** Returns pointer to normed Quaternion.
     *
     * NormedQuaternion = thisQuaternion./norm.
     *
     */
    Quaternion* newQuaternion = malloc(sizeof(Quaternion));
    DType norm = normQuaternion(this);
    newQuaternion->a = this->a/norm;
    newQuaternion->i = this->i/norm;
    newQuaternion->j = this->j/norm;
    newQuaternion->k = this->k/norm;
    return newQuaternion;

}
