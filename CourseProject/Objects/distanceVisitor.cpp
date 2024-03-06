#include "Objects/distanceVisitor.h"
#include "Objects/compositObject.h"
#include "Objects/atomObject.h"
#include "Objects/lineObject.h"

DistanceVisitor::DistanceVisitor(const FlatCoords& coords)
{
    this->atom = nullptr;
    this->line = nullptr;
    this->new_atom = false;
    this->new_line = false;

    AtomObject tmp;
    this->atom_len = tmp.radius - 5;
    this->line_len = 4;
    this->point = coords;
}

void DistanceVisitor::visitAtom(AtomObject& _atom)
{
    float len = _atom.coords.distance(point);
    if (len < this->atom_len)
    {
        this->atom_len = len;
        this->new_atom = true;
    }
}

void DistanceVisitor::visitLine(LineObject& line)
{
    FlatCoords p1 = line.atomStart->coords, p2 = line.atomEnd->coords;
    FlatCoords move = (p2 - p1) * 0.15;
    p1 += move; p2 -= move;
    float min_len = p2.distance(this->point), cur_len = p2.distance(this->point);
    if (cur_len < min_len)
        min_len = cur_len;

    FlatCoords normal = this->point.normalIntersect(p1, p2);
    if ((p1.y - normal.y) * (p2.y - normal.y) <= 0 && (p1.x - normal.x) * (p2.x - normal.x) <= 0)
    {
        cur_len = normal.distance(this->point);
        if (cur_len < min_len)
            min_len = cur_len;
    }

    if (min_len < line_len)
    {
        line_len = min_len;
        new_line = true;
    }
}

void DistanceVisitor::visitComposit(CompositObject &composit)
{
    for (ObjIter iter = composit.begin(); iter != composit.end(); iter++)
    {
        (*iter)->accept(*this);
        if (new_line)
        {
            line = *iter;
            new_line = false;
        }
        else if (new_atom)
        {
            atom = *iter;
            new_atom = false;
        }
    }
}

ObjPtr DistanceVisitor::closestAtom()
{
    return this->atom;
}

ObjPtr DistanceVisitor::closestLine()
{
    return this->line;
}

ObjPtr DistanceVisitor::closestObject()
{
    if (line_len < atom_len && line)
        return this->line;
    else
        return this->atom;
}
