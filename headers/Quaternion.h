//
// Created by Andrew Korzhuk on 29.04.2019.
//

#ifndef QUATERNION_KORZHUK_QUATERNION_H
#define QUATERNION_KORZHUK_QUATERNION_H

#include "../headers/common.h"
typedef struct quaternion{
    DType a; /*<Real coefficient of Quaternion>*/
    DType i; /*<Coefficient near i>*/
    DType j; /*<Coefficient near j>*/
    DType k; /*<Coefficient near k>*/
} Quaternion;

Quaternion* makeQuaternion(DType a, DType i, DType j, DType k);
/*<Returns a pointer to Quaternion3D with given coordinates.>*/

Quaternion *addQuaternion(Quaternion* this, Quaternion* other); /*<Returns sum of two Quaternions.>*/

Quaternion *subQuaternion(Quaternion* this, Quaternion* other); /*<Returns subtraction result of two Quaternions.>*/

Quaternion *mulQuaternion(Quaternion* this, Quaternion* other); /*<Returns multiplication result of two Quaternions.>*/

Quaternion *divQuaternion(Quaternion* this, Quaternion* other); /*<Returns division result of two Quaternions.>*/

DType normQuaternion(Quaternion* this); /*<Return norm of quaternion.>*/

Quaternion *invQuaternion(Quaternion* this); /*<Returns pointer to inverted Quaternion.>*/

Quaternion *conjQuaternion(Quaternion* this); /*<Returns pointer to conjugate quaternion.>*/

Quaternion *getNormedQuaternion(Quaternion* this); /*<Returns pointer to normed Quaternion.>*/

#endif //QUATERNION_KORZHUK_QUATERNION_H
