#include "strategy/action/placeFigureAction.h"
#include "Objects/atomObject.h"
#include "Objects/lineObject.h"

PlaceFigureAction::PlaceFigureAction(const FlatCoords& begin, ObjPtr _line, ObjPtr _atom, unsigned _angles)
    : ActionStrategy(begin, nullptr)
{
    this->angles = _angles;
    this->line = std::dynamic_pointer_cast<LineObject>(_line);
    this->atom = std::dynamic_pointer_cast<AtomObject>(_atom);
    if (line == nullptr && atom)
    {
        atom->coords = begin;
        line = std::shared_ptr<LineObject>(new LineObject(*atom, 1));
    }

    _active = CompositObject::createPolygon(angles, atom, line);
    _active->isSelected = true;
    this->tempObj = _active;
}

bool PlaceFigureAction::action(std::shared_ptr<CompositObject> objectsSet, const FlatCoords& coords)
{
    bool changed = false;
    FlatCoords p1 = line->atomStart->coords, p2 = line->atomEnd->coords;
    FlatCoords vect = p1 - p2, phi = p1 - coords;
    if (vect.angle(phi) > 180)
    {
        changed = true;
        std::shared_ptr<AtomObject> tmp = line->atomStart;
        line->atomStart = line->atomEnd;
        line->atomEnd = tmp;

        _active = CompositObject::createPolygon(angles, atom, line);
        _active->isSelected = true;
        this->tempObj = _active;
    }
    return changed;
}

ObjPtr PlaceFigureAction::returnActive()
{
    return this->_active;
}
