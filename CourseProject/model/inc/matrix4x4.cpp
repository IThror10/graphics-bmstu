#include "model/inc/matrix4x4.h"

matrix4x4 zero_matrix_init()
{
    matrix4x4 init;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            init.data[i][j] = 0;
    return init;
}

matrix4x4 unity_matrix_init()
{
    matrix4x4 init;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            init.data[i][j] = (i == j);
    return init;
}

matrix4x4 move_matrix(const SpaceCoords& coords)
{
    matrix4x4 matrix = unity_matrix_init();
    matrix.data[3][0] = coords.x;
    matrix.data[3][1] = coords.y;
    matrix.data[3][2] = coords.z;
    return matrix;
}

matrix4x4 back_move_matrix(const SpaceCoords& coords)
{
    matrix4x4 matrix = unity_matrix_init();
    matrix.data[3][0] = -coords.x;
    matrix.data[3][1] = -coords.y;
    matrix.data[3][2] = -coords.z;
    return matrix;
}

SpaceCoords mult_vector(const SpaceCoords& coords, const matrix4x4& rotate)
{
    SpaceCoords answer;

    answer.x =  coords.x * rotate.data[0][0] + coords.y * rotate.data[1][0] +\
                coords.z * rotate.data[2][0] + coords.empty * rotate.data[3][0];
    answer.y =  coords.x * rotate.data[0][1] + coords.y * rotate.data[1][1] +\
                coords.z * rotate.data[2][1] + coords.empty * rotate.data[3][1];
    answer.z =  coords.x * rotate.data[0][2] + coords.y * rotate.data[1][2] +\
                coords.z * rotate.data[2][2] + coords.empty * rotate.data[3][2];
    answer.empty = coords.x * rotate.data[0][3] + coords.y * rotate.data[1][3] +\
                coords.z * rotate.data[2][3] + coords.empty * rotate.data[3][3];
    return answer;
}

matrix4x4 mult_matrix(const matrix4x4& left, const matrix4x4& right)
{
    matrix4x4 answer = zero_matrix_init();
    for (int row = 0; row < 4; row++)
        for (int col = 0; col < 4; col++)
            for (int mid = 0; mid < 4; mid++)
                answer.data[row][col] += left.data[row][mid] * right.data[mid][col];
    return answer;
}
