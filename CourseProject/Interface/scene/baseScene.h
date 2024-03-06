#ifndef BASESCENE_H
#define BASESCENE_H

#include <memory>
#include "Core/flatCoords.h"

class CompositObject;
class CanvasMenu;
class BaseCanvas;

#include "strategy/select/selectStrategy.h"
#include "strategy/action/actionStrategy.h"

class BaseBuilder;

class BaseScene
{
public:
    BaseScene()=delete;
    BaseScene(void *parent, const FlatCoords& position);

    void doSelect(const FlatCoords& coords);
    void setSelectStategy(std::shared_ptr<SelectStrategy> selectFunc);

    void doAction(const FlatCoords& coords);
    void setActionStrategy(std::shared_ptr<ActionStrategy> actionFunc, const FlatCoords& coords = FlatCoords(0, 0));
    void saveAction();

    void clearScene();
    bool createModel(std::shared_ptr<BaseBuilder> builder);

protected:
    void *parent;
    BaseCanvas *flatCanvas;
    CanvasMenu *menu;

    std::shared_ptr<CompositObject> composit;
    void drawScene();

    std::shared_ptr<SelectStrategy> selectFunc;
    std::shared_ptr<ActionStrategy> actionFunc;

private:
    bool clicked;
    FlatCoords coords;
};
#endif // BASESCENE_H
