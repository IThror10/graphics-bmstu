#include <cmath>
#include <stdio.h>
#include <xmmintrin.h>

// Умножение матрицы Nx4 на 4x4
// Right матрица подается транспонированной
// Результат в left
// Левая и правая матрица не пересекаются в памяти
void ASMmtrxMult(int N, float *left, float *right)
{
    asm
    (
        "MultMatrixLoop:"
            "movups (%r8), %xmm0\n\t"
            "movups 16(%r8), %xmm1\n\t"
            "movups 32(%r8), %xmm2\n\t"
            "movups 48(%r8), %xmm3\n\t"

            "mulps (%rdx), %xmm0\n\t"
            "mulps (%rdx), %xmm1\n\t"
            "mulps (%rdx), %xmm2\n\t"
            "mulps (%rdx), %xmm3\n\t"

            "haddps %xmm1, %xmm0\n\t"
            "haddps %xmm3, %xmm2\n\t"
            "haddps %xmm2, %xmm0\n\t"
            
            "movups %xmm0, (%rdx)\n\t"
            "add $16, %rdx\n\t"
            "loop MultMatrixLoop\n\t"
    );
}

void ASMmove(float *point, float *move)
{
    //__m128 reg1, reg2;
    //reg1 = _mm_loadu_ps(point);
    //reg2 = _mm_loadu_ps(move);
    //reg1 = _mm_add_ps(reg1, reg2);
    //_mm_storeu_ps(point, reg1);
    asm
    (
        "movaps (%rcx), %xmm0\n\t"
        "addps (%rdx), %xmm0\n\t"
        "movaps %xmm0, (%rcx)\n\t"
    );
}

void ASMmoveBack(float *point, float *move)
{
    asm
    (
        "movups (%rcx), %xmm0\n\t"
        "subps (%rdx), %xmm0\n\t"
        "movups %xmm0, (%rcx)\n\t"
    );
}

void ASMscale(float *point, float *center, float *coef)
{
    asm
    (
        "movups (%rcx), %xmm0\n\t"
        "subps (%rdx), %xmm0\n\t"
        "mulps (%r8), %xmm0\n\t"
        "addps (%rdx), %xmm0\n\t"
        "movups %xmm0, (%rcx)\n\t"
    );
}

void to_zero_matrix(float *matrix)
{
    asm
    (
        "subps %xmm4, %xmm4\n\t"
        "movups %xmm4, (%rcx)\n\t"
        "movups %xmm4, 16(%rcx)\n\t"
        "movups %xmm4, 32(%rcx)\n\t"
        "movups %xmm4, 48(%rcx)\n\t"
    );
}

static void to_xy_matrix(float *matrix, float rads)
{
    to_zero_matrix(matrix);
    matrix[0] = cos(rads);
    matrix[1] = sin(rads);
    matrix[4] = -matrix[1];
    matrix[5] = matrix[0];
    asm
    (
        "fld1\n\t"
        "fsts 40(%rcx)\n\t"
        "fstps 60(%rcx)\n\t"
    );
}

static void to_xz_matrix(float *matrix, float rads)
{
    to_zero_matrix(matrix);
    matrix[0] = cos(rads);
    matrix[2] = -sin(rads);
    matrix[8] = -matrix[2];
    matrix[10] = matrix[0];
    asm
    (
        "fld1\n\t"
        "fsts 20(%rcx)\n\t"
        "fstps 60(%rcx)\n\t"
    );
}

static void to_yz_matrix(float *matrix, float rads)
{
    to_zero_matrix(matrix);
    matrix[5] = cos(rads);
    matrix[6] = sin(rads);
    matrix[9] = -matrix[6];
    matrix[10] = matrix[5];
    asm
    (
        "fld1\n\t"
        "fsts (%rcx)\n\t"
        "fstps 60(%rcx)\n\t"
    );
}


//4 координата center инициализирована нулем
//result - единичная матрица
//tmp - вспомогательная область памяти
void ASMrotateMatrix(float *result, float *center, float *angles, float *tmp)
{
    asm
    (
        "mov %rcx, %rsi\n\t"
        "movups (%rdx), %xmm5\n\t"
        "movups 48(%rsi), %xmm6\n\t"
        "subps %xmm5, %xmm6\n\t"
        "movups %xmm6, 48(%rsi)\n\t"
    );
    
    to_xy_matrix(tmp, angles[0]);
    ASMmtrxMult(4, result, tmp);
    
    to_yz_matrix(tmp, angles[1]);
    ASMmtrxMult(4, result, tmp);
    
    to_xz_matrix(tmp, angles[2]);
    ASMmtrxMult(4, result, tmp);
    
    //Перенос в изначальное положение
    asm
    (
        "movups 48(%rsi), %xmm6\n\t"
        "addps %xmm5, %xmm6\n\t"
        "movups %xmm6, 48(%rsi)\n\t"
    );

    //Транспанирование
    asm
    (
        //mtr[0][1] <==> mtr[1][0]
        "flds 4(%rsi)\n\t"
        "flds 16(%rsi)\n\t"
        "fstps 4(%rsi)\n\t"
        "fstps 16(%rsi)\n\t"

        //mtr[0][2] <==> mtr[2][0]
        "flds 8(%rsi)\n\t"
        "flds 32(%rsi)\n\t"
        "fstps 8(%rsi)\n\t"
        "fstps 32(%rsi)\n\t"
    
        //mtr[0][3] <==> mtr[3][0]
        "flds 12(%rsi)\n\t"
        "flds 48(%rsi)\n\t"
        "fstps 12(%rsi)\n\t"
        "fstps 48(%rsi)\n\t"

        //mtr[1][2] <==> mtr[2][1]
        "flds 24(%rsi)\n\t"
        "flds 36(%rsi)\n\t"
        "fstps 24(%rsi)\n\t"
        "fstps 36(%rsi)\n\t"

        //mtr[1][3] <==> mtr[3][1]
        "flds 28(%rsi)\n\t"
        "flds 52(%rsi)\n\t"
        "fstps 28(%rsi)\n\t"
        "fstps 52(%rsi)\n\t"

        //mtr[2][3] <==> mtr[3][2]
        "flds 44(%rsi)\n\t"
        "flds 56(%rsi)\n\t"
        "fstps 44(%rsi)\n\t"
        "fstps 56(%rsi)\n\t"
    );
}