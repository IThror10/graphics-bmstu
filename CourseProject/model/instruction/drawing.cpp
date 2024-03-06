#include "model/instruction/drawing.h"
#include "model/myMath/my_math.h"
#include "model/instruction/scaling.h"
#include "model/instruction/moving.h"
#include <QPolygon>
#include <malloc.h>

//Очистка сцены
void clear_scene(drawing& params)
{
    if (params.scene)
    {
        params.scene->clear();
    }
}

//Отрисовка полигона из 4 точек с границами Pen и заполнением Brush
void draw_poly(drawing& params, const SpaceCoords& pntA, const SpaceCoords &pntB,\
               const SpaceCoords& pntC, const SpaceCoords &pntD, QPen pen = QPen(), QBrush brush = QBrush())
{
    QPolygon poly;
    poly << QPoint(pntA.x, pntA.z) << QPoint(pntB.x, pntB.z) << QPoint(pntC.x, pntC.z) << QPoint(pntD.x, pntD.z);
    params.scene->addPolygon(poly, pen, brush);
}

//Отрисовка полигона из 3 точек с границами Pen и заполнением Brush
void draw_poly(drawing& params, const SpaceCoords& pntA, const SpaceCoords &pntB,\
                const SpaceCoords& pntC, QPen& pen, QBrush& brush)
{
    QPolygon poly;
    poly << QPoint(pntA.x, pntA.z) << QPoint(pntB.x, pntB.z) << QPoint(pntC.x, pntC.z);
    params.scene->addPolygon(poly, pen, brush);
}

//Создание модели выбранного атома в координатах наблюдатедю
static void fill_temp(sphere_struct& temp, const sphere_struct& global, const Atom& atom, const matrix4x4& translate)
{
    matrix4x4 mult;
    //Перенос в центр -> перенос в координаты наблюдателя -> масштабирование
    mult = mult_matrix(move_matrix(atom.center), translate);
    mult = mult_matrix(scale_matrix(atom.radius), mult);

    temp.top = mult_vector(global.top, mult);
    temp.bottom = mult_vector(global.bottom, mult);

    ASMmtrxMult(global.rows * global.cols, temp.body[0], global.body[0], &mult);
    ASMmtrxMult((global.rows + 1) * global.cols, temp.normals[0], global.normals[0], &translate);
}

//Перенос соединения в координаты наблюдателя
static void fill_temp(Connection &temp, const Connection& given, const matrix4x4& translate)
{
    ASMmtrxMult(given.amount, temp.bottom, given.bottom, &translate);
    ASMmtrxMult(given.amount, temp.top, given.top, &translate);
}

//Отрисовка цилиндра
void draw_connection(const Connection& given, drawing &params)
{
    QPen pen = QColor(0, 0, 0, 255);
    QBrush brush(QColor(128, 128, 128, 200));
    for (int i = 0; i < given.amount - 1; i++)
         draw_poly(params,given.bottom[i], given.bottom[i + 1], given.top[i + 1], given.top[i], pen, brush);
    draw_poly(params, given.bottom[0], given.top[0], given.top[given.amount - 1], given.bottom[given.amount - 1], pen, brush);
}

//Выбор цвета закраски в зависимости от алгоритма
void set_color(const SpaceCoords& pntA, const SpaceCoords& pntB, const SpaceCoords& pntC, const SpaceCoords& pntD,\
                 const SpaceCoords& normal, const QColor color, QPen& pen, QBrush& brush, fill_t fill)
{
    switch (fill)
    {
        case mono:
        {
            SpaceCoords light(0.5, -1, -0.5);
            float k = scalar_mult(normal, light);
            pen = color.darker(165 - 100 * k);
            brush = pen.color();
            break;
        }

        case gouraud:
        {
            SpaceCoords light(0.5, -1, -0.5);
            float k = scalar_mult(normal, light);
            pen = color.darker(165 - 100 * k);
            brush = pen.color();
            break;
        }

        case flat:
        {
            pen = color;
            brush = QColor(255, 255, 255);
            break;
        }

        case not_set:
        {
            pen = QColor(255, 255, 255);
            break;
        }
    }
}

