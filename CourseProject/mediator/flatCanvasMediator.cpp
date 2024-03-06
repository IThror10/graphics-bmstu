#include "mediator/flatCanvasMediator.h"
#include "Interface/scene/baseScene.h"
#include "strategy/action/moveStrategy.h"

FlatCanvasMediator::FlatCanvasMediator(BaseScene *_scene)
    : CanvasMediator(_scene)
{
    this->scene = _scene;
    _left = false;
    _right = false;
}

void FlatCanvasMediator::left_clicked(const FlatCoords& coords)
{
    if (!_right)
    {
        if (scene)
            scene->setActionStrategy(nullptr, coords);
        _left = true;
    }
}

void FlatCanvasMediator::right_clicked(const FlatCoords& coords)
{
    if (!_left)
    {
        if (scene)
            scene->setActionStrategy(std::shared_ptr<MoveAction>(new MoveAction(coords)), coords);
        _right = true;
    }
}

void FlatCanvasMediator::released()
{
    if (_left || _right)
    {
        if (scene)
            scene->saveAction();
        _left = false;
        _right = false;
    }
}

void FlatCanvasMediator::mouse_moved(const FlatCoords& coords)
{
    if (scene)
    {
        if (_left || _right)
            scene->doAction(coords);
        else
            scene->doSelect(coords);
    }
}

void FlatCanvasMediator::wheel_event(int up, int left)
{
    ;
}
