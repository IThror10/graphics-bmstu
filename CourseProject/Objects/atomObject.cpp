#include "Objects/atomObject.h"

float AtomObject::stdRadius = 25;

AtomObject::AtomObject()
{
    this->name = "C";
    this->color = RGBColor(128, 128, 128);
    this->radius = this->stdRadius;
    this->isSelected = false;
}

AtomObject::AtomObject(const FlatCoords& _coords, const std::string& _name)
    : BaseObject(_coords)
{
    this->name = _name;
    this->color = RGBColor(128, 128, 128);
    this->radius = this->stdRadius;
    this->isSelected = false;
}

AtomObject::AtomObject(const AtomObject& given)
    : BaseObject(given.coords, given.isSelected)
{
    this->name = given.name;
    this->radius = given.radius;
    this->color = given.color;
}

AtomObject& AtomObject::operator=(const AtomObject& given)
{
    this->coords = given.coords;
    this->isSelected = given.isSelected;
    this->name = given.name;
    this->radius = given.radius;
    this->color = given.color;
    return *this;
}

void AtomObject::accept(BaseVisitor& visitor)
{
    visitor.visitAtom(*this);
}

ObjPtr AtomObject::clone() const
{
    return ObjPtr(new AtomObject(*this));
}
