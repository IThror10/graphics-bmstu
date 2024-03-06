#ifndef DIRECTOR_H
#define DIRECTOR_H

#include <memory>
class CompositObject;
class BaseBuilder;

class Director
{
public:
    Director(std::shared_ptr<BaseBuilder> builder);
    virtual bool build(const CompositObject &composit);

protected:
    std::shared_ptr<BaseBuilder> builder;
};

#endif // DIRECTOR_H
