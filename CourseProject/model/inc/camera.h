#ifndef CAMERA_H
#define CAMERA_H

#include "Core/spaceCoords.h"
#include "model/inc/matrix4x4.h"

typedef struct
{
    SpaceCoords eye_pos;
    SpaceCoords look_pos;
    SpaceCoords n1;
    SpaceCoords n2;
} camera_struct;

camera_struct init_camera();
matrix4x4 translate_matrix(const camera_struct& camera);
#endif // CAMERA_H