//Отрисовка сферы
void draw_atom(const sphere_struct& sphere, drawing &params, const Atom& atom, fill_t fill, const sphere_struct& global)
{
    QPen pen;
    QBrush brush;

    int rows = sphere.rows, cols = sphere.cols;
    //Draw top
    for (int i = 0; i < cols - 1; i++)
        if (sphere.normals[0][i].y < 0) //Здесь и далее - условие видимости плоскости
        {
            set_color(global.top, global.body[0][i], global.body[0][i + 1], global.top, sphere.normals[0][i],
                    atom.color, pen, brush, fill);
            draw_poly(params, sphere.top, sphere.body[0][i],
                        sphere.body[0][i + 1], pen, brush);
        }
    if (sphere.normals[0][cols - 1].y < 0)
    {
        set_color(global.top, global.body[0][cols - 1], global.body[0][0], global.top, sphere.normals[0][cols - 1],
                atom.color, pen, brush, fill);
        draw_poly(params, sphere.top, sphere.body[0][cols - 1],
                    sphere.body[0][0], pen, brush);
    }

    //Draw bottom
    for (int i = 0; i < cols - 1; i++)
        if (sphere.normals[rows][i].y < 0)
        {
            set_color(global.bottom, global.body[rows - 1][i], global.body[rows - 1][i + 1], global.bottom, sphere.normals[rows][i],
                    atom.color, pen, brush, fill);
            draw_poly(params, sphere.bottom, sphere.body[rows - 1][i],
                        sphere.body[rows - 1][i + 1], pen, brush);
        }
    if (sphere.normals[rows][cols - 1].y < 0)
    {
        set_color(global.bottom, global.body[rows - 1][cols - 1], global.body[rows - 1][0], global.bottom, sphere.normals[rows][cols - 1],
                atom.color, pen, brush, fill);
        draw_poly(params, sphere.bottom, sphere.body[rows - 1][cols - 1],
                    sphere.body[rows - 1][0], pen, brush);
    }

    //Draw body
    for (int i = 0; i < rows - 1; i++)
    {
        for (int j = 0; j < cols - 1; j++)
        {
            if (sphere.normals[i + 1][j].y < 0)
            {
                set_color(global.body[i][j], global.body[i][j + 1],\
                        global.body[i + 1][j + 1], global.body[i + 1][j], sphere.normals[i + 1][j],
                        atom.color, pen, brush, fill);
                draw_poly(params, sphere.body[i][j], sphere.body[i][j + 1],\
                        sphere.body[i + 1][j + 1], sphere.body[i + 1][j], \
                        pen, brush);
            }
        }
        if (sphere.normals[i + 1][cols - 1].y < 0)
        {
            set_color(global.body[i][cols - 1], global.body[i][0],\
                    global.body[i + 1][0], global.body[i + 1][cols - 1], sphere.normals[i + 1][cols - 1],
                    atom.color, pen, brush, fill);
            draw_poly(params, sphere.body[i][cols - 1], sphere.body[i][0],\
                sphere.body[i + 1][0], sphere.body[i + 1][cols - 1], \
                pen, brush);
        }
    }
}

//Отображение атома с соединениями
void show_atom(const Atom& atom, const ConnectionArr& connect, const matrix4x4 &translate,\
               drawing& params, const sphere_struct& global, sphere_struct& temp, fill_t fill)
{
    //Создание буфера с координатами сферы и её отрисовка
    fill_temp(temp, global, atom, translate);
    draw_atom(temp, params, atom, fill, global);

    //Отрисовка соединений, которые направлены к наблюдателю
    //Соединения, направленные от наблюдателя, были отрисованы с предыдущими атомами
    node_t *list = atom.list.next;
    while (list)
    {
        Connection &con = connect.data[list->n];
        SpaceCoords a = con.bottom[0], b = con.top[0];

        SpaceCoords vect;
        if (distance(a, atom.center) < distance(b, atom.center))
            vect = SpaceCoords(b.x - a.x, b.y - a.y, b.z - a.z);
        else
            vect = SpaceCoords(a.x - b.x, a.y - b.y, a.z - b.z);

        if (mult_vector(vect, translate).y <= 0)
        {
            fill_temp(connect.data[0], connect.data[list->n], translate);
            draw_connection(connect.data[list->n], params);
        }

        list = list->next;
    }
}

//Упрощенный алгоритм Художника
void draw_scene(const AtomArr& atoms, const ConnectionArr& connect, const camera_struct& camera,\
                drawing& params, const sphere_struct& global, sphere_struct& temp, fill_t fill)
{
    float *dist = (float*) malloc(sizeof(float) * atoms.amount);
    if (dist == nullptr)
        return;

    matrix4x4 matrix = translate_matrix(camera);
    //Массив расстояний от наблюдателя до атома
    for (int i = 0; i < atoms.amount; i++)
        dist[i] = mult_vector(atoms.data[i].center, matrix).y;

    for (int i = 0; i < atoms.amount; i++)
    {
        //Выбор наиболее удаленного
        int ind = 0;
        float max = -Q_INFINITY;
        for (int j = 0; j < atoms.amount; j++)
        {
            if (dist[j] > max)
            {
                max = dist[j];
                ind = j;
            }
        }

        //Отрисовка атома
        show_atom(atoms.data[ind], connect, matrix, params, global, temp, fill);
        //Пометка как отрисованного
        dist[ind] = -Q_INFINITY;
    }

    free(dist);
}
