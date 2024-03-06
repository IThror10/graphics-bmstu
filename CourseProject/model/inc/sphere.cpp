#include "model/inc/sphere.h"
#include <malloc.h>
#include <cmath>

static float rads(float angle)
{
    return (M_PI * angle) / 180;
}

sphere_struct init_sphere()
{
    sphere_struct sphere;
    sphere.rows = 0;
    sphere.cols = 0;
    sphere.faces = 0;
    sphere.normals = nullptr;
    sphere.body = nullptr;
    return sphere;
}

//Нормали поверхностей, аппроксимирующих сферу
static status create_normals(sphere_struct& sphere)
{
    status result = ok;

    int rows = sphere.faces, cols = sphere.cols;
    int size = rows * cols * sizeof(SpaceCoords) + rows * sizeof(SpaceCoords*);
    sphere.normals = (SpaceCoords**) malloc(size);

    if (sphere.normals == nullptr)
        result = memory_error;
    else
    {
        sphere.normals[0] = (SpaceCoords*)((char*)sphere.normals + sizeof(SpaceCoords*) * rows);
        for (int i = 1; i < rows; i++)
            sphere.normals[i] = (SpaceCoords*)((char*)sphere.normals[i - 1] + sizeof(SpaceCoords) * cols);

        SpaceCoords center(0, 0, 0);
        //Top && Bottom
        for (int i = 0; i < cols; i++)
        {
            sphere.normals[0][i] = find_normal(sphere.top, sphere.body[0][i], sphere.body[0][(i + 1) % cols], center);
            sphere.normals[rows - 1][i] = find_normal(sphere.bottom,\
                                sphere.body[sphere.rows - 1][i], sphere.body[sphere.rows - 1][(i + 1) % cols], center);
        }

        //Body
        for (int i = 1; i < rows - 1; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                sphere.normals[i][j] = find_normal(sphere.body[i - 1][j], sphere.body[i][j],
                        sphere.body[i][(j + 1) % cols], center);
            }
        }
    }
    return result;
}

//Инициализация сферы
//Орты к вершинам плоскостей, аппроксимирующих сферу
static status create_body(sphere_struct& sphere)
{
    status result = ok;
    sphere.rows = sphere.faces - 1;
    sphere.cols = 2 * sphere.faces;

    sphere.top = SpaceCoords(0, 0, 1);
    sphere.bottom = SpaceCoords(0, 0, -1);

    int size = sphere.rows * sphere.cols * sizeof(SpaceCoords) + sphere.rows * sizeof(SpaceCoords*);
    sphere.body = (SpaceCoords**) malloc(size);

    if (sphere.body == nullptr)
        result = memory_error;
    else
    {
        sphere.body[0] = (SpaceCoords*)((char*)sphere.body + sizeof(SpaceCoords*) * sphere.rows);
        for (int i = 1; i < sphere.rows; i++)
            sphere.body[i] = (SpaceCoords*)((char*)sphere.body[i - 1] + sizeof(SpaceCoords) * sphere.cols);

        //Шаг по медианам и широтам
        double ltd_step = rads(180. / (sphere.rows + 1));
        double mrd_step = rads(360. / (sphere.cols - 1));

        double ltd_cur = M_PI / 2 - ltd_step;
        for (int i = 0; i < sphere.rows; i++, ltd_cur -= ltd_step)
        {
            double mrd_cur = 0;
            for (int j = 0; j < sphere.cols; j++, mrd_cur += mrd_step)
            {
                float x = 1 * cos(ltd_cur) * sin(mrd_cur);
                float y = 1 * cos(ltd_cur) * cos(mrd_cur);
                float z = 1 * sin(ltd_cur);
                sphere.body[i][j] = SpaceCoords(x, y, z);
            }
        }
    }
    return result;
}

sphere_struct create_sphere(status &result, int faces_amount)
{
    //Инициализация структуры начальными параметрами
    sphere_struct sphere = init_sphere();
    if (faces_amount < 3 || faces_amount > 100)
    {
        result = wrong_settings;
        return sphere;
    }
    else
    {
        sphere.faces = faces_amount;

        result = create_body(sphere);
        if (result == ok)
            result = create_normals(sphere);

        if (result != ok)
            free_sphere(sphere);
    }
    return sphere;
}

void free_sphere(sphere_struct& sphere)
{
    if (sphere.body)
    {
        free(sphere.body);
        free(sphere.normals);

        sphere.body = nullptr;
        sphere.normals = nullptr;
    }
}
