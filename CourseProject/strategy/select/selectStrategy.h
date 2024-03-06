#ifndef SELECTSTRATEGY_H
#define SELECTSTRATEGY_H

#include "Objects/compositObject.h"
class FlatCoords;

class SelectStrategy
{
public:
    ObjPtr returnSelected();
    virtual bool select(std::shared_ptr<CompositObject> objectsSet, const FlatCoords& position) = 0;

protected:
    ObjPtr pointed;
};

class SelectLine: public SelectStrategy
{
public:
    virtual bool select(std::shared_ptr<CompositObject> objectsSet, const FlatCoords& position) override;
};

class SelectAtom: public SelectStrategy
{
public:
    virtual bool select(std::shared_ptr<CompositObject> objectsSet, const FlatCoords& position) override;
};

class SelectAny: public SelectStrategy
{
public:
    virtual bool select(std::shared_ptr<CompositObject> objectsSet, const FlatCoords& position) override;
};

#endif // SELECTSTRATEGY_H
