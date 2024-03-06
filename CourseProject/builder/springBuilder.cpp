#include "builder/springBuilder.h"
#include "model/instruction/scaling.h"
#include <malloc.h>
#include <cmath>

SpringBuilder::SpringBuilder()
{
    model.atoms = nullptr;
    model.connections = nullptr;
    model.amount = 0;
}

//Пружинный алгоритм расположения графа с пространстве
//
bool SpringBuilder::separateAlgorithm()
{
    return true;
}

//Начальное расположение модели с масштабированием и переносом
bool SpringBuilder::placeModel()
{
    float x_min = INFINITY, z_min = x_min;
    float x_max = -INFINITY, z_max = x_max;

    for (int i = 0; i < atoms.size(); i++)
    {
        float radius = atoms[i].radius;
        SpaceCoords &cur = atoms[i].center;

        if (cur.x - radius < x_min)
            x_min = cur.x - radius;
        if (cur.x + radius > x_max)
            x_max = cur.x + radius;
        if (cur.z - radius < z_min)
            z_min = cur.z - radius;
        if (cur.z + radius > z_max)
            z_max = cur.z + radius;
    }
    x_min -= 150;   x_max += 150;   z_min -= 150;   z_max += 150;

    float k1 = 750 / (x_max - x_min), k2 = 750 / (z_max - z_min);
    float coeff = k1 < k2 ? k1 : k2;
    matrix4x4 scale = scale_matrix(coeff);

    for (int i = 0; i < atoms.size(); i++)
    {
        atoms[i].center = mult_vector(atoms[i].center, scale);
        atoms[i].radius *= coeff;
    }

    x_min = INFINITY, z_min = x_min;
    for (int i = 0; i < atoms.size(); i++)
    {
        float radius = atoms[i].radius;
        SpaceCoords &cur = atoms[i].center;

        if (cur.x - radius < x_min)
            x_min = cur.x - radius;
        if (cur.z - radius < z_min)
            z_min = cur.z - radius;
    }

    SpaceCoords move(-x_min + 100, 0, -z_min + 100);
    for (int i = 0; i < atoms.size(); i++)
    {
        move_point(atoms[i].center, move);
    }

    for (int i = 0; i < parts.size(); i++)
    {
        for (int j = 0; j < parts[i].size(); j++)
            atoms[parts[i][j]].center.y = i * 200;
    }
    return true;
}

//Создание модели для сервера
model_data SpringBuilder::createModel()
{
    int size = atoms.size();
    model.amount = size;

    model.atoms = (Atom*) malloc(sizeof(Atom) * size);
    if (model.atoms) for (int i = 0; i < size; i++)
        model.atoms[i] = atoms[i];

    int **matrix = nullptr;
    if (size)
    {
        matrix = (int**) malloc(sizeof(int) * size * size + sizeof(int*) * size);
        matrix[0] = (int*)((char*)matrix + sizeof(int*) * size);
    }
    if (matrix) for (int i = 1; i < size; i++)
        matrix[i] = (int*)((char*)matrix[i - 1] + sizeof(int) * size);
    if (matrix) for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            matrix[i][j] = connections[i][j];
    model.connections = matrix;
    return model;
}

//Освобождение памяти из-под модели
void SpringBuilder::delete_model()
{
    if (model.atoms)
        free(model.atoms);
    model.atoms = nullptr;
    if (model.connections)
        free(model.connections);
    model.connections = nullptr;
    model.amount = 0;
}
