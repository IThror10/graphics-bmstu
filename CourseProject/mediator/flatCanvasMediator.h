#ifndef FLATCANVASMEDIATOR_H
#define FLATCANVASMEDIATOR_H

#include "mediator/canvasMediator.h"

class FlatCanvasMediator: public CanvasMediator
{
public:
    FlatCanvasMediator(BaseScene *scene);
    virtual void left_clicked(const FlatCoords& coords) override;
    virtual void right_clicked(const FlatCoords& coords) override;;
    virtual void released() override;
    virtual void mouse_moved(const FlatCoords& coords) override;
    virtual void wheel_event(int up, int left) override;

protected:
    BaseScene *scene;
    bool clicked;
};

#endif // FLATCANVASMEDIATOR_H
