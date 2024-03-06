#ifndef LINEATOMACTION_H
#define LINEATOMACTION_H

#include "strategy/action/actionStrategy.h"

class LineAtomAction: public ActionStrategy
{
public:
    LineAtomAction(std::shared_ptr<AtomObject> atom, std::shared_ptr<LineObject> line,\
                   std::shared_ptr<AtomObject> add, const FlatCoords& coords);
    virtual bool action(std::shared_ptr<CompositObject> objectsSet, const FlatCoords& coords) override;
    virtual ObjPtr returnActive() override;
protected:
    std::shared_ptr<LineObject> line;
    std::shared_ptr<AtomObject> atomAdd;
    std::shared_ptr<AtomObject> atomBeg;
};

#endif // LINEATOMACTION_H
