#ifndef LINEOBJECT_H
#define LINEOBJECT_H

#include "Objects/baseObject.h"
class AtomObject;

class LineObject: public BaseObject
{
public:
    unsigned linesCnt;
    float width;

    std::shared_ptr<AtomObject> atomStart;
    std::shared_ptr<AtomObject> atomEnd;

    LineObject(const AtomObject& atom, unsigned linesAmount);
    LineObject(const AtomObject& atom, const FlatCoords& vector, unsigned linesAmount);
    LineObject(std::shared_ptr<AtomObject>& start, std::shared_ptr<AtomObject>& end, unsigned linesAmount);
    LineObject(std::shared_ptr<AtomObject>& start, const AtomObject& end, unsigned linesAmount);
    LineObject(const LineObject&);
    LineObject& operator=(const LineObject&);

    void accept(BaseVisitor&) override;
    ObjPtr clone() const override;

    static float getStdLen();
private:
    static float stdWidth;
    static float stdLen;
};

#endif // LINEOBJECT_H
