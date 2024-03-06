#include "Objects/moveVisitor.h"
#include "Objects/atomObject.h"
#include "Objects/lineObject.h"
#include "Objects/compositObject.h"

MoveVisitor::MoveVisitor(const FlatCoords& coords)
    : move(coords) {}

void MoveVisitor::visitAtom(AtomObject &atom)
{
    atom.coords += move;
}

void MoveVisitor::visitLine(LineObject &line)
{

}

void MoveVisitor::visitComposit(CompositObject &composit)
{
    for (ObjIter iter = composit.begin(); iter != composit.end(); iter++)
        (*iter)->accept(*this);
}



RemoveVisitor::RemoveVisitor(ObjPtr object)
    : removing(object), remove_cur(false) {}

void RemoveVisitor::visitAtom(AtomObject &atom)
{
    remove_cur = false;
}

void RemoveVisitor::visitLine(LineObject &line)
{
    if (line.atomStart == removing || line.atomEnd == removing)
        remove_cur = true;
    else
        remove_cur = false;
}

void RemoveVisitor::visitComposit(CompositObject &composit)
{
    ObjIter end = composit.end();
    for (ObjIter iter = composit.begin(); iter != end && composit.size(); iter++)
    {
        if (iter->get())
            (*iter)->accept(*this);
        if (*iter == removing || remove_cur)
        {
            composit.remove(iter);
            iter = composit.begin();
            end = composit.end();
            remove_cur = false;
        }
    }
}
