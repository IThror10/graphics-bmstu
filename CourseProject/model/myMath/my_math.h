#ifndef MY_MATH_H
#define MY_MATH_H

#include "model/inc/matrix4x4.h"

void ASMmtrxMult(int N, SpaceCoords *dest, SpaceCoords *src, const matrix4x4 *matrix);

#endif // MY_MATH_H
