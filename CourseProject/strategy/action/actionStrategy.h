#ifndef ACTIONSTRATEGY_H
#define ACTIONSTRATEGY_H

#include "Objects/compositObject.h"
#include "Core/flatCoords.h"

class ActionStrategy
{
public:
    ActionStrategy(const FlatCoords& begin, ObjPtr obj);
    virtual bool action(std::shared_ptr<CompositObject> objectsSet, const FlatCoords& coords) = 0;
    virtual ObjPtr returnActive();
    ObjPtr returnResult();

protected:
    ObjPtr tempObj;
    FlatCoords startPos;
};

#endif // ACTIONSTRATEGY_H
