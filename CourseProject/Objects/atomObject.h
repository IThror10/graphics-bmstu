#ifndef ATOMOBJECT_H
#define ATOMOBJECT_H

#include "Objects/baseObject.h"
#include "Core/rgbColor.h"
#include <iostream>

class AtomObject: public BaseObject
{
public:
    std::string name;
    float radius;
    RGBColor color;

    AtomObject();
    AtomObject(const FlatCoords&, const std::string& name);
    AtomObject(const AtomObject&);
    AtomObject& operator=(const AtomObject&);

    void accept(BaseVisitor&) override;
    ObjPtr clone() const override;

private:
    static float stdRadius;
};

#endif // ATOMOBJECT_H
