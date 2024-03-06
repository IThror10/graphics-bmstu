#ifndef QTFACTORY_H
#define QTFACTORY_H

#include "Interface/abstractFactory.h"

class QtFactory: public AbstractFactory
{
public:
    virtual PushButton* createButton() override;
    virtual CanvasMenu* createMenu(BaseScene *scene, void *parent, const FlatCoords& coords) override;
    virtual BaseCanvas* createCanvas(void *parent, const FlatCoords& coords, const FlatCoords& size) override;
    virtual PainterImp* createPainterImp() override;

    virtual BaseUserDialog* createUserDialog() override;
};

#endif // QTFACTORY_H
