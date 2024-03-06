#ifndef CANVASMENU_H
#define CANVASMENU_H

#include "Core/flatCoords.h"
#include "Interface/button/pushButton.h"
#include "Objects/atomObject.h"
#include "Interface/scene/baseScene.h"

class CanvasMenu
{
public:
    CanvasMenu()=delete;
    CanvasMenu(BaseScene *scene, void *parent, const FlatCoords& coords);
    ObjPtr selectedFigure();
    std::shared_ptr<AtomObject> selectedAtom();

protected:
    AtomObject _activeAtom;
    ObjPtr _activeFigure;
    FlatCoords position;

    BaseScene *scene;
    void *parent;

protected:
    PushButton *activeFigureButton;
    PushButton *activeAtomButton;

    PushButton *single_line;
    PushButton *double_line;
    PushButton *tripple_line;

    PushButton *triangle;
    PushButton *square;
    PushButton *pentagon;
    PushButton *geksagon;
    PushButton *septagon;

    PushButton *remove;
    PushButton *clear;

    PushButton *c_elem;
    PushButton *h_elem;
    PushButton *n_elem;
    PushButton *o_elem;
    PushButton *s_elem;
    PushButton *choose_elem;
};

#endif // CANVASMENU_H
