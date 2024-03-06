#ifndef ATOM_H
#define ATOM_H

#include "Core/spaceCoords.h"
#include "Core/node_list.h"
#include "model/inc/status.h"
#include <QColor>

struct Atom
{
    QColor color;
    float radius;
    SpaceCoords center;
    node_t list;
};

struct AtomArr
{
    int amount;
    Atom *data;
};

AtomArr init_AtomArr();
AtomArr create_AtomArr(status& result, int size);
AtomArr create_AtomArr(status& result, int size, const Atom *arr);
void free_AtomArr(AtomArr& arr);

void rotate_Atom(Atom& atom);
void rotate_AtomArr(AtomArr& arr);
void move_Atom(Atom& atom);
void move_AtomArr(AtomArr &arr);
SpaceCoords find_center(AtomArr &arr);

#endif // ATOM_H
