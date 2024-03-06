#include "strategy/action/removeStrategy.h"
#include "Objects/baseObject.h"
#include "Objects/moveVisitor.h"

RemoveAction::RemoveAction(const FlatCoords& coords, ObjPtr obj)
    : ActionStrategy(coords, obj) {}

bool RemoveAction::action(std::shared_ptr<CompositObject> objectsSet, const FlatCoords& coords)
{
    bool changed = false;
    if (tempObj)
    {
        changed = true;
        RemoveVisitor visitor(tempObj);
        objectsSet->accept(visitor);
    }
    tempObj = nullptr;
    return changed;
}
