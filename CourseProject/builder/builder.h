#ifndef BUILDER_H
#define BUILDER_H

#include <memory>
#include <vector>
#include "Core/flatCoords.h"

class AtomObject;
class LineObject;
class CompositObject;
struct Atom;

class BaseBuilder
{
public:
    BaseBuilder() = default;
    virtual bool joinElements(const CompositObject& composit);
    virtual bool splitParts();
    virtual bool separateAlgorithm() = 0;
    virtual bool placeModel() = 0;

protected:
    std::vector<Atom> atoms;
    std::vector<std::vector<int>> connections;
    std::vector<std::vector<int>> parts;

private:
    std::vector<FlatCoords> uniqueCoords;
    std::vector<int> visitNode(int i);
    bool selectUniqueAtoms(std::vector<AtomObject> atomVect);
    bool selectConnections(std::vector<LineObject> atomVect);
};

#endif // BUILDER_H
