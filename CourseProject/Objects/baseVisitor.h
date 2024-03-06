#ifndef VISITOR_H
#define VISITOR_H

class AtomObject;
class LineObject;
class CompositObject;

class BaseVisitor
{
public:
    virtual void visitAtom(AtomObject&) = 0;
    virtual void visitLine(LineObject&) = 0;
    virtual void visitComposit(CompositObject&) = 0;
};
#endif // VISITOR_H
