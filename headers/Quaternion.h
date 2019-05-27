//
// Created by Mariia on 30.04.2019.
//

#ifndef QUATERNION_PANKOVA_QUATERNION_H
#define QUATERNION_PANKOVA_QUATERNION_H

#include "../headers/common.h"

typedef struct quaternion{
    DType a; //Real coefficient
    DType i; //Coefficient near i
    DType j; //Coefficient near j
    DType k; //Coefficient near k
} Quaternion;

Quaternion* make_Quaternion(DType a, DType i, DType j, DType k); //Returns a pointer to Quaternion3D with given coordinates.

Quaternion *addQuaternion(Quaternion* this, Quaternion* other); //Returns sum of two Quaternions.

Quaternion *subQuaternion(Quaternion* this, Quaternion* other); //Returns subtraction result of two Quaternions.

Quaternion *mulQuaternion(Quaternion* this, Quaternion* other); //Returns multiplication result of two Quaternions.

Quaternion *divQuaternion(Quaternion* this, Quaternion* other); //Returns division result of two Quaternions.

DType get_norm_Quaternion(Quaternion *this); //Return norm of quaternion.

Quaternion *invert_Quaternion(Quaternion *this); //Returns pointer to Quaternion raised to a power of -1.

Quaternion *get_normed_Quaternion(Quaternion *this); //Returns pointer to normed Quaternion.

#endif //QUATERNION_PANKOVA_QUATERNION_H
