#ifndef DRAWING_H
#define DRAWING_H

#include <QGraphicsScene>
#include <QLineEdit>

#include "Core/spaceCoords.h"
#include "model/inc/atom.h"
#include "model/inc/connection.h"
#include "model/inc/sphere.h"
#include "model/inc/camera.h"
#include "Meta/settings.h"

struct drawing
{
    QGraphicsScene *scene;
    QLineEdit *label;
};

void clear_scene(drawing& params);
void draw_scene(const AtomArr& atoms, const ConnectionArr& connect, const camera_struct& camera,\
                drawing& params, const sphere_struct& global, sphere_struct& temp, fill_t type);

#endif // DRAWING_H
