#ifndef MOVEVISITOR_H
#define MOVEVISITOR_H

#include "Core/flatCoords.h"
#include "Objects/baseVisitor.h"
#include "Objects/baseObject.h"

class MoveVisitor: public BaseVisitor
{
public:
    MoveVisitor(const FlatCoords& coords);
    virtual void visitAtom(AtomObject&) override;
    virtual void visitLine(LineObject&) override;
    virtual void visitComposit(CompositObject&) override;
protected:
    FlatCoords move;
};

class RemoveVisitor: public BaseVisitor
{
public:
    RemoveVisitor(ObjPtr object);
    virtual void visitAtom(AtomObject&) override;
    virtual void visitLine(LineObject&) override;
    virtual void visitComposit(CompositObject&) override;
protected:
    ObjPtr removing;
    bool remove_cur;
};

#endif // MOVEVISITOR_H
