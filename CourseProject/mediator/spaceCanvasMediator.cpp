#include "mediator/spaceCanvasMediator.h"
#include "Interface/scene/baseScene.h"
#include "strategy/action/moveStrategy.h"
#include "model/command_main.h"

SpaceCanvasMediator::SpaceCanvasMediator(ProgramWindow *ProgramWindow)
    : CanvasMediator(nullptr)
{
    this->window = ProgramWindow;
    _left = false;
    _right = false;
}

void SpaceCanvasMediator::left_clicked(const FlatCoords& coords)
{
    if (!_left)
    {
        prev = coords;
        _left = true;
    }
}

void SpaceCanvasMediator::right_clicked(const FlatCoords& coords)
{
    if (!_right)
    {
        _right = true;
        prev = coords;
    }
}

void SpaceCanvasMediator::released()
{
    _left = false;
    _right = false;
}

void SpaceCanvasMediator::mouse_moved(const FlatCoords& coords)
{
    command instruction;
    if (_left)
    {
        instruction.task = to_rotate_figure;
        rotating params;
        params.ox_rotate = (prev.x - coords.x) / 5;
        params.oy_rotate = 0;
        params.oz_rotate = -(prev.y - coords.y) / 5;
        instruction.params.rotate_params = params;
    }
    else if (_right)
    {
        instruction.task = to_move_figure;
        moving params;
        params.dx = coords.x - prev.x;
        params.dy = coords.y - prev.y;
        instruction.params.move_params = params;
    }
    else
    {
        prev = coords;
        instruction.task = no_command;
    }

    if (instruction.task != no_command && complete_command(instruction) == ok)
        complete_command(window->draw_command);
    prev = coords;
}

void SpaceCanvasMediator::wheel_event(int up, int left)
{
    const float N = 3;
    command instruction;
    instruction.task = to_zoom_camera;
    scaling params;
    params.coeff = up + left;
    instruction.params.scale_params = params;
    complete_command(instruction);
    complete_command(window->draw_command);
}
