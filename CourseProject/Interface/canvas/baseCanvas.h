#ifndef BASECANVAS_H
#define BASECANVAS_H

#include "Objects/compositObject.h"
#include "mediator/canvasMediator.h"
#include "Core/flatCoords.h"

class BaseCanvas
{
public:
    BaseCanvas(void *parent, const FlatCoords& coords, const FlatCoords& size);
    virtual void clear() = 0;
    virtual void restoreSize() = 0;
    void setMediator(std::shared_ptr<CanvasMediator> mediator);

protected:
    void *parent;
    FlatCoords position;
    FlatCoords mySize;
    std::shared_ptr<CanvasMediator> mediator;
};

#endif // BASECANVAS_H
