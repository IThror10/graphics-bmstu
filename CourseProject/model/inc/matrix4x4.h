#ifndef MATRIX4X4_H
#define MATRIX4X4_H

#include "Core/spaceCoords.h"

typedef struct
{
    float data[4][4];
} matrix4x4;

matrix4x4 zero_matrix_init();
matrix4x4 unity_matrix_init();
matrix4x4 back_move_matrix(const SpaceCoords& coords);
matrix4x4 move_matrix(const SpaceCoords& coords);

SpaceCoords mult_vector(const SpaceCoords& coords, const matrix4x4& rotate);
matrix4x4 mult_matrix(const matrix4x4& left, const matrix4x4& right);
#endif // MATRIX4X4_H
