#ifndef ABSTRACTFACTORY_H
#define ABSTRACTFACTORY_H

#include <memory>
class AbstractFactory;
using Factory = std::shared_ptr<AbstractFactory>;

//Generated classes
#include "Interface/button/pushButton.h"
#include "Interface/menu/canvasMenu.h"
#include "Interface/canvas/baseCanvas.h"
#include "Painter/PainterImp.h"

class BaseCanvas;
class BaseUserDialog;
//Template Buttons

class AbstractFactory
{
public:
    static Factory Instance();

    virtual PushButton* createButton() = 0;
    virtual CanvasMenu* createMenu(BaseScene *scene, void *parent, const FlatCoords& coords) = 0;
    virtual BaseCanvas* createCanvas(void *parent, const FlatCoords& coords, const FlatCoords& size) = 0;

    virtual PainterImp* createPainterImp() = 0;
    virtual BaseUserDialog* createUserDialog() = 0;

protected:
    AbstractFactory()=default;
    AbstractFactory& operator=(const AbstractFactory&) = delete;
    static Factory _instance;
};

#endif // ABSTRACTFACTORY_H
