#ifndef REMOVEVISITOR_H
#define REMOVEVISITOR_H

#include "Objects/baseVisitor.h"
#include "Objects/baseObject.h"
#include <memory>

class RemoveVisitor: public BaseVisitor
{
public:
    RemoveVisitor(std::shared_ptr<>ObjPtr removing);
    virtual void visitAtom(AtomObject&) override;
    virtual void visitLine(LineObject&) override;
    virtual void visitComposit(CompositObject&) override;
protected:
    std::shared_ptr<CompositObject> composit;
};

#endif // REMOVEVISITOR_H
