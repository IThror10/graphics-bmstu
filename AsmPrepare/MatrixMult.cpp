#include <cmath>
//Умножение матриц nXk и kXm
void matrixMult(float first[4][4], float second[4][4], float res[4][4], int n = 4, int k = 4, int m = 4)
{
    for (int j = 0; j < m; j++)
        for (int i = 0; i < n; i++)
            for (int mid = 0; mid < k; mid++)
                res[j][i] += first[i][mid] * second[mid][j];
}

void move(float first[4], float second[4])
{
    first[0] += second[0];
    first[1] += second[1];
    first[2] += second[2];
    first[3] += second[3];
}

void scale(float *point, float *center, float *coef)
{
    point[0] = coef[0] * point[0] + center[0] * (1 - coef[0]);
    point[1] = coef[1] * point[1] + center[1] * (1 - coef[1]);
    point[2] = coef[2] * point[2] + center[2] * (1 - coef[2]);
}


static void to_zero_matrix(float *matrix)
{
    for (int i = 0; i < 16; i++)
        matrix[i] = 0;
}

void to_unity_matrix(float *matrix)
{
    to_zero_matrix(matrix);
    for (int i = 0; i < 16; i += 5)
        matrix[i] = 1;
}

void to_move_matrix(float *matrix, float dx, float dy, float dz)
{
    to_unity_matrix(matrix);
    matrix[12] = dx;
    matrix[13] = dy;
    matrix[14] = dz;
}

static double radians(const double degrees)
{
    return M_PI * degrees / 180;
}

static void to_xy_rotate_matrix(float *matrix, double angle)
{
    const double rads = radians(angle);
    to_unity_matrix(matrix);

    matrix[0] = cos(rads);
    matrix[1] = sin(rads);
    matrix[4] = -sin(rads);
    matrix[5] = cos(rads);
}

static void to_xz_rotate_matrix(float *matrix, const double angle)
{
    const double rads = radians(angle);
    to_unity_matrix(matrix);

    matrix[0] = cos(rads);
    matrix[2] = -sin(rads);
    matrix[8] = sin(rads);
    matrix[10] = cos(rads);
}

static void to_yz_rotate_matrix(float *matrix, const double angle)
{
    const double rads = radians(angle);
    to_unity_matrix(matrix);

    matrix[5] = cos(rads);
    matrix[6] = sin(rads);
    matrix[9] = -sin(rads);
    matrix[10] = cos(rads);
}

//Не работает. Для сравнения быстродействия
void create_rotate_matrix(float result[4][4], float *center, float *angles, float tmp[4][4])
{
    to_move_matrix((float*)result, -center[0], -center[1], -center[2]);
    to_xy_rotate_matrix((float*)tmp, angles[0]);
    matrixMult(result, tmp, tmp);

    to_xz_rotate_matrix((float*)tmp, angles[1]);
    matrixMult(result, tmp, tmp);

    to_yz_rotate_matrix((float*)tmp, angles[2]);
    matrixMult(result, tmp, tmp);

    to_move_matrix((float*)tmp, center[0], center[1], center[2]);
    matrixMult(result, tmp, tmp);
}