#include <iostream>
#include <stdio.h>
#include <chrono>
#include <cmath>

using namespace std::chrono;

void ASMmtrxMult(int n_rows, float *first, float *second);
typedef void (*asmfunction)(int, float*, float*);
long measure(asmfunction mult, int n_rows, float *first, float *second)
{
    auto begin = steady_clock::now();

    for (volatile int i = 0; i < 1000; i++)
        mult(n_rows, first, second);
    
    auto end = steady_clock::now();
    auto time = duration_cast<nanoseconds>(end - begin);
    return time.count();
}

void matrixMult(float first[4][4], float second[4][4], float res[4][4], int n, int k, int m);
typedef void (*function)(float[4][4], float[4][4], float[4][4], int, int, int);
long measure(function mult, float first[4][4], float second[4][4], float res[4][4], int n, int k, int m)
{
    auto begin = steady_clock::now();

    for (volatile int i = 0; i < 1000; i++)
        mult(first, second, res, n, k, m);
    
    auto end = steady_clock::now();
    auto time = duration_cast<nanoseconds>(end - begin);
    return time.count();
}


void move(float first[4], float second[4]);
void ASMmove(float *a, float *b);
typedef void (*moving)(float[4], float[4]);
long measure(moving move_func, float first[4], float second[4])
{
    auto begin = steady_clock::now();

    for (volatile int i = 0; i < 1000; i++)
        move_func(first, second);
    
    auto end = steady_clock::now();
    auto time = duration_cast<nanoseconds>(end - begin);
    return time.count();
}

void scale(float *point, float *center, float *coef);
void ASMscale(float *point, float *center, float *coef);
typedef void (*scaling)(float*, float*, float*);
long measure(scaling scale_func, float first[4], float second[4], float res[4])
{
    auto begin = steady_clock::now();

    for (volatile int i = 0; i < 1000; i++)
        scale_func(first, second, res);
    
    auto end = steady_clock::now();
    auto time = duration_cast<nanoseconds>(end - begin);
    return time.count();
}

void ASMrotateMatrix(float *result, float *center, float *angles, float *tmp);
typedef void (*createRotate)(float*, float*, float*, float*);
long measure(createRotate creation, float *result, float *center, float *angles, float *temp)
{
    auto begin = steady_clock::now();

    for (volatile int i = 0; i < 100; i++)
        creation(result, center, angles, temp);
    
    auto end = steady_clock::now();
    auto time = duration_cast<nanoseconds>(end - begin);
    return time.count();
}

void create_rotate_matrix(float result[4][4], float *center, float *angles, float tmp[4][4]);
typedef void (*Rotate)(float a[4][4], float *c, float *d, float b[4][4]);
long measure(Rotate creation, float result[4][4], float *center, float *angles, float temp[4][4])
{
    auto begin = steady_clock::now();

    for (volatile int i = 0; i < 100; i++)
        creation(result, center, angles, temp);
    
    auto end = steady_clock::now();
    auto time = duration_cast<nanoseconds>(end - begin);
    return time.count();
}

#include <xmmintrin.h>
void time_research()
{
    //void *ptr = _mm_malloc(4 * 20, 64);
    //float asm_ma = (float**) _mm_malloc(4 * 16)
    float ma[4][4], mb[4][4], mres[4][4];

    void *anew = _mm_malloc(4 * 20, 64);
    void *bnew = _mm_malloc(4 * 20, 64);
    void *cnew = _mm_malloc(4 * 20, 64);
    float *pa = (float*) anew;
    float *pb = (float*) bnew;
    float *pc = (float*) cnew;
    //float *anew = _mm_malloc(4 * 20, 64), *pa = anew;
    //float *bnew = _mm_malloc(4 * 20, 64), *pb = bnew;
    //float *cnew = _mm_malloc(4 * 20, 64), *pc = cnew;

    std::cout << "Matrix X Matrix Times" << std::endl;
    {
        measure(matrixMult, ma, mb, mres, 4, 4, 4);
        std::cout << "Std mult time: " << measure(matrixMult, ma, mb, mres, 4, 4, 4) << std::endl;
        
        measure(ASMmtrxMult, 4, pa, pb);
        std::cout << "Asm mult time: " << measure(ASMmtrxMult, 4, pa, pb) << std::endl;
    } 


    std::cout << std::endl << "Vector X Matrix Times" << std::endl;
    {
        measure(matrixMult, ma, mb, mres, 1, 4, 4);
        std::cout << "Std mult time: " << measure(matrixMult, ma, mb, mres, 1, 4, 4) << std::endl;
        
        measure(ASMmtrxMult, 1, pa, pb);
        std::cout << "Asm mult time: " << measure(ASMmtrxMult, 1, pa, pb) << std::endl;
    }

    std::cout << std::endl << "Point move Times" << std::endl;
    {
        measure(move, pa, pb);
        std::cout << "Std move time: " << measure(move, pa, pb) << std::endl;
        
        measure(ASMmove, pa, pb);
        std::cout << "Asm move time: " << measure(ASMmove, pa, pb) << std::endl;
    }

    std::cout << std::endl << "Point scale Times" << std::endl;
    {
        measure(scale, pa, pb, pc);
        std::cout << "Std scale time: " << measure(scale, pa, pb, pc) << std::endl;
        
        measure(ASMscale, pa, pb, pc);
        std::cout << "Asm scale time: " << measure(ASMscale, pa, pb, pc) << std::endl;
    }

    std::cout << std::endl << "Rotate Matrix init Time" << std::endl;
    {
        measure(create_rotate_matrix, ma, pa, pb, mb);
        std::cout << "Std time: " << measure(create_rotate_matrix, ma, pa, pb, mb) << std::endl;

        measure(ASMrotateMatrix, (float*)ma, pa, pb, (float*)mb);
        std::cout << "Asm time: " << measure(ASMrotateMatrix, (float*)ma, pa, pb, (float*)mb) << std::endl;
    }
    _mm_free(anew);
    _mm_free(bnew);
    _mm_free(cnew);
}


