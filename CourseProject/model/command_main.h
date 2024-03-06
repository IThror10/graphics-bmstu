#ifndef __MODELMAIN_H__
#define __MODELMAIN_H__

#include "model/inc/status.h"

#include "model/instruction/moving.h"
#include "model/instruction/rotating.h"
#include "model/instruction/model_data.h"
#include "model/instruction/drawing.h"
#include "model/instruction/scaling.h"
#include "Meta/settings.h"

typedef enum
{
    no_command,
    to_move_figure,
    to_rotate_figure,
    to_zoom_camera,
    to_create_model,
    to_draw_scene,
    to_set_settings,
    to_delete,
} action;

typedef union
{
    moving move_params;
    rotating rotate_params;
    scaling scale_params;
    model_data model;
    drawing canvas;
    Settings settings;
} action_params;

struct command
{
    action task;
    action_params params;
};

status complete_command(const command& instruction);

#endif //__MODELMAIN_H__
