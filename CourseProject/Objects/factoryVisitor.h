#ifndef FACTORYVISITOR_H
#define FACTORYVISITOR_H

#include "Objects/baseVisitor.h"
#include "strategy/action/actionStrategy.h"

class FactoryVisitor: public BaseVisitor
{
public:
    virtual void visitAtom(AtomObject &atom) override;
    virtual void visitLine(LineObject &line) override;
    virtual void visitComposit(CompositObject &composit) override;

    std::shared_ptr<ActionStrategy> create(ObjPtr pointed, ObjPtr line, const FlatCoords& coords);

public:
    std::shared_ptr<ActionStrategy> strategy;
};
#endif // FACTORYVISITOR_H
