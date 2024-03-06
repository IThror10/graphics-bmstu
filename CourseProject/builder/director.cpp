#include "builder/director.h"
#include "Objects/compositObject.h"
#include "builder/builder.h"

Director::Director(std::shared_ptr<BaseBuilder> _builder)
{
    this->builder = _builder;
}

bool Director::build(const CompositObject &composit)
{
    bool success = builder != nullptr;
    if (success)
        success = builder->joinElements(composit);
    if (success)
        success = builder->splitParts();
    if (success)
        success = builder->separateAlgorithm();
    if (success)
        success = builder->placeModel();
    return success;
}
