#include "model/inc/camera.h"

//Задел на вращение камеры и перспективной проекции
camera_struct init_camera()
{
    camera_struct camera;
    camera.eye_pos = SpaceCoords(0, 200, 0);
    camera.look_pos = SpaceCoords(0, 0, 0);
    camera.n1 = SpaceCoords(1, 0, 0);
    camera.n2 = SpaceCoords(0, 0, 1);
    return camera;
}

//Матрица перехода от глобальных координат в координаты наблюдателя
matrix4x4 translate_matrix(const camera_struct& camera)
{
    matrix4x4 answer = zero_matrix_init();
    answer.data[3][3] = 1;

    const SpaceCoords &n1 = camera.n1, &n3 = camera.n2;
    const SpaceCoords &start = camera.eye_pos, &end = camera.look_pos;
    SpaceCoords n2(end.x - start.x, end.y - start.y, end.z - start.z);
    float length = len(n2);
    n2.x /= length;
    n2.y /= length;
    n2.z /= length;

    answer.data[0][0] = n1.x;   answer.data[0][1] = n2.x;   answer.data[0][2] = n3.x;
    answer.data[1][0] = n1.y;   answer.data[1][1] = n2.y;   answer.data[1][2] = n3.y;
    answer.data[2][0] = n1.z;   answer.data[2][1] = n2.z;   answer.data[2][2] = n3.z;
    return answer;
}
