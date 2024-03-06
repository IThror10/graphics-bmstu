#include "model/instruction/scaling.h"
#include "model/myMath/my_math.h"

matrix4x4 scale_matrix(float coeff)
{
    matrix4x4 matrix = zero_matrix_init();
    matrix.data[0][0] = coeff;
    matrix.data[1][1] = coeff;
    matrix.data[2][2] = coeff;
    matrix.data[3][3] = 1;
    return  matrix;
}

void scale_connection(ConnectionArr& arr, matrix4x4& matrix)
{
    for (int i = 1; i < arr.size; i++)
    {
        Connection &cur = arr.data[i];
        ASMmtrxMult(cur.amount, cur.bottom, cur.bottom, &matrix);
        ASMmtrxMult(cur.amount, cur.top, cur.top, &matrix);
    }
}

void scale_atoms(AtomArr& arr, matrix4x4& matrix, float coeff)
{
    for (int i = 0; i < arr.amount; i++)
    {
        arr.data[i].center = mult_vector(arr.data[i].center, matrix);
        arr.data[i].radius *= coeff;
    }
}
