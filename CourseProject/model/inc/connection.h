#ifndef CONNECTION_H
#define CONNECTION_H

#include "Core/spaceCoords.h"
#include "model/inc/status.h"
#include "model/inc/atom.h"
#include "model/inc/sphere.h"

typedef struct
{
    int amount;
    SpaceCoords *bottom;
    SpaceCoords *top;
} Connection;

struct ConnectionArr
{
    int size;
    Connection *data;
};

ConnectionArr init_ConnectionArr();
ConnectionArr create_ConnectionArr(status& result, int size);
void free_ConnectionArr(ConnectionArr& arr);

Connection init_connection();
Connection create_Connection(status& result, int faces, float rad, const SpaceCoords& start, const SpaceCoords& end);
void free_Connection(Connection& connect);

status initialize_connections(int **connect, int size, ConnectionArr& connections, AtomArr &atoms, int faces);
void cut_connections(ConnectionArr& arr, const AtomArr& atoms);

#endif // CONNECTION_H
