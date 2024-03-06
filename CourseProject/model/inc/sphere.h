#ifndef SPHERE_H
#define SPHERE_H

#include "Core/spaceCoords.h"
#include "model/inc/status.h"

typedef struct
{
    int rows;
    int cols;
    int faces;
    SpaceCoords **body;
    SpaceCoords top;
    SpaceCoords bottom;
    SpaceCoords **normals;
} sphere_struct;

sphere_struct create_sphere(status &result, int faces_amount);
void free_sphere(sphere_struct& sphere);
sphere_struct init_sphere();

#endif // SPHERE_H
