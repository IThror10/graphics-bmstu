#ifndef LINESWAPACTION_H
#define LINESWAPACTION_H

#include "strategy/action/actionStrategy.h"
#include "Objects/baseObject.h"

class LineSwapAction: public ActionStrategy
{
public:
    LineSwapAction(std::shared_ptr<LineObject> pointed, std::shared_ptr<LineObject> selected);
    virtual bool action(std::shared_ptr<CompositObject> objectsSet, const FlatCoords& coords) override;
protected:
    bool worked;
};

#endif // LINESWAPACTION_H
