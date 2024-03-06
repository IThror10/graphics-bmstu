#ifndef MODEL_DATA_H
#define MODEL_DATA_H

#include <vector>
#include "model/inc/atom.h"

struct model_data
{
    int amount;
    Atom *atoms;
    int **connections;
};

#endif // MODEL_DATA_H
