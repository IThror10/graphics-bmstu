#include "strategy/action/lineSwapAction.h"
#include "Objects/lineObject.h"

LineSwapAction::LineSwapAction(std::shared_ptr<LineObject> pointed, std::shared_ptr<LineObject> selected)
    : ActionStrategy(FlatCoords(0, 0), std::dynamic_pointer_cast<BaseObject>(pointed))
{
    this->worked = true;
    pointed->linesCnt = selected->linesCnt;
    this->tempObj->isSelected = true;
}

bool LineSwapAction::action(std::shared_ptr<CompositObject> objectsSet, const FlatCoords& coords)
{
    bool changed = this->worked;
    this->worked = false;
    return changed;
}
