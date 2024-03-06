#include "Interface/scene/baseScene.h"
#include "Interface/abstractFactory.h"

#include "strategy/select/selectStrategy.h"
#include "strategy/action/moveStrategy.h"
#include "strategy/action/removeStrategy.h"
#include "strategy/action/placeFigureAction.h"
#include "strategy/action/placeSelectedAction.h"
#include "strategy/action/LineAtomAction.h"
#include "strategy/action/lineSwapAction.h"

#include "Objects/compositObject.h"
#include "Objects/lineObject.h"

#include "mediator/flatCanvasMediator.h"
#include "Painter/molPainter.h"
#include "Objects/drawVisitor.h"
#include "builder/director.h"

#include <memory>
#include <QDebug>

BaseScene::BaseScene(void *_parent, const FlatCoords& position)
{
    this->parent = _parent;
    this->coords = position;

    this->clicked = false;
    this->composit = std::shared_ptr<CompositObject>(new CompositObject);

    menu = AbstractFactory::Instance()->createMenu(this, parent, position + FlatCoords(10, 10));

    flatCanvas = AbstractFactory::Instance()->createCanvas(parent, position + FlatCoords(10, 81), FlatCoords(741, 671));
    flatCanvas->setMediator(std::shared_ptr<CanvasMediator>(new FlatCanvasMediator(this)));

    this->actionFunc = nullptr;
    this->drawScene();
}

void BaseScene::doSelect(const FlatCoords& coords)
{
    if (this->selectFunc && this->selectFunc->select(composit, coords))
    {
        this->flatCanvas->clear();
        this->drawScene();
    }
}

void BaseScene::setSelectStategy(std::shared_ptr<SelectStrategy> strategy)
{
    this->selectFunc = strategy;
}

void BaseScene::doAction(const FlatCoords& coords)
{
    if (actionFunc && this->actionFunc->action(composit, coords))
    {
        this->flatCanvas->clear();
        this->drawScene();
    }
}

void BaseScene::setActionStrategy(std::shared_ptr<ActionStrategy> strategy, const FlatCoords& coords)
{
    if (strategy)
        actionFunc = strategy;
    else
    {
        ObjPtr menuSelected = menu->selectedFigure();
        ObjPtr pointedObj = selectFunc->returnSelected();
        if (menuSelected == nullptr)
            actionFunc = std::shared_ptr<ActionStrategy>(new RemoveAction(coords, pointedObj));
        else if (menuSelected->isComposit())
            actionFunc = std::shared_ptr<ActionStrategy>\
                    (new PlaceFigureAction(coords, pointedObj, menu->selectedAtom(), menuSelected->size() / 2));
        else
        {
            std::shared_ptr<AtomObject> menuAtom = menu->selectedAtom();
            std::shared_ptr<LineObject> line = std::dynamic_pointer_cast<LineObject>(menuSelected);
            std::shared_ptr<AtomObject> pAtom = std::dynamic_pointer_cast<AtomObject>(pointedObj);
            std::shared_ptr<LineObject> pLine = std::dynamic_pointer_cast<LineObject>(pointedObj);

            if (pLine)
                actionFunc = std::shared_ptr<ActionStrategy>(new LineSwapAction(pLine, line));
            else
                actionFunc = std::shared_ptr<ActionStrategy>\
                        (new PlaceSelectedAction(pAtom, line, menuAtom, coords));
        }
    }
    this->doAction(coords);
    this->drawScene();
}

void BaseScene::clearScene()
{
    this->composit->reset();
    this->flatCanvas->clear();
}

void BaseScene::drawScene()
{
    static molPainter painter(std::shared_ptr<PainterImp>(AbstractFactory::Instance()->createPainterImp()));

    DrawVisitor visitor(flatCanvas, &painter);
    if (composit)
        composit->accept(visitor);

    ObjPtr temp;
    if (actionFunc && (temp = actionFunc->returnActive()))
        temp->accept(visitor);

    this->flatCanvas->restoreSize();
}

void BaseScene::saveAction()
{
    if (actionFunc)
        composit->add(actionFunc->returnResult());
    actionFunc = nullptr;

    this->flatCanvas->clear();
    this->drawScene();
}

bool BaseScene::createModel(std::shared_ptr<BaseBuilder> builder)
{
    Director director(builder);
    return director.build(*this->composit);
}
