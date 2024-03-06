#include "Objects/baseObject.h"

BaseObject::BaseObject() :
    isSelected(false) {}
BaseObject::BaseObject(const FlatCoords& given, bool selected) :
    coords(given), isSelected(selected) {}
BaseObject::BaseObject(const BaseObject& given) :
    coords(given.coords), isSelected(given.isSelected) {}

bool BaseObject::isComposit() { return false; }
bool BaseObject::add(ObjPtr obj) { return false; }
bool BaseObject::remove(ObjIter iter) { return false; }
bool BaseObject::reset() { return false; }
int BaseObject::size() { return 1; }
