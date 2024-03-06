#include "strategy/action/moveStrategy.h"
#include "Objects/moveVisitor.h"

MoveAction::MoveAction(const FlatCoords& coords)
    : ActionStrategy(coords, nullptr) {}

bool MoveAction::action(std::shared_ptr<CompositObject> objectsSet, const FlatCoords& coords)
{
    bool changed = false;
    if (coords != startPos)
    {
        MoveVisitor visitor(coords - startPos);
        startPos = coords;
        objectsSet->accept(visitor);
        changed = true;
    }
    return changed;
}
