#include "model/inc/atom.h"
#include <malloc.h>

AtomArr init_AtomArr()
{
    AtomArr arr;
    arr.data = nullptr;
    arr.amount = 0;
    return arr;
}

AtomArr create_AtomArr(status& result, int size)
{
    AtomArr arr;
    arr.data = (Atom*) malloc(sizeof(Atom) * size);
    if (arr.data == nullptr)
        result = memory_error;
    else
    {
        for (int i = 0; i < size; i++)
            arr.data[i].list = list_init();
        arr.amount = size;
        result = ok;
    }
    return arr;
}

AtomArr create_AtomArr(status& result, int size, const Atom *other)
{
    AtomArr arr;
    arr.data = (Atom*) malloc(sizeof(Atom) * size);
    if (arr.data == nullptr)
        result = memory_error;
    else
    {
        result = ok;
        arr.amount = size;
        if (other) for (int i = 0; i < size; i++)
        {
            arr.data[i] = other[i];
            arr.data[i].list = list_init();
        }
    }
    return arr;
}

void free_AtomArr(AtomArr& arr)
{
    if (arr.data)
    {
        for (int i = 0; i < arr.amount; i++)
            free_list(arr.data[i].list);
    }

    free(arr.data);
    arr.data = nullptr;
}

//Координаты центра модели
SpaceCoords find_center(AtomArr &arr)
{
    SpaceCoords coords(0, 0, 0);
    if (arr.data)
    {
        Atom &start = arr.data[0];
        float x_min = start.center.x, x_max = x_min;
        float y_min = start.center.y, y_max = y_min;
        float z_min = start.center.z, z_max = z_min;

        for (int i = 0; i < arr.amount; i++)
        {
            SpaceCoords &cur = arr.data[i].center;
            if (cur.x < x_min)
                x_min = cur.x;
            else if (cur.x > x_max)
                x_max = cur.x;

            if (cur.y < y_min)
                y_min = cur.y;
            else if (cur.y > y_max)
                y_max = cur.y;

            if (cur.z < z_min)
                z_min = cur.z;
            else if (cur.z > z_max)
                z_max = cur.z;
        }

        coords.x = (x_max + x_min) / 2;
        coords.y = (y_max + y_min) / 2;
        coords.z = (z_max + z_min) / 2;
    }
    return coords;
}
