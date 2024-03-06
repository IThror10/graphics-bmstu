#ifndef DRAWVISITOR_H
#define DRAWVISITOR_H

class BaseCanvas;
class molPainter;
#include "Objects/baseVisitor.h"

class DrawVisitor: public BaseVisitor
{
    typedef enum
    {
        start,
        lines,
        atoms
    } drawStatus;

public:
    DrawVisitor(BaseCanvas *canvas, molPainter *painter);
    virtual void visitAtom(AtomObject&) override;
    virtual void visitLine(LineObject&) override;
    virtual void visitComposit(CompositObject&) override;
protected:
    BaseCanvas *canvas;
    molPainter *painter;
    drawStatus status;
};

#endif // DRAWVISITOR_H
