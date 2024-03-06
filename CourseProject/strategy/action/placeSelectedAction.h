#ifndef PLACESELECTEDACTION_H
#define PLACESELECTEDACTION_H

#include "strategy/action/actionStrategy.h"

class PlaceSelectedAction: public ActionStrategy
{
public:
    PlaceSelectedAction(std::shared_ptr<AtomObject> _selected, std::shared_ptr<LineObject> _line,\
                        std::shared_ptr<AtomObject> _atom, const FlatCoords& coords);
    virtual bool action(std::shared_ptr<CompositObject> objectsSet, const FlatCoords& coords) override;
    virtual ObjPtr returnActive() override;
protected:
    bool isline;
    float angle;
    std::shared_ptr<LineObject> line;
    std::shared_ptr<AtomObject> add;
    std::shared_ptr<AtomObject> init;
    std::shared_ptr<AtomObject> copy;
};

#endif // PLACESELECTEDACTION_H
