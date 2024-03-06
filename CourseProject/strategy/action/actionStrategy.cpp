#include "strategy/action/actionStrategy.h"
#include "Objects/moveVisitor.h"
#include "Objects/compositObject.h"

ObjPtr ActionStrategy::returnResult()
{
    if (tempObj)
        tempObj->isSelected = false;
    return this->tempObj;
}

ActionStrategy::ActionStrategy(const FlatCoords& begin, ObjPtr obj)
    : startPos(begin), tempObj(obj) {}


ObjPtr ActionStrategy::returnActive()
{
    return nullptr;
}
