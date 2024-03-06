#include "model/instruction/rotating.h"
#include <cmath>

static double radians(const double degrees)
{
    return M_PI * degrees / 180;
}

static matrix4x4 xy_rotate_matrix(const double angle)
{
    const double rads = radians(angle);
    matrix4x4 rotate = unity_matrix_init();

    rotate.data[0][0] = cos(rads);
    rotate.data[0][1] = sin(rads);
    rotate.data[1][0] = -sin(rads);
    rotate.data[1][1] = cos(rads);
    return rotate;
}

static matrix4x4 xz_rotate_matrix(const double angle)
{
    const double rads = radians(angle);
    matrix4x4 rotate = unity_matrix_init();

    rotate.data[0][0] = cos(rads);
    rotate.data[0][2] = -sin(rads);
    rotate.data[2][0] = sin(rads);
    rotate.data[2][2] = cos(rads);
    return rotate;
}

static matrix4x4 yz_rotate_matrix(const double angle)
{
    const double rads = radians(angle);
    matrix4x4 rotate = unity_matrix_init();

    rotate.data[1][1] = cos(rads);
    rotate.data[1][2] = sin(rads);
    rotate.data[2][1] = -sin(rads);
    rotate.data[2][2] = cos(rads);
    return rotate;
}

//Матрица вращения вокруг произвольной оси
matrix4x4 create_rotate_matrix(const SpaceCoords& vector, float angle)
{
    matrix4x4 matrix = unity_matrix_init();
    angle = radians(angle);
    matrix.data[0][0] = cos(angle) + (1 - cos(angle)) * pow(vector.x, 2);
    matrix.data[1][0] = (1 - cos(angle)) * vector.x * vector.y + sin(angle) * vector.z;
    matrix.data[2][0] = (1 - cos(angle)) * vector.z * vector.x - sin(angle) * vector.y;

    matrix.data[0][1] = (1 - cos(angle)) * vector.x * vector.y - sin(angle) * vector.z;
    matrix.data[1][1] = cos(angle) + (1 - cos(angle)) * pow(vector.y, 2);
    matrix.data[2][1] = (1 - cos(angle)) * vector.z * vector.y + sin(angle) * vector.x;

    matrix.data[0][2] = (1 - cos(angle)) * vector.x * vector.z + sin(angle) * vector.y;
    matrix.data[1][2] = (1 - cos(angle)) * vector.y * vector.z - sin(angle) * vector.x;
    matrix.data[2][2] = cos(angle) + (1 - cos(angle)) * pow(vector.z, 2);
    return matrix;
}

//Матрица вращения относительно точки center
matrix4x4 create_rotate_matrix(const camera_struct& camera, const rotating& params, const SpaceCoords& center)
{
    const SpaceCoords &n1 = camera.n1, &n2 = camera.n2;
    float xy_angle = n1.x * params.ox_rotate + n2.x * params.oz_rotate;
    float xz_angle = n1.y * params.ox_rotate + n2.y * params.oz_rotate;
    float yz_angle = n1.z * params.ox_rotate + n2.z * params.oz_rotate;

    matrix4x4 answer = unity_matrix_init();
    answer = mult_matrix(answer, back_move_matrix(center));
    answer = mult_matrix(answer, xy_rotate_matrix(xy_angle));
    answer = mult_matrix(answer, xz_rotate_matrix(xz_angle));
    answer = mult_matrix(answer, yz_rotate_matrix(yz_angle));
    answer = mult_matrix(answer, move_matrix(center));
    return answer;
}

void rotate_atoms(AtomArr& atoms, const matrix4x4& rotate)
{
    for (int i = 0; i < atoms.amount; i++)
        atoms.data[i].center = mult_vector(atoms.data[i].center, rotate);
}

void rotate_sphere(sphere_struct& sphere, const matrix4x4& rotate)
{
    sphere.top = mult_vector(sphere.top, rotate);
    sphere.bottom = mult_vector(sphere.bottom, rotate);
    for (int i = 0; i < sphere.rows; i++)
        for (int j = 0; j < sphere.cols; j++)
            sphere.body[i][j] = mult_vector(sphere.body[i][j], rotate);
    for (int i = 0; i < sphere.faces; i++)
        for (int j = 0; j < sphere.cols; j++)
            sphere.normals[i][j] = mult_vector(sphere.normals[i][j], rotate);
}

void rotate_connections(ConnectionArr& arr, const matrix4x4& rotate)
{
    for (int i = 1; i < arr.size; i++)
    {
        Connection &cur = arr.data[i];
        for (int j = 0; j < cur.amount; j++)
        {
            cur.bottom[j] = mult_vector(cur.bottom[j], rotate);
            cur.top[j] = mult_vector(cur.top[j], rotate);
        }
    }
}

void rotate_camera_struct(camera_struct& camera, const matrix4x4& rotate)
{
    camera.n1 = mult_vector(camera.n1, rotate);
    camera.n2 = mult_vector(camera.n2, rotate);
    camera.eye_pos = mult_vector(camera.eye_pos, rotate);
}
