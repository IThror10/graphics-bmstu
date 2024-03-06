#include "Objects/lineObject.h"
#include "Objects/atomObject.h"
#include "Objects/compositObject.h"

float LineObject::stdWidth = 4;
float LineObject::stdLen = 100;

LineObject::LineObject(const AtomObject& atom, unsigned linesAmount)
{
    this->linesCnt = linesAmount;
    this->width = stdWidth;

    this->atomStart = std::shared_ptr<AtomObject>(new AtomObject(atom));
    this->atomEnd = std::shared_ptr<AtomObject>(new AtomObject(atom));

    FlatCoords move(stdLen / 2, 0);
    atomStart->coords -= move;
    atomEnd->coords += move;
}

LineObject::LineObject(std::shared_ptr<AtomObject>& start, const AtomObject& end, unsigned linesAmount)
{
    this->linesCnt = linesAmount;
    this->width = stdWidth;

    this->atomStart = start;
    this->atomEnd = std::shared_ptr<AtomObject>(new AtomObject(end));
}

LineObject::LineObject(std::shared_ptr<AtomObject>& start, std::shared_ptr<AtomObject>& end, unsigned linesAmount)
{
    this->linesCnt = linesAmount;
    this->width = stdWidth;

    this->atomStart = start;
    this->atomEnd = end;
}

LineObject::LineObject(const AtomObject& atom, const FlatCoords& vector, unsigned linesAmount)
{
    this->linesCnt = linesAmount;
    this->width = stdWidth;

    FlatCoords newPos = atom.coords + vector.createVector(this->stdLen);
    atomStart = std::shared_ptr<AtomObject>(new AtomObject(atom));
    atomEnd = std::shared_ptr<AtomObject>(new AtomObject(newPos, atom.name));
}

LineObject::LineObject(const LineObject& given)
{
    this->linesCnt = given.linesCnt;
    this->width = given.width;

    this->atomStart = given.atomStart;
    this->atomEnd = given.atomEnd;
}

LineObject& LineObject::operator=(const LineObject &given)
{
    this->linesCnt = given.linesCnt;
    this->width = given.width;

    this->atomStart = given.atomStart;
    this->atomEnd = given.atomEnd;
    return *this;
}

void LineObject::accept(BaseVisitor &visitor)
{
    visitor.visitLine(*this);
}

ObjPtr LineObject::clone() const
{
    return ObjPtr(new LineObject(*this));
}

float LineObject::getStdLen()
{
    return LineObject::stdLen;
}
