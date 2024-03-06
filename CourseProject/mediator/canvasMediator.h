#ifndef CANVASMEDIATOR_H
#define CANVASMEDIATOR_H

#include <memory>
class FlatCoords;
class BaseScene;

class CanvasMediator
{
public:
    CanvasMediator(BaseScene *scene);
    virtual void left_clicked(const FlatCoords& coords) = 0;
    virtual void right_clicked(const FlatCoords& coords) = 0;
    virtual void released() = 0;
    virtual void mouse_moved(const FlatCoords& coords) = 0;
    virtual void wheel_event(int up, int left) = 0;

protected:
    BaseScene *scene;
    bool _left;
    bool _right;
};

#endif // CANVASMEDIATOR_H
