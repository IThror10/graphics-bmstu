#include "Objects/compositObject.h"
#include "Objects/lineObject.h"
#include "Objects/atomObject.h"

CompositObject::CompositObject(const CompositObject& given)
{
    for (CObjIter iter = given.cbegin(); iter != given.cend(); iter++)
        this->data.push_back((*iter)->clone());
}

CompositObject& CompositObject::operator=(const CompositObject& given)
{
    data.clear();
    for (CObjIter iter = given.cbegin(); iter != given.cend(); iter++)
        this->data.push_back((*iter)->clone());
    return *this;
}

bool CompositObject::isComposit()
{
    return true;
}

bool CompositObject::add(ObjPtr given)
{
    if (given && given->isComposit())
    {
        std::shared_ptr<CompositObject> other = std::dynamic_pointer_cast<CompositObject>(given);
        if (other) for (ObjIter iter = other->begin(); iter != other->end(); iter++)
            this->add(*iter);
    }
    else if (given)
    {
        bool repeat = false;
        for (ObjIter iter = this->begin(); iter != this->end(); iter++)
            if (*iter == given)
                repeat = true;
        if (repeat == false)
            data.push_back(given);
    }
    return true;
}

bool CompositObject::remove(ObjIter iter)
{
    data.erase(iter);
    return true;
}

bool CompositObject::reset()
{
    this->data.clear();
    return true;
}


void CompositObject::accept(BaseVisitor& visitor)
{
    visitor.visitComposit(*this);
}

ObjPtr CompositObject::clone() const
{
    return ObjPtr(new CompositObject(*this));
}

ObjIter CompositObject::begin()
{
    return this->data.begin();
}

ObjIter CompositObject::end()
{
    return this->data.end();
}

CObjIter CompositObject::cbegin() const
{
    return this->data.cbegin();
}

CObjIter CompositObject::cend() const
{
    return this->data.cend();
}

int CompositObject::size()
{
    return this->data.size();
}

std::vector<LineObject> CompositObject::getLines() const
{
    std::vector<LineObject> result;
    for (int i = 0; i < data.size(); i++)
    {
        std::shared_ptr<LineObject> line = std::dynamic_pointer_cast<LineObject>(data[i]);
        if (line)
            result.push_back(*line);
    }
    return result;
}

std::vector<AtomObject> CompositObject::getAtoms() const
{
    std::vector<AtomObject> result;
    for (int i = 0; i < data.size(); i++)
    {
        std::shared_ptr<AtomObject> atom = std::dynamic_pointer_cast<AtomObject>(data[i]);
        if (atom)
            result.push_back(*atom);
    }
    return result;
}

ObjPtr CompositObject::createPolygon(unsigned angles, std::shared_ptr<AtomObject> atom, std::shared_ptr<LineObject> line)
{
    ObjPtr result(new CompositObject);

    if (line == nullptr)
        line = std::shared_ptr<LineObject>(new LineObject(*atom, FlatCoords(1, 0), 1));

    if (angles >= 3)
    {
        std::shared_ptr<AtomObject> begin = line->atomStart, prev = line->atomEnd, next = nullptr;
        FlatCoords curPoint = prev->coords - begin->coords, from = prev->coords;

        result->add(begin);
        result->add(prev);
        result->add(line);

        float angle = 360 / angles;
        for (int i = 0; i < angles - 2; i++)
        {
            curPoint.rotate(angle);
            from += curPoint;
            next = std::shared_ptr<AtomObject>(new AtomObject(*atom));
            next->coords = from;

            result->add(next);
            result->add(std::shared_ptr<LineObject>(new LineObject(prev, next, 1)));
            prev = next;
        }
        result->add(std::shared_ptr<LineObject>(new LineObject(begin, prev, 1)));
    }
    return result;
}
