#ifndef SCALING_H
#define SCALING_H

#include "Core/flatCoords.h"
#include "model/inc/matrix4x4.h"
#include "model/inc/atom.h"
#include "model/inc/connection.h"

typedef struct
{
    float x;
    float y;
    float coeff;
} scaling;

matrix4x4 scale_matrix(float coeff);
void scale_connection(ConnectionArr& arr, matrix4x4& matrix);
void scale_atoms(AtomArr& arr, matrix4x4& matrix, float coeff);
#endif // SCALING_H