void unit_tests()
{
    std::cout << std::endl << "Unit Tests: " << std::endl;
    
    int doesnt_work = 0;
    float left[4][4], right[4][4], answer[4][4], result[4][4], tmp[4][4];
    float point[4], center[4], coeff[4], res[4], angles[4];
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
        {
            left[i][j] = (i == j ? 1 : 0);
            right[i][j] = i + j;
            result[i][j] = 0;
        }

    std::cout << "Matrix X Matrix: ";
    {
        left[0][0] = 1;     left[0][1] = 2;
        left[1][1] = 3;     left[1][2] = 4;
        left[2][2] = 5;     left[2][3] = 6;
        left[3][3] = 7;

        answer[0][0] = 2;   answer[1][0] = 11;  answer[2][0] = 28;  answer[3][0] = 21;
        answer[0][1] = 5;   answer[1][1] = 18;  answer[2][1] = 39;  answer[3][1] = 28;
        answer[0][2] = 8;   answer[1][2] = 25;  answer[2][2] = 50;  answer[3][2] = 35;
        answer[0][3] = 11;  answer[1][3] = 32;  answer[2][3] = 61;  answer[3][3] = 42;

        ASMmtrxMult(4, (float*) left, (float*) right);
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (abs(left[i][j] - answer[i][j]) > 1e-6)
                    doesnt_work = 1;
                right[i][j] = (i == j ? 1 : 0);
            }
        }
    }
    std::cout << (doesnt_work ? "0/1" : "1/1") << std::endl;
    doesnt_work = 0;

    std::cout << "Vector X Matrix: ";
    {
        left[0][0] = 1.5; left[0][1] = 2; left[0][2] = 3; left[0][3] = 1;
        right[0][3] = 5.5; right[1][3] = 6.5; right[2][3] = 7;
        answer[0][0] = 7; answer[0][1] = 8.5; answer[0][2] = 10; answer[0][3] = 1;

        ASMmtrxMult(1, (float*) left, (float*) right);
        for (int i = 0; i < 1; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (fabs(left[i][j] - answer[i][j]) > 1e-6)
                    doesnt_work = 1;
            }
        }
    }
    std::cout << (doesnt_work ? "0/1" : "1/1") << std::endl;
    doesnt_work = 0;

    std::cout << "Point move: ";
    {
        point[0] = 5;   point[1] = 3;   point[2] = 12; point[3] = 1;
        center[0] = -2; center[1] = 17; center[2] = 0; center[3] = 0;
        res[0] = 3;     res[1] = 20;    res[2] = 12;   res[3] = 1;
        ASMmove(point, center);
        for (int i = 0; i < 4; i++)
            if (fabs(point[i] - res[i]) > 1e-6)
                doesnt_work = 1;
    }
    std::cout << (doesnt_work ? "0/1" : "1/1") << std::endl;
    doesnt_work = 0;

    std::cout << "Point scale: ";
    {
        point[0] = 5;   point[1] = 3;   point[2] = 12; point[3] = 1;
        center[0] = -2; center[1] = 17; center[2] = 0; center[3] = 0;
        coeff[0] = 2;   coeff[1] = 0.5; coeff[2] = -1; coeff[3] = 1; 
        res[0] = 12;    res[1] = 10;    res[2] = -12;   res[3] = 1;
        ASMscale(point, center, coeff);
        for (int i = 0; i < 4; i++)
            if (fabs(point[i] - res[i]) > 1e-6)
                doesnt_work = 1;
    }
    std::cout << (doesnt_work ? "0/1" : "1/1") << std::endl;
    doesnt_work = 0;

    std::cout << "Point rotate: ";
    {
        point[0] = 2;   point[1] = 2;   point[2] = 2;   point[3] = 1;
        center[0] = 1;  center[1] = 1;  center[2] = 1;  center[3] = 0;
        angles[0] = 90; angles[1] = 0;  angles[2] = 90;
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                result[i][j] = (i == j ? 1 : 0);

        ASMrotateMatrix((float*) result, center, angles, (float*) tmp);
        ASMmtrxMult(1, point, (float*)result);
        result[0][0] = -2;  result[0][1] = 0;   result[0][2] = 0;   result[0][3] = 1;
        for (int i = 0; i < 4; i++)
            if (fabs(point[i] - result[0][i]) > 1e-6)
                doesnt_work = 1;

    }
    std::cout << (doesnt_work ? "0.5/1" : "1/1") << std::endl;
    doesnt_work = 0;
}

int main()
{
    time_research();
    unit_tests();
    return 0;
}