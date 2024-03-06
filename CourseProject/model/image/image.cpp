#include "model/image/image.h"
#include "model/instruction/drawing.h"
#include <QDebug>
#include <chrono>
#include <ctime>

class Timer
{
public:
    Timer(){
        this->clear_data();
        this->size = 200;
    }

    void clear_data(){
        this->cur_ind = 0;
        this->is_full = false;
        for (int i = 0; i < this->size; i++)
            this->fps_arr[i] = 0;
        this->start();
    }

    int avg_fps(){
        int i;
        float sum = 0;
        for (i = 0; i < this->size && this->fps_arr[i] > 0; i++)
            sum += this->fps_arr[i];
        return sum / i;
    }

    void start(){
        begin = std::chrono::steady_clock::now();
    }

    void stop(){
        end = std::chrono::steady_clock::now();
        auto res = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
        this->fps_arr[this->cur_ind] = (1e6 / res.count());
        this->cur_ind = (this->cur_ind + 1) % this->size;
    }

private:
    float fps_arr[200];
    int size;
    int cur_ind;
    bool is_full;

    std::chrono::steady_clock::time_point begin;
    std::chrono::steady_clock::time_point end;
};

Timer timer = Timer();

//Количество соединений модели
static int count_connections(int** const arr, int size)
{
    int amount = 0;
    for (int i = 0; i < size; i++)
    {
        for (int j = i + 1; j < size; j++)
            amount += arr[i][j];
    }
    return amount;
}

//Инициализация модели пустыми значениями
image_data image_init()
{
    image_data data;
    data.initialized = false;
    data.tmp_sphere = init_sphere();
    data.global_sphere = init_sphere();
    data.atoms = init_AtomArr();
    data.connect = init_ConnectionArr();
    data.camera = init_camera();
    data.center = SpaceCoords(0, 0, 0);
    return data;
}

//Перенос изображения
status move_image(image_data &image, const moving& params)
{
    if (image.initialized)
    {
        timer.start();
        SpaceCoords move = find_move(image.camera, params);
        move_atoms(image.atoms, move);
        move_point(image.center, move);
        move_connections(image.connect, move);
    }
    return ok;
}

//Масштабирование изображения
status zoom_camera(image_data &image, const scaling& params)
{
    if (image.initialized)
    {
        timer.start();
        float coeff = params.coeff > 0 ? 1.25 : 0.75;
        matrix4x4 matrix = move_matrix(image.center);
        matrix = mult_matrix(matrix, scale_matrix(coeff));
        matrix = mult_matrix(matrix, back_move_matrix(image.center));

        scale_connection(image.connect, matrix);
        scale_atoms(image.atoms, matrix, coeff);
        image.center = mult_vector(image.center, matrix);
    }
    return ok;
}

//Поворот изображения вокруг его центра
status rotate_image(image_data &image, const rotating& params)
{
    if (image.initialized)
    {
        timer.start();
        matrix4x4 rotate_matrix = create_rotate_matrix(image.camera, params, image.center);
        rotate_atoms(image.atoms, rotate_matrix);
        rotate_connections(image.connect, rotate_matrix);

        rotate_matrix = create_rotate_matrix(image.camera, params, SpaceCoords(0, 0, 0));
        rotate_sphere(image.global_sphere, rotate_matrix);
    }
    return ok;
}

//Инициализация изображения
//Выполняется единожды для каждой модели
//Время инициализации малосущественно. Цель - создание условий
//для дальнейшей быстрой обработки модели
status create_image(image_data &image, const model_data& model)
{
    Settings settings = image.settings;
    status result = ok;

    image_data new_image = image_init();
    {
        //Буфер-сфера для проведения операций
        new_image.tmp_sphere = create_sphere(result, settings.sphere_faces);

        //Глобальная сфера для описания атома
        if (result == ok)
            new_image.global_sphere = create_sphere(result, settings.sphere_faces);

        //Инициализация массива атомов
        if (result == ok)
            new_image.atoms = create_AtomArr(result, model.amount, model.atoms);

        //Установка центра изображения (для вращения модели)
        if (result == ok)
            new_image.center = find_center(new_image.atoms);

        //Подсчет и создание массива соединений
        //Первый элемент является буфером
        int con_size = count_connections(model.connections, model.amount) + 1;
        if (result == ok)
            new_image.connect = create_ConnectionArr(result, con_size);

        //Создание соединений между атомами
        if (result == ok)
            result = initialize_connections(model.connections, model.amount, new_image.connect, new_image.atoms, settings.cylinder_faces);

        //Обрезание невидимых частей соединения
        if (result == ok)
            cut_connections(new_image.connect, new_image.atoms);
    }

    if (result == ok)
    {
        //Сохранение старых настроек графики
        apply_settings(new_image, image.settings);
        new_image.initialized = true;

        if (image.initialized)
            image_free(image);
        image = new_image;

        timer.clear_data();
    }
    else
        image_free(new_image);
    return result;
}


//Отрисовка изображения
status draw_image(image_data &image, drawing& params)
{
    if (image.initialized)
    {
        clear_scene(params);
        draw_scene(image.atoms, image.connect, image.camera, params, \
                   image.global_sphere, image.tmp_sphere, image.settings.fill_type);

        timer.stop();
        params.label->setText("FPS: " + QString::number(timer.avg_fps()));
    }
    return ok;
}

//Изменение настроек графики
status apply_settings(image_data &image, const Settings& settings)
{
    return change_settings(image.settings, settings);
}

//Освобождение памяти из-под изображения
void image_free(image_data &image)
{
    if (image.initialized)
    {
        free_sphere(image.tmp_sphere);
        free_sphere(image.global_sphere);
        free_AtomArr(image.atoms);
        free_ConnectionArr(image.connect);
        image.initialized = false;
    }
}
