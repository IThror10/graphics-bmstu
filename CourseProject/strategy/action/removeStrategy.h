#ifndef REMOVESTRATEGY_H
#define REMOVESTRATEGY_H

#include "strategy/action/actionStrategy.h"

class RemoveAction: public ActionStrategy
{
public:
    RemoveAction(const FlatCoords& coords, ObjPtr obj);
    virtual bool action(std::shared_ptr<CompositObject> objectsSet, const FlatCoords& coords) override;
};

#endif // REMOVESTRATEGY_H
