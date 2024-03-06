#ifndef SPACECANVASMEDIATOR_H
#define SPACECANVASMEDIATOR_H

#include "mediator/canvasMediator.h"
#include "Core/flatCoords.h"
#include "programwindow.h"

class SpaceCanvasMediator: public CanvasMediator
{
public:
    SpaceCanvasMediator(ProgramWindow *ProgramWindow);
    virtual void left_clicked(const FlatCoords& coords) override;
    virtual void right_clicked(const FlatCoords& coords) override;;
    virtual void released() override;
    virtual void mouse_moved(const FlatCoords& coords) override;
    virtual void wheel_event(int up, int left) override;

protected:
    ProgramWindow *window;
    FlatCoords prev;
    BaseScene *scene;
    bool clicked;
};

#endif // SPACECANVASMEDIATOR_H
