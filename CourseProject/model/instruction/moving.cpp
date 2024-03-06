#include "model/instruction/moving.h"

//Смещение относительно положения камеры
SpaceCoords find_move(const camera_struct& camera, const moving& params)
{
    const SpaceCoords &n1 = camera.n1, &n2 = camera.n2;
    SpaceCoords coords;
    coords.x = n1.x * params.dx + n2.x * params.dy;
    coords.y = n1.y * params.dx + n2.y * params.dy;
    coords.z = n1.z * params.dx + n2.z * params.dy;
    return coords;
}

void move_atoms(AtomArr &arr, const SpaceCoords& move)
{
    for (int i = 0; i < arr.amount; i++)
        move_point(arr.data[i].center, move);
}

void move_connections(ConnectionArr& arr, const SpaceCoords& move)
{
    matrix4x4 matrix = move_matrix(move);
    for (int i = 1; i < arr.size; i++)
    {
        Connection &cur = arr.data[i];
        for (int j = 0; j < cur.amount; j++)
        {
            cur.bottom[j] = mult_vector(cur.bottom[j], matrix);
            cur.top[j] = mult_vector(cur.top[j], matrix);
        }
    }
}
