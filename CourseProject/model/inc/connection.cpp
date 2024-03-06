#include "model/inc/connection.h"
#include "model/instruction/rotating.h"
#include "model/myMath/my_math.h"
#include "model/instruction/scaling.h"
#include <malloc.h>
#include <cmath>

ConnectionArr init_ConnectionArr()
{
    ConnectionArr arr;
    arr.data = nullptr;
    arr.size = 0;
    return arr;
}

void free_ConnectionArr(ConnectionArr& arr)
{
    if (arr.data)
    {
        for (int i = 0; i < arr.size; i++)
            free_Connection(arr.data[i]);
    }
    free(arr.data);
    arr.data = nullptr;
}

ConnectionArr create_ConnectionArr(status& result, int size)
{
    ConnectionArr arr;
    arr.data = (Connection*) malloc(sizeof(Connection) * size);
    if (arr.data == nullptr)
        result = memory_error;
    else
    {
        result = ok;
        arr.size = size;
        for (int i = 0; i < size; i++)
            arr.data[i] = init_connection();
    }
    return arr;
}

//Одиночная связь
static status single_connection(ConnectionArr& connections, int current, Atom& first, Atom& second, int faces)
{
    status result = ok;
    float radius = (first.radius + second.radius) / 16;
    connections.data[current] = create_Connection(result, faces, radius, first.center, second.center);

    //Добавление информации в списки атомов
    if (result == ok)
    {
        result = add_node(&first.list, current);
        if (result == ok)
            result = add_node(&second.list, current);
    }
    return result;
}

//Двойная связь
static status double_connection(ConnectionArr& connections, int current, Atom& first, Atom& second, int faces)
{
    status result = ok;
    SpaceCoords move = find_normal(first.center, second.center);
    float radius = (first.radius + second.radius) / 16;

    //Смещение относительно отрезка, соединяющего центры атомов
    SpaceCoords a = first.center, b = second.center;
    move.x *= 3 * radius;   move.y *= 3 * radius;   move.z *= 3 * radius;
    move_point(a, move);    move_point(b, move);

    //Одиночное соединение
    connections.data[current] = create_Connection(result, faces, radius, a, b);
    if (result == ok)
    {
        result = add_node(&first.list, current);
        if (result == ok)
            result = add_node(&second.list, current);
    }

    //Симметричный сдвиг
    move.x *= -2;   move.y *= -2;   move.z *= -2;
    move_point(a, move);    move_point(b, move);

    //Одиночное соединение
    if (result == ok)
        connections.data[current + 1] = create_Connection(result, faces, radius, a, b);
    if (result == ok)
    {
        result = add_node(&first.list, current + 1);
        if (result == ok)
            result = add_node(&second.list, current + 1);
    }
    return result;
}

//Инициализация цилиндров, соединяющих сферы
status initialize_connections(int **connect, int size, ConnectionArr& connections, AtomArr &atoms, int faces)
{
    int cur = 1;
    status result = ok;
    for (int i = 0; i < size && result == ok; i++)
    {
        for (int j = i + 1; j < size && result == ok; j++)
        {
            switch (connect[i][j])
            {
            case 3:
                result = double_connection(connections, cur, atoms.data[i], atoms.data[j], faces);
                if (result == ok)
                    result = single_connection(connections, cur + 2, atoms.data[i], atoms.data[j], faces);
                cur += 3;
                break;
            case 2:
                result = double_connection(connections, cur, atoms.data[i], atoms.data[j], faces);
                cur += 2;
                break;
            case 1:
                result = single_connection(connections, cur, atoms.data[i], atoms.data[j], faces);
                cur += 1;
                break;
            }
        }
    }

    //Соединение буфер
    if (result == ok)
        connections.data[0] = create_Connection(result, faces, 5, SpaceCoords(0, 0, 0), SpaceCoords(0, 0, 1));
    return result;
}

Connection init_connection()
{
    Connection connect;
    connect.bottom = nullptr;
    connect.top = nullptr;
    connect.amount = 0;
    return connect;
}

void free_Connection(Connection& connect)
{
    free(connect.bottom);
    free(connect.top);

    connect.bottom = nullptr;
    connect.top = nullptr;
}

//Инициализация соединения
Connection create_Connection(status& result, int faces, float radius, const SpaceCoords& start, const SpaceCoords& end)
{
    Connection connect = init_connection();
    connect.amount = faces;

    connect.bottom = (SpaceCoords*) malloc(sizeof(SpaceCoords) * faces);
    connect.top = (SpaceCoords*) malloc(sizeof(SpaceCoords) * faces);
    if (connect.bottom == nullptr || connect.top == nullptr)
        free_Connection(connect);
    else
    {
        //Сдвиг по нормали от оси до образующей
        SpaceCoords vect = find_normal(start, end);
        float coeff = radius / len(vect);
        vect.x *= coeff;
        vect.y *= coeff;
        vect.z *= coeff;

        float angle = 360. / faces;
        //Нормированный вектор оси
        SpaceCoords os(start.x - end.x, start.y - end.y, start.z - end.z);
        coeff = len(os);
        os.x /= coeff;
        os.y /= coeff;
        os.z /= coeff;

        //Матрица вращения вокруг произвольной оси
        matrix4x4 mtr = create_rotate_matrix(os, angle);

        //Координаты образующих
        for (int i = 0; i < faces; i++)
        {
            vect = mult_vector(vect, mtr);
            SpaceCoords down(start.x + vect.x, start.y + vect.y, start.z + vect.z);
            SpaceCoords up(end.x + vect.x, end.y + vect.y, end.z + vect.z);
            connect.bottom[i] = down;
            connect.top[i] = up;
        }
    }
    return connect;
}

//Усечение образующей цилиндра в точке пересечения идеальной сферы
//Достаточное приближение
static void cut_line(SpaceCoords &start, SpaceCoords &end, const Atom &atom)
{
    float d1 = distance(start, atom.center);
    float d2 = distance(end, atom.center);
    if (d1 < atom.radius)
    {
        SpaceCoords vect(end.x - start.x, end.y - start.y, end.z - start.z);
        float coeff = (sqrt(pow(atom.radius, 2) - pow(d1, 2))) / len(vect);
        vect.x *= coeff;
        vect.y *= coeff;
        vect.z *= coeff;
        move_point(start, vect);
    }
    else if (d2 < atom.radius)
    {
        SpaceCoords vect(start.x - end.x, start.y - end.y, start.z - end.z);
        float coeff = (sqrt(pow(atom.radius, 2) - pow(d2, 2))) / len(vect);
        vect.x *= coeff;
        vect.y *= coeff;
        vect.z *= coeff;
        move_point(end, vect);
    }
}

//Усечение каждой образующей цилиндра
static void do_cut(Connection& connect, const Atom& atom)
{
    for (int i = 0; i < connect.amount; i++)
        cut_line(connect.top[i], connect.bottom[i], atom);
}

//Удаление невидимых частей цилиндра
void cut_connections(ConnectionArr& arr, const AtomArr& atoms)
{
    for (int i = 0; i < atoms.amount; i++)
    {
        node_t *list = atoms.data[i].list.next;
        while (list)
        {
            do_cut(arr.data[list->n], atoms.data[i]);
            list = list->next;
        }
    }
}
