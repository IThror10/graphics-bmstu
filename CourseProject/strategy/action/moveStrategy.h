#include "strategy/action/actionStrategy.h"

class MoveAction: public ActionStrategy
{
public:
    MoveAction(const FlatCoords& coords);
    virtual bool action(std::shared_ptr<CompositObject> objectsSet, const FlatCoords& coords) override;
};
