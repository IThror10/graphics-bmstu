#include "Interface/QtFactory.h"

#include "Interface/button/qtButton.h"
#include "Interface/menu/qtCanvasMenu.h"
#include "Interface/canvas/qtCanvas.h"
#include "Painter/QtPainterImp.h"

class QtUserDialog;

PushButton* QtFactory::createButton()
{
    return new QtButton;
}

CanvasMenu* QtFactory::createMenu(BaseScene *scene, void *parent, const FlatCoords& coords)
{
    return new QtCanvasMenu(scene, parent, coords);
}

BaseCanvas* QtFactory::createCanvas(void *parent, const FlatCoords& coords, const FlatCoords& size)
{
    return new QtCanvas(parent, coords, size);
}

PainterImp* QtFactory::createPainterImp()
{
    return new QtPainterImp;
}

BaseUserDialog* QtFactory::createUserDialog()
{
    return nullptr;
//    return new QtUserDialog;
}
