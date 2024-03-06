#include "model/command_main.h"
#include "model/image/image.h"

//Точка входа сервера
status complete_command(const command& instruction)
{
    status result = ok;
    action_params params = instruction.params;

    static image_data image = image_init();

    switch (instruction.task)
    {
    case to_move_figure:
        result = move_image(image, params.move_params);
        break;

    case to_rotate_figure:
        result = rotate_image(image, params.rotate_params);
        break;

    case to_zoom_camera:
        result = zoom_camera(image, params.scale_params);
        break;

    case to_create_model:
        result = create_image(image, params.model);
        break;

    case to_draw_scene:
        result = draw_image(image, params.canvas);
        break;

    case to_set_settings:
        result = apply_settings(image, params.settings);
        break;

    case to_delete:
        image_free(image);
        break;

    default:
        result = unknown_action;
    }
    return result;
}
