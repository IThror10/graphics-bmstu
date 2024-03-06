#ifndef MOVING_H
#define MOVING_H

#include "Core/spaceCoords.h"
#include "model/inc/camera.h"
#include "model/inc/atom.h"
#include "model/inc/connection.h"

struct moving
{
    float dx;
    float dy;
};

SpaceCoords find_move(const camera_struct& camera, const moving& params);
void move_atoms(AtomArr &arr, const SpaceCoords& move);
void move_connections(ConnectionArr& arr, const SpaceCoords& move);
#endif // MOVING_H
