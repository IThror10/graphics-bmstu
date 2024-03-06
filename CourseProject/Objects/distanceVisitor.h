#ifndef DISTANCEVISITOR_H
#define DISTANCEVISITOR_H

#include "Objects/baseVisitor.h"
#include "Objects/baseObject.h"
#include "Core/flatCoords.h"

class DistanceVisitor: public BaseVisitor
{
public:
    DistanceVisitor(const FlatCoords& coords);
    virtual void visitAtom(AtomObject&) override;
    virtual void visitLine(LineObject&) override;
    virtual void visitComposit(CompositObject&) override;

    ObjPtr closestAtom();
    ObjPtr closestLine();
    ObjPtr closestObject();

    float atom_len;
    float line_len;
protected:
    FlatCoords point;

    ObjPtr atom;
    bool new_atom;

    ObjPtr line;
    bool new_line;
};

#endif // DISTANCEVISITOR_H
