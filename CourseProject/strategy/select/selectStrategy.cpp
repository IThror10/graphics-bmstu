#include "strategy/select/selectStrategy.h"
#include "Objects/distanceVisitor.h"

ObjPtr SelectStrategy::returnSelected()
{
    ObjPtr ret = pointed;
    if (pointed)
    {
        pointed->isSelected = false;
        pointed = nullptr;
    }
    return ret;
}

bool SelectAtom::select(std::shared_ptr<CompositObject> objectsSet, const FlatCoords& position)
{
    bool updated = false;

    DistanceVisitor visitor(position);
    objectsSet->accept(visitor);
    ObjPtr candidat = visitor.closestAtom();

    if (pointed != candidat)
    {
        if (pointed)
            pointed->isSelected = false;
        pointed = candidat;
        updated = true;
        if (pointed)
            pointed->isSelected = true;
    }
    return updated;
}

bool SelectLine::select(std::shared_ptr<CompositObject> objectsSet, const FlatCoords& position)
{
    bool updated = false;

    DistanceVisitor visitor(position);
    objectsSet->accept(visitor);
    ObjPtr candidat = visitor.closestLine();

    if (pointed != candidat)
    {
        if (pointed)
            pointed->isSelected = false;
        pointed = candidat;
        updated = true;
        if (pointed)
            pointed->isSelected = true;
    }
    return updated;
}

bool SelectAny::select(std::shared_ptr<CompositObject> objectsSet, const FlatCoords& position)
{
    bool updated = false;

    DistanceVisitor visitor(position);
    objectsSet->accept(visitor);
    ObjPtr candidat = visitor.closestObject();

    if (pointed != candidat)
    {
        if (pointed)
            pointed->isSelected = false;
        pointed = candidat;
        updated = true;
        if (pointed)
            pointed->isSelected = true;
    }
    return updated;
}
