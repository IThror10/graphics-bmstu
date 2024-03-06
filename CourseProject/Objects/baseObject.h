#ifndef BASEOBJECT_H
#define BASEOBJECT_H

#include "Core/flatCoords.h"
#include "Objects/baseVisitor.h"

#include <memory>
#include <vector>

class BaseObject;
using ObjPtr = std::shared_ptr<BaseObject>;
using ObjVect = std::vector<ObjPtr>;
using ObjIter = ObjVect::iterator;
using CObjIter = ObjVect::const_iterator;

class BaseObject
{
public:
    FlatCoords coords;
    bool isSelected;

    BaseObject();
    BaseObject(const FlatCoords&, bool selected = false);
    BaseObject(const BaseObject& given);

    virtual bool isComposit();
    virtual bool add(ObjPtr);
    virtual bool remove(ObjIter);
    virtual bool reset();
    virtual int size();

    virtual void accept(BaseVisitor&) = 0;
    virtual ObjPtr clone() const = 0;
};

#endif // BASEOBJECT_H
