#include "model/myMath/my_math.h"

//Функция, написанная с использованием расширения SSE
//Выигрыш в скорости
void ASMmtrxMult(int N, SpaceCoords *dest, SpaceCoords *src, const matrix4x4 *matrix)
{
    asm
    (
        //Загрузка матрицы
        "movups (%%rdx), %%xmm0\n\t"
        "movups 16(%%rdx), %%xmm4\n\t"
        "movups 32(%%rdx), %%xmm5\n\t"
        "movups 48(%%rdx), %%xmm6\n\t"

        //Транспонирование матрицы
        "movaps %%xmm0, %%xmm2\n\t"
        "unpcklps %%xmm4, %%xmm0\n\t"
        "unpckhps %%xmm4, %%xmm2\n\t"

        "movaps %%xmm5, %%xmm7\n\t"
        "unpcklps %%xmm6, %%xmm5\n\t"
        "unpckhps %%xmm6, %%xmm7\n\t"

        "movaps %%xmm5, %%xmm1\n\t"
        "movhlps %%xmm0, %%xmm1\n\t"
        "movlhps %%xmm5, %%xmm0\n\t"

        "movaps %%xmm7, %%xmm3\n\t"
        "movhlps %%xmm2, %%xmm3\n\t"
        "movlhps %%xmm7, %%xmm2\n\t"

        //Умножение
        "MultLoop:"
            //Изменяемый вектор
            "movups (%%rsi), %%xmm4\n\t"

            //Копирование матрицы (без повторного чтения из памяти)
            "movups %%xmm0, %%xmm5\n\t"
            "movups %%xmm1, %%xmm6\n\t"
            "movups %%xmm2, %%xmm7\n\t"
            "movups %%xmm3, %%xmm8\n\t"

            //Матричное умножение
            "mulps %%xmm4, %%xmm5\n\t"
            "mulps %%xmm4, %%xmm6\n\t"
            "mulps %%xmm4, %%xmm7\n\t"
            "mulps %%xmm4, %%xmm8\n\t"
            "haddps %%xmm6, %%xmm5\n\t"
            "haddps %%xmm8, %%xmm7\n\t"
            "haddps %%xmm7, %%xmm5\n\t"

            //Сохранение результата, следующий элемент
            "movups %%xmm5, (%%rdi)\n\t"
            "add $16, %%rdi\n\t"
            "add $16, %%rsi\n\t"
            "loop MultLoop\n\t"

            :
            : "D"(dest), "S"(src), "c"(N), "d"(matrix)
            :

    );
}
