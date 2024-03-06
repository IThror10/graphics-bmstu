#include "strategy/action/placeSelectedAction.h"
#include "Objects/distanceVisitor.h"
#include "Objects/atomObject.h"
#include "Objects/lineObject.h"

PlaceSelectedAction::PlaceSelectedAction(std::shared_ptr<AtomObject> _selected, std::shared_ptr<LineObject> _line,\
                   std::shared_ptr<AtomObject> _atom, const FlatCoords& coords)
    : ActionStrategy(coords, std::shared_ptr<CompositObject>(new CompositObject))
{
    add = _atom;
    line = _line;
    init = _selected;
    if (init == nullptr)
    {
        init = std::shared_ptr<AtomObject>(new AtomObject(*_atom));
        init->coords = coords;
        add->coords = coords;
    }
    else
        add->coords = init->coords;

    line->atomStart = init;
    copy = std::shared_ptr<AtomObject>(new AtomObject(*init));

    isline = true;
    angle = -30;
    tempObj->isSelected = true;
    tempObj->add(init);
}

bool PlaceSelectedAction::action(std::shared_ptr<CompositObject> objectsSet, const FlatCoords& coords)
{
    bool changed = false;
    if (init->coords.distance(coords) - init->radius < 0)
    {
        if (isline)
        {
            isline = false;
            changed = true;
            angle = -30;

            tempObj->reset();
            tempObj->add(init);

            *init = *add;
            line->atomStart = init;
            line->atomEnd = nullptr;
        }
    }
    else
    {
        DistanceVisitor visitor(coords);
        objectsSet->accept(visitor);
        ObjPtr newAtom = visitor.closestAtom();
        if (newAtom && newAtom != line->atomEnd)
        {
            changed = true;
            isline = true;
            *init = *add;

            tempObj->reset();
            tempObj->add(init);
            tempObj->add(line);
            tempObj->add(newAtom);
            line->atomEnd = std::dynamic_pointer_cast<AtomObject>(newAtom);
        }
        else
        {
            FlatCoords vect = coords - line->atomStart->coords;
            float tmp_angle = vect.angle(FlatCoords(1, 0));
            tmp_angle = int((tmp_angle + 15) / 30) * 30 % 360;
            if (angle != tmp_angle || line->atomEnd == nullptr)
            {
                changed = true;
                isline = true;
                angle = tmp_angle;
                *init = *copy;

                FlatCoords move(1, 0);
                move = move.createVector(LineObject::getStdLen());
                move.rotate(-angle);
                line->atomEnd = std::shared_ptr<AtomObject>(new AtomObject(*add));
                line->atomEnd->coords = line->atomStart->coords + move;

                tempObj->reset();
                tempObj->add(init);
                tempObj->add(line);
                tempObj->add(line->atomEnd);
            }
        }
    }
    return changed;
}

ObjPtr PlaceSelectedAction::returnActive()
{
    return this->tempObj;
}
