#ifndef SPRINGBUILDER_H
#define SPRINGBUILDER_H

#include "builder/builder.h"
#include "model/instruction/model_data.h"

class SpringBuilder: public BaseBuilder
{
public:
    SpringBuilder();
    virtual bool separateAlgorithm() override;
    virtual bool placeModel() override;
    model_data createModel();
    void delete_model();

private:
    model_data model;
};

#endif // SPRINGBUILDER_H
