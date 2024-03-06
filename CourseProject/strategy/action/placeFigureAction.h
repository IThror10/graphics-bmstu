#ifndef PLACEFIGUREACTION_H
#define PLACEFIGUREACTION_H

#include "strategy/action/actionStrategy.h"

class PlaceFigureAction: public ActionStrategy
{
public:
    PlaceFigureAction(const FlatCoords& begin, ObjPtr line, ObjPtr atom, unsigned angles);
    virtual bool action(std::shared_ptr<CompositObject> objectsSet, const FlatCoords& coords) override;
    virtual ObjPtr returnActive() override;
protected:
    ObjPtr _active;
    unsigned angles;
    std::shared_ptr<LineObject> line;
    std::shared_ptr<AtomObject> atom;
};

#endif // PLACEFIGUREACTION_H
