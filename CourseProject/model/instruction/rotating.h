#ifndef ROTATING_H
#define ROTATING_H

#include "model/inc/matrix4x4.h"
#include "model/inc/camera.h"
#include "model/inc/atom.h"
#include "model/inc/sphere.h"
#include "model/inc/connection.h"

struct rotating
{
    float x;
    float y;

    float ox_rotate;
    float oy_rotate;
    float oz_rotate;
};

void rotate_atoms(AtomArr& atoms, const matrix4x4& rotate);
void rotate_sphere(sphere_struct& sphere, const matrix4x4& rotate);
void rotate_connections(ConnectionArr& arr, const matrix4x4& rotate);
void rotate_camera_struct(camera_struct& camera, const matrix4x4& rotate);

matrix4x4 create_rotate_matrix(const SpaceCoords& vector, float angle);
matrix4x4 create_rotate_matrix(const camera_struct& camera, const rotating& params, const SpaceCoords& center);
#endif // ROTATING_H
