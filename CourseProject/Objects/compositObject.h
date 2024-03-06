#ifndef COMPOSITOBJECT_H
#define COMPOSITOBJECT_H

#include "Objects/baseObject.h"

class CompositObject: public BaseObject
{
public:
    CompositObject() = default;
    CompositObject(const CompositObject& given);
    CompositObject& operator=(const CompositObject&);

    virtual bool isComposit() override;
    virtual bool add(ObjPtr) override;
    virtual bool remove(ObjIter) override;
    virtual bool reset() override;

    virtual void accept(BaseVisitor&) override;
    virtual ObjPtr clone() const override;

    std::vector<LineObject> getLines() const;
    std::vector<AtomObject> getAtoms() const;

    ObjIter begin();
    ObjIter end();
    CObjIter cbegin() const;
    CObjIter cend() const;
    virtual int size() override;

    static ObjPtr createPolygon(unsigned angles, std::shared_ptr<AtomObject> atom, std::shared_ptr<LineObject> line = nullptr);

private:
    std::vector<ObjPtr> data;
};
#endif // COMPOSITOBJECT_H
