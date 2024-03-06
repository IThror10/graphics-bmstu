#include "Objects/drawVisitor.h"
#include "Painter/molPainter.h"
#include "Objects/baseObject.h"
#include "Objects/compositObject.h"

DrawVisitor::DrawVisitor(BaseCanvas *_canvas, molPainter *_painter)
    : canvas(_canvas), painter(_painter), status(start) {}

void DrawVisitor::visitAtom(AtomObject &atom)
{
    if (painter && canvas && status == atoms)
        painter->draw_atom(*canvas, atom);
}

void DrawVisitor::visitLine(LineObject &line)
{
    if (painter && canvas && status == lines)
        painter->draw_line(*canvas, line);
}

void DrawVisitor::visitComposit(CompositObject &composit)
{
    if (painter && canvas)
    {
        if (status == start)
            status = lines;

        bool selected = composit.isSelected;
        for (ObjIter iter = composit.begin(); iter != composit.end(); iter++)
        {
            bool was_selected = (*iter)->isSelected;
            (*iter)->isSelected = was_selected || selected;
            (*iter)->accept(*this);
            (*iter)->isSelected = was_selected;
        }

        status = atoms;
        for (ObjIter iter = composit.begin(); iter != composit.end(); iter++)
        {
            bool was_selected = (*iter)->isSelected;
            (*iter)->isSelected = was_selected || selected;
            (*iter)->accept(*this);
            (*iter)->isSelected = was_selected;
        }

        status = start;
    }
}
